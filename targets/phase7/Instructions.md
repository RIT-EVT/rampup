# Phase 7: CANOpen

## Learning Objectives

- CAN communication
- CANopen standard
- Main target development
- Memory addressing in C++
- Waveform analysis with an oscilloscope

## Summary

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

## Task Breakdown

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

## Suggestions

- Read the [CAN documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/controller-area-network-can?authuser=0).
- Read the [CANopen documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/controller-area-network-can/canopen).
- Look at the canopen_sample in EVT-core for an example.
- If the HUDL doesn't work right away, debug the output with the PEAK can dongle
  and the Saleae.
- Read the [FUN-E SNAIL documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/fun-e-snail?authuser=0).
- Read the [PEAK dongle documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/peak-can-viewer?authuser=0).
- Read the [oscilloscope documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/oscilloscope?authuser=0).

## Completion

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

