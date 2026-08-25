#include <dev/TMP117.hpp>

namespace rampup {

// TMP117::TMP117(io::I2C& i2c, uint8_t i2cSlaveAddress) : i2cSlaveAddress(/*something here*/), i2c(/*something here*/)
// {}

/**
 * @brief Reads the temperature over I2C
 * Create variables to hold the I2C output and the register value you need to read from. Then, do a multibyte I2C read
 * due to the wanted register being 2 bytes.
 * Be careful of integer overflows; creating a temporary variable (u32 or u64) may be helpful for the conversion math.
 * Convert the raw output into a human readable value. The raw output is 1 unit = 7.8125 m°C (= 0.0078125°C).
 * Assign the value of the converted temp to the temperature variable.
 *
 * @param[out] temp The variable to put the final temperature value in
 * @return The status of the I2C read performed
 */
// io::I2C::I2CStatus TMP117::readTemp(uint16_t& temp) {
//     // Implementation here
// }

} // namespace rampup
