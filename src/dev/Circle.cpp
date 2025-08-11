#include "../../include/dev/Circle.hpp"

///100 * 3.14, for use with fixed point math
#define ONE_HUN_PI 314

namespace rampup {
Circle::Circle(uint32_t radius) : radius(radius) {}

uint32_t Circle::getArea() {
    return (radius * radius * ONE_HUN_PI) / 100;
}

uint32_t Circle::getPerimeter() {
    return (2 * radius * ONE_HUN_PI) / 100;
}

uint32_t Circle::getRadius() {
    return radius;
}

} // namespace rampup
