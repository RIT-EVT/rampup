# Phase 4: Serial Peripheral Interface (SPI) 

## Learning Objectives
- SPI communication
- Advanced driver development
- Analog-to-Digital Converter (ADC) use
- Reading datasheets
- Running code on EVT hardware

## Summary
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

## Task Breakdown
1. Read the [SPI documentation](
https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/serial-peripheral-interface-spi?authuser=0).
2. Read the datasheets.md section about the MAX22530 datasheet.
3. Write the header file for `MAX22530`, so that it can be used to read voltages
from each channel.
4. Implement the functions defined in the header file.
5. Write the target code to call the functions and print all voltages over UART.
6. Use the Saleae to decode the waveforms on CS, SCL, MOSI, and MISO and confirm
the data matches what is output over UART.

## Suggestions

- Read the SPI documentation.
- Fully plan out the MAX22530 class in the header file before starting on the
  implementation.
- Look at the SPI sample in EVT-core for an example.
- Read the ST-Link documentation to see how to use it.
- Read the running code documentation to see how to flash the PVC.

## Completion
Once you think it's working, get a variable power supply and apply different
voltages to the input channels. If you're not familiar with power supplies, have
a senior member help you set it up. Be sure to limit the current to only a few 
milliamps to make sure it's safe. Does the voltage on the power supply match the
UART output? When you're happy with its performance, have a senior member look
at your Saleae output and your code. If it looks good, have them get you a DEV1
PVC to test the code on. With their help, use the power supply to test the ADC
on the PVC. If it works, you can start on the last phase.