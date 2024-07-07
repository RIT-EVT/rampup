#ifndef RAMPUP_BOARD_HPP
#define RAMPUP_BOARD_HPP

#include <cstdint>

#include <EVT/io/CANDevice.hpp>
#include <EVT/io/CANOpenMacros.hpp>
#include <EVT/io/pin.hpp>
#include <co_core.h>

#include "dev/MAX22530.hpp"
#include "dev/TMP117.hpp"

namespace IO = EVT::core::IO;

namespace rampup {

/**
 * Represents the board used for the rampup project.
 */
class RampupBoard : public CANDevice {
public:
    /** Rampup Board Pinout */
    static constexpr IO::Pin UART_TX_PIN = IO::Pin::UART_TX;
    static constexpr IO::Pin UART_RX_PIN = IO::Pin::UART_RX;
    static constexpr IO::Pin CAN_TX_PIN = IO::Pin::PA_12;
    static constexpr IO::Pin CAN_RX_PIN = IO::Pin::PA_11;
    static constexpr IO::Pin SPI_CS = IO::Pin::SPI_CS;
    static constexpr IO::Pin SPI_MOSI = IO::Pin::SPI_MOSI;
    static constexpr IO::Pin SPI_MISO = IO::Pin::SPI_MISO;
    static constexpr IO::Pin SPI_SCK = IO::Pin::SPI_SCK;

    /** Node ID used to identify the board on the CAN network. */
    static constexpr uint8_t NODE_ID = 50;

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
    MAX22530 max;
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
        MANDATORY_IDENTIFICATION_ENTRIES_1000_1014,
        HEARTBEAT_PRODUCER_1017(2000),
        IDENTITY_OBJECT_1018,
        SDO_CONFIGURATION_1200,

        // TPDO0 settings:
        // 0: The TPDO number, 0.
        // 1: How the TPO is triggered, timed triggering.
        // 2: Inhibit time, disabled or 0.
        // 3: Timer trigger time in 1ms units, 0 will disable the timer based triggering.
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(0, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE, 0 /*Replace with trigger interval*/),

        // TPDO1 settings:
        // 0: The TPDO number, 1
        // 1: How the TPO is triggered, timed triggering.
        // 2: Inhibit time, disabled or 0.
        // 3: Timer trigger time in 1ms units, 0 will disable the timer based triggering.
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(1, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE, 0 /*Replace with trigger interval*/),

        // TPDO0 mapping, determines the PDO messages to send when TPDO0 is triggered.
        // 0: The number of PDO messages associated with the TPDO.
        // 1: Link to the first voltage PDO data.
        // 2: Link to the second voltage PDO data.
        // 3: Link to the third voltage PDO data.
        // 4: Link to the fourth voltage PDO data.
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(0, 4),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 1, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 2, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 3, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0, 4, PDO_MAPPING_UNSIGNED16),

        // TPDO1 mapping, determines the PDO messages to send when TPDO1 is triggered.
        // 0: The number of PDO messages associated with the TPDO.
        // 1: Link to the temperature PDO data.
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(1, 1),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(1, 1, PDO_MAPPING_UNSIGNED16),

        // User defined data, this will be where we put elements that can be.
        // accessed via SDO and the first PDO.
        DATA_LINK_START_KEY_21XX(0, 4),
        DATA_LINK_21XX(0, 1, CO_TUNSIGNED16, nullptr /*Replace with address of first voltage*/),
        DATA_LINK_21XX(0, 2, CO_TUNSIGNED16, nullptr /*Replace with address of second voltage*/),
        DATA_LINK_21XX(0, 3, CO_TUNSIGNED16, nullptr /*Replace with address of third voltage*/),
        DATA_LINK_21XX(0, 4, CO_TUNSIGNED16, nullptr /*Replace with address of fourth voltage*/),

        // User defined data, this will be where we put elements that can be.
        // accessed via SDO and the second PDO.
        DATA_LINK_START_KEY_21XX(1, 1),
        DATA_LINK_21XX(1, 1, CO_TUNSIGNED16, nullptr /*Replace with address of temperature*/),

        // End of dictionary marker.
        CO_OBJ_DICT_ENDMARK,
    };
};

}// namespace rampup

#endif//RAMPUP_BOARD_HPP
