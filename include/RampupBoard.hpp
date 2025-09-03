#ifndef RAMPUP_BOARD_HPP
#define RAMPUP_BOARD_HPP

#include <cstdint>

#include <co_core.h>
#include <core/io/CANDevice.hpp>
#include <core/io/CANOpenMacros.hpp>
#include <core/io/pin.hpp>

#include <dev/ADXL345.hpp>
#include <dev/TMP117.hpp>

namespace io = core::io;

namespace rampup {

/**
 * Represents the board used for the rampup project.
 */
class RampupBoard : public CANDevice {
public:
    /** Rampup Board Pinout */
    static constexpr io::Pin UART_TX_PIN = io::Pin::UART_TX;
    static constexpr io::Pin UART_RX_PIN = io::Pin::UART_RX;
    static constexpr io::Pin CAN_TX_PIN  = io::Pin::PA_12;
    static constexpr io::Pin CAN_RX_PIN  = io::Pin::PA_11;
    static constexpr io::Pin SPI_CS      = io::Pin::SPI_CS;
    static constexpr io::Pin SPI_MOSI    = io::Pin::SPI_MOSI;
    static constexpr io::Pin SPI_MISO    = io::Pin::SPI_MISO;
    static constexpr io::Pin SPI_SCK     = io::Pin::SPI_SCK;

    /** Node ID used to identify the board on the CAN network. */
    static constexpr uint8_t NODE_ID = 50;

    RampupBoard(ADXL345 adxl345, TMP117 tmp);

    /**
     * Get a pointer to the start of the object dictionary.
     *
     * @return Pointer to the start of the object dictionary.
     */
    CO_OBJ_T* getObjectDictionary() override {
        return &objectDictionary[0];
    };

    /**
     * Get the number of elements in the object dictionary.
     *
     * @return The number of elements in the object dictionary.
     */
    uint8_t getNumElements() override {
        return OBJECT_DICTIONARY_SIZE + 1;
    };

    /**
     * Get the device's node ID.
     *
     * @return The node ID of the can device.
     */
    uint8_t getNodeID() override {
        return NODE_ID;
    };

    /**
     * Run the core logic of the board by collecting data from peripherals.
     */
    void process();

private:
    /** MAX instance used to get voltage data*/
    ADXL345 adxl345;
    /** TMP instance used to get temperature data */
    TMP117 tmp;
    /** Current voltages */
    uint16_t voltages[4];
    /** Current temperature */
    uint16_t temp;

    /**
     * Have to know the size of the object dictionary for initialization
     * process.
     */
    static constexpr uint8_t OBJECT_DICTIONARY_SIZE = 37;

    /**
     * The object dictionary itself. Will be populated by this object during
     * construction.
     *
     * The plus one is for the special "end of dictionary" marker.
     */
    CO_OBJ_T objectDictionary[OBJECT_DICTIONARY_SIZE + 1] = {
        //*********************** Begin Required Board Entries ************************//
        MANDATORY_IDENTIFICATION_ENTRIES_1000_1014,
        HEARTBEAT_PRODUCER_1017(2000),
        IDENTITY_OBJECT_1018,
        SDO_CONFIGURATION_1200,

        //**************************** Begin TPDO Settings ****************************//
        /**
         * RampupBoard TPDO 0 settings:
         * 0: The TPDO number, 0.
         * 1: How the TPO is triggered, timed triggering.
         * 2: Inhibit time, disabled or 0.
         * 3: Timer trigger time in 1ms units, 0 will disable the timer based triggering.
         */
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(0, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE,
                                          1000 /*Replace with trigger interval*/),

        /**
         * RampupBoard TPDO 1 settings:
         * 0: The TPDO number, 1.
         * 1: How the TPO is triggered, timed triggering.
         * 2: Inhibit time, disabled or 0.
         * 3: Timer trigger time in 1ms units, 0 will disable the timer based triggering.
         */
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(1, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE,
                                          1000 /*Replace with trigger interval*/),

        //***************************** Begin TPDO Maping *****************************//
        /**
         * RampupBoard TPDO 0 Mapping:
         * Determines the PDO messages to send when TPDO 0 is triggered.
         * 0: The number of PDO message associated with the TPDO.
         * 1: Link to the first voltage PDO data.
         * 2: Link to the second voltage PDO data.
         * 3: Link to the third voltage PDO data.
         * 4: Link to the fourth voltage PDO data.
         */
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(0, 4),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 1, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 2, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 3, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 4, PDO_MAPPING_UNSIGNED16),

        /**
         * RampupBoard TPDO 1 Mapping:
         * Determines the PDO messages to send when TPDO 1 is triggered.
         * 0: The number of PDO message associated with the TPDO.
         * 1: Link to the temperature PDO data.
         */
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(1, 1),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(1, 1, PDO_MAPPING_UNSIGNED16),

        //**************************** Begin Data Linking *****************************//
        /**
         * User defined data. This will be where we put elements that can be accessed
         * via SDO and the first PDO.
         */
        /* Link the data we want to map into RampupBoard TPDO 0 to variables */
        DATA_LINK_START_KEY_21XX(0, 4),
        DATA_LINK_21XX(0, 1, CO_TUNSIGNED16, &voltages[0] /*Replace with address of first voltage*/),
        DATA_LINK_21XX(0, 2, CO_TUNSIGNED16, &voltages[1] /*Replace with address of second voltage*/),
        DATA_LINK_21XX(0, 3, CO_TUNSIGNED16, &voltages[2] /*Replace with address of third voltage*/),
        DATA_LINK_21XX(0, 4, CO_TUNSIGNED16, &voltages[3] /*Replace with address of fourth voltage*/),

        /* Link the data we want to map into RampupBoard TPDO 1 to variables */
        DATA_LINK_START_KEY_21XX(1, 1),
        DATA_LINK_21XX(1, 1, CO_TUNSIGNED16, &temp /*Replace with address of temperature*/),

        //*************************** End Object Dictionary ***************************//
        CO_OBJ_DICT_ENDMARK,
    };
};

} // namespace rampup

#endif // RAMPUP_BOARD_HPP
