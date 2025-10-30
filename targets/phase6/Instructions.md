# Phase 6: CAN

## Learning Objectives
- CAN Communication Protocol
- Interrupt Handler Creation
- Interboard communication
- Debugging & Sniffing the CAN network

## Summary
The communication protocol that we probably use the most is CAN. All the boards on the bike
communicate with one another via CAN. To use this protocol, you're going to need two Nucleos,
a FUN-E SNAIL, and the PEAK CAN Dongle. One of boards you will flash with the canboard target,
and the other with your own custom code. The boards will send CAN messages back and forth.

The FUN-E SNAIL will distribute power to both Nucleos and be the CAN network between them, and the PEAK CAN Dongle
allows you to sniff the CAN communication using your computer.

## Task Breakdown
1. Read the [CAN Documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/communication-protocols/controller-area-network-can?authuser=0)
2. Read the [FUN-E SNAIL Documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/fun-e-snail?authuser=0)
3. Read the [PEAK CAN Dongle Documentation](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/device-documentation/peak-can-dongle?authuser=0)
4. In `phase6/main.cpp`, add code to repeatedly send a CAN message with the payload "DEADBEEF" (in hexadecimal)
5. In the same file, add code to print out any received CAN messages
6. Flash one Nucleo with the canboard target and one with your target, and make sure your board is receiving "BEEFEEEF"
7. Connect the PEAK CAN and download PCAN Viewer and take a look at the traffic on the CAN bus.

## Suggestions
- Take a look at the backandforth sample or the canboard target code if you need assistance

## Completion
Once you've got it working, play around with it to get a feel for how you would send different CAN messages. 
Try adding a significant sleep() to your main loop and print the size of the CAN message queue, and see what is happening.