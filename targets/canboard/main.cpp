/**
 * This is the main code running on the HUDL responsible for displaying
 * information that other boards that broadcast through the CAN network.
 */
#include <core/dev/Timer.hpp>
#include <core/io/CAN.hpp>
#include <core/io/GPIO.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>
#include <core/utils/log.hpp>
#include <core/utils/time.hpp>

#include <dev/HUDL.hpp>

namespace io   = core::io;
namespace dev  = core::dev;
namespace time = core::time;
namespace log  = core::log;

#define MY_ID                    2
#define MY_DATA_LENGTH           4
#define OTHER_BOARD_ID           1
#define OTHER_MESSAGE_SIZE_BYTES 4

using namespace std;

constexpr io::Pin CAN_TX_PIN = io::Pin::PA_12;
constexpr io::Pin CAN_RX_PIN = io::Pin::PA_11;

uint8_t my_payload[MY_DATA_LENGTH] = {0xBE, 0xEF, 0xEE, 0xEF};
io::CANMessage responseMessage     = io::CANMessage(MY_ID, MY_DATA_LENGTH, my_payload, false);

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

// create a can interrupt handler
void canInterrupt(io::CANMessage& message, void* priv) {
    core::types::FixedQueue<CAN_MESSAGE_QUEUE_SIZE, io::CANMessage>* queue =
        (core::types::FixedQueue<CAN_MESSAGE_QUEUE_SIZE, io::CANMessage>*) priv;

    if (queue != nullptr) {
        queue->append(message);
    }
}

/****************************************************************************************
 * Main program. This includes all the logic to initalized the necessary hardware and run
 * the main processing loop.
 ***************************************************************************************/
int main() {
    // Initialize system.
    core::platform::init();

    // Initialize UART.
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);
    log::LOGGER.setUART(&uart);

    // Initialize the timer.
    dev::Timerf3xx timer(TIM2, 160);

    /************************************************************************************
     * Setup CAN configuration, this handles making drivers, applying settings. And
     * generally creating the CANopen stack node which is the interface between the
     * application (the code we write) and the physical CAN network.
     ***********************************************************************************/

    // Create the CAN queue
    core::types::FixedQueue<CAN_MESSAGE_QUEUE_SIZE, io::CANMessage> canQueue =
        core::types::FixedQueue<CAN_MESSAGE_QUEUE_SIZE, io::CANMessage>();

    // Initialize CAN, add an IRQ which will add messages to the queue above.

    io::CAN& can = io::getCAN<CAN_TX_PIN, CAN_RX_PIN>();
    can.addIRQHandler(canInterrupt, reinterpret_cast<void*>(&canQueue));

    // Attempt to join the CAN network.
    io::CAN::CANStatus result = can.connect();

    // Test that the board is connected to the can network.
    if (result != io::CAN::CANStatus::OK) {
        log::LOGGER.log(log::Logger::LogLevel::ERROR, "Failed to connect to CAN network\r\n");
        return 1;
    } else {
        log::LOGGER.log(log::Logger::LogLevel::INFO, "Connected to CAN network\r\n");
    }

    time::wait(500);

    /**************************************************************************
     *                               Main loop
     *************************************************************************/

    io::CANMessage message = io::CANMessage();
    while (true) {

        // pop the message out of the queue
        canQueue.pop(&message);

        uint8_t* payload;
        uint32_t expandedPayload = 0;

        // make sure this message is one we care about
        if (message.getId() == OTHER_BOARD_ID && message.getDataLength() == OTHER_MESSAGE_SIZE_BYTES) {
            payload = message.getPayload();

            for (uint8_t i = 0; i < OTHER_MESSAGE_SIZE_BYTES; i++) {
                expandedPayload <<= 8;
                expandedPayload |= payload[i];
            }

            if (expandedPayload == 0xDEADBEEF) {
                can.transmit(responseMessage);
            }
        }

        time::wait(10);
    }
}
