/**
 * This is the main target for the rampup phase 4 project.
 */

#include <core/io/CANopen.hpp>
#include <core/io/types/CANMessage.hpp>

namespace io = core::io;

/****************************************************************************************
 * EVT-core CAN callback and CAN setup. This will include logic to set aside CANopen 
 * messages into a specific queue.
***************************************************************************************/

/**
 * Interrupt handler to get CAN messages. A function pointer to this function
 * will be passed to the EVT-core CAN interface which will in turn call this
 * function each time a new CAN message comes in.
 *
 * NOTE: For this sample, every non-extended (so 11 bit CAN IDs) will be
 * assumed to be intended to be passed as a CANopen message.
 *
 * @param message[in] The passed in CAN message that was read.
 */
void canInterrupt(io::CANMessage& message, void* priv) {
    auto* queue = (core::types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage>*) priv;
    if (queue != nullptr)
        queue->append(message);
}

// Create array of 1 GPIO pointer for the chip select GPIO

/****************************************************************************************
 * Main program. This includes all the logic to initalized the necessary hardware and run
 * the main processing loop.
 ***************************************************************************************/
int main() {
    // Initialize system.

    // Set up UART.

    // Set up I2C.

    // Set up chip select GPIO and put in array.

    // Set up and configure SPI (<10 MHz, Mode 0, MSB first).

    // Initialize the timer.

    // Create TMP117 instance.

    // Create MAX22530 instance.

    // Create RampupBoard instance.

    /************************************************************************************
     * Setup CAN configuration, this handles making drivers, applying settings. And 
     * generally creating the CANopen stack node which is the interface between the 
     * application (the code we write) and the physical CAN network.
     ***********************************************************************************/
    // Create queue to store CANopen messages that will be populated by the EVT-core CAN interrupt.

    // Initialize CAN, add an IRQ which will add messages to the queue above.

    // Reserved memory for CANopen stack usage.

    // Reserve CAN drivers.

    // Reserve CAN node.

    // Attempt to join the CAN network.

    // Initialize all the CANOpen drivers.

    // Initialize the CANOpen node.

    // Set the node to operational mode.

    /**************************************************************************
     *                               Main loop
     *************************************************************************/
    while (1) {
        // Run rampup board process.

        // Process CAN messages.

        // Wait 100 ms.
    }
}
