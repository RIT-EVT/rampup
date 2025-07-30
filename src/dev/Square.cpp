
#include "dev/Square.hpp"

namespace rampup {
    // This constructor has been provided- notice that we are calling the initializer of the Rectangle superclass
    Square::Square(uint32_t sideLength) : Rectangle(sideLength, sideLength), sideLength(sideLength) {}
} //namespace rampup
