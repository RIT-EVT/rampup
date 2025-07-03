// clang-format off
#include <dev/HUDL.hpp>
#include <core/utils/log.hpp>

#include <cstdio>
// clang-format on

namespace io = core::io;
namespace dev = core::dev;
namespace log = core::log;

namespace rampup {

HUDL::HUDL(io::GPIO& reg_select, io::GPIO& reset, io::SPI& spi) : lcd(dev::LCD(reg_select, reset, spi)) {}

void HUDL::initLCD() {
    lcd.initLCD();
    lcd.clearLCD();
    lcd.setEntireScreenBitMap(evtBitMap);
    core::time::wait(2000);
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
