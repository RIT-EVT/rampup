/**
 * This is a simple example of reading data over I2C and printing it over UART.
 */
#include <dev/TMP117.hpp>
#include <core/io/I2C.hpp>
#include <core/io/UART.hpp>
#include <core/manager.hpp>

using namespace std;
namespace io = core::io;
namespace time = core::time;

// This is known by looking at the click board and table in datasheet, depends on what the ADD0 pin is connected to (GND, 3.3V, SDA, SCL)
constexpr uint8_t i2cSlaveAddress = 0x48;

int main() {
    // Initialize system
    core::platform::init();

    // Set up UART
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);

    // Set up I2C
    io::I2C& i2c = io::getI2C<io::Pin::PB_8, io::Pin::PB_9>();

    // Create TMP117 instance
    rampup::TMP117 tmp(i2c, i2cSlaveAddress);

    // Create a variable to hold temperature data
    uint16_t temperature;

    while (1) {
        // Read temperature
        io::I2C::I2CStatus status = tmp.readTemp(temperature);

        // Print temperature as normal celsius (2534 centi-Celsius => 25.34 Celsius)
        uart.printf("Temp: %d.%d Celsius\n\r", temperature / 100, temperature % 100);

        // Wait 1 s
        time::wait(1000);
    }
}
