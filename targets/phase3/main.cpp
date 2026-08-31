/**
 * This is a simple example of reading data over SPI and printing it over UART.
 */
#include <core/io/GPIO.hpp>
#include <core/io/SPI.hpp>
#include <core/io/UART.hpp>
#include <core/manager.hpp>
#include <core/utils/log.hpp>
#include <core/utils/time.hpp>
#include <dev/ADXL345.hpp>

namespace io   = core::io;
namespace time = core::time;
namespace log  = core::log;

constexpr uint8_t DEVICE_COUNT = 1;

// Create array of 1 GPIO pointer for the chip select GPIO
io::GPIO* devices[DEVICE_COUNT];

int main() {
    // Initialize system
    core::platform::init();

    // Set up UART
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);
    log::LOGGER.setUART(&uart);
    log::LOGGER.setLogLevel(log::Logger::LogLevel::DEBUG);

    // Set up chip select GPIO and put in array
    devices[0] = &io::getGPIO<io::Pin::PA_9>(io::GPIO::Direction::OUTPUT);
    devices[0]->writePin(io::GPIO::State::HIGH);

    uart.printf("starting up\r\n");
    // Set up and configure SPI (<1 MHz, Mode 3, MSB first)
    io::SPI& spi = io::getSPI<io::Pin::SPI_SCK, io::Pin::SPI_MOSI, io::Pin::SPI_MISO>(devices, DEVICE_COUNT);
    spi.configureSPI(SPI_SPEED_500KHZ, io::SPI::SPIMode::SPI_MODE3, SPI_MSB_FIRST);
    uart.printf("SPI'ed\r\n");
    // Create ADXL345 instance
    rampup::ADXL345 adxl345(spi, 0);

    // Create a uint16_t array to store the three accelerations
    uint16_t accel[3];
    const rampup::ADXL345::AccelAxis axes[3] = {
        rampup::ADXL345::AccelAxis::X, rampup::ADXL345::AccelAxis::Y, rampup::ADXL345::AccelAxis::Z};

    uart.printf("starting loop\r\n");
    while (1) {
        // Read all 3 axes
        for (int i = 0; i < 3; i++) {
            adxl345.readAccel(axes[i], accel[i]);
        }

        // Print the accelerations in g-force to 2 decimal places
        for (int i = 0; i < 3; i++) {
            auto centiG = (int16_t) accel[i];
            uart.printf("%d.%02d g\t", centiG / 100, centiG % 100 < 0 ? -(centiG % 100) : centiG % 100);
        }
        uart.printf("\n\r");

        // Wait 1 s
        time::wait(1000);
    }
}
