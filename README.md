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
1. Over UART, read two numbers input by the user up to 10 digits.
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

### Summary


### Learning Objectives
- 

### Task Breakdown
1. 

### Suggestions
- 

### Completion



## Phase 3: SPI

### Summary


### Learning Objectives
- 

### Task Breakdown
1.

### Suggestions
- 

### Completion



## Phase 4: CAN

### Summary


### Learning Objectives
- 

### Task Breakdown
1.

### Suggestions
- 

### Completion

