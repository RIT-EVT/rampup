# Rampup Project

## Overview

Hello and welcome to EVT! This project is designed to give you a look into what
it is like to develop on the firmware team. The goal is for you to get exposure
to the full life cycle of development for EVT, from prototyping with a breakout
board to communicating information between boards. This process is broken down
into four phases, each introducing a communication protocol that the team
commonly uses. Throughout the process, you'll learn everything you need to be a
firmware engineer, from C++ fundamentals to class-level software design to
hardware debugging.

If this is your first time doing embedded development, it will take some time
to get used to all the new concepts and the quirks of working with hardware.
Through this process, be sure to use all the resources at your disposal.
Google is great for general C++ questions, and the firmware docs are useful for
background on the tools we use for development, but when you're stuck, your
best resource is going to be other firmware members, new and old. Collaboration
is critical to our team's success, and it's often a lot more fun than
grinding out code on your own!


## Phase 1: UART

### Learning Objectives
- C++ syntax
- EVT-core basics
- Making a UART interface
- Working with a nucleo

### Summary
The first communication protocol you should be aware of is UART, which we
commonly use to communicate between a laptop and a board, mostly for debugging.
To use this protocol, you'll only need a Nucleo and your laptop. Your goal will
be to simply take two numbers from the user, add them, and print the result.
Obviously, the actual work being done isn't very complex, but this first step
will help you understand how to work in C++ and with EVT-core, our custom
library. The only file you'll need to modify is `targets/phase1/main.cpp`.

### Task Breakdown
1. Over UART, read two numbers input by the user, up to 10 digits each.
2. Print the sum of the two numbers over UART.

### Suggestions
- Be sure you know how to open a serial console.
    - PuTTY for Windows users
    - `screen` for MacOS/Linux
- Read over the UART documentation.
- Copy code from the echo sample for a starting point.
- Look up standard C++ functions for converting from character array to
  integer.

### Completion
Once you've gotten it working, play around with it for a bit to see if you can
break it. What happens when you put in something that isn't a number? What
happens when you put in a really long input? Once you're happy with what you
have, show your code to a designated senior firmware member. Once they say it
looks good, you can move on to the next phase.


## Phase 2: I2C

### Learning Objectives
- I2C communication
- Object-oriented programming in C++
- Basic driver development
- Fixed point data formatting
- Waveform analysis with a logic analyzer

### Summary
Now that you can communicate between the microcontroller (uC) and your 
computer, you can start playing with other communication protocols and report
the results back over UART. The first one we'll cover is Inter-Integrated
Circuit, abbreviated I2C, which is read as "eye-two-cee" or "eye-squared-cee".
You'll use this protocol to communicate between the uC and an integrated
circuit (IC) used for temperature sensing. For this phase, you'll need a little
more hardware. Specifically, you'll need a Firmware Test Board (FTB) and a click
board with the TMP117 chip on it. At the end, you'll also need a Saleae Logic
Analyzer to see the I2C waveforms. To get this working, you need to modify
`targets/phase2/main.cpp` and `src/dev/TMP117.cpp`. The header file
`include/dev/TMP117.hpp` has been provided for you.

### Task Breakdown
1. Write the constructor and implementation for `readTemp()` in `TMP117.hpp`.
2. Write the target code to call these functions and print temperatures over 
UART.
3. Use the Saleae to decode the waveforms on SDA and SCL and confirm the data 
matches what is output over UART.

### Suggestions
- Read the I2C documentation.
- Set up the UART code before finishing your TMP117 implementation, so you can
use the target to test.
- Look at the I2C sample in EVT-core for an example.
- Combine the two bytes you read into a single 16-bit integer
- Read the Saleae documentation.

### Completion
When believe you've gotten everything working, try holding your thumb against
the TMP chip to heat it up. Then, blow on it to cool it down. Does the reported
value update appropriately? Once you're satisfied with your code's performance,
call over a senior member and show them your work. Also be sure to show them the
waveform recorded by the Saleae. Once they say it looks good, you can move on to
the next phase.


## Phase 3: SPI

### Learning Objectives
- SPI communication
- Advanced driver development
- Analog-to-Digital Converter (ADC) use
- Reading datasheets
- Running code on EVT hardware

### Summary
The next communication protocol to cover is Serial Peripheral Interface,
abbreviated SPI, which is read like "spy." You'll use this protocol to
communicate between the uC and an Analog-to-Digital Converter (ADC), which is an
IC that converts an analog signal (continuous) to a digital signal (discrete).
For our purposes, we're just going to be using it to read the voltage on each of
the input channels. You'll still need the Saleae and FTB, but you'll need to 
switch out the TMP117 board for the MAX22530 board. To test the board, you'll 
also need to get a power supply connected to the input of the ADC to test it.
For this phase, the header file hasn't been provided for you, so you'll have to
write that yourself. The files you need to edit are `include/dev/MAX22530.hpp`,
`src/dev/MAX22530.cpp`, and `targets/phase3/main.cpp`. Once the code is working,
you'll also get to run it on a DEV1 Powertrain Voltage Controller (PVC).


