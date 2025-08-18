# Phase 5: ADC (Analog to Digital Converter)

## Learning Objectives
- Learn the basics of what an ADC is
- Understand the basics of an ADC driver
- Learn how to setup and use a potentiometer
- Finding pins on a STM32F446

## Summary
Now that you have learned how to use SPI, you are going to learn the basics of using the STM32 Nucleo's onboard ADCs. You will not need the Firmware Test Board (FTB) or the Saleae Logic Analyzer for this. 

## Task Breakdown
1. Check out the ADC samples in EVT-core to get a better idea of how it works.
2. Find out which pin you want to use (Hint: There are 16 possible pins you can use).
3. Write the target code to initialize and read values back from the throttle (potentiometer).
4. The throttle should read back ~0V to ~3.3V depending on where it is twisted to.

## Suggestions
- Check out this link at [mbed.com](https://os.mbed.com/platforms/ST-Nucleo-F446RE/) for more information on which pins are used for ADC functionality.
- Look at the single_adc sample in EVT-core for examples on how to set them up.

## Completion
- Your UART terminal should display a voltage that makes sense depending on where the potentiometer is turned.
- 0V when turned fully counter-clockwise.
- 3.3V when turned fully clockwise.