/**
 * This is a simple example of ADCs
 */
#include <core/io/UART.hpp>
#include <core/io/ADC.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>
#include <core/utils/log.hpp>

namespace io = core::io;
namespace time = core::time;

int main() {
    // Start up the system
    core::platform::init();

    // Set up the logger to catch errors in ADC creation
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);
    core::log::LOGGER.setUART(&uart);
    core::log::LOGGER.setLogLevel(core::log::Logger::LogLevel::INFO);

    // Set up the ADC device
    io::ADC& throttle = io::getADC<io::Pin::PA_0, io::ADCPeriph::ONE>();

    while (true) {
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, "--------------------");
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, "ADC0 : %d mV", static_cast<uint32_t>(throttle.read() * 1000));
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, "ADC0: %d%%", static_cast<uint32_t>(throttle.readPercentage() * 100));
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, "ADC0 raw: %d", throttle.readRaw());
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, "--------------------\r\n");
        // Clear the screen
        core::log::LOGGER.log(core::log::Logger::LogLevel::INFO, " \033[2J\033[1;1H");
        time::wait(10);
    }
}
