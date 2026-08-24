# Understanding CANopen (for Phase 4)

Phase 4 is the biggest jump in the rampup project. Phases 1–3 each introduce
one new protocol and one new chip, but Phase 4 asks you to use everything at
once *and* learn CANopen, which has more moving parts than UART, I2C, or SPI.
This page exists to break CANopen down before you dive into
[`include/RampupBoard.hpp`](../include/RampupBoard.hpp), which already
contains a partially filled-in CANopen object dictionary you'll be
editing.

Read the team's [CAN documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/controller-area-network-can) first if you haven't. Everything here assumes
you already understand how normal CAN works (broadcast messages, IDs, etc).
See [`docs/GLOSSARY.md`](GLOSSARY.md) for quick definitions of the terms
used below (object dictionary, SDO, PDO, COB-ID, etc.).

## Why CANopen on top of CAN?

Basic CAN only defines *how data get across the wire*, not how to read that data.
If every board on the bike invented its own message format, every other board
(and every debugging tool) would need custom code to understand it.

CANopen is a standard built on top of CAN that fixes this: it defines a
common way to organize a node's data (the **object dictionary**), a common
way to request/change that data (**SDO**), and a common lightweight way to
broadcast it on a schedule (**PDO**). Our CANopen stack (in
`libs/EVT-core/libs/canopen`) implements all the boilerplate for this. Your
job in Phase 4 is to describe *your* board's data using its conventions, not
to implement the protocol yourself.

## The object dictionary

Every CANopen node has an **object dictionary**: a table of variables, each
addressed by a 16-bit **index** and an 8-bit **subindex** (e.g. index
`0x1017`, subindex `0`). Some index ranges are reserved by the CANopen
standard for things every node has (device info, heartbeat settings, PDO
configuration); one range (`0x2000`–`0x5FFF`) is left open for
manufacturer-specific data. This is where your temperature and voltage
readings live.

Under the hood, each entry is one `CO_OBJ_T` struct with an index+subindex
key, a data type, and either a literal value or a pointer to the C++
variable holding the data. You *can* write these structs out by hand, but
`RampupBoard.hpp` and `HUDL.hpp` instead build their dictionaries out of
helper macros from
[`CANOpenMacros.hpp`](../libs/EVT-core/include/core/io/CANOpenMacros.hpp),
the same macros used on the team's real boards. Each macro expands into one
or more `CO_OBJ_T` entries, so you rarely need to think about the raw struct
at all. The ones you'll actually touch in Phase 4:

- `TRANSMIT_PDO_SETTINGS_OBJECT_18XX(tpdoNumber, triggerType, inhibitTime, interval)`
  - Configures a TPDO: how it's triggered and, for timer-triggered PDOs,
    how often (`interval`, in ms).
- `TRANSMIT_PDO_MAPPING_START_KEY_1AXX(tpdoNumber, numEntries)` /
  `TRANSMIT_PDO_MAPPING_ENTRY_1AXX(tpdoNumber, subIndex, dataSize)`
  - Declares which values get bundled into a TPDO's payload when it fires,
    in order.
- `DATA_LINK_START_KEY_21XX(pdoNumber, numEntries)` /
  `DATA_LINK_21XX(pdoNumber, subIndex, dataType, dataPointer)`
  - The actual wiring: points a mapped entry at the real address of a C++
    variable, so the stack reads live data instead of a stale copy.

There are RPDO equivalents too (`RECEIVE_PDO_SETTINGS_OBJECT_140X`,
`RECEIVE_PDO_MAPPING_START_KEY_16XX`/`_ENTRY_16XX`); you'll see those used
in `HUDL.hpp`, since the HUDL *receives* RampupBoard's data rather than
transmitting its own. `MANDATORY_IDENTIFICATION_ENTRIES_1000_1014`,
`HEARTBEAT_PRODUCER_1017(interval)`, `IDENTITY_OBJECT_1018`, and
`SDO_CONFIGURATION_1200` cover the standard boilerplate every node needs;
you won't need to touch those.

## Node identity: node ID and COB-IDs

`RampupBoard::NODE_ID` is `50`. Every CAN message this board sends or
receives has an ID (COB-ID) derived from that node ID plus a fixed offset
defined by the CANopen standard, e.g.:

| Purpose               | Formula            | With NODE_ID = 50 |
|------------------------|--------------------|--------------------|
| SDO request (in)       | `0x600 + NodeID`   | `0x632`            |
| SDO response (out)     | `0x580 + NodeID`   | `0x5B2`            |
| TPDO0 (out)             | `0x180 + NodeID`   | `0x1B2`            |
| TPDO1 (out)             | `0x280 + NodeID`   | `0x2B2`            |

The dictionary macros handle this math for you (RampupBoard's own COB-IDs
are computed at runtime from whatever `getNodeID()` returns; HUDL's RPDO
settings take the *other* node's ID as a parameter, since it needs to know
whose TPDOs to listen for). When you're debugging with the PEAK CAN dongle
in Phase 4, the IDs in the table above are what you should expect to see on
the bus. If you see nothing at `0x1B2`, your TPDO0 isn't firing.

## SDO vs. PDO: two ways to move data

- **SDO (Service Data Object)**
  - A request/response exchange: a leader asks "what's the value at index
    X?" and the node answers. Reliable, but has overhead for every single
    value. Good for configuration, not for streaming sensor data.
