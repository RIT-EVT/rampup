#include <dev/TMP117.hpp>

namespace rampup {

TMP117::TMP117(io::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(i2cSlaveAddress), i2c(i2c) {}

io::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    uint8_t registerValue = TEMP_REG;
    uint8_t outputBuffer[2];

    io::I2C::I2CStatus status = i2c.readReg(i2cSlaveAddress, &registerValue, 1, outputBuffer, 2);

    // Raw output is 1 unit = 7.8125 m°C; use a wider type to avoid overflow during conversion
    uint64_t raw = (outputBuffer[0] << 8) | outputBuffer[1];
    raw = raw * 78125 / 10000;

    temperature = raw;

    return status;
}

} // namespace rampup
