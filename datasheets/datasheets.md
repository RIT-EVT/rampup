# Datasheets

## Introduction to Datasheets
Datasheets (aka documentation), are instruction manuals for code, hardware, 
tools, or systems you’re working with. It explains what something is, how it 
works, and how to use it correctly. Creators/Manufacturers will make them, and 
they contain all the information about a chip or board, like its memory layout, 
power pins, timers, and communication interfaces. If you ask a technical question
to a senior member, there is a chance you get a response something like "have you 
read the documentation / datasheet?" (Shout out to Matthew 'Read the Docs' Heller), 
and they are referring to the datasheet of whatever you are working with.

Reading datasheets is far from the most interesting work we do on the team, but 
it is an important skill to have as an engineer of any discipline. Like any
skill, it does take some time to develop through practice. For this project, the
goal is just to give you some exposure to datasheets with guided examples. Below
are explanations describing what data to look for in datasheets for I2C and SPI
devices and where that data is found in the datasheets for the two ICs used for
the project. This page will be assuming you've already read the team's 
documentation on I2C and SPI, so be sure to read over those if you haven't.

## TMP117 Datasheet

### Slave Address
As it says in the documentation, the first thing you're going to want to find is
the slave address of the device. In the case of the TMP117 datasheet, this 
information can be found in section 7.5.3.1.2. Obviously, you don't want to read
every section to find this, so how should you go about finding this? Generally, 
you want to either use the provided Table of Contents and do some skimming or 
Ctrl+F your way to the right section. 

The Table of Contents unfortunately only goes down one layer, but it does
indicate that section 7.5 is titled "Programming," which is definitely something
we're interested in. Skimming from there, you'll pretty quickly end up in 
7.5.3 "I2C and SMBus Interface" and then 7.5.3.1.2 "Serial Bus Address." If 
you're using Ctrl+F, results will vary from datasheet to datasheet, but you can
pretty reliably use "I2C", "address", "slave address", "I2C address", etc. For 
this datasheet, any one of these will get you where you need to go.

Once you've gotten to the right place, you'll need to figure out how to
interpret the table that's there. The first thing to understand is the column
headers for the table "DEVICE TWO-WIRE ADDRESS" for our purposes just means I2C
slave address. Here it calls it a "two-wire address" because it's the same
address for both I2C and SMBus, which each use two wires. "ADD0 PIN CONNECTION"
indicates which pin should be connected to the ADD0 to pin to set the address on
the left. This way, the electrical engineers can configure the address of the 
device just by changing which pin they have connected to ADD0.

In the left column, there are 4 possible addresses listed, each of the form 
"10010##x". These indicate the actual bits of each of the bits. The last bit is
an "x" because is could be either a 0 or 1, depending on if a read or write is
being done. Our code is set up, so that it automatically handles that logic, so
we're just worried about the upper 7 bits. Converting these numbers to
hexadecimal, we get 4 possibilities:
 - 1001000 -> 0x48
 - 1001001 -> 0x49
 - 1001010 -> 0x4A
 - 1001011 -> 0x4B

The slave address for your device will be one of these four. Normally, you'd 
have to talk with the electrical engineers who are designing the PCB you're 
writing code for to get this number, but for the evaluation modules (EVMs) 
you're working with, you should be able to see some indication on the board 
of what address it's set up for. If you're having trouble, ask a senior member 
to point it out for you.

### Register Addresses
After you've found the address of the slave device, you need to find the address
for the data you're looking for inside the slave device. Luckily, this time,
it's pretty easy to find as section 7.6 is titled "Register Map." There are 10
registers, but the only one we're interested in is Temp_Result at address 0x00. 

Here, it has the register address written as "00h", but it means the same thing 
as 0x00. The prefix "0x" and the suffix "h" are both just used to indicate that 
the number is hexadecimal instead of decimal.

### Register Details
After the table, there are a few sections that go into detail about each 
register. 

The datasheet explains in section 7.6.2, “Temperature Register,” that the 
Temp_Result register holds the temperature data, stored as a two-byte integer. 
That makes this pretty simple, you will just need to be sure you use the 
multi-byte readReg() method of the I2C class, not the single-byte read.

The datasheet also explains that each least significant bit (each raw unit of output)
in the temperature register, equals 7.8125 millidegrees Celsius (m°C), or 0.0078125°C. 
This means the sensor’s raw 16-bit output is not in degrees Celsius, but instead 
must be converted to be human-readable.

