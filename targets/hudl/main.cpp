/**
 * This is the main code running on the HUDL responsible for displaying
 * information that other boards that broadcast through the CAN network
 */
#include <co_core.h>
#include <core/io/CANopen.hpp>
#include <core/io/GPIO.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>
#include <core/utils/log.hpp>
#include <core/utils/time.hpp>

#include <dev/HUDL.hpp>

namespace io = core::io;
namespace dev = core::dev;
namespace time = core::time;
namespace log = core::log;

const uint32_t SPI_SPEED = SPI_SPEED_500KHZ;
const uint8_t deviceCount = 1;

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

int main() {
    // Initialize system
    core::platform::init();

    // Will store CANopen messages that will be populated by the EVT-core CAN
    // interrupt
    auto canOpenQueue = core::types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage>(true);

    // Initialize CAN, add an IRQ which will add messages to the queue above
    io::CAN& can = io::getCAN<io::Pin::PA_12, io::Pin::PA_11>();
    can.addIRQHandler(canInterrupt, reinterpret_cast<void*>(&canOpenQueue));

    // Initialize the timer
    dev::Timer& timer = dev::getTimer<dev::MCUTimer::Timer2>(160);

    //create the RPDO node
    io::GPIO* devices[deviceCount];

    io::GPIO& regSelect = io::getGPIO<io::Pin::PA_3>(io::GPIO::Direction::OUTPUT);

    // HUDL 1.2
    io::GPIO& reset = io::getGPIO<io::Pin::PB_7>(io::GPIO::Direction::OUTPUT);
    devices[0] = &io::getGPIO<io::Pin::PB_12>(io::GPIO::Direction::OUTPUT);

    devices[0]->writePin(io::GPIO::State::HIGH);

    auto& hudl_spi = io::getSPI<io::Pin::SPI_SCK, io::Pin::SPI_MOSI>(devices, deviceCount);

    io::PWM& brightness = io::getPWM<io::Pin::PC_0>();
    brightness.setPeriod(1);
    brightness.setDutyCycle(100);

    hudl_spi.configureSPI(SPI_SPEED, io::SPI::SPIMode::SPI_MODE0, SPI_MSB_FIRST);

    rampup::HUDL hudl(regSelect, reset, hudl_spi);

    // Reserved memory for CANopen stack usage
    uint8_t sdoBuffer[CO_SSDO_N * CO_SDO_BUF_BYTE];
    CO_TMR_MEM appTmrMem[16];

    // Attempt to join the CAN network
    io::CAN::CANStatus result = can.connect();

    //test that the board is connected to the can network
    if (result != io::CAN::CANStatus::OK) {
        log::LOGGER.log(log::Logger::LogLevel::ERROR, "Failed to connect to CAN network\r\n");
        return 1;
    } else {
        log::LOGGER.log(log::Logger::LogLevel::INFO, "Connected to CAN network\r\n");
    }

    ///////////////////////////////////////////////////////////////////////////
    // Setup CAN configuration, this handles making drivers, applying settings.
    // And generally creating the CANopen stack node which is the interface
    // between the application (the code we write) and the physical CAN network
    ///////////////////////////////////////////////////////////////////////////
    CO_IF_DRV canStackDriver;
    CO_IF_CAN_DRV canDriver;
    CO_IF_TIMER_DRV timerDriver;
    CO_IF_NVM_DRV nvmDriver;

    io::initializeCANopenDriver(&canOpenQueue, &can, &timer, &canStackDriver, &nvmDriver, &timerDriver, &canDriver);

    CO_NODE canNode;
    io::initializeCANopenNode(&canNode, &hudl, &canStackDriver, sdoBuffer, appTmrMem);

    CONmtSetMode(&canNode.Nmt, CO_OPERATIONAL);

    time::wait(500);

    //print any CANopen errors
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "Error: %d\r\n", CONodeGetErr(&canNode));

    hudl.initLCD();

    while (true) {
        hudl.updateLCD();

        io::processCANopenNode(&canNode);

        time::wait(10);
    }
}
