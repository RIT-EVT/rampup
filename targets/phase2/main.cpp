/**
 * This is a simple example of taking user input and printing output over UART.
 */
#include <core/io/UART.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>

namespace io = core::io;

int main() {
    // Initialize system
    core::platform::init();

    // Set up UART
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);

    // Declare two arrays of characters to store user input
    char userInput1[100];
    char userInput2[100];

    while (1) {
        // Read user input
        uart.printf("\n\rEnter first number: ");
        uart.gets(userInput1, 100);

        uart.printf("\n\rEnter second number: ");
        uart.gets(userInput2, 100);

        // Convert the two character arrays to uint64_t
        uint64_t num1 = static_cast<uint64_t>(userInput1[0] - '0');
        uint64_t num2 = static_cast<uint64_t>(userInput2[0] - '0');

        // Output the sum of the two numbers
        uint64_t num3 = num1 + num2;
        uart.printf("\n\r%u\n\r", num3);
    }
}
