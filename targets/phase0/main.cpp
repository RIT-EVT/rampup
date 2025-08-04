/**
 * This is a simple example of C++ coding
 */

#include <cstdint>
#include <cstdio>
#include "../../include/dev/Shape.hpp"
#include "../../include/dev/Rectangle.hpp"
#include "../../include/dev/Square.hpp"

#define SHAPE_ARRAY_LENGTH 4

int main() {
    //constructing two rectangles
    rampup::Rectangle rect1(2,3), rect2(3,4);
    //TODO: (Step 6) construct 2 square objects here, then add them to the shapeArray

    //TODO: (Step 7) when you make your other type of Shape, construct it here

    // this is an array of pointers to Shape objects- note that's different than an array of Shape objects themselves
    rampup::Shape* shapeArr[SHAPE_ARRAY_LENGTH] = {
        &rect1, &rect2,
    };
    for (int i = 0; i < SHAPE_ARRAY_LENGTH; i++) {
        printf("Shape %u has area %lu and perimeter %lu", i, shapeArr[i]->getArea(), shapeArr[i]->getPerimeter());
    }
}
