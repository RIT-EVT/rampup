/**
 * This is a simple example of GPIO usage
 */
#include <core/manager.hpp>

namespace io = core::io;
namespace time = core::time;

int main() {
    // Initialize system
    core::platform::init();

    // Setup GPIO pin for LED
    io::GPIO& led = io::getGPIO<io::Pin::PA_1>();

    // variable to store state in
    io::GPIO::State state = io::GPIO::State::HIGH;

    // Loop infinitely while toggling the LED on/off
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
