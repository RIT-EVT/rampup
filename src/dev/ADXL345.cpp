#include <core/utils/log.hpp>
#include <core/utils/time.hpp>

#include <dev/ADXL345.hpp>

namespace log  = core::log;
namespace time = core::time;

namespace rampup {

ADXL345::ADXL345(io::SPI& spi, uint8_t deviceId) : spi(spi), deviceId(deviceId) {
    // Poll the device ID register until the sensor responds, confirming the wiring/SPI config is correct
    uint8_t id = 0;
    while (id != 0xE5) {
        io::SPI::SPIStatus status = readByte(REG_DEVID, id);
        log::LOGGER.log(log::Logger::LogLevel::DEBUG, "ADXL345 devid read: status=%d id=0x%02X\n\r", (int) status, id);
        time::wait(500);
    }

    // Put the device into measurement mode
    writeByte(REG_POWER_CTL, POWER_CTL_MEASURE_BIT);
}

io::SPI::SPIStatus ADXL345::readAccel(AccelAxis axis, uint16_t& accel) {
    uint8_t bytes[2];
    io::SPI::SPIStatus status = readBytes(REG_DATAX0 + axis, bytes, 2);

    // Combine the two bytes into the raw two's complement axis reading
    int16_t raw = (int16_t) ((bytes[1] << 8) | bytes[0]);

    // Convert raw register counts to centi-g (Gforce * 100)
    accel = (uint16_t) ((raw * 100) / G_SCALING_FACTOR);

    return status;
}

io::SPI::SPIStatus ADXL345::readByte(uint8_t reg, uint8_t& out) {
    return spi.readReg(deviceId, (reg & REG_MASK) | REG_READ_FLAG, &out);
}

io::SPI::SPIStatus ADXL345::readBytes(uint8_t reg, uint8_t* out, uint8_t len) {
    return spi.readReg(deviceId, (reg & REG_MASK) | REG_READ_FLAG | REG_MULTIBYTE_FLAG, out, len);
}

io::SPI::SPIStatus ADXL345::writeByte(uint8_t reg, uint8_t in) {
    return spi.writeReg(deviceId, reg & REG_MASK, in);
}

} // namespace rampup
