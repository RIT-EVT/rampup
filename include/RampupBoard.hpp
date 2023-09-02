#ifndef RAMPUP_BOARD_HPP
#define RAMPUP_BOARD_HPP

#include <cstdint>

#include <Canopen/co_core.h>

#include "dev/MAX22530.hpp"
#include "dev/TMP117.hpp"
#include <EVT/io/pin.hpp>

namespace IO = EVT::core::IO;

namespace rampup {

/**
 * Represents the board used for the rampup project
 */
class RampupBoard {
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

    /** Node ID used to identify the board on the CAN network */
    static constexpr uint8_t NODE_ID = 50;

    // Constructor

    /**
     * Run the core logic of the board by collecting data from peripherals
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
    static constexpr uint8_t OBJECT_DICTIONARY_SIZE = 30;

    /**
     * The object dictionary itself. Will be populated by this object during
     * construction.
     *
     * The plus one is for the special "end of dictionary" marker.
     */
    CO_OBJ_T objectDictionary[OBJECT_DICTIONARY_SIZE + 1] = {
        // Sync ID, defaults to 0x80
        {
            CO_KEY(0x1005, 0, CO_UNSIGNED32 | CO_OBJ_D__R_),
            nullptr,
            (uintptr_t) 0x80,
        },

        // Enable heartbeat
        {
            CO_KEY(0x1017, 0, CO_UNSIGNED16 | CO_OBJ_D__R_),
            CO_THB_PROD,
            (uintptr_t) 100,
        },

        // Information about the hardware, hard coded sample values for now
        // 1: Vendor ID
        // 2: Product Code
        // 3: Revision Number
        // 4: Serial Number
        {
            .Key = CO_KEY(0x1018, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x10,
        },
        {
            .Key = CO_KEY(0x1018, 2, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x11,
        },
        {
            .Key = CO_KEY(0x1018, 3, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x12,
        },
        {
            .Key = CO_KEY(0x1018, 4, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x13,
        },

        // SDO CAN message IDS.
        // 1: Client -> Server ID, default is 0x600 + NODE_ID
        // 2: Server -> Client ID, default is 0x580 + NODE_ID
        {
            .Key = CO_KEY(0x1200, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x600 + NODE_ID,
        },
        {
            .Key = CO_KEY(0x1200, 2, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0x580 + NODE_ID,
        },

        // TPDO0 settings
        // 0: The TPDO number, default 0
        // 1: The COB-ID used by TPDO0, provided as a function of the TPDO number
        // 2: How the TPO is triggered, default to manual triggering
        // 3: Inhibit time, defaults to 0
        // 5: Timer trigger time in 1ms units, 0 will disable the timer based triggering
        {
            .Key = CO_KEY(0x1800, 0, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0,
        },
        {
            .Key = CO_KEY(0x1800, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) CO_COBID_TPDO_DEFAULT(0) + NODE_ID,
        },
        {
            .Key = CO_KEY(0x1800, 2, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0xFE,
        },
        {
            .Key = CO_KEY(0x1800, 3, CO_UNSIGNED16 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0,
        },
        {
            .Key = CO_KEY(0x1800, 5, CO_UNSIGNED16 | CO_OBJ_D__R_),
            .Type = CO_TEVENT,
            .Data = (uintptr_t) 0 /*Replace with trigger time*/,
        },

        // TPDO1 settings
        // 0: The TPDO number, default 0
        // 1: The COB-ID used by TPDO0, provided as a function of the TPDO number
        // 2: How the TPO is triggered, default to manual triggering
        // 3: Inhibit time, defaults to 0
        // 5: Timer trigger time in 1ms units, 0 will disable the timer based triggering
        {
            .Key = CO_KEY(0x1801, 0, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 1,
        },
        {
            .Key = CO_KEY(0x1801, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) CO_COBID_TPDO_DEFAULT(1) + NODE_ID,
        },
        {
            .Key = CO_KEY(0x1801, 2, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0xFE,
        },
        {
            .Key = CO_KEY(0x1801, 3, CO_UNSIGNED16 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 0,
        },
        {
            .Key = CO_KEY(0x1801, 5, CO_UNSIGNED16 | CO_OBJ_D__R_),
            .Type = CO_TEVENT,
            .Data = (uintptr_t) 0 /*Replace with trigger time*/,
        },

        // TPDO0 mapping, determines the PDO messages to send when TPDO1 is triggered
        // 0: The number of PDO messages associated with the TPDO
        // 1: Link to the first PDO message
        // n: Link to the nth PDO message
        {
            .Key = CO_KEY(0x1A00, 0, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 4,
        },
        {
            .Key = CO_KEY(0x1A00, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = CO_LINK(0x2100, 0, 16),
        },
        {
            .Key = CO_KEY(0x1A00, 2, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = CO_LINK(0x2100, 1, 16),
        },
        {
            .Key = CO_KEY(0x1A00, 3, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = CO_LINK(0x2100, 2, 16),
        },
        {
            .Key = CO_KEY(0x1A00, 4, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = CO_LINK(0x2100, 3, 16),
        },

        // TPDO1 mapping, determines the PDO messages to send when TPDO1 is triggered
        // 0: The number of PDO messages associated with the TPDO
        // 1: Link to the first PDO message
        // n: Link to the nth PDO message
        {
            .Key = CO_KEY(0x1A01, 0, CO_UNSIGNED8 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = (uintptr_t) 1,
        },
        {
            .Key = CO_KEY(0x1A01, 1, CO_UNSIGNED32 | CO_OBJ_D__R_),
            .Type = nullptr,
            .Data = CO_LINK(0x2101, 0, 16),
        },

        // User defined data, this will be where we put elements that can be
        // accessed via SDO and depending on configuration PDO
        {
            .Key = CO_KEY(0x2100, 0, CO_UNSIGNED16 | CO_OBJ___PRW),
            .Type = nullptr,
            .Data = (uintptr_t) nullptr /*Replace with address of first voltage*/,
        },
        {
            .Key = CO_KEY(0x2100, 1, CO_UNSIGNED16 | CO_OBJ___PRW),
            .Type = nullptr,
            .Data = (uintptr_t) nullptr /*Replace with address of second voltage*/,
        },
        {
            .Key = CO_KEY(0x2100, 2, CO_UNSIGNED16 | CO_OBJ___PRW),
            .Type = nullptr,
            .Data = (uintptr_t) nullptr /*Replace with address of third voltage*/,
        },
        {
            .Key = CO_KEY(0x2100, 3, CO_UNSIGNED16 | CO_OBJ___PRW),
            .Type = nullptr,
            .Data = (uintptr_t) nullptr /*Replace with address of fourth voltage*/,
        },
        {
            .Key = CO_KEY(0x2101, 0, CO_UNSIGNED16 | CO_OBJ___PRW),
            .Type = nullptr,
            .Data = (uintptr_t) nullptr /*Replace with address of temperature*/,
        },

        // End of dictionary marker
        CO_OBJ_DIR_ENDMARK,
    };
};

}// namespace rampup

#endif//RAMPUP_BOARD_HPP
