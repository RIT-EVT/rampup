/**
 * This is the main target for the rampup phase 7 project.
 */

#include <core/io/CANopen.hpp>
#include <core/io/types/CANMessage.hpp>
#include <core/manager.hpp>
#include <RampupBoard.hpp>

namespace io = core::io;
namespace types = core::types;
namespace time = core::time;

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

// I2C and SPI variables
constexpr uint8_t deviceCount = 1;
constexpr uint8_t i2cSlaveAddress = 0x48;
constexpr uint32_t SPI_SPEED   = SPI_SPEED_500KHZ; // 500KHz
constexpr uint8_t DEVICE_COUNT = 1;

// Create array of 1 GPIO pointer for the chip select GPIO
io::GPIO* devices[deviceCount];

/****************************************************************************************
 * Main program. This includes all the logic to initialize the necessary hardware and run
 * the main processing loop.
s ***************************************************************************************/
int main() {
    // Initialize system.
    core::platform::init();

    // Set up UART.
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);

    // Set up I2C.
    io::I2C& i2c = io::getI2C<io::Pin::PB_8, io::Pin::PB_9>();

    // Set up chip select GPIO and put in array.
    uart.printf("\n\r Setting up GPIO");
    devices[0] = &io::getGPIO<io::Pin::SPI_CS>(io::GPIO::Direction::OUTPUT);
    devices[0]->writePin(io::GPIO::State::HIGH);

    // Set up and configure SPI (<10 MHz, Mode 0, MSB first).
    io::SPI& spi = io::getSPI<io::Pin::SPI_SCK, io::Pin::SPI_MOSI, io::Pin::SPI_MISO>(devices, DEVICE_COUNT);
    spi.configureSPI(SPI_SPEED, io::SPI::SPIMode::SPI_MODE3, SPI_MSB_FIRST);

    // Initialize the timer.

    // Create TMP117 instance.
    rampup::TMP117 tmp(i2c, i2cSlaveAddress);

    // Create MAX22530 instance.
    rampup::ADXL345 adxl345(spi, 0);

    // Create RampupBoard instance.
    rampup::RampupBoard rampupBoard(adxl345, tmp);

    /************************************************************************************
     * Setup CAN configuration, this handles making drivers, applying settings. And
     * generally creating the CANopen stack node which is the interface between the
     * application (the code we write) and the physical CAN network.
     ***********************************************************************************/
    // Create queue to store CANopen messages that will be populated by the EVT-core CAN interrupt.
    types::FixedQueue<CANOPEN_QUEUE_SIZE, io::CANMessage> canOpenQueue;

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

    core::dev::Timerf3xx timer(TIM2, 100);

    // Initialize all the CANOpen drivers.
    io::initializeCANopenDriver(&canOpenQueue, &can, &timer, &canStackDriver, &nvmDriver, &timerDriver, &canDriver);

    // Initialize the CANOpen node.
    io::initializeCANopenNode(&canNode, &rampupBoard, &canStackDriver, sdoBuffer, appTmrMem);

    // Set the node to operational mode.
    CONmtSetMode(&canNode.Nmt, CO_OPERATIONAL);

    /**************************************************************************
     *                               Main loop
     *************************************************************************/
    while (1) {
        // Run rampup board process.
        rampupBoard.process();
        // Process CAN messages.
        io::processCANopenNode(&canNode);
        // Wait 100 ms.
        time::wait(100);
    }
}
