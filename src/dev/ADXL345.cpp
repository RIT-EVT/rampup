#include <core/utils/log.hpp>
#include <core/utils/time.hpp>

#include <dev/ADXL345.hpp>

namespace log  = core::log;
namespace time = core::time;

namespace rampup {

// Implementations here
ADXL345::ADXL345(io::SPI& spi, int id) : adxl_spi(spi), device_id(id) {
    uint8_t byte = 0;

    while (byte != 0xE5) {
        io::SPI::SPIStatus status = readByte(ADXL345_REG_DEVID, byte);
        if (status != io::SPI::SPIStatus::OK) {
            log::LOGGER.log(log::Logger::LogLevel::WARNING, "SPI readReg Error!");
            time::wait(500);
            continue;
        }

       log::LOGGER.log(log::Logger::LogLevel::DEBUG,"device ID: 0x%X, %s\n\r", byte, byte == 0xE5 ? "Verified!" : "Invalid!"); // should be 0xE5
    }

    // Start measurements
    writeByte(ADXL345_REG_POWER_CTL, ADXL345_REG_POWER_CTL_MEASURE_BIT);
}

io::SPI::SPIStatus ADXL345::readAccel(AccelAxis axis, int16_t& accel) {
    uint8_t bytes[2];
    io::SPI::SPIStatus status = readBytes(ADXL345_REG_DATAX0 + axis, bytes, 2);
    
    //combine the two bytes in order to make 1 int16 value
    accel = (bytes[1] << 8) | bytes[0]; 

    //convert register value to milli-Gforce
    accel = ((int32_t) accel * 1000) / G_SCALING_FACTOR;

    return status;
}

io::SPI::SPIStatus ADXL345::readByte(uint8_t reg, uint8_t& out) {
    return adxl_spi.readReg(device_id, (reg & ADXL345_REG_MASK) | ADXL345_REG_READ_FLAG, &out);
}

io::SPI::SPIStatus ADXL345::readBytes(uint8_t reg, uint8_t* out, uint8_t len) {
    return adxl_spi.readReg(
        device_id, (reg & ADXL345_REG_MASK) | ADXL345_REG_READ_FLAG | ADXL345_REG_MULTIBYTE_FLAG, out, len);
}

io::SPI::SPIStatus ADXL345::writeByte(uint8_t reg, uint8_t in) {
    return adxl_spi.writeReg(device_id, (reg & ADXL345_REG_MASK), in);
}

io::SPI::SPIStatus ADXL345::writeBytes(uint8_t reg, uint8_t* in, uint8_t len) {
    return adxl_spi.writeReg(device_id, (reg & ADXL345_REG_MASK) | ADXL345_REG_MULTIBYTE_FLAG, in, len);
}

} // namespace rampup
