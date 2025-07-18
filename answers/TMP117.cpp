#include <dev/TMP117.hpp>

namespace rampup {

TMP117::TMP117(IO::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(i2cSlaveAddress), i2c(i2c) 
{}

IO::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    uint8_t reg = TEMP_REG;
    uint8_t buffer[2];

    IO::I2C::I2CStatus status = i2c.read(i2cSlaveAddress, &reg, 1, buffer, 2); // Method found here https://github.com/RIT-EVT/EVT-core/blob/main/src/core/io/I2C.cpp#L47

    // Not necessary but probably a good idea to have, or some sort of error handling...
    if (status != IO::I2C::I2CStatus::OK) {
        temperature = 0;
        return status;
    }

    // Need to have a temporary variable (u32 or u64) to do conversion math in
    uint64_t raw;

    // combine sensor output
    raw = (buffer[0] << 8) | buffer[1];
    
    // The raw output is 1 unit = 7.8125 m°C = 0.0078125°C
    // so convert, without floating point math
    raw *= 78125;
    raw /= 10000000;

    temperature = raw;

    return status;
}

} // namespace rampup
