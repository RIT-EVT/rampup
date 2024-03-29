/**
 * This is the main code running on the HUDL responsible for displaying
 * information that other boards that broadcast through the CAN network
 */
#include <Canopen/co_core.h>
#include <Canopen/co_tmr.h>
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
void canInterrupt(IO::CANMessage& message, void* priv) {
    EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>* queue =
        (EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>*) priv;

    if (queue != nullptr) {
        queue->append(message);
    }
}

///////////////////////////////////////////////////////////////////////////////
// CANopen specific Callbacks. Need to be defined in some location
///////////////////////////////////////////////////////////////////////////////
extern "C" void CONodeFatalError(void) {}

extern "C" void COIfCanReceive(CO_IF_FRM* frm) {}

extern "C" int16_t COLssStore(uint32_t baudrate, uint8_t nodeId) { return 0; }

extern "C" int16_t COLssLoad(uint32_t* baudrate, uint8_t* nodeId) { return 0; }

extern "C" void CONmtModeChange(CO_NMT* nmt, CO_MODE mode) {}

extern "C" void CONmtHbConsEvent(CO_NMT* nmt, uint8_t nodeId) {}

extern "C" void CONmtHbConsChange(CO_NMT* nmt, uint8_t nodeId, CO_MODE mode) {}

extern "C" int16_t COParaDefault(CO_PARA* pg) { return 0; }

extern "C" void COPdoTransmit(CO_IF_FRM* frm) {}

extern "C" int16_t COPdoReceive(CO_IF_FRM* frm) { return 0; }

extern "C" void COPdoSyncUpdate(CO_RPDO* pdo) {}

extern "C" void COTmrLock(void) {}

extern "C" void COTmrUnlock(void) {}

extern "C" void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef* hcan) {
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "RX Full");
}

int main() {
    // Initialize system
    EVT::core::platform::init();

    // Will store CANopen messages that will be populated by the EVT-core CAN
    // interrupt
    auto canOpenQueue = EVT::core::types::FixedQueue<CANOPEN_QUEUE_SIZE, IO::CANMessage>(true);

    // Initialize CAN, add an IRQ which will add messages to the queue above
    IO::CAN& can = IO::getCAN<IO::Pin::PA_12, IO::Pin::PA_11>();
    can.addIRQHandler(canInterrupt, reinterpret_cast<void*>(&canOpenQueue));

    // Initialize the timer
    DEV::Timerf3xx timer(TIM2, 160);

    //create the RPDO node
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

    hudl_spi.configureSPI(SPI_SPEED, SPI_MODE0, SPI_MSB_FIRST);

    rampup::HUDL hudl(regSelect, reset, hudl_spi);

    // Reserved memory for CANopen stack usage
    uint8_t sdoBuffer[1][CO_SDO_BUF_BYTE];
    CO_TMR_MEM appTmrMem[4];

    // Attempt to join the CAN network
    IO::CAN::CANStatus result = can.connect();

    //test that the board is connected to the can network
    if (result != IO::CAN::CANStatus::OK) {
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
    // Make drivers
    CO_IF_DRV canStackDriver;

    CO_IF_CAN_DRV canDriver;
    CO_IF_TIMER_DRV timerDriver;
    CO_IF_NVM_DRV nvmDriver;

    IO::getCANopenCANDriver(&can, &canOpenQueue, &canDriver);
    IO::getCANopenTimerDriver(&timer, &timerDriver);
    IO::getCANopenNVMDriver(&nvmDriver);

    canStackDriver.Can = &canDriver;
    canStackDriver.Timer = &timerDriver;
    canStackDriver.Nvm = &nvmDriver;

    //setup CANopen Node
    CO_NODE_SPEC canSpec = {
        .NodeId = rampup::HUDL::NODE_ID,
        .Baudrate = IO::CAN::DEFAULT_BAUD,
        .Dict = hudl.getObjectDictionary(),
        .DictLen = hudl.getObjectDictionarySize(),
        .EmcyCode = NULL,
        .TmrMem = appTmrMem,
        .TmrNum = 16,
        .TmrFreq = 1,
        .Drv = &canStackDriver,
        .SdoBuf = reinterpret_cast<uint8_t*>(&sdoBuffer[0]),
    };

    CO_NODE canNode;

    CONodeInit(&canNode, &canSpec);
    CONodeStart(&canNode);
    CONmtSetMode(&canNode.Nmt, CO_OPERATIONAL);

    time::wait(500);

    //print any CANopen errors
    log::LOGGER.log(log::Logger::LogLevel::DEBUG, "Error: %d\r\n", CONodeGetErr(&canNode));

    hudl.initLCD();

    while (true) {
        hudl.updateLCD();

        CONodeProcess(&canNode);
        // Update the state of timer based events
        COTmrService(&canNode.Tmr);
        // Handle executing timer events that have elapsed
        COTmrProcess(&canNode.Tmr);

        time::wait(10);
    }
}