### Task Breakdown
1. Write the header file for `MAX22530`, so that it can be used to read voltages
from each channel.
2. Implement the functions defined in the header file.
3. Write the target code to call the functions and print all voltages over UART.
4. Use the Saleae to decode the waveforms on CS, SCL, MOSI, and MISO and confirm
the data matches what is output over UART.

### Suggestions
- Read the SPI documentation.
- Fully plan out the MAX22530 class in the header file before starting on the 
implementation.
- Look at the SPI sample in EVT-core for an example.
- Read the ST-Link documentation to see how to use it.
- Read the running code documentation to see how to flash the PVC.

### Completion
Once you think it's working, get a variable power supply and apply different
voltages to the input channels. If you're not familiar with power supplies, have
a senior member help you set it up. Be sure to limit the current to only a few 
milliamps to make sure it's safe. Does the voltage on the power supply match the
UART output? When you're happy with its performance, have a senior member look
at your Saleae output and your code. If it looks good, have them get you a DEV1
PVC to test the code on. With their help, use the power supply to test the ADC
on the PVC. If it works, you can start on the last phase.


## Phase 4: CAN

### Learning Objectives
- CAN communication
- CANopen standard
- Main target development
- Memory addressing in C++
- Waveform analysis with an oscilloscope

### Summary
This last phase explores a new communication protocol, Controller Area Network,
abbreviated CAN. It also serves as a culmination of all the phases leading up to
this one. For this phase, you'll be using both the drivers you just wrote in a
single "RampupBoard" class. This class is supposed to represent a board that the
team would make that reports temperature and voltage data over CAN. We haven't
made a PCB that does that, but you can prototype one using the FTB. For this
phase, you'll need a click board for the TMP117 or the MAX22530 and an
evaluation module for whichever IC isn't on your click. You'll also need a FUN-E
SNAIL and HUDL, as well as harnesses to connect the FTB and HUDL to the FUN-E 
SNAIL. Lastly, you'll need the oscilloscope and the PEAK CAN dongle to see the 
messages being sent. At this point, you'll have a fair amount of hardware, so be
sure to ask a senior member for help getting this set up. You'll also need to 
ask them to flash the HUDL with the necessary display code.

For this phase, the end goal is going to be collecting data from the two ICs and
reporting it over CAN, so that it can be displayed on the HUDL. To accomplish
this, you'll make calls to the drivers you wrote and work with the CANopen stack
to have it output over CAN following the CANopen standard. To start, you'll
still be using UART for debugging, but once the data is being reported properly,
you can test the ICs the same ways you did in earlier phases, but now you can 
just look at the data as it appears on the HUDL to confirm it's working. You'll 
also learn how to use the oscilloscope and the PEAK CAN dongle to debug. For 
this phase, the files you need to edit are `include/RampupBoard.hpp`, 
`src/RampupBoard.cpp`, and `targets/phase4/main.cpp`.

### Task Breakdown
1. Modify the RampupBoard header file to link the data to the CANopen 
dictionary. Search through the dictionary to find all the "replace" comments.
2. Write the constructor and `process()` methods for RampupBoard in the header
and implementation files.
3. Write the main target to initialize everything. Then run `process()` and the 
necessary functions to get CANopen working.
4. Plug the FTB and HUDL into the FUN-E SNAIL to confirm the data displays on
the HUDL.
5. Use the PEAK CAN dongle to decode the CAN messages and confirm the data 
matches what is being sent.
6. Use the Saleae to decode the waveforms on CAN TX and RX to confirm that it
matches the data that should be sent.
7. Use the Oscilloscope to see the CAN messages on CAN high and low.

### Suggestions
- Read the CAN documentation.
- Look at the canopen_sample in EVT-core for an example.
- If the HUDL doesn't work right away, debug the output with the PEAK can dongle
and the Saleae.
- Read the FUN-E SNAIL documentation.
- Read the PEAK dongle documentation.
- Read the oscilloscope documentation.

### Completion
Once you have all the code written, you can start trying out all the testing
equipment we use as a team. When the code works, you should see all the data
being reported show up on the HUDL, but, especially in embedded systems, the 
code rarely works on the first try. The Saleae, PEAK dongle, and oscilloscope
will all be useful for finding different types of issues. While we've put a lot
of effort into the documentation for each of these tools, there is some
practical debugging knowledge that needs to be shown directly. You should start
by collecting as much information as you can about whatever problem you're
facing, but feel free to reach out to senior firmware members for any help in
setting up the hardware or debugging your software.

Once the HUDL is displaying the data properly, make sure you spend some time to
try out any debugging tools you haven't used yet. When you feel comfortable
enough with each of them, you can show your code to a senior firmware member for
a final check. When they approve it, you've officially completed the rampup
project.

## Next Steps
Congratulations on completing the rampup project! If you're new to firmware
development, starting something new like this can be very time-consuming and
difficult, but you met that challenge and overcame it. I hope you got a good 
idea of how the firmware team operates and the type of work we do as a team. 
Having completed the rampup project, you are now a fully-fledged member of our
team, so you can begin work on a project for one of our bikes. If there's 
anything else you want to learn about or don't understand, be sure to take some
time now to read over some documentation and play around with it now. Once you 
think you're ready, you can reach out to the firmware lead to get your first 
project.

Good luck!
