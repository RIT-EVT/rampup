#include "dev/Rectangle.hpp"

namespace rampup {
    Rectangle::Rectangle(uint32_t length, uint32_t width) : length(length), width(width) {}

    uint32_t Rectangle::getArea() {
        return length*width;
    }

    uint32_t Rectangle::getPerimeter() {
        return length * 2 + width * 2;
    }

    uint32_t Rectangle::getWidth() {
        return width;
    }

    uint32_t Rectangle::getLength() {
        return length;
    }

} //namespace rampup
