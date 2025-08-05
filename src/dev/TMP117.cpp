#include <dev/TMP117.hpp>

namespace rampup {

/*
 * The "slave(slave), i2c(i2c)" on line 9 are the c++ constructor initializer list.
 * This is effectively just saying to do i2c (the class variable) = i2c (the one passed in as a parameter) and the same
 * for slave
 */
TMP117::TMP117(io::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(i2cSlaveAddress), i2c(i2c) {}

io::I2C::I2CStatus TMP117::readTemp(uint16_t& temperature) {
    // Create variable to hold the register variable (the TEMP_REG value defined in the TMP117.hpp)

    // Create a buffer to hold the temperature from the I2C

    // Do a multibyte i2c read as we need 2 bytes back (temperature register is 2 bytes)

    // Create a temporary variable (u32 or u64) to do conversion math in

    // combine the two bytes of sensor data

    // Convert; The raw output is 1 unit = 7.8125 m°C (= 0.078125°C)

    // Assign the value of the converted temp to the temperature variable

    // Return the i2c read status
    return io::I2C::I2CStatus::ERROR; // temporary placeholder to be replaced
}

} // namespace rampup
