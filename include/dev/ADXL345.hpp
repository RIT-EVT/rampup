#ifndef ADXL345_HPP
#define ADXL345_HPP

#include <core/io/SPI.hpp>

namespace io = core::io;

namespace rampup {

/**
 * Handles reading acceleration data from the ADXL345 accelerometer.
 * Datasheet: datasheets/adxl345.pdf
 */
class ADXL345 {
public:
    enum AccelAxis : uint8_t {
        X = 0,
        Y = 2,
        Z = 4,
    };

    /**
     * ADXL345 constructor. Verifies the device is present and puts it into
     * measurement mode.
     *
     * @param spi used to talk to the accelerometer
     * @param deviceId the slave index of the accelerometer on the SPI bus
     */
    ADXL345(io::SPI& spi, uint8_t deviceId);

    /**
     * Reads the acceleration of a given axis.
     *
     * @param axis the axis to read
     * @param[out] accel the acceleration in centi-g (Gforce * 100)
     * @return the SPI status of the operation
     */
    io::SPI::SPIStatus readAccel(AccelAxis axis, uint16_t& accel);

private:
    /** The R/W bit of the register address, see datasheet p.14-15 */
    static constexpr uint8_t REG_READ_FLAG = 0x80;
    /** The multi-byte transaction bit of the register address, see datasheet p.14-15 */
    static constexpr uint8_t REG_MULTIBYTE_FLAG = 0x40;
    /** Bit mask for the 5-bit register address */
    static constexpr uint8_t REG_MASK = 0x3F;

    /** Device ID register, always reads back as 0xE5 */
    static constexpr uint8_t REG_DEVID = 0x00;
    /** Power control register */
    static constexpr uint8_t REG_POWER_CTL = 0x2D;
    /** Measurement mode bit of the power control register */
    static constexpr uint8_t POWER_CTL_MEASURE_BIT = 0x08;
    /** First (LSB) data register of the X axis; Y and Z follow at +2/+4 */
    static constexpr uint8_t REG_DATAX0 = 0x32;

    /** Raw register counts per 1 g of acceleration */
    static constexpr int G_SCALING_FACTOR = 256;

    io::SPI::SPIStatus readByte(uint8_t reg, uint8_t& out);
    io::SPI::SPIStatus readBytes(uint8_t reg, uint8_t* out, uint8_t len);
    io::SPI::SPIStatus writeByte(uint8_t reg, uint8_t in);

    /** SPI instance used to talk to the accelerometer */
    io::SPI& spi;
    /** Slave index of the accelerometer on the SPI bus */
    uint8_t deviceId;
};

} // namespace rampup

#endif // ADXL345_HPP
