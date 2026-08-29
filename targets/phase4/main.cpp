/**
 * This is the main target for the rampup project.
 */

#include <co_core.h>

#include <core/io/CANopen.hpp>
#include <core/io/types/CANMessage.hpp>

namespace io = core::io;

///////////////////////////////////////////////////////////////////////////////
// EVT-core CAN callback and CAN setup. This will include logic to set
// aside CANopen messages into a specific queue
///////////////////////////////////////////////////////////////////////////////

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

int main() {
    // Initialize system

    // Set up UART

    // Set up I2C

    // Create TMP117 instance

    // Set up chip select GPIO and put in array

    // Set up and configure SPI (<1 MHz, Mode 3, MSB first)

    // Create ADXL345 instance

    // Create RampupBoard instance

    // Create queue to store CANopen messages that will be populated by the EVT-core CAN interrupt

    // Initialize CAN, add an IRQ which will add messages to the queue above

    // Initialize the timer

    // Reserved memory for CANopen stack usage

    // Attempt to join the CAN network

    ///////////////////////////////////////////////////////////////////////////
    // Setup CAN configuration, this handles making drivers, applying settings.
    // And generally creating the CANopen stack node which is the interface
    // between the application (the code we write) and the physical CAN network
    ///////////////////////////////////////////////////////////////////////////
    // Make drivers, then build and start the CANopen node from the
    // RampupBoard instance (see docs/CANOPEN_GUIDE.md and
    // targets/hudl/main.cpp for a fully worked example of this pattern)

    while (1) {
        // Run rampup board process

        // Process incoming CAN messages and timer events (io::processCANopenNode(&canNode))

        // Wait 100 ms
    }
}
