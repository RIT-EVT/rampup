# Rampup Project

## Summary

Hello and welcome to EVT! This project is designed to give you a look into what
it is like to develop on the firmware team. The goal is for you design a
device driver for communicating with an "IC" this IC is a voltage and
temperature sensor that you communicate with over I2C. Your job is to pull
out the device ID, temperature, and voltage data from the device. You will
then print that data out over UART and view the data on the serial console.

The IC in question will be replicated using an Arduino acting as an I2C device.
The Arduino will be listening for I2C request and responding very similarly to
how the various chips on the EVT boards do.

## Task Breakdown

1. Flash the Arduino with the code to have it act as an IC (in the `arduino/`
folder)
2. Modify `src/main.cpp` to make I2C requests to the Arduino.
3. Connect the STM32 to the Arduino via the I2C lines.
4. Print out the read in I2C messages on a serial console.

### "Bonus Points"

The above steps are a great start, to try out development more closely related
to EVT development try out some of the following tweaks.

1. Creating a class `ArduinoDevice` that has methods for the various I2C
register reads.
2. Along side sending the data over UART, try sending the data over CAN and
reading back the data on another STM32.

## Arduino Device Documentation

When dealing with a "real IC" you will get a datasheet from the manufacturer
that will detail how to communicate with the device. Here you will be given
a more abbreviated document on how to read data from the Arduino.

The Arduino is setup as an I2C device that has values stored in "registers".
Registers can be thought of blocks of storage that can store values. The
registers will be of a fixed size (8 bits in this case), and will be accessed
via an address (which will also be 8 bits). Below is a table breaking down
the register address and the cooresponding value. In an actual device, the
register values won't be fixed, but will represent the actual data. For the
sake of testing, these values are fixed.

| Register | Description                                    | Expected Value |
|----------|------------------------------------------------|----------------|
| 0x00     | The ID of the device                           | 0xAA           |
| 0x01     | Least significant byte of the temperature data | 0x10           |
| 0x02     | Most significant byte of the temperature data  | 0x11           |
| 0x03     | Least significant byte of the voltage data     | 0x12           |
| 0x04     | Most signficant byte of the voltage data       | 0x13           |

Having values stored in registers is a common approach used by ICs that are
communicated with via I2C. The general format is that the "host" or "master"
device (the STM) will write out the address it wants to read from. Then the
"device" or "slave" will respond with the value associated with that
address.

For example, say we want to read the ID of the device. We will write from
the STM 0x00, then the Arduino will respond with 0xAA.

That isn't the whole story. In actual applications, there can be many
I2C devices attached to a host device. In order to differentiate between them,
each one has an address. For the Arduino this will be 0x04. So the complete
picture is that the STM will write 0x00 to I2C device 0x04, then will read
from the I2C device 0x04.

## Getting Started

1. Add a ssh-key to Github. I would recommend looking up how to do that on
your specific setup.

2. Clone the repository. The repository has "submodules" so cloning is a little
different then normal.

```
git clone --recurse-submodules git@github.com:RIT-EVT/rampup.git
```

Or if you cloned normally and didn't realize there were submodules.

```
git clone git@github.com:RIT-EVT/rampup.git
git submodule update --init
```

3. Build the code, you can follow the instructions in `EVT-core` for building
project.

## Explaination

Often times on the various boards, we will need to commiunicate with other
chips in order to gain data on the bike. This can include temperate, voltage,
pump flow rate, ground fault detection, etc. It is very common for that data
to be collected by communicating with an IC via I2C. This project provides and
entry point into doing embedded development in such a way that is inline with
what we do in EVT.

The instructions are left purposfully a little vague. Since this is a college
level team, there are a lot of times where no one may know the answer and we
have to learn on our own. Other members of the team will be more then happy to
help. But don't be afraid to try things out, Google search, play around with
samples in EVT-core, and look at examples online. The goal is not to make you
feel overwhelmed, but to acclimate you to joining a team where answers are
sometimes hard to come by and learning is a continous process.

My hope is that you find this exercise educational and enjoyable. At any point
if you feel stuck, please reach out to a team member. This isn't a class, you
won't be graded, and it's meant to be a fun project.

Good luck!
