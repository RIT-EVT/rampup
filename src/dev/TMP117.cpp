#include <dev/TMP117.hpp>

namespace rampup {

/*
 * The slave(slave), i2c(i2c) in this line are the c++ constructor initializer list.
 * This is effectively just saying to do i2c (the class variable) = i2c (the one passed in as a parameter)
 */
TMP117::TMP117(io::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(i2cSlaveAddress), i2c(i2c) {}

io::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    // Create variable to hold the register variable (the TEMP_REG defined in the TMP117.hpp)
    uint8_t registerValue = TEMP_REG;

    // Create a buffer to hold
    uint8_t outputBuffer[2];

    // Do a multibyte i2c read as we need 2 bytes back (temperature register is 2 bytes)
    io::I2C::I2CStatus status = i2c.readReg(i2cSlaveAddress, &registerValue, 1, outputBuffer, 2);

    // Create a temporary variable (u32 or u64) to do conversion math in
    uint64_t raw;

    // combine the two bytes of sensor data
    raw = (outputBuffer[0] << 8) | outputBuffer[1];

    // The raw output is 1 unit = 7.8125 m°C (= 0.078125°C)
    // so convert, without floating point math
    raw *= 78125;
    raw /= 10000; // they could add 2 zeros to return in normal Celsius, but all temps would be rounded down (sensors 20.759°C returned as 20°C)

    // Assign the value of the converted temp to the temperature variable
    temperature = raw;

    // Return the i2c read status
    return status;
}

} // namespace rampup
