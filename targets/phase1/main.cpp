/**
 * This is a simple example of GPIO usage
 */
#include <core/manager.hpp>
#include <core/io/GPIO.hpp>

namespace io = core::io;

int main() {
    // Initialize the EVT system
    core::platform::init();

    // Setup GPIO
    io::GPIO& gpio = io::getGPIO<io::Pin::PA_5>(io::GPIO::Direction::OUTPUT, io::GPIO::Pull::PULL_DOWN);

    io::GPIO::State state = io::GPIO::State::HIGH;

    // Loop and toggle LED on and off; waiting .5 seconds after each toggle
    while (1) {
        // Update GPIO output
        gpio.writePin(state);

        // Swap state HIGH/LOW
        if (state == io::GPIO::State::HIGH) {
            state = io::GPIO::State::LOW;
        } else {
            state = io::GPIO::State::HIGH;
        }

        // Wait .5 seconds
        core::time::wait(500);
    }
}
