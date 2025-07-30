#ifndef _SQUARE_
#define _SQUARE_

#include <stdint.h>
#include "Rectangle.hpp"

namespace rampup {

/**
 * Represents a Square of a specific side length. Inherits from Rectangle
 */
class Square : public Rectangle {
public:
    Square(uint32_t sideLength);
private:
    uint32_t sideLength;
};

} //namespace rampup

#endif // _SQUARE_
