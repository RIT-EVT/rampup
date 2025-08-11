#ifndef _CIRCLE
#define _CIRCLE

#include "Shape.hpp"
#include <cstdint>

namespace rampup {

/**
 * Represents a circle of a specific radius. Inherits from Shape class
 */
class Circle : public Shape {
public:
    /**
     * Constructs a new Circle object with the given radius
     *
     * @param[in] radius The radius of the new circle
     */
    Circle(uint32_t radius);

    /**
     * Gets the radius of the circle
     *
     * @return the radius of the circle
     */
    uint32_t getRadius();

    // Overridden methods from Shape
    uint32_t getArea() override;
    uint32_t getPerimeter() override;

private:
    /**
     * Radius of the circle
     */
     uint32_t radius;

};

} // namespace rampup


#endif // _CIRCLE
