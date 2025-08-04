#include "dev/Rectangle.hpp"

namespace rampup {
Rectangle::Rectangle(uint32_t length, uint32_t width) {}

// notice how each method starts with 'Rectangle::'?
// This is how C++ links the declarations of the methods in Rectangle.hpp
// with the implementations here in Rectangle.cpp.
uint32_t Rectangle::getArea() {
    return -1;
}

uint32_t Rectangle::getPerimeter() {
    return -1;
}

uint32_t Rectangle::getWidth() {
    return -1;
}

uint32_t Rectangle::getLength() {
    return -1;
}

} // namespace rampup
