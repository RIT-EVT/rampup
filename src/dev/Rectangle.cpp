#include "../../include/dev/Rectangle.hpp"

#include <iostream>
#include <ostream>

namespace rampup {

Rectangle::Rectangle(uint32_t length, uint32_t width) : length(length), width(width) {}

// notice how each method starts with 'Rectangle::'?
// This is how C++ links the declarations of the methods in Rectangle.hpp
// with the implementations here in Rectangle.cpp.
uint32_t Rectangle::getArea() {
   const uint32_t Area = length * width;
    return Area;
    return -1;
}

uint32_t Rectangle::getPerimeter() {
 const uint32_t perimeter = (length * 2) + (width * 2);
    return perimeter;
    return -1;
}

uint32_t Rectangle::getWidth() {
    std::cout << width << std::endl;
    return -1;
}

uint32_t Rectangle::getLength() {
    std::cout << length << std::endl;
    return -1;
}

} // namespace rampup
