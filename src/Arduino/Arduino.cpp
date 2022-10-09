/*
    Arduino.cpp
    Zachary lineman
    10/3/22
    
    =================
    DESCRIPTION
    =================
*/

#include "Arduino.hpp"

namespace IO = EVT::core::IO;

Arduino::Arduino(IO::I2C &i2C, IO::UART &uart) : i2c(i2C), uart(uart) { }

uint8_t Arduino::readRegister(uint8_t reg) {
    return i2c.readReg(ARDUINO_ADDRESS, reg);
}

void Arduino::logAllBasicData() {
    uart.printf("\n\rID: 0x%X\n\r", readRegister(ID_REGISTER));
    uart.printf("\n\rLSTD: 0x%X\n\r", readRegister(LSTD_REGISTER));
    uart.printf("\n\rMSTD: 0x%X\n\r", readRegister(MSTD_REGISTER));
    uart.printf("\n\rLSVD: 0x%X\n\r", readRegister(LSVD_REGISTER));
    uart.printf("\n\rMSVD: 0x%X\n\r", readRegister(MSVD_REGISTER));
}



