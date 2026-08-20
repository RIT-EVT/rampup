#include <RampupBoard.hpp>

namespace rampup {

// Constructor and process() implementation here

// Required CanOpen functions
CO_OBJ_T* RampupBoard::getObjectDictionary() {
    return &objectDictionary[0];
}

uint8_t RampupBoard::getNumElements() {
    return OBJECT_DICTIONARY_SIZE;
}

uint8_t RampupBoard::getNodeID() {
    return NODE_ID;
}

} // namespace rampup
