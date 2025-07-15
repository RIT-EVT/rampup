/**
 * This is the main code running on the HUDL responsible for displaying
 * information that other boards that broadcast through the CAN network.
 */
#include <core/dev/Timer.hpp>
#include <core/io/CANopen.hpp>
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

using namespace std;

const uint32_t SPI_SPEED  = SPI_SPEED_500KHZ;
const uint8_t deviceCount = 1;

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
    core::types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage>* queue =
        (core::types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage>*) priv;

    if (queue != nullptr) {
        queue->append(message);
    }
}

extern "C" void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef* hcan) {
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "RX Full");
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

    // Set up chip select GPIO and put in array.
    io::GPIO* devices[deviceCount];

    io::GPIO& regSelect = io::getGPIO<io::Pin::PA_3>(core::io::GPIO::Direction::OUTPUT);

    // HUDL 1.2
    io::GPIO& reset = io::getGPIO<io::Pin::PB_7>(core::io::GPIO::Direction::OUTPUT);

    devices[0] = &io::getGPIO<io::Pin::PB_12>(core::io::GPIO::Direction::OUTPUT);
    devices[0]->writePin(io::GPIO::State::HIGH);

    auto& hudl_spi = io::getSPI<io::Pin::SPI_SCK, io::Pin::SPI_MOSI>(devices, deviceCount);

    io::PWM& brightness = io::getPWM<io::Pin::PC_0>();
    brightness.setPeriod(1);
    brightness.setDutyCycle(100);

    hudl_spi.configureSPI(SPI_SPEED, io::SPI::SPIMode::SPI_MODE0, SPI_MSB_FIRST);

    // Initialize the timer.
    dev::Timerf3xx timer(TIM2, 160);

    // Create HUDL instance.
    rampup::HUDL hudl(regSelect, reset, hudl_spi);

    /************************************************************************************
     * Setup CAN configuration, this handles making drivers, applying settings. And
     * generally creating the CANopen stack node which is the interface between the
     * application (the code we write) and the physical CAN network.
     ***********************************************************************************/
    // Create queue to store CANopen messages that will be populated by the EVT-core CAN interrupt.
    auto canOpenQueue = core::types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage>(true);

    // Initialize CAN, add an IRQ which will add messages to the queue above.
    io::CAN& can = io::getCAN<io::Pin::PA_12, io::Pin::PA_11>();
    can.addIRQHandler(canInterrupt, reinterpret_cast<void*>(&canOpenQueue));

    // Reserved memory for CANopen stack usage.
    uint8_t sdoBuffer[CO_SSDO_N * CO_SDO_BUF_BYTE];
    CO_TMR_MEM appTmrMem[16];

    // Reserve CAN drivers.
    CO_IF_DRV canStackDriver;

    CO_IF_CAN_DRV canDriver;
    CO_IF_TIMER_DRV timerDriver;
    CO_IF_NVM_DRV nvmDriver;

    // Reserve CAN node.
    CO_NODE canNode;

    // Attempt to join the CAN network.
    io::CAN::CANStatus result = can.connect();

    // Test that the board is connected to the can network.
    if (result != io::CAN::CANStatus::OK) {
        log::LOGGER.log(log::Logger::LogLevel::ERROR, "Failed to connect to CAN network\r\n");
        return 1;
    } else {
        log::LOGGER.log(log::Logger::LogLevel::INFO, "Connected to CAN network\r\n");
    }

    // Initialize all the CANOpen drivers.
    io::initializeCANopenDriver(&canOpenQueue, &can, &timer, &canStackDriver, &nvmDriver, &timerDriver, &canDriver);

    // Initialize the CANOpen node we are using.
    io::initializeCANopenNode(&canNode, &hudl, &canStackDriver, sdoBuffer, appTmrMem);

    // Set CAN mode.
    CONmtSetMode(&canNode.Nmt, CO_OPERATIONAL);

    time::wait(500);

    // print any CANopen errors.
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "Error: %d\r\n", CONodeGetErr(&canNode));

    hudl.initLCD();

    /**************************************************************************
     *                               Main loop
     *************************************************************************/
    while (true) {
        hudl.updateLCD();

        io::processCANopenNode(&canNode);

        time::wait(10);
    }
}
