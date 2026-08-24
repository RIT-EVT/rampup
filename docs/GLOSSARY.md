# Glossary

A running reference of terms you'll hit while working through rampup and your 
time with EVT. Terms are grouped by theme and roughly ordered the
way you'll meet them, from Phase 1 through Phase 4.

If you read a term here and it still doesn't make sense, or find a term that isn't included here, 
that's a great question for a senior firmware member, and tell them to send it to the firmware lead 
so it can be added here before the next group of people try to do rampup.

## Embedded Systems Basics

### Microcontroller

Also called a uC. A tiny computer on a board that runs your code and
controls hardware. It usually has a CPU, memory, and [GPIO](#gpio) pins,
all on a single chip.

### Peripheral

An extra device connected to (or built into) a microcontroller that lets it
interact with the outside world: collecting data, displaying information,
storing data, or communicating with other systems (a temperature sensor, a
screen, a [UART](#uart) port, etc.).

### Integrated Circuit

Commonly shortened to IC, or just called a chip. An electrical circuit
built to do one specific job (sense temperature, convert a signal, drive a
motor, amplify a signal, etc.), manufactured as a single small package
instead of being wired together out of individual parts. The TMP117 (Phase 2) 
is an IC whose job is sensing temperature; the MAX22530 (Phase 3) is an
IC whose job is converting an analog voltage into a digital value.

### GPIO

Short for General Purpose Input/Output. Pins on the microcontroller that
you can program to read signals (input) or control devices (output).

### Driver

Software that lets your microcontroller talk to a specific piece of
hardware (a sensor, display, or motor controller) without you having to
spell out every low-level step each time. A driver exposes high level
commands like `readTemp()` and internally does whatever
[protocol](#communication-protocol)-specific work is needed to make that
happen. Writing drivers for the TMP117 and MAX22530 is the core of Phases 2
and 3.

### Flashing

The process of writing your compiled program onto a microcontroller's
memory so it actually runs there.

### .bin file

Short for binary file. The actual [compiled](#compiler) output you flash
onto a board: raw machine code and nothing else, no symbol names or debug
info attached. This is the file `docs/GETTING_STARTED.md` has you drag
onto a Nucleo or select in STM32CubeProgrammer.

### OpenOCD

OCD stands for On-Chip Debugging. OpenOCD is an open-source OCD tool that 
connects to a board over SWD/JTAG (through the [ST-Link](#st-link)) and lets
you debug your code while it's actually running on the microcontroller: 
pause execution, walk through the program line by line, and inspect variable values in real time. 
Its extremely helpful when trying to debug a problem in your code.

## Working with Data

### Bit

The smallest piece of data; either `0` or `1`.

### Byte

Eight [bits](#bit). A byte can represent 256 different values (`0` to `255`
[unsigned](#unsigned-vs-signed), or `-128` to `127` [signed](#unsigned-vs-signed)).

### Unsigned vs Signed

*Unsigned* means the data can only be positive (`0` to *x*). *Signed* means
it can be negative or positive (`-y` to `y - 1`, where `y = x / 2`), since
one [bit](#bit) is used to represent the sign instead of the value itself.

### MSB

Short for Most Significant Bit. In any binary number, this is the
[bit](#bit) with the highest value (the one farthest to the left). It
contributes the most to the number's value, the same way the leftmost
digit does in a decimal number (in 523, that's the `5`).

### LSB

Short for Least Significant Bit. The [bit](#bit) with the least value (the
one farthest to the right), contributing the least to the number's value,
the same way the rightmost digit does in a decimal number (in 523, that's
the `3`).

## Communication Fundamentals

### Bus

A set of wires that lets different parts of a system communicate, shared by
more than two devices (as opposed to a simple point-to-point wire between
just two). The CAN bus is what lets every board on the bike talk over one
shared set of wires.

### Serial Communication

Data is sent one [bit](#bit) at a time, over a single wire (or pair of
wires). [UART](#uart), [I2C](#i2c), and [SPI](#spi) are all serial.

### Parallel Communication

Many bits of data are sent at the same time, each over its own wire.

### Half-Duplex

Communication where data can flow in both directions, but only one
direction at a time, like a walkie-talkie. [I2C](#i2c)'s data line (SDA) is
shared this way between master and slave.

### Full-Duplex

Communication where data can flow in both directions at the same time,
like a phone call, because each direction gets its own dedicated wire.
[UART](#uart) (separate TX/RX lines) and [SPI](#spi) (separate MOSI/MISO
lines) are both full-duplex.

### Baud Rate

The speed of data transmission, usually measured in bits per second (bps),
for [serial communication](#serial-communication) like [UART](#uart).
Rampup's UART phase uses 9600 baud.

### Communication Protocol

A set of rules two devices agree on ahead of time so they can reliably
exchange data: things like who talks first, how fast, and how bits are
grouped into meaningful values.

### Master / Slave

A communication model where the master decides when communication happens
and who it talks to. Slave devices wait and respond only when the master
addresses them. [I2C](#i2c) and [SPI](#spi) both use this model.

### Polling

Repeatedly checking a value in a loop to see if it's changed (e.g. "is
there new UART data yet?"), instead of waiting to be notified by an
[interrupt](#interrupt). Simple to write, but wastes CPU time re-checking
things that haven't changed, and can miss brief changes if you're not
checking often enough.

### Interrupt

A signal that pauses whatever the microcontroller is currently doing so it
can immediately run a special function in response to an event (a pin
changing state, incoming data, a timer elapsing). Lets code react to
something without having to constantly [poll](#polling) for it in a loop.

### Clock / Oscillator

A *clock* is a signal that switches between high and low at a steady,
repeating rate, used to keep operations in a digital circuit synchronized.
An *oscillator* is the physical hardware component that generates that
signal.

### Analog vs Digital

An *analog* signal is continuous, it can take any value in a range (like
the voltage out of a sensor). A *digital* signal is discrete, it only takes
specific values, most commonly just two (`1`/`0`, "high"/"low"). An ADC
(see Phase 3) converts an analog signal into a digital one your
microcontroller can work with.

### PWM

Short for Pulse Width Modulation. A digital signal rapidly switched on and
off, where the fraction of time it's "on" (the duty cycle) sets its average
value. Used to fake an analog output (control brightness, speed, etc.)
using only a [GPIO](#gpio) pin.

## Protocols You'll Use in Rampup

### UART

*Phase 1*

Short for Universal Asynchronous Receiver/Transmitter. A simple,
asynchronous [serial](#serial-communication)
[protocol](#communication-protocol) with no shared clock signal; both sides
just have to agree on the [baud rate](#baud-rate) ahead of time. Used
mainly for laptop-to-board debugging output.

### I2C

*Phase 2*

Short for Inter-Integrated Circuit, read "eye-two-cee" or "eye-squared-cee."
A two-wire, synchronous, [master/slave](#master-slave)
[serial](#serial-communication) protocol: one wire for data (SDA) and one
for a shared clock (SCL), which tells the devices when to read the value from the data line. 
Multiple slave devices can share the same two wires, each addressed individually. 
Used in rampup to read the TMP117 temperature sensor.

### SPI

*Phase 3*

Short for Serial Peripheral Interface, read "spy." A faster, synchronous,
[master/slave](#master-slave) [serial](#serial-communication) protocol
using separate data lines for each direction (MOSI/MISO), a shared clock
(SCK), and a dedicated chip-select (CS) line per slave device. Used in
rampup to talk to the MAX22530 ADC.

### CAN

*Phase 4*

Short for Controller Area Network. A serial bus, originally built for cars,
where every device on the bus sees every message and decides for itself
whether to care about it (unlike [I2C](#i2c)/[SPI](#spi), there's no single
fixed master). It's the shared bus EVT's boards use to talk to each other
on a bike.

### CANopen

*Phase 4*

A standard built on top of raw [CAN](#can) that defines a common way to
organize and exchange data between nodes, so every board and every
debugging tool can read messages the same way, instead of every board
making up its own format. [`docs/CANOPEN_GUIDE.md`](CANOPEN_GUIDE.md) walks 
through it in depth. The core vocabulary is below.

#### Object Dictionary

A table of a node's variables, each addressed by a 16-bit *index* and 8-bit
*subindex* (e.g. index `0x1017`, subindex `0`).

#### SDO

Short for Service Data Object. A request/response exchange: something asks
"what's the value at index X?" and the node answers. Reliable, but has
overhead per value, so it's better suited to configuration than to
streaming sensor data.

#### PDO

Short for Process Data Object. A lightweight broadcast of one or more
values, sent out on a trigger (like a timer) with no request needed.

#### TPDO

Short for Transmit [PDO](#pdo). A PDO that a node *sends out*. RampupBoard
only sends, so this is the one you'll use in Phase 4.

#### RPDO

Short for Receive [PDO](#pdo). A PDO that a node *listens for* from another
node. HUDL uses RPDOs to receive RampupBoard's [TPDOs](#tpdo).

#### COB-ID

The CAN message ID used for a particular purpose (an [SDO](#sdo) request, a
specific [TPDO](#tpdo), etc.), derived from a node's [Node ID](#node-id)
plus a fixed offset defined by the CANopen standard.

#### Node ID

A unique number identifying a device on the CANopen network, used to derive
its [COB-IDs](#cob-id).

## Electrical & PCB Terms

### PCB

Short for Printed Circuit Board. The physical board that holds and
electrically connects a circuit's components, via layers of copper traces
instead of loose wires.

### Pull-up / Pull-down Resistor

A resistor connected to hold a signal at a known default voltage (high for
pull-up, low for pull-down) when nothing else is actively driving it, so
the line doesn't float at an undefined value. Very common on [I2C](#i2c)
bus lines.

### GND

Also called Ground. The circuit's shared 0V reference point that every
voltage measurement is made relative to.

### VCC

The positive power supply pin/wire on a chip or board (commonly 3.3V or 5V
on our boards). Pairs with [GND](#gnd): current flows in from VCC and back
out through GND.

### Bring-up

The process of testing a newly manufactured/assembled [PCB](#pcb) for the
first time, to confirm it powers on and behaves as designed before more
complex firmware runs on it.

## Team Tools & Hardware

You'll encounter this hardware throughout rampup; see each phase's
"Suggestions" section in the [README](../README.md) for links to the full
documentation on each.

### Nucleo

An off-the-shelf STMicroelectronics development board built around one of
the microcontrollers we use. Exposes [GPIO](#gpio) and built-in peripherals
for quick testing and debugging without spending time to design a custom
[PCB](#pcb) or build it on a breadboard.

### FTB

Short for Firmware Test Board. An EVT-built board for connecting
standardized "[click board](#click-board)" ICs to a [Nucleo](#nucleo),
letting you prototype and test driver code without needing a full custom
EVT board.

### Click Board

A small standardized board carrying a single [IC](#integrated-circuit)
(like the TMP117 or MAX22530), designed to plug into sockets like the
[FTB](#ftb)'s for easy swapping during development.

### Saleae Logic Analyzer

A tool that records digital signals on a set of wires and decodes them into
the protocol traffic they represent ([I2C](#i2c), [SPI](#spi), [CAN](#can),
etc.), so you can visually confirm what's actually being sent on the wire.

### Oscilloscope

A tool that displays how a voltage changes over time on one or more
channels. Used in Phase 4 to view the raw CAN High/Low waveform, and
generally useful for looking at analog signal quality that a logic
analyzer's digital view wouldn't show.

### PEAK CAN Dongle

A USB adapter and accompanying software used to view and decode raw
[CAN](#can) bus traffic (including CANopen messages) directly on a
computer.

### ST-Link

STMicroelectronics' programmer/debugger hardware, used to
[flash](#flashing) and debug EVT's custom boards, which don't have the
[Nucleo](#nucleo)'s built-in USB drag-and-drop [bootloader](#bootloader).

### HUDL

The [CAN](#can) node used in Phase 4 to display the data your
`RampupBoard` sends: a small screen driven by its own [CANopen](#canopen)
node that receives your [TPDOs](#tpdo) as [RPDOs](#rpdo). A senior member
will [flash](#flashing) it for you.

### FUN-E SNAIL

The board rampup uses to combine and route [CAN](#can) harnesses between
devices (the [FTB](#ftb) and [HUDL](#hudl), in Phase 4). It's basically a
hub for the CAN bus during testing.
