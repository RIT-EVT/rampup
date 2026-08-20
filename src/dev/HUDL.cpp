/**
 * Implementation of the HUDL device: an LCD display plus the object
 * dictionary used to receive temperature and voltage data over CAN.
 */

// clang-format off
#include <core/dev/LCD.hpp>
#include <core/io/GPIO.hpp>
#include <core/io/SPI.hpp>
#include <core/utils/log.hpp>
#include <core/utils/time.hpp>
#include <dev/HUDL.hpp>

#include <cstdio>
#include <cstring>
// clang-format on

namespace io  = core::io;
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

CO_OBJ_T* HUDL::getObjectDictionary() {
    return &objectDictionary[0];
}

uint8_t HUDL::getNumElements() {
    return OBJECT_DICTIONARY_SIZE;
}

uint8_t HUDL::getNodeID() {
    return NODE_ID;
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
} // namespace rampup
