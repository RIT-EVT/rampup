# Phase 1: GPIO

## Learning Objectives
- What GPIO is and how it works
- Using EVT-core to configure and control a GPIO pin
- Building and flashing code to a microcontroller

## Summary

### What is GPIO?
GPIO stands for General-Purpose Input/Output.

- General-Purpose → Not tied to one specific function. The same pin could be used for reading a button today, controlling an LED tomorrow.

- Input → The microcontroller reads a signal from the outside world (e.g., a button press, a sensor output).

- Output → The microcontroller sends a signal to control something (e.g., turning an LED on/off, activating a motor).

### Why Do We Use GPIO?

GPIO is the simplest way for a microcontroller to interact with the outside world.
You’ll use it to:

- Control indicators (LEDs, buzzers, relays).

- Read the state of switches, buttons, or sensors.

- Communicate with other sensors or microcontrollers.

In EVT’s bikes, GPIO pins are used for things like reading from sensors and sending commands to other microcontrollers.

### Your First Embedded Program: Blink an LED

#### Step 1 – Understand the Hardware
- An LED has 2 legs, one longer (the anode) and one shorter (the cathode)
  - The longer leg needs to be connected to a pin to power the LED
  - The shorter leg needs to be connected to the boards ground (GND)
- The LED **MUST have a resistor** to avoid burning out the LED or damaging the uC. 
  - The resistor limits the current to a safe level, letting the LED light up without overheating or failing. 
- The LED is connected to a specific pin on your board (e.g., PA_5).
- The pin must be set as Output, as you are sending a signal (turn on, or turn off) to the LED.
- As the LED is connected to a pin, when the pin is set to HIGH, it will send out a 3.3 volt signal, which will cause the LED to turn on

#### Step 2 - Choosing a pin
- You will need to figure out what pin to connect your LED to
  - This will be done by looking at a pinout for the microcontroller you are using

#### Step 3 - Writing the code
- create a gpio for your pin
- create an infinite loop
  - toggle the led on/off and wait .5 seconds

#### Step 4 - Flashing (Running) the code
- Something here about flashing code

## Task Breakdown
- Follow [**The Time Guide**](Time.md) to learn how to use the namespace functions in `time.hpp`
- Follow [**The GPIO Guide**](GPIO.md) to learn how to use the `GPIO.hpp` class 
- Initialize GPIO on the chosen pin
- Create loop to turn LED on and off
- Test with actual LED (DO NOT FORGET THE RESISTOR)

## Suggestions
- Sorry if you're a visual or auditory learner... Ask a senior member to walk you through anything that 
you don't understand

## Completion

Once you've gotten it working, play around with it for a bit, maybe try to have 2 LED's
that are offset. Once you're happy with what you have, show your code to a senior firmware member. 
Once they say it looks good, you can move on to the next phase.
