#ifndef TMP117_HPP
#define TMP117_HPP

#include <EVT/io/I2C.hpp>

#define TEMP_REG 0x00

namespace IO = EVT::core::IO;

namespace rampup {

/**
 * Temp sensor for TMS
 * https://www.ti.com/lit/ds/symlink/tmp117.pdf
 */
class TMP117 {
public:
    /**
     * Temp sensor constructor
     *
     * @param i2c used to read temperature
     * @param i2cSlaveAddress address to ID the sensor on the I2C bus
     * */
    TMP117(IO::I2C& i2c, uint8_t i2cSlaveAddress);

    /**
     * Reads the temperature
     *
     * @return temperature reading in degrees centi celsius
     */
    IO::I2C::I2CStatus readTemp(uint16_t& temp);

private:
    /** Device ID */
    uint8_t i2cSlaveAddress;

    /** I2C instance */
    IO::I2C& i2c;
};

}// namespace rampup

#endif//TMP117_HPP
