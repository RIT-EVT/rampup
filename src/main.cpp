/**
 * This is a basic sample of using the UART module. The program provides a
 * basic echo functionality where the uart will write back whatever the user
 * enters.
 */
#include <EVT/io/manager.hpp>
#include <EVT/utils/time.hpp>
#include "Arduino/Arduino.hpp"

namespace IO = EVT::core::IO;
namespace time = EVT::core::time;

int main() {
    // Initialize system
    IO::init();

    // Setup UART
    IO::UART& uart = IO::getUART<IO::Pin::UART_TX, IO::Pin::UART_RX>(9600);

    // Setup i2c Communication
    IO::I2C& i2c = IO::getI2C<IO::Pin::PB_8, IO::Pin::PB_9>();

    Arduino temperatureController = Arduino(i2c, uart);

    while (1) {
        // Read user input
        temperatureController.logAllBasicData();

        time::wait(1000);
    }
}
