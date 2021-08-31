/*
 * file: i2c_device.ino
 * purpose: Have the Arduino act as an I2C device (specifcally a temp sensor) for testing
 *          I2C functionality.
 */

#include <Wire.h>

#define I2C_ADDR 0x04


void receive_handler(int count);
void request_handler();

char response_buf[] = "o";

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

void setup()
{
    Wire.begin(I2C_ADDR);               // Join the I2C bus with an address of 4
    Wire.onReceive(receive_handler);    // Register the receive handler
    Wire.onRequest(request_handler);    // Register the request handler
    Serial.begin(9600); // Start serial communications for debugging
    Serial.println("I2C test...");
}

void loop()
{
    delay(50);  // We're waiting for events so do nothing here.
}

void receive_handler(int count)
{
    char temp;
    while (Wire.available())    // While there are chars to read
    {
        temp = Wire.read();     // Read a char
        if(temp == 0)
          response_buf[0] = 'o';
        else
          response_buf[0] = 'k';
    }
    Serial.println();           // Move to the next line
}

void request_handler()
{
    Wire.write(response_buf);   // Respond with the message expected by the master.
}
