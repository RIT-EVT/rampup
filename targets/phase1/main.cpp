/**
 * This is a simple example of GPIO usage
 */
#include <core/manager.hpp>

namespace io = core::io;
namespace time = core::time;

int main() {
    // Initialize the EVT system
    core::platform::init();

    // Setup GPIO pin for LED
    io::GPIO& led = io::getGPIO<io::Pin::PB_13>(); // Might be PA_5 if on f446 board

    // variable to store state in
    io::GPIO::State state = io::GPIO::State::HIGH;

    // Loop and toggle LED on and off; waiting .5 seconds after each toggle
    while (true) {
        // Toggle the LED on/off
        led.writePin(state);

        // Swap state to other option
        if (state == io::GPIO::State::HIGH) {
            state = io::GPIO::State::LOW;
        } else {
            state = io::GPIO::State::HIGH;
        }

        // Wait .5 seconds
        time::wait(500);
    }
}
