#ifndef _RECTANGLE_
#define _RECTANGLE_

#include <stdint.h>
#include "Shape.hpp"

namespace rampup {

/**
 * Represents a rectangle, defined as a width and height. Inherits from Shape class
 */
class Rectangle : public Shape {
public:
    /**
     * Constructs a new rectangle object with the given width and height
     *
     * @param[in] length
     * @param[in] width
     */
    Rectangle(uint32_t length, uint32_t width);

    /**
     * Gets the length of the rectangle.
     *
     * @return length of the rectangle.
     */
    virtual uint32_t getLength();

    /**
     * Gets the width of the rectangle.
     *
     * @return width of the rectangle.
     */
    virtual uint32_t getWidth();

    // Overrided methods from Shape
    uint32_t getArea() override;
    uint32_t getPerimeter() override;
private:
    //TODO: add 2 variables here that store all the information that is needed about a Rectangle


};

} //namespace rampup

#endif // _RECTANGLE_
