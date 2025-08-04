/**
 * This is a simple example of reading data over I2C and printing it over UART.
 */
#include <include/dev/TMP117.hpp>
#include <EVT/io/I2C.hpp>
#include <EVT/io/UART.hpp>
#include <EVT/manager.hpp>

using namespace std;
namespace io = core::io;
namespace time = core::time;

int main() {
    // Initialize system

    // Set up UART

    // Set up I2C

    // Create TMP117 instance

    // Create a variable to hold temperature data

    while (1) {
        // Read temperature

        // Print the temperature as normal celsius (2534 centi-Celsius => 25.34 Celsius)

        // Wait 1 s

    }
}
