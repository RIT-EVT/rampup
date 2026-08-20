#ifndef RAMPUP_BOARD_HPP
#define RAMPUP_BOARD_HPP

#include <cstdint>

#include <co_core.h>

#include "dev/MAX22530.hpp"
#include "dev/TMP117.hpp"
#include <core/io/CANDevice.hpp>
#include <core/io/CANOpenMacros.hpp>
#include <core/io/pin.hpp>

namespace io = core::io;

namespace rampup {

/**
 * Represents the board used for the rampup project
 */
class RampupBoard : public CANDevice {
public:
    /** Rampup Board Pinout */
    static constexpr io::Pin UART_TX_PIN = io::Pin::UART_TX;
    static constexpr io::Pin UART_RX_PIN = io::Pin::UART_RX;
    static constexpr io::Pin CAN_TX_PIN = io::Pin::PA_12;
    static constexpr io::Pin CAN_RX_PIN = io::Pin::PA_11;
    static constexpr io::Pin SPI_CS = io::Pin::SPI_CS;
    static constexpr io::Pin SPI_MOSI = io::Pin::SPI_MOSI;
    static constexpr io::Pin SPI_MISO = io::Pin::SPI_MISO;
    static constexpr io::Pin SPI_SCK = io::Pin::SPI_SCK;

    /** Node ID used to identify the board on the CAN network */
    static constexpr uint8_t NODE_ID = 50;

    // Constructor

    /**
     * Run the core logic of the board by collecting data from peripherals
     */
    void process();

    /**
     * Get a pointer to the start of the object dictionary
     *
     * @return Pointer to the start of the object dictionary
     */
    CO_OBJ_T* getObjectDictionary() override;

    /**
     * Get the number of elements in the object dictionary.
     *
     * @return The number of elements in the object dictionary
     */
    uint8_t getNumElements() override;

    /**
     * Get the device's node ID
     *
     * @return The node ID of the can device.
     */
    uint8_t getNodeID() override;

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
        HEARTBEAT_PRODUCER_1017(100),
        IDENTITY_OBJECT_1018,
        SDO_CONFIGURATION_1200,

        // TPDO0 settings: reports the 4 ADC voltages
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(0x00, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE,
                                          0 /*Replace with trigger time*/),
        // TPDO1 settings: reports the temperature
        TRANSMIT_PDO_SETTINGS_OBJECT_18XX(0x01, TRANSMIT_PDO_TRIGGER_TIMER, TRANSMIT_PDO_INHIBIT_TIME_DISABLE,
                                          0 /*Replace with trigger time*/),

        // TPDO0 mapping: 4 voltages
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(0x00, 0x04),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0x00, 0x01, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0x00, 0x02, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0x00, 0x03, PDO_MAPPING_UNSIGNED16),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0x00, 0x04, PDO_MAPPING_UNSIGNED16),

        // TPDO1 mapping: temperature
        TRANSMIT_PDO_MAPPING_START_KEY_1AXX(0x01, 0x01),
        TRANSMIT_PDO_MAPPING_ENTRY_1AXX(0x01, 0x01, PDO_MAPPING_UNSIGNED16),

        // Data links, this is where we tie the mapped PDO entries to our
        // actual member variables. Accessible via SDO and, depending on
        // configuration, PDO.
        DATA_LINK_START_KEY_21XX(0x00, 0x04),
        DATA_LINK_21XX(0x00, 0x01, CO_TUNSIGNED16, nullptr /*Replace with address of first voltage*/),
        DATA_LINK_21XX(0x00, 0x02, CO_TUNSIGNED16, nullptr /*Replace with address of second voltage*/),
        DATA_LINK_21XX(0x00, 0x03, CO_TUNSIGNED16, nullptr /*Replace with address of third voltage*/),
        DATA_LINK_21XX(0x00, 0x04, CO_TUNSIGNED16, nullptr /*Replace with address of fourth voltage*/),

        DATA_LINK_START_KEY_21XX(0x01, 0x01),
        DATA_LINK_21XX(0x01, 0x01, CO_TUNSIGNED16, nullptr /*Replace with address of temperature*/),

        // End of dictionary marker
        CO_OBJ_DICT_ENDMARK,
    };
};

}// namespace rampup

#endif//RAMPUP_BOARD_HPP
