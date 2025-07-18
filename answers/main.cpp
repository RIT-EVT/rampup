/**
 * This is a simple example of reading data over I2C and printing it over UART.
 */
#include "dev/TMP117.hpp"
#include <EVT/io/I2C.hpp>
#include <EVT/io/UART.hpp>
#include <EVT/manager.hpp>

using namespace std;
namespace IO = EVT::core::IO;
namespace time = EVT::core::time;
constexpr uint8_t i2cSlaveAddress = 0x48;

int main() {
    // Initialize system
    EVT::core::platform::init();

    // Set up UART
    IO::UART& uart = IO::getUART<IO::Pin::UART_TX, IO::Pin::UART_RX>(9600);

    // Set up I2C
    IO::I2C& i2c = IO::getI2C<IO::Pin::PB_8, IO::Pin::PB_9>();

    // Create TMP117 instance
    rampup::TMP117 tmp(i2c, i2cSlaveAddress);

    uint16_t temperature;

    while (1) {
        // Read temperature
        tmp.readTemp(temperature);

        // Print temperature
        uart.printf("Temp: %d\n\r", temperature);

        // Wait 1 s
        time::wait(1000);
    }
}
