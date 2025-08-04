/**
 * This is a simple example of reading data over I2C and printing it over UART.
 */
#include <dev/TMP117.hpp>
#include <EVT/io/I2C.hpp>
#include <EVT/io/UART.hpp>
#include <EVT/manager.hpp>

using namespace std;
namespace io = core::io;
namespace time = core::time;

// This is known by looking at the click board and table in datasheet, depends on what the ADD0 pin is connected to (GND, 3.3V, SDA, SCL)
constexpr uint8_t i2cSlaveAddress = 0x48;

int main() {
    // Initialize system
    EVT::core::platform::init();

    // Set up UART
    io::UART& uart = IO::getUART<IO::Pin::UART_TX, IO::Pin::UART_RX>(9600);

    // Set up I2C

    // Create TMP117 instance

    // Create a variable to hold temperature data

    while (1) {
        // Read temperature

        // Print the temperature as normal celsius (2534 centi-Celsius => 25.34 Celsius)

        // Wait 1 s

    }
}
