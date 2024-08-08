#ifndef _HUDL_
#define _HUDL_

#include <stdint.h>

#include <EVT/dev/LCD.hpp>
#include <EVT/io/CANDevice.hpp>
#include <EVT/io/CANOpenMacros.hpp>
#include <EVT/io/GPIO.hpp>
#include <EVT/io/SPI.hpp>
#include <co_core.h>

namespace IO = EVT::core::IO;
namespace DEV = EVT::core::DEV;

namespace rampup {

/**
 * Interfaces with the HUDL device. Provides an object dictionary
 * for communicating with other devices on the CAN network and functionality
 * for displaying what a user wants to an LCD screen
 */
class HUDL : public CANDevice {
public:
    /**
         * The node ID used to identify the device on the CAN network.
         */
    static constexpr uint8_t NODE_ID = 0x11;

    /**
         * Default Constructor for the HUDL class
         *
         * @param[in] reg_select is the register select pin
         * @param[in] reset is the reset pin
         * @param[in] spi is the SPI instance
         */
    HUDL(IO::GPIO& reg_select, IO::GPIO& reset, IO::SPI& spi);

    /**
         * Initializes LCD for use
         */
    void initLCD();

    /**
     * Get a pointer to the start of the object dictionary
     *
     * @return Pointer to the start of the object dictionary
     */
    CO_OBJ_T* getObjectDictionary() override {
        return &objectDictionary[0];
    };

    /**
     * Get the number of elements in the object dictionary.
     *
     * @return The number of elements in the object dictionary
     */
    uint8_t getNumElements() override {
        return OBJECT_DICTIONARY_SIZE + 1;
    };

    /**
    * Get the device's node ID
    *
    * @return The node ID of the can device.
     */
    uint8_t getNodeID() override {
        return NODE_ID;
    };

    /**
         * Updates the LCD display with values received from the CAN network
         */
    void updateLCD();

    /**
         * reg_select PA_3
         * reset      PB_3
         * cs         PB_12
         */
    DEV::LCD lcd;

    static constexpr uint8_t RAMPUP_NODE_ID = 50;

private:
    unsigned char evtBitMap[1024] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x3F, 0x3F,
        0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
        0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
        0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
        0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xF7, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x18, 0x1F,
        0x1F, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1F,
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F,
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x9F, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x01, 0x00, 0x00,
        0x00, 0x00, 0xC0, 0xF8, 0xFE, 0xFF, 0xFF, 0x3F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFB, 0xF8, 0xF8, 0x78, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
        0xF8, 0xFF, 0xFF, 0x3F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
        0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xF3, 0xF0, 0xF0,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFC, 0xFF, 0xFF, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8,
        0xF8, 0xF8, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x9F, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03,
        0x01, 0x01, 0x00, 0xC0, 0xE0, 0xE0, 0xF0, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xFE, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF1,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
        0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    uint16_t voltages[4];
    uint16_t temperature;

    static constexpr uint16_t OBJECT_DICTIONARY_SIZE = 33;

    CO_OBJ_T objectDictionary[OBJECT_DICTIONARY_SIZE + 1] = {
        //*********************** Begin Required Board Entries ************************//
        MANDATORY_IDENTIFICATION_ENTRIES_1000_1014,
        HEARTBEAT_PRODUCER_1017(2000),
        IDENTITY_OBJECT_1018,
        SDO_CONFIGURATION_1200,

        //**************************** Begin RPDO Settings ****************************//
        /**
         * RampupBoard RPDO 0 Settings:
         * 0: The RPDO number, 0
         * 1: The PDO number to receive, 0
         * 2: The COB-ID to receive PDOs from.
         * 3: transmission trigger
         */
        RECEIVE_PDO_SETTINGS_OBJECT_140X(0, 0, RAMPUP_NODE_ID, RECEIVE_PDO_TRIGGER_ASYNC),

        /**
         * RampupBoard RPDO 1 Settings:
         * 0: The RPDO number, 1
         * 1: The PDO number to receive, 1
         * 2: The COB-ID to receive PDOs from.
         * 3: transmission trigger
         */
        RECEIVE_PDO_SETTINGS_OBJECT_140X(1, 1, RAMPUP_NODE_ID, RECEIVE_PDO_TRIGGER_ASYNC),

        //***************************** Begin RPDO Maping *****************************//
        /**
         * RampupBoard RPDO 0 Mapping:
         * Determines the PDO messages to receive when RPDO 0 is triggered
         * 0: The number of PDO message associated with the RPDO
         * 1: Link to the first voltage PDO data.
         * 2: Link to the second voltage PDO data.
         * 3: Link to the third voltage PDO data.
         * 4: Link to the fourth voltage PDO data.
         */
        RECEIVE_PDO_MAPPING_START_KEY_16XX(0, 4),
        RECEIVE_PDO_MAPPING_ENTRY_16XX(0, 1, PDO_MAPPING_UNSIGNED16),
        RECEIVE_PDO_MAPPING_ENTRY_16XX(0, 2, PDO_MAPPING_UNSIGNED16),
        RECEIVE_PDO_MAPPING_ENTRY_16XX(0, 3, PDO_MAPPING_UNSIGNED16),
        RECEIVE_PDO_MAPPING_ENTRY_16XX(0, 4, PDO_MAPPING_UNSIGNED16),

        /**
         * RampupBoard RPDO 1 Mapping
         * Determines the PDO messages to receive when RPDO 1 is triggered
         * 0: The number of PDO message associated with the RPDO
         * 1: Link to the temperature PDO data.
         */
        RECEIVE_PDO_MAPPING_START_KEY_16XX(1, 1),
        RECEIVE_PDO_MAPPING_ENTRY_16XX(1, 1, PDO_MAPPING_UNSIGNED16),

        //**************************** Begin Data Linking *****************************//
        /**
         * User defined data. Put elements that can be accessed via SDO
         * and depending on the configuration PDO
         */
        /* Assign the data we mapped in the RampupBoard RPDO 0 Mapping to variables */
        DATA_LINK_START_KEY_21XX(0, 4),
        DATA_LINK_21XX(0, 1, CO_TUNSIGNED16, &voltages[0]),
        DATA_LINK_21XX(0, 2, CO_TUNSIGNED16, &voltages[1]),
        DATA_LINK_21XX(0, 3, CO_TUNSIGNED16, &voltages[2]),
        DATA_LINK_21XX(0, 4, CO_TUNSIGNED16, &voltages[3]),

        /* Assign the data we mapped in the RampupBoard RPDO 1 Mapping to variables */
        DATA_LINK_START_KEY_21XX(1, 1),
        DATA_LINK_21XX(1, 1, CO_TUNSIGNED16, &temperature),

        //*************************** End Object Dictionary ***************************//
        CO_OBJ_DICT_ENDMARK,
    };
};

}// namespace rampup

#endif