- **PDO (Process Data Object)**
  - A lightweight broadcast: no request needed, the node just sends the
    current value(s) on some trigger. This is what RampupBoard uses for
    its actual sensor data, because we want the HUDL to just receive
    updates, not have to constantly make requests for them.
  - A **TPDO** (Transmit PDO) is data *this* node sends; an **RPDO**
    (Receive PDO) is data it listens for from another node. RampupBoard
    only transmits, so you'll only see TPDOs.

## Walking through RampupBoard's dictionary

The dictionary in `RampupBoard.hpp` is organized in blocks, in this order:

1. **`MANDATORY_IDENTIFICATION_ENTRIES_1000_1014`, `HEARTBEAT_PRODUCER_1017(100)`,
   `IDENTITY_OBJECT_1018`, `SDO_CONFIGURATION_1200`**
   - Standard boilerplate every node needs (device info, a periodic "I'm
     alive" heartbeat message, identity numbers, SDO request/response
     COB-IDs). Not something you need to change for rampup.
2. **`TRANSMIT_PDO_SETTINGS_OBJECT_18XX(...)`**
   - One call per TPDO (TPDO0 for voltages, TPDO1 for temperature). Each
     configures that TPDO's trigger type (`TRANSMIT_PDO_TRIGGER_TIMER`
     means "send on a timer" rather than only in response to an external
     sync message) and, as the last argument, the timer interval in
     milliseconds. **This interval is one of the values you need to fill
     in.** Search for the `/*Replace with trigger time*/` comments.
3. **`TRANSMIT_PDO_MAPPING_START_KEY_1AXX` / `TRANSMIT_PDO_MAPPING_ENTRY_1AXX`**
   - These say *which* values get bundled into each TPDO's CAN payload, and
     in what order. TPDO0 maps four 16-bit entries (the four ADC voltages,
     fitting in one 8-byte CAN frame); TPDO1 maps one 16-bit entry (the
     temperature).
4. **`DATA_LINK_START_KEY_21XX` / `DATA_LINK_21XX`**
   - The actual data, in the manufacturer-specific `0x2100`/`0x2101` range.
     Each `DATA_LINK_21XX` call currently passes `nullptr` with a
     `/*Replace with address of ...*/` comment as its last argument. **This
     is the other thing you need to fill in.** Pass the real address of the
     corresponding variable (e.g. `&voltages[0]`) instead, so that when the
     stack builds the TPDO payload, it reads the live sensor value, not a
     stale copy.

## What you're actually implementing in Phase 4

Given the above, the task breakdown in the [README](../README.md#phase-4-can)
maps onto three concrete pieces of work:

1. **Wire up the dictionary** (`RampupBoard.hpp`)
   - Replace the `nullptr` arguments in the `DATA_LINK_21XX` calls with
     addresses of your `voltages[4]` and `temp` member variables, and pick
     a sensible event timer interval (the last argument to each
     `TRANSMIT_PDO_SETTINGS_OBJECT_18XX` call). How often should the board
     really report new data? (Compare to how often you read the sensors in
     Phases 2–3.) `RampupBoard` already implements the `CANDevice`
     interface (`getObjectDictionary()`, `getNumElements()`, `getNodeID()`
     are filled in for you in `RampupBoard.cpp`), so you don't need to
     touch those three methods yourself.
2. **`RampupBoard::process()`** (`RampupBoard.cpp`)
   - This should call into your Phase 2/3 drivers (`TMP117`, `MAX22530`) to
     refresh `temp` and `voltages`. The CANopen stack reads whatever is
     currently in those variables when a TPDO fires. It has no idea how to
     talk to the sensors itself, so if `process()` isn't called regularly,
     the board will keep broadcasting stale data.
3. **The main target** (`targets/phase4/main.cpp`)
   - Initialize everything (UART, I2C, SPI, the CAN driver), then set up
     the CANopen node with two calls: `io::initializeCANopenDriver(...)` to
     wire up the CAN/timer/NVM drivers, and
     `io::initializeCANopenNode(&canNode, &rampupBoard, &canStackDriver,
     sdoBuffer, appTmrMem)` to build the node from your `RampupBoard`
     instance (since it's a `CANDevice`, the stack pulls the object
     dictionary, element count, and node ID from it automatically). In the
     main loop, call `process()` alongside
     `io::processCANopenNode(&canNode)`, which handles the stack's own
     message and timer processing for you. See `targets/hudl/main.cpp` for
     a working example of this same pattern, since the HUDL target is
     already fully implemented.

## Debugging tips

- **Nothing shows up on the HUDL**
  - Confirm with the PEAK CAN dongle that your TPDOs are actually being
    sent at all, at the COB-IDs from the table above, before assuming the
    HUDL side is broken.
- **Data appears but looks wrong**
  - Check byte order and scaling. Remember the raw values you're sending
    are the same 16-bit integers from Phases 2–3, not pre-converted to any
    particular unit.
- **Nothing happens on the bus at all**
  - Double-check `process()` and the CANopen stack's processing functions
    are actually being called in the main loop, and that the node reached
    `CO_OPERATIONAL` mode (see how `targets/hudl/main.cpp` calls
    `CONmtSetMode`).
- As always, the Saleae and oscilloscope can confirm signals are present on
  CAN TX/RX and CAN H/L even before you trust the higher-level CANopen
  interpretation.

Once your board's data is showing up correctly on the HUDL, head back to the
["Completion" section under Phase 4 in the README](../README.md#phase-4-can)
for the final steps to wrap up rampup.
