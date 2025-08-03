# Phase 4: Serial Peripheral Interface (SPI) 

## Learning Objectives
- SPI communication
- Advanced driver development
- Accelerometers
- Reading datasheets
- Running code on EVT hardware

## Summary

The next communication protocol to cover is the Serial Peripheral Interface (SPI, pronounced "spy"). You'll use this protocol to communicate between the uC and a 3-axis accelerometer, which is an IC that is capable of sensing the acceleration of a device in three dimensions. For our purposes, we're going to read the acceleration of all three axes and print it out. You'll still need the Saleae and FTB, but you'll need to switch out the TMP117 board for the ADXL345 board. For this phase, the header file hasn't been provided for you, so you'll have to write that yourself. The files you need to edit are `include/dev/ADXL345.hpp`,`src/dev/ADXL345.cpp`, and `targets/phase4/main.cpp`. 

## Task Breakdown
1. Read the [SPI documentation](
https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/serial-peripheral-interface-spi?authuser=0).
2. Read the datasheets.md section about the ADXL345 datasheet.
3. Write the header file for the `ADXL345`, so that it can be used to read all three static acceleration axes and configure the .
4. Implement the functions defined in the header file.
5. Write the target code to call the functions and print all voltages over UART.
6. Use the Saleae to decode the waveforms on CS, SCL, MOSI, and MISO and confirm
the data matches what is output over UART.

## Suggestions

- Read the SPI documentation.
- Fully plan out the ADXL345 class in the header file before starting on the
  implementation.
- Look at the SPI sample in EVT-core for an example.
- Read the ST-Link documentation to see how to use it.
- Read the running code documentation to see how to flash the PVC.

## Completion
Once you have completed your implementation, you should see the acceleration in the z-axis around 9.8m/s due to gravity. Try standing the board up on one end to see if the acceleration shifts to one of the other axes. Try it again on the perpendicular axis. You should be able to see a positive and negative acceleration due to gravity on each axis. When you're happy with the performance, have a senior member look at your Saleae output and your code. If it looks good, you can start on phase 5.