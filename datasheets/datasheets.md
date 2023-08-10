# Reading Datasheets

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
you're working with, you should be able to see some indication on the board of
what address it's set up for. If you're having trouble, ask a senior member to
point it out for you.

### Register Addresses
After you've found the address of the slave device, you need to find the address
for the data you're looking for inside the slave device. Luckily, this time,
it's pretty easy to find as section 7.6 is titled "Register Map." There are 10
registers, but the only one we're interested in is Temp_Result at address 0x00.
Here, it has the address written as "00h", but it means the same thing as 0x00.
The prefix "0x" and the suffix "h" are both just used to indicate that the
number is hexadecimal instead of decimal.

After the table, there are a few sections that go into detail about each 
register. You will need this information in some cases, but here, the register
just stores a two-byte integer that we want to read, so it's straightforward.

### Implementation
Based on this information from the datasheet, you're going to want an I2C call
that looks something like `i2c.readReg(0x48, 0x00, &outputBuffer);`. This will
attempt to read the data in register 0x00 from the device at address 0x48. If 
everything goes well, it will then put the data into the variable 
`outputBuffer`. If you're having issues with this, set up the Saleae to check if
the signals being sent match these values.

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
header "Timing Diagram," so it's easy to find. The 

### Byte Order

### Register Addresses

### Implementation

