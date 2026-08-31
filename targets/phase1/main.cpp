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
    char userInput1[10];
    char userInput2[10];

    while (1) {
        // Read user input
        uart.printf("\n\rEnter first number: ");
        uart.gets(userInput1, 10);

        uart.printf("\n\rEnter second number: ");
        uart.gets(userInput2, 10);

        // Convert the two character arrays to uint64_t
        uint64_t num1 = atoi(userInput1);
        uint64_t num2 = atoi(userInput2);

        // Output the sum of the two numbers
        uint64_t num3 = num1 + num2;
        uart.printf("\n\r%u\n\r", num3);
    }
}
