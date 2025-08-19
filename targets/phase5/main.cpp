/**
 * This is a simple example of ADCs
 */

// Add all the necessary include statements here
#include <core/manager.hpp>

namespace io = core::io;
namespace time = core::time;

int main() {
    // Start up the system
    core::platform::init();

    // Set up UART at a baudrate of 9600

    // Set up the logger at the INFO level

    // Set up the ADC device

    // The main loop
    while (true) {
        // Print out the voltage value, voltage percentage, and raw data with the logger

        // Wait for 500 milliseconds

        // Reset the screen and return the cursor to the top (use the escape sequence: "\033[2J\033[H")

    }
}
