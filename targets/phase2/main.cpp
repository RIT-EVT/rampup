/**
 * This is a simple example of reading data over I2C and printing it over UART.
 */
#include <core/io/I2C.hpp>
#include <core/io/UART.hpp>
#include <core/manager.hpp>
#include <core/utils/time.hpp>
#include <dev/TMP117.hpp>

namespace io   = core::io;
namespace time = core::time;

// Known from the click board and the ADD0 pin table in the datasheet
constexpr uint8_t i2cSlaveAddress = 0x48;

int main() {
    // Initialize system
    core::platform::init();

    // Set up UART
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);

    uart.printf("starting up\r\n");
    // Set up I2C
    io::I2C& i2c = io::getI2C<io::Pin::PB_8, io::Pin::PB_9>();
    uart.printf("i2c'ed\r\n");

    // Create TMP117 instance
    rampup::TMP117 tmp(i2c, i2cSlaveAddress);

    uart.printf("starting loop\r\n");
    while (1) {
        // Read temperature
        uint16_t temperature;
        tmp.readTemp(temperature);

        // Print temperature (25348 milli-Celsius => 25.348 Celsius)
        uart.printf("Temp: %d.%d Celsius\n\r", temperature / 1000, temperature % 1000);

        // Wait 1 s
        time::wait(1000);
    }
}
