#ifndef _SQUARE_
#define _SQUARE_

#include "Rectangle.hpp"
#include <stdint.h>

namespace rampup {

/**
 * Represents a Square of a specific side length. Inherits from Rectangle
 */
class Square : public Rectangle {
public:
    Square(uint32_t sideLength);

private:
};

} // namespace rampup

#endif // _SQUARE_
