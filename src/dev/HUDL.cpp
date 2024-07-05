/**
* This is a basic sample of using the UART module. The program provides a
* basic echo functionality where the uart will write back whatever the user
* enters.
*/

// clang-format off
#include <EVT/dev/LCD.hpp>
#include <EVT/io/GPIO.hpp>
#include <EVT/io/SPI.hpp>
#include <EVT/utils/log.hpp>
#include <dev/HUDL.hpp>

#include <cstdio>
#include <cstring>
// clang-format on

namespace IO = EVT::core::IO;
namespace DEV = EVT::core::DEV;
namespace log = EVT::core::log;

namespace rampup {

HUDL::HUDL(IO::GPIO& reg_select, IO::GPIO& reset, IO::SPI& spi) : lcd(DEV::LCD(reg_select, reset, spi)) {}

void HUDL::initLCD() {
    lcd.initLCD();
    lcd.clearLCD();
    lcd.setEntireScreenBitMap(evtBitMap);
    EVT::core::time::wait(2000);
    lcd.clearLCD();

    // The segment titles
    char* titles[9] = {
        "Volt 1",
        "Volt 2",
        "Volt 3",
        "Volt 4",
        "Temp",
        "Not Set",
        "Not Set",
        "Not Set",
        "Not Set",
    };
    lcd.setDefaultSections(titles);
    lcd.displaySectionHeaders();
}

void HUDL::updateLCD() {
    for (int x = 0; x < 4; x++) {
        char voltage[9];
        std::sprintf(voltage, "%d", voltages[x]);
        lcd.setTextForSection(x, voltage);
    }

    char temp[9];
    std::sprintf(temp, "%d", temperature);
    lcd.setTextForSection(4, temp);
}
}// namespace rampup
