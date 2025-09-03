#include <RampupBoard.hpp>

namespace rampup {

// Implementations here

RampupBoard::RampupBoard(ADXL345 adxl345, TMP117 tmp) : adxl345(adxl345), tmp(tmp) {}

void RampupBoard::process() {
    // io::SPI::SPIStatus maxReadStatus = max.readVoltages(voltages);
    io::I2C::I2CStatus tempReadStatus = tmp.readTemp(temp);
}

}