### Implementation
Based on this information from the datasheet, you're going to want an I2C call
that looks something like 
`i2c.readReg(slaveAddress, registerBuffer, 1, outputBuffer, 2);`. This will attempt to 
read 2 bytes from the slave device at address `slaveAddress` on the I2C bus. From this device, it 
will read the data at the 1 byte address stored in `registerBuffer`, which you should 
set to 0x00 (the Temp_Result register). `outputBuffer` should be a two-byte buffer used to store the 
output, which you can create with `uint8_t outputBuf[2];`. If everything goes 
well, it will then put the data into the `outputBuffer`. If you're having issues
with this, set up the Saleae to check if the signals being sent match the values
in this call. 

After that, you will need to properly convert the output, in a ratio
of 1 to 7.8125 (34.56 °C would be stored as 3456 m°C). If you are having issues with 
losing data, make sure to use a temporary variable of larger scale, like a 
uint32_t or uint64_t (32 or 64 bit integer).

## MAX22530 Datasheet

### Speed
The first configuration parameter you'll want to locate is speed. Most SPI
devices support a range of speeds, but they should have a maximum speed.
Generally, we're always going to want to operate at the fastest speed possible to
limit latency, so we should operate at the max speed of the device.

Searching with Ctrl+F or using the table, we can pretty quickly find the section
titled "SPI Interface," which has the speed limit of 10 MHz directly under it.
This information can also be found in the "Electrical Characteristics" table
under the heading "SPI TIMING CHARACTERISTICS." 

### Mode
Mode is often the most difficult information to pin down for a SPI device.
Because SPI is not strictly standardized, different companies use different
modes, and they describe what mode they use in different ways. Some datasheets
may directly tell you the clock polarity and phase, but in this case, the
datasheet is not so direct. If all else fails, almost all IC datasheets with a
serial communication protocol will have a timing diagram that shows how the 
communication works at the logical level (1s and 0s). With a good understanding 
of clock polarity and phase, we can use the timing diagram to figure out the 
mode. That said, it's very easy to make a mistake here, so debug this early on
if you're having issues. Sometimes, it's easiest to just guess and check the
mode.

The timing diagram on this datasheet is conveniently found right under the
header "Timing Diagram," so it's easy to find. The first thing to notice is the
clock polarity. On the left side of the diagram, we can see that the clock
starts low, meaning clock polarity is 0. To figure out clock phase, we can look
at the state of the clock while the data is changing. In the diagram, possible
changes in the data are represented with the two lines next to SDI crossing.
Whenever this happens, the clock is low, which, as we determined above, is its
idle state. When the data switches while the clock is idle, it means that the
clock polarity is 0. Because CPHA and CPOL are both 0, the mode is 0.

### Bit Order
The bit order is sometimes listed plainly somewhere in the document, which can
normally be found by searching for keywords. In this case, keyword search isn't
very helpful, so we have to refer back to the timing diagram used for the mode.
In that diagram, you can see the bytes sent labeled as A5, A4, A3, etc. This
labeling indicates that the most significant bit (A5) is being sent first, so
the bit order is MSB first.

### Register Addresses
Once all the configuration parameters have been figured out, the next thing
you'll need to do is find which registers are holding the data you're looking
for. For this data sheet, it seems pretty straightforward. Under the "Register
Map" section, there's a table that shows that the four registers we're
interested in are 0x01 - 0x04.

This should be fairly straightforward, but there is one more stumbling block.
In the SPI interface section, there is a table titled "SPI Read Command," which
shows the breakdown of the bytes sent during a read command. Here, we can see
that the register address is only six bits, instead of the normal eight. The
address makes up the first six bits, followed by one bit to differentiate
reading and writing and one bit to indicate whether it's a burst read. We want 
both of these additional bits to be 0, so we can take the register value and
left shift it twice. For example, to read the value in register 0x03, we should
actually send the SPI instance a request to read from register 0x0C because the
bits 00000011 become 00001100. As a result, the four register addresses we want
to read over SPI are 0x04, 0x08, 0x0C, and 0x10.

### Register Details
Like the TMP117, the registers being read here are all 2 bytes, so they can be
combined in the same way you did for that driver. However, for that driver, all
of the register was just the value we wanted to read. Looking at the register
map for the ADC registers, we can see that the actual ADC value only goes in 
bits 0-11. Therefore, we should overwrite the top 4 bits to always be 0.

### Implementation
In the target, you should initialize the SPI instance with the parameters found
in the datasheet, using a function call like 
`spi.configureSPI(SPI_SPEED_4HZ, SPI_MODE0, SPI_MSB_FIRST);`. In the
implementation of MAX22530, you can read the value of a register with a call
like `spi.readReg(0, register, &outputBuffer, 2)`. Here the 0 indicates that 
it's reading from the 0th slave on the bus. The `register` is the register 
we're trying to read, having been left-shifted twice. `outputBuffer` is a
two-byte buffer allocated to hold the output data. The 2 indicates that you're
reading two bytes from the slave. Once again, if you're having issues, be sure
to use the Saleae to check what's happening
