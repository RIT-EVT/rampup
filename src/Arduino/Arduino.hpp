/*
    Arduino.hpp
    Zachary lineman
    10/3/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef RAMPUP_ARDUINO_HPP
#define RAMPUP_ARDUINO_HPP

#include <EVT/io/manager.hpp>
#include <EVT/io/pin.hpp>
#include <EVT/io/I2C.hpp>

class Arduino {
    static constexpr uint8_t ARDUINO_ADDRESS = 0x04;
    static constexpr uint8_t ID_REGISTER = 0x00;
    static constexpr uint8_t LSTD_REGISTER = 0x01;
    static constexpr uint8_t MSTD_REGISTER = 0x02;
    static constexpr uint8_t LSVD_REGISTER = 0x03;
    static constexpr uint8_t MSVD_REGISTER = 0x04;

    EVT::core::IO::I2C& i2c;
    EVT::core::IO::UART& uart;

    uint8_t readRegister(uint8_t reg);

public:
    Arduino(EVT::core::IO::I2C &i2C, EVT::core::IO::UART &uart);

    void logAllBasicData();
};


#endif //RAMPUP_ARDUINO_HPP
