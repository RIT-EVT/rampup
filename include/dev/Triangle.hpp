//
// Created by Joshua Cruz on 12/23/25.
//

#ifndef RAMPUP_TRIANGLE_H
#define RAMPUP_TRIANGLE_H

#include "Shape.hpp"
#include <cstdint>

namespace rampup {

/**
 * Represents a rectangle, defined as a width and height. Inherits from Shape class
 */
class Triangle : public Shape {
public:
    /**
     * Constructs a new rectangle object with the given width and height
     *
     * @param[in] length
     * @param[in] width
     */
    Triangle(uint32_t length, uint32_t width);

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

    // Overridden methods from Shape
    uint32_t getArea() override;
    uint32_t getPerimeter() override;

private:
    // TODO: add 2 variables here that store all the information that is needed about a Rectangle
    uint32_t length;
    uint32_t width;

};

} // namespace rampup

#endif // RAMPUP_TRIANGLE_H
