/**
 * This is a simple example of GPIO usage
 */
#include <core/io/GPIO.hpp>
#include <core/manager.hpp>

namespace io = core::io;

int main() {
    // Initialize the EVT system
    core::platform::init();

    // Setup GPIO

    // Loop and toggle LED on and off; waiting .5 seconds after each toggle

}
