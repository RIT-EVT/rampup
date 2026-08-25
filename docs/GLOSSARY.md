# Glossary

A running reference of terms you'll hit while working through rampup and your 
time with EVT. Terms are grouped by theme and roughly ordered the
way you'll meet them, from Phase 1 through Phase 4.

If you read a term here and it still doesn't make sense, or find a term that isn't included here, 
that's a great question for a senior firmware member, and tell them to send it to the firmware lead 
so it can be added here before the next group of people try to do rampup.

## Acronym Quick Reference

A place to lookup the acronyms you'll run into, both in rampup and
around EVT more broadly. Acronyms with a full write-up elsewhere in this
doc link to it; short signal/pin names that don't need their own section
just get a one-line note here.

| Acronym | Meaning                                                                                                                                                                               |
| --- |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ACK | Acknowledge: a response signal confirming data was received correctly, opposite of NACK. Basically a "yep, got it."                                                                   |
| ADC | Analog-to-Digital Converter: turns a real-world, wobbly voltage into a number your code can use. The MAX22530 you use in Phase 3 is one; see [Analog vs Digital](#analog-vs-digital). |
| [CAN](#can) | Controller Area Network                                                                                                                                                               |
| CLK | Clock, a generic name for a clock signal line. See [Clock / Oscillator](#clock--oscillator).                                                                                          |
| [COB-ID](#cob-id) | CAN message ID used for a specific purpose                                                                                                                                            |
| CPHA | Clock Phase, part of an SPI device's mode setting (paired with CPOL). A fiddly timing detail you'll rarely have to figure out yourself, the datasheet will tell you the right value.  |
| CPOL | Clock Polarity, part of an SPI device's mode setting (paired with CPHA). Same idea as CPHA, another timing detail the datasheet spells out for you.                                   |
| CRC | Cyclic Redundancy Check: error-checking bits included at the end of a CAN frame, like a checksum that catches data that got corrupted along the way.                                  |
| CS | Chip Select: the SPI line that tells one follower device it's being addressed, like tapping one specific person on the shoulder before talking to them.                               |
| DBC | Database CAN: a file format for documenting what a CAN message's bytes mean.                                                                                                          |
| [FTB](#ftb) | Firmware Test Board                                                                                                                                                                   |
| [GND](#gnd) | Ground                                                                                                                                                                                |
| [GPIO](#gpio) | General Purpose Input/Output                                                                                                                                                          |
| HAL | Hardware Abstraction Layer: ST's own driver layer that EVT-core is built on top of, so you get to call simple functions instead of poking at raw hardware registers yourself.         |
| [HUDL](#hudl) | Phase 4's display node                                                                                                                                                                |
| [I2C](#i2c) | Inter-Integrated Circuit                                                                                                                                                              |
| IC | Integrated Circuit; see the [full entry](#integrated-circuit)                                                                                                                         |
| IDE | Integrated Development Environment: the actual application you write, build, and debug your code in, e.g. CLion or VS Code.                                                           |
| IWDG | Independent Watchdog: a hardware timer that resets the microcontroller if your code hangs, so a bug can't leave the board stuck forever.                                              |
| JTAG | Joint Test Action Group: a standard multi-pin hardware debugging interface. EVT mainly uses the simpler two-wire SWD instead.                                                         |
| LED | Light-Emitting Diode. Basically a tiny light bulb that you can switch on/off (or dim) from a GPIO pin.                                                                                |
| [LSB](#lsb) | Least Significant Bit                                                                                                                                                                 |
| MISO | Master-In Slave-Out: the SPI line carrying data from follower to leader                                                                                                               |
| MOSI | Master-Out Slave-In: the SPI line carrying data from leader to follower                                                                                                               |
| [MSB](#msb) | Most Significant Bit                                                                                                                                                                  |
| NACK | Not Acknowledge, the opposite of ACK. Basically a "nope, that didn't come through."                                                                                                   |
| NVM | Non-Volatile Memory: storage that keeps its contents without power, like a USB drive, unlike RAM which forgets everything the moment power is cut.                                    |
| [PCB](#pcb) | Printed Circuit Board                                                                                                                                                                 |
| [PDO](#pdo) | Process Data Object                                                                                                                                                                   |
| [PWM](#pwm) | Pulse Width Modulation                                                                                                                                                                |
| [RPDO](#rpdo) | Receive [PDO](#pdo)                                                                                                                                                                   |
| RTC | Real-Time Clock: a peripheral that keeps track of the actual date and time, independent of your main program.                                                                         |
| SCK | Serial Clock: SPI's shared clock line                                                                                                                                                 |
| SCL | Serial Clock: I2C's shared clock line (same name as SCK, different bus)                                                                                                               |
| SDA | Serial Data: I2C's shared data line                                                                                                                                                   |
| [SDO](#sdo) | Service Data Object                                                                                                                                                                   |
| [SPI](#spi) | Serial Peripheral Interface                                                                                                                                                           |
| SWD | Serial Wire Debug: the two-wire debugging interface used through an ST-Link. Lets you pause your code mid-run and look around while it's actually executing on the board.             |
| [TPDO](#tpdo) | Transmit [PDO](#pdo)                                                                                                                                                                  |
| TX / RX | Transmit / Receive: sending data out and receiving data in, respectively.                                                                                                             |
| [UART](#uart) | Universal Asynchronous Receiver/Transmitter                                                                                                                                           |
| USART | Universal Synchronous/Asynchronous Receiver/Transmitter: UART's synchronous-capable sibling. EVT boards mostly just use it in plain UART (asynchronous) mode.                         |
| USB | Universal Serial Bus. The same kind of cable and port you already use to charge your phone or plug in a mouse.                                                                        |
| [VCC](#vcc) | Positive power supply line                                                                                                                                                            |

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

Short for binary file. The actual compiled output you flash
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

*Unsigned* means the data can only be positive, whereas *signed* means
it can be negative or positive (i.e. in 4 bits, while signed you can do `[-8, 7]`, when unsigned, you can do `[0, 15]`), since
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
shared this way between leader and follower.

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

### Leader (Master) / Follower (Slave)

A communication model where the leader decides when communication happens
and who it talks to. Follower devices wait and respond only when the leader
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
A two-wire, synchronous, [leader/follower](#leader-master--follower-slave)
[serial](#serial-communication) protocol: one wire for data (SDA) and one
for a shared clock (SCL), which tells the devices when to read the value from the data line. 
Multiple follower devices can share the same two wires, each addressed individually. 
Used in rampup to read the TMP117 temperature sensor.

### SPI

*Phase 3*

Short for Serial Peripheral Interface, read "spy." A faster, synchronous,
[leader/follower](#leader-master--follower-slave) [serial](#serial-communication) protocol
using separate data lines for each direction (MOSI/MISO), a shared clock
(SCK), and a dedicated chip-select (CS) line per follower device. Used in
rampup to talk to the MAX22530 ADC.

### CAN

*Phase 4*

Short for Controller Area Network. A serial bus, originally built for cars,
where every device on the bus sees every message and decides for itself
whether to care about it (unlike [I2C](#i2c)/[SPI](#spi), there's no single
fixed leader). It's the shared bus EVT's boards use to talk to each other
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
[Nucleo](#nucleo)'s built-in USB drag-and-drop bootloader.

### HUDL

The [CAN](#can) node used in Phase 4 to display the data your
`RampupBoard` sends: a small screen driven by its own [CANopen](#canopen)
node that receives your [TPDOs](#tpdo) as [RPDOs](#rpdo). A senior member
will [flash](#flashing) it for you.

### FUN-E SNAIL

The board rampup uses to combine and route [CAN](#can) harnesses between
devices (the [FTB](#ftb) and [HUDL](#hudl), in Phase 4). It's basically a
hub for the CAN bus during testing.
