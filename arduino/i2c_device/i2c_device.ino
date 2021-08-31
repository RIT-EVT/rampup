/**
 * This Arduino is confiured to be a ficticious battery cell voltage sensor
 * that includes an internal temperature sensor. The Arduino is setup for
 * a rather standard register implementation where users first write out
 * the address of the register they want to read, the Arduino will in response
 * return the value stored in that register. Below is the register map for
 * the Arduino. Unlike an actual device, the values returned for all
 * registers are fixed. This is for easier testing.
 * 
 * | Register | Description                                    | Expected Value |
 * |----------|------------------------------------------------|----------------|
 * | 0x00     | The ID of the device                           | 0xAA           | 
 * | 0x01     | Least significant byte of the temperature data | 0x10           |
 * | 0x02     | Most significant byte of the temperature data  | 0x11           |
 * | 0x03     | Least significant byte of the voltage data     | 0x12           |
 * | 0x04     | Most signficant byte of the voltage data       | 0x13           |
 * 
 * 
 */

#include <Wire.h>

#define I2C_ADDR 0x04


void receive_handler(int count);
void request_handler();

/**
 * Represents an I2C register, value pair. In this example the register
 * values are fixed. But in a "real" system this would actually read
 * values from hardware.
 * 
 * @address The address of the I2C register
 * @value The value that will be associated with the register address
 * @message The message to be associated with the register (debug usage)
 */
struct i2c_pair {
  uint8_t address;
  uint8_t value;
  char message[100];
};

/**
 * Representation of the register map of the device. Contains all possible
 * registers and their associated values.
 */
struct i2c_pair reg_map[] = {
  { 0x00, 0xAA, "Identifier for the I2C device" },
  { 0x01, 0x10, "Least significant byte of the temperature" },
  { 0x02, 0x11, "Most significant byte of the temperature" },
  { 0x03, 0x12, "Least singificant byte of the voltage data" },
  { 0x04, 0x13, "Most significant byte of the voltage data" }
};

/**
 * Represents the max number of registers
 */
uint8_t num_registers = 5;

/**
 * The index into reg_map. Used for determing which value to return when a
 * read request is made.
 */
int reg_index = 0;

void setup() {
    Wire.begin(I2C_ADDR);               // Join the I2C bus with an address of 4
    Wire.onReceive(receive_handler);    // Register the receive handler
    Wire.onRequest(request_handler);    // Register the request handler
    Serial.begin(9600);                 // Start serial communications for debugging
    Serial.println("I2C test...");
}

void loop() {
    delay(50);  // We're waiting for events so do nothing here.
}

void receive_handler(int count) {
    while (Wire.available()) {
        reg_index = Wire.read();
        if (reg_index >= num_registers) {
          Serial.println("Invalid register selected!");
          reg_index = 0;
        }
        // Print out the register that was selected
        Serial.print("Register Selected: ");
        Serial.println(reg_index, HEX);
    }
    Serial.println();           // Move to the next line
}

void request_handler() {
  Serial.print("Returning value for register: ");
  Serial.println(reg_index, HEX);
  
  Serial.print("Register value: ");
  Serial.println(reg_map[reg_index].value, HEX);

  // Write out value over I2C
  Wire.write(reg_map[reg_index].value);
}
