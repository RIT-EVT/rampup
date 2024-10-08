/**
 * This is the main code running on the HUDL responsible for displaying
 * information that other boards that broadcast through the CAN network.
 */
#include <EVT/dev/Timer.hpp>
#include <EVT/io/CANopen.hpp>
#include <EVT/io/GPIO.hpp>
#include <EVT/io/pin.hpp>
#include <EVT/manager.hpp>
#include <EVT/utils/log.hpp>
#include <EVT/utils/time.hpp>

#include <dev/HUDL.hpp>

namespace IO = EVT::core::IO;
namespace DEV = EVT::core::DEV;
namespace time = EVT::core::time;
namespace log = EVT::core::log;
using namespace std;

const uint32_t SPI_SPEED = SPI_SPEED_500KHZ;
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
void canInterrupt(IO::CANMessage& message, void* priv) {
    EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>* queue =
        (EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>*) priv;

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
    EVT::core::platform::init();

    // Initialize UART.
    IO::UART& uart = IO::getUART<IO::Pin::UART_TX, IO::Pin::UART_RX>(9600);
    log::LOGGER.setUART(&uart);

    // Set up chip select GPIO and put in array.
    IO::GPIO* devices[deviceCount];

    IO::GPIO& regSelect = IO::getGPIO<IO::Pin::PA_3>(EVT::core::IO::GPIO::Direction::OUTPUT);

    // HUDL 1.2
    IO::GPIO& reset = IO::getGPIO<IO::Pin::PB_7>(EVT::core::IO::GPIO::Direction::OUTPUT);
    devices[0] = &IO::getGPIO<IO::Pin::PB_12>(EVT::core::IO::GPIO::Direction::OUTPUT);

    devices[0]->writePin(IO::GPIO::State::HIGH);

    auto& hudl_spi = IO::getSPI<IO::Pin::SPI_SCK, IO::Pin::SPI_MOSI>(devices, deviceCount);

    IO::PWM& brightness = IO::getPWM<IO::Pin::PC_0>();
    brightness.setPeriod(1);
    brightness.setDutyCycle(100);

    hudl_spi.configureSPI(SPI_SPEED, IO::SPI::SPIMode::SPI_MODE0, SPI_MSB_FIRST);

    // Initialize the timer.
    DEV::Timerf3xx timer(TIM2, 160);

    // Create HUDL instance.
    rampup::HUDL hudl(regSelect, reset, hudl_spi);

    /************************************************************************************
     * Setup CAN configuration, this handles making drivers, applying settings. And 
     * generally creating the CANopen stack node which is the interface between the 
     * application (the code we write) and the physical CAN network.
     ***********************************************************************************/
    // Create queue to store CANopen messages that will be populated by the EVT-core CAN interrupt.
    auto canOpenQueue = EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>(true);

    // Initialize CAN, add an IRQ which will add messages to the queue above.
    IO::CAN& can = IO::getCAN<IO::Pin::PA_12, IO::Pin::PA_11>();
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
    IO::CAN::CANStatus result = can.connect();

    // Test that the board is connected to the can network.
    if (result != IO::CAN::CANStatus::OK) {
        log::LOGGER.log(log::Logger::LogLevel::ERROR, "Failed to connect to CAN network\r\n");
        return 1;
    } else {
        log::LOGGER.log(log::Logger::LogLevel::INFO, "Connected to CAN network\r\n");
    }

    // Initialize all the CANOpen drivers.
    IO::initializeCANopenDriver(&canOpenQueue, &can, &timer, &canStackDriver, &nvmDriver,
                                &timerDriver, &canDriver);

    // Initialize the CANOpen node we are using.
    IO::initializeCANopenNode(&canNode, &hudl, &canStackDriver, sdoBuffer, appTmrMem);

    // Set CAN mode.
    CONmtSetMode(&canNode.Nmt, CO_OPERATIONAL);

    time::wait(500);

    //print any CANopen errors.
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "Error: %d\r\n", CONodeGetErr(&canNode));

    hudl.initLCD();

    /**************************************************************************
     *                               Main loop
     *************************************************************************/
    while (true) {
        hudl.updateLCD();

        IO::processCANopenNode(&canNode);

        time::wait(10);
    }
}
