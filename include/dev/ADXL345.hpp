#ifndef ADXL345_HPP
#define ADXL345_HPP

#include <core/io/SPI.hpp>

namespace rampup {

namespace io = core::io;

/**
 * Handles reading acceleration data from the ADXL345 accelerometer.
 * Datasheet: datasheets/adxl345.pdf
 */
class ADXL345 {
public:
    enum AccelAxis : uint8_t {
        X = 0,
        Y = 2,
        Z = 4
    };

    /** The R/W bit of the register address P.14-15*/
    static constexpr uint8_t ADXL345_REG_READ_FLAG      = 0x80;

    /** The Multibyte transmission bit of the register address P.14-15*/
    static constexpr uint8_t ADXL345_REG_MULTIBYTE_FLAG = 0x40;

    /** Bit mask for register address */
    static constexpr uint8_t ADXL345_REG_MASK           = 0x3F;

    /** Register address for the device ID P.24. Always returns 0xE5  */
    static constexpr uint8_t ADXL345_REG_DEVID     = 0x00;

    /** Register address for the power control P.26. */
    static constexpr uint8_t ADXL345_REG_POWER_CTL = 0x2D;

    /** Bit mask for the power control measurement mode bit P26. Enables measurements */
    static constexpr uint8_t ADXL345_REG_POWER_CTL_MEASURE_BIT = 0x08;

    /** Register address for the Data X LSB (data is two sequential byte registers) P.27 */
    static constexpr uint8_t ADXL345_REG_DATAX0    = 0x32;

    /** Register address for the Data Y LSB (data is two sequential byte registers) P.27 */
    static constexpr uint8_t ADXL345_REG_DATAY0    = 0x34;

    /** Register address for the Data Z LSB (data is two sequential byte registers) P.27 */
    static constexpr uint8_t ADXL345_REG_DATAZ0    = 0x36;

    /** The scaling factor to convert the register value to Gforce */
    static constexpr int G_SCALING_FACTOR = 256;

    // Public methods
    ADXL345(io::SPI& spi, int id);

    /**
     * Reads the acceleration of a given axis
     *
     * @param axis The axis to get the acceleration from
     * @param[out] accel A reference to return the current acceleration in milli-Gforce
     * @return The spi status of the operation
     */
    io::SPI::SPIStatus readAccel(AccelAxis axis, int16_t& accel);

private:
    /**
     * Reads a single byte from the ADXL345
     *
     * @param reg The register to read from
     * @param out The byte read from the sensor
     * @return The spi status of the operation
     */
    io::SPI::SPIStatus readByte(uint8_t reg, uint8_t& out);

    /**
     * Reads multiple bytes from the ADXL345
     *
     * @param reg The register to read from
     * @param out A array to store the bytes read from the sensor
     * @param len The number of bytes to read
     * @return The spi status of the operation
     */
    io::SPI::SPIStatus readBytes(uint8_t reg, uint8_t* out, uint8_t len);

    /**
     * Write a single byte to the ADXL345
     *
     * @param reg The register to write to
     * @param in The byte write to the sensor
     * @return The spi status of the operation
     */
    io::SPI::SPIStatus writeByte(uint8_t reg, uint8_t in);

    /**
     * Write multiple bytes to the ADXL345
     *
     * @param reg The register to write to
     * @param in A array to of bytes to write to the sensor
     * @param len The number of bytes to write
     * @return The spi status of the operation
     */
    io::SPI::SPIStatus writeBytes(uint8_t reg, uint8_t* in, uint8_t len);

    // Private member variables

    /** SPI reference to talk to ADXL */
    io::SPI& adxl_spi;

    /** Device ID of ADXL instance*/
    int device_id;
};

} // namespace rampup

#endif // ADXL345_HPP
