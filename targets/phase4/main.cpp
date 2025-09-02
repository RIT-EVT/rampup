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

constexpr uint32_t SPI_SPEED   = SPI_SPEED_500KHZ; // 500KHz
constexpr uint8_t DEVICE_COUNT = 1;

int main() {
    // Initialize system
    core::platform::init();

    // Set up UART
    io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);
    log::LOGGER.setUART(&uart);
    log::LOGGER.setLogLevel(log::Logger::LogLevel::DEBUG);

    // Create array of 1 GPIO pointer for the chip select GPIO
    io::GPIO* devices[DEVICE_COUNT];

    // Set up chip select GPIO and put in array
    devices[0] = &io::getGPIO<io::Pin::SPI_CS>(io::GPIO::Direction::OUTPUT);
    devices[0]->writePin(io::GPIO::State::HIGH);

    // Set up and configure SPI (<1 MHz, Mode 3, MSB first)
    io::SPI& spi = io::getSPI<io::Pin::SPI_SCK, io::Pin::SPI_MOSI, io::Pin::SPI_MISO>(devices, DEVICE_COUNT);
    spi.configureSPI(SPI_SPEED, io::SPI::SPIMode::SPI_MODE3, SPI_MSB_FIRST);

    // Create ADXL345 instance
    rampup::ADXL345 adxl345(spi, 0xE5);

    // Create a uint16_t array to store the three accelerations
    int16_t accel[3];
    const rampup::ADXL345::AccelAxis axis[] = {
        rampup::ADXL345::AccelAxis::X, rampup::ADXL345::AccelAxis::Y, rampup::ADXL345::AccelAxis::Z};
    while (1) {
        // Read all 3 accelerations
        for (int a = 0; a < 3; a++) {
            adxl345.readAccel(axis[a], accel[a]);
        }
        // Nicely print the three accelerations to 2 decimal places
        uart.printf("X: %5d; Y: %5d; Z: %5d\r\n", accel[0], accel[1], accel[2]);
        // Wait 1 s
        time::wait(100);
    }
}
