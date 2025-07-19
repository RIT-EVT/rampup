# Phase 3 Answers
## Code

### targets/phase3/main.cpp
The main things that need to be seen in here is just that they create/setup I2C
 and the TMP117, and they are calling the readTemp(...) and printing it.

```
#include "dev/TMP117.hpp"
#include <EVT/io/I2C.hpp>
#include <EVT/io/UART.hpp>
#include <EVT/manager.hpp>

using namespace std;
namespace IO = EVT::core::IO;
namespace time = EVT::core::time;
constexpr uint8_t i2cSlaveAddress = 0x48; // This is known by looking at the click board and table in datasheet, depends on what the ADD0 pin is connected to (GND, 3.3V, SDA, SCL)

int main() {
    // Initialize system
    EVT::core::platform::init();

    // Set up UART
    IO::UART& uart = IO::getUART<IO::Pin::UART_TX, IO::Pin::UART_RX>(9600);

    // Set up I2C
    IO::I2C& i2c = IO::getI2C<IO::Pin::PB_8, IO::Pin::PB_9>();

    // Create TMP117 instance
    rampup::TMP117 tmp(i2c, i2cSlaveAddress);

    uint16_t temperature;

    while (1) {
        // Read temperature
        tmp.readTemp(temperature);

        // Error handling
        if (status != IO::I2C::I2CStatus::OK) {
            uart.printf("I2C Error!");
            continue;
        }

        // Print temperature as normal celsius (2534 centi-Celsius => 25.34 Celsius)
        uart.printf("Temp: %d.%d Celsius\n\r", temperature / 100, temperature % 100); 

        // Wait 1 s
        time::wait(1000);
    }
}
```

### src/dev/TMP117.cpp readTemp() function
The main things that need to be checked in the code is that they are reading from 
i2c `i2c.read(...)`, combining the raw output from the sensor 
`(outputBuffer[0] << 8) | outputBuffer[1]`, and they are converting it into either 
centi-celsius (preferred) or celsius `rawOutput * 78125 / 10000 or 1000000`.

```
IO::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    uint8_t registerBuffer = TEMP_REG;
    uint8_t outputBuffer[2];

    // Doing multi-byte read as we need 2 bytes back (temperature register is 2 bytes)
    IO::I2C::I2CStatus status = i2c.read(i2cSlaveAddress, &registerBuffer, 1, outputBuffer, 2);

    // Not necessary but probably a good idea to have, for some sort of error handling...
    if (status != IO::I2C::I2CStatus::OK) {
        temperature = 0;
        return status;
    }

    // Need to have a temporary variable (u32 or u64) to do conversion math in
    uint64_t raw;

    // combine sensor output
    raw = (outputBuffer[0] << 8) | outputBuffer[1];
    
    // The raw output is 1 unit = 7.8125 m°C (= 0.078125°C)
    // so convert, without floating point math
    raw *= 78125;
    raw /= 10000; // they could add 2 zeros to return in normal celsius, but all temps would be rounded down (sensors 20.75°C returned as 20°C) 

    temperature = raw;

    return status;
}
```

## Expected UART output

IMAGE TO BE ADDED!


## Saleae Expected Images

IMAGE TO BE ADDED!