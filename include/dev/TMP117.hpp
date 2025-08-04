#ifndef TMP117_HPP
#define TMP117_HPP

#include <core/io/I2C.hpp>

#define TEMP_REG 0x00

namespace io = core::io;

namespace rampup {

/**
 * Temp sensor for TMS
 * Datasheet: https://www.ti.com/lit/ds/symlink/tmp117.pdf
 */
class TMP117 {
public:
    /**
     * Temp sensor constructor
     *
     * @param i2c used to read temperature
     * @param[in] i2cSlaveAddress address to identify the sensor on the I2C bus
     * */
    TMP117(io::I2C& i2c, uint8_t i2cSlaveAddress);

    /**
     * Reads the temperature from the TMP sensor
     *
     * @param[out] temperature reading in centi-degrees Celsius (Celsius * 100)
     * @return I2CStatus indicating the success or failure of the read.
     */
    io::I2C::I2CStatus readTemp(uint16_t& temperature);

private:
    /** Device ID */
    uint8_t i2cSlaveAddress;

    /** I2C instance */
    io::I2C& i2c;
};

} // namespace rampup

#endif // TMP117_HPP
