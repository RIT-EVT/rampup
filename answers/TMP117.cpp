#include <dev/TMP117.hpp>

namespace rampup {

TMP117::TMP117(IO::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(i2cSlaveAddress), i2c(i2c) 
{}

IO::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    uint8_t registerBuffer = TEMP_REG;
    uint8_t outputBuffer[2];

    // Doing multi-byte read as we need 2 bytes back (temp register is 2 bytes)
    IO::I2C::I2CStatus status = i2c.read(i2cSlaveAddress, &registerBuffer, 1, outputBuffer, 2); // Method found here https://github.com/RIT-EVT/EVT-core/blob/main/src/core/io/I2C.cpp

    // Not necessary but probably a good idea to have, or some sort of error handling...
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

} // namespace rampup
