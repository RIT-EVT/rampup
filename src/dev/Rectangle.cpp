#include "../../include/dev/Rectangle.hpp"

namespace rampup {

Rectangle::Rectangle(uint32_t length, uint32_t width) : length(length), width(width) {}

// notice how each method starts with 'Rectangle::'?
// This is how C++ links the declarations of the methods in Rectangle.hpp
// with the implementations here in Rectangle.cpp.
uint32_t Rectangle::getArea() {
    return length * width;
}

uint32_t Rectangle::getPerimeter() {
    return 2 * length + 2 * width;
}

uint32_t Rectangle::getWidth() {
    return width;
}

uint32_t Rectangle::getLength() {
    return length;
}

} // namespace rampup
