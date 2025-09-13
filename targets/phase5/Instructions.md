# Phase 5: ADC (Analog to Digital Converter)

## Learning Objectives
- Learn the basics of what an ADC is
- Understand the basics of an ADC driver
- Learn how to set up and use a potentiometer
- Finding pins on a STM32 Nucleo

## Summary
Now that you have learned how to use SPI, you are going to learn the basics of using the STM32 Nucleo's onboard ADCs. You will not need the Firmware Test Board (FTB) or the Saleae Logic Analyzer for this (But they can be used if desired). 

An ADC (Analog to Digital Converter) is a device that, in this case, takes an analog (continuous) voltage signal and converts it to a discrete (think integer (no decimal)) value. The STM32 has different ADC peripherals that can be accessed by multiple different pins. Each version will have different pinouts and amount of peripherals (peripherals are the actual devices that receive the signals from the pins). It will be your job to set up a potentiometer that takes a 3V3 (3.3V) voltage from the board and reads it back as a different voltage depending on how much you turn it. The potentiometer should read back ~0V to ~3.3V depending on whether it is twisted fully counter-clockwise or fully clockwise respectively. You will then write code that properly sets up an ADC device and the EVT-core logger and then displays the voltage being read from the potentiometer on a UART terminal.

## Task Breakdown
1. First make sure that you actually have a STM32 Nucleo board. This section can be done with any of the boards available, but you will have to find the pinout of the other boards as none of them will be the exact same as far as pins go.
2. Check out the ADC samples in EVT-core to get a better idea of how to set it up.
3. Find out which pin you want to use (Hint: There are 16 possible pins you can use).
4. Write the target code to initialize and read values back from the throttle (potentiometer).
5. The throttle should read back ~0.0V to ~3.3V depending on where it is twisted to.

## Suggestions
- Check out these links at mbed.com for more information on which pins are used for ADC functionality.
- [STM32F302](https://os.mbed.com/platforms/ST-Nucleo-F302R8/)
- [STM32F334](https://os.mbed.com/platforms/ST-Nucleo-F334R8/)
- [STM32F446](https://os.mbed.com/platforms/ST-Nucleo-F446RE/)
- Look at the single_adc sample in EVT-core for examples on how to set them up.

## Completion
- Your UART terminal should display a voltage that makes sense depending on where the potentiometer is turned.
- 0.0V when turned fully counter-clockwise.
- 3.3V when turned fully clockwise.
- Verify it with a senior member of the team and then you can move on.