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

#### Step 1 – Understand Controlling LED's
- The LED is connected to a specific pin on your board (e.g., PA_5).
- The pin must be set as Output, as you are sending a signal (turn on, or turn off) to the LED.
- As the LED is connected to a pin, when the pin is set to HIGH, it will send out a 3.3 volt signal,
which will cause the LED to turn on.

#### Step 2 - Choosing a pin
- You will need to figure out what pin to connect your LED to
  - This will be done by looking at a pinout for the microcontroller you are using

#### Step 3 - Writing the code
- create a gpio for your pin
- create an infinite loop
  - toggle the LED on/off and wait .5 seconds

#### Step 4 - Flashing (Running) the code
To run code on a microcontroller, the code needs to be compiled from C++ to binary,
the language the microcontroller understands, then the code needs to be flashed by sending said 
binary code to the microcontroller for it to run.

There are two main ways this can be done, either by using OpenOCD (a program that handles this),
or by manually clicking the build button and then dragging created binary file (.bin) to the 

##### The manual way:
1. Build/compile the code
   - In the top right of your CLion, you should see a white hammer, a green play button, and a green bug.
   - To the left of the hammer there should be a dropdown menu, open it and select **phase1**.
   - Press the build hammer, and you should see messages come through the Build menu at the bottom of the screen.


2. Finding the output from the Build
   - Now, in the project directory, there should be a `build` folder (often colored orange). It might be called `cmake-build-debug`.
   - The build folder contains any build code, and other output from the code, like log messages.
   - Inside the build folder, go to `targets/phase1`, and if the build succeeded, you should see
   a `phase1.bin`, `phase1.elf`, and `phase1.hex` among others. These are the compiled versions of your 
   program.


3. Flash output to microcontroller
   - We only care about the `phase1.bin`.
   - Copy (control + c) this file from CLion to the external disc the microcontroller is seen as.
     - The microcontroller disc can be found in the file explorer.
   - The microcontroller disc should automatically disconnect/disappear, and the program will soon be running on the uC.

## Task Breakdown
- Learn about GPIO by reading above, or watching [a 15 minute video](https://www.youtube.com/watch?v=H9XcE1vDX1Q)
- Follow [**The Time Guide**](Time.md) to learn how to use the namespace functions in `time.hpp`
- Follow [**The GPIO Guide**](GPIO.md) to learn how to use the `GPIO.hpp` class 
- Initialize GPIO on the chosen pin
- Create loop to turn LED on and off
- Test the code on the actual microcontroller

## Suggestions
- If you are confused about any parts of GPIO or the task, ask a senior member anything and everything

## Completion

Once you've gotten it working, try changing the wait time, or make a pattern of the blinking. 
Once you're happy with what you have, show your code to a senior firmware member. 
Once they say it looks good, you can move on to the next phase.
