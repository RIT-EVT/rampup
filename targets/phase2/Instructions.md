# Phase 2: UART

## Learning Objectives

- C++ syntax
- EVT-core basics
- Making a UART interface
- Working with a nucleo

## Summary

The first communication protocol you should be aware of is UART, which we
commonly use to communicate between a laptop and a board, mostly for debugging.
To use this protocol, you'll only need a Nucleo and your laptop. Your goal will
be to simply take two numbers from the user, add them, and print the result.
Obviously, the actual work being done isn't very complex, but this first step
will help you understand how to work in C++ and with EVT-core, our custom
library. The only file you'll need to modify is `targets/phase1/main.cpp`.

## Task Breakdown

1. Read the [Nucleo documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/stm32-nucleo).
2. Read over the [UART documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/universal-synchronousasynchronous-receivertransmitter-usartuart). 
3. Over UART, read two numbers input by the user, up to 10 digits each. 
4. Print the sum of the two numbers over UART.

## Suggestions

- Be sure you know how to open a serial console. (Documented
  [here](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/getting-started/running-code)) - PuTTY for Windows users - `screen` for MacOS/Linux
- Copy code from the echo sample for a starting point.
- Look up standard C++ functions for converting from character array to
  integer.

## Completion

Once you've gotten it working, play around with it for a bit to see if you can
break it. What happens when you put in something that isn't a number? What
happens when you put in a really long input? Once you're happy with what you
have, show your code to a designated senior firmware member. Once they say it
looks good, you can move on to the next phase.

