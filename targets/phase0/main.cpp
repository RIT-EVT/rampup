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

    //This is an array of pointers to Shape objects- note that's different than an array of Shape objects themselves
    rampup::Shape* shapeArr[SHAPE_ARRAY_LENGTH] = {
        &rect1, &rect2,
    };
    for (int i = 0; i < SHAPE_ARRAY_LENGTH; i++) {
        printf("Shape %u has area %lu and perimeter %lu", i, shapeArr[i]->getArea(), shapeArr[i]->getPerimeter());
        //Notice how we write shapeArr[i]->getArea() -- this is because shapeArr[i] returns a Shape* (i.e. a pointer to
        // a Shape object). We can't write shapeArr[i].getArea(), because you can only call getArea() on a Shape, not a
        // Shape*. We could write (*shapeArr[i]).getArea(), dereferencing the pointer before calling getArea, but the
        // -> operator performs the exact same function.

        //TODO: (Step 8) add an if statement that checks if the area to perimeter ratio is greater than or equal to 0.5.
        // You'll have to use fixed point numbers for this!
    }
}
