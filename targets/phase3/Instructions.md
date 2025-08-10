# Phase 3: I2C

## Learning Objectives
- I2C communication
- Object-oriented programming in C++
- Basic driver development
- Fixed point data formatting
- Waveform analysis with a logic analyzer

## Summary
Now that you can communicate between the microcontroller (uC) and your 
computer, you can start playing with other communication protocols and report
the results back over UART. The first one we'll cover is Inter-Integrated
Circuit, abbreviated I2C, which is read as "eye-two-cee" or "eye-squared-cee".
You'll use this protocol to communicate between the uC and an integrated
circuit (IC) used for temperature sensing. 

For this phase, you'll need a little more hardware. Specifically, you'll need a 
Firmware Test Board (FTB) and a click board with the TMP117 chip on it. 
A click board is a small board with an IC meant to 'click' into the spot on the 
FTB for easy testing. 

To get this phase working, you will need to modify `targets/phase3/main.cpp` and 
`src/dev/TMP117.cpp`. The header file `include/dev/TMP117.hpp` has been 
provided for you.

At the end, you'll also need a Saleae Logic Analyzer to see the I2C waveforms. For 
more information on the Saleae Logic Analyzer, visit [our webpage](
https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/saleae-logic-analyzer),
or ask a senior member to explain.

## Task Breakdown
1. Read the [FTB documentation](
   https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/firmware-test-board-ftb).
2. Learn about I2C through a [short video](https://www.youtube.com/watch?v=CAvawEcxoPU) (10 min) or if you have a poor attention span, a [really short video](https://www.youtube.com/shorts/8R13KHx4dTQ) (1 min).
3. Read the [I2C documentation](
   https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/inter-integrated-circuit-i2c?authuser=0).
4. Read the `datasheets/datasheets.md` section about the TMP117 datasheet.
5. Write the constructor and implementation for `readTemp()` in `TMP117.cpp`.
6. Write the target code to call these functions and print temperatures over
   UART.
7. Read the [Saleae documentation](
   https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/saleae-logic-analyzer?authuser=0).
8. Use the Saleae to decode the waveforms on SDA and SCL and confirm the data 
matches what is output over UART.

## Suggestions
- Set up the UART code before finishing your TMP117 implementation, so you can
use the target to test.
- Combine the two bytes you read into a single 16-bit integer.
- Avoid floating point math, i.e. instead of 2 * .05, do (2 * 5) / 100
- Look at the I2C sample in EVT-core for an example.

## Completion
When believe you've gotten everything working, try holding your thumb against
the TMP chip to heat it up. Then, blow on it to cool it down. Does the reported
value update appropriately? Once you're satisfied with your code's performance,
call over a senior member and show them your work. Also be sure to show them the
waveform recorded by the Saleae. Once they say it looks good, you can move on to
the next phase.
