# Phase 0 Answers
The objectives of phase 0 is to become familiar C++ programming in general.

## Step 4
@ line 42 of dev/Rectangle.hpp: 
```cpp
/**
 * Length of this rectangle
 */
uint32_t length;
/**
 * Width of this rectangle
 */
uint32_t width;
```
If they don't have comments on the variables, explain to them that comments are a must.
Make sure to also explain a docstrings (/**) comment vs. a normal multiline comment (/*).

## Step 5
In dev/Rectangle.cpp
```cpp
uint32_t Rectangle::getArea() {
    return length*width;
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
```

## Step 6
- construct 2 square objects here, then add them to the shapeArray
```cpp
    rampup::Square sqr1(2), sqr2(4); //(any values side length values are fine)
```

## Step 7
In phase0/main.cpp
- Make sure to import the hpp of your new shape here.
```cpp
#include "../../include/dev/NEW_SHAPE.hpp
```
- When you're adding more shapes to the array, make sure the array is large enough to hold all of them!
```cpp
#define SHAPE_ARRAY_LENGTH 6
```

- when you make your other type of Shape, construct it here
```cpp
    rampup::NEW_SHAPE ns1(4,5), ns2(5,5);
```
- add new shape to the array
```cpp
rampup::Shape* shapeArr[SHAPE_ARRAY_LENGTH] = {
        &rect1,
        &rect2,
        &sqr1,
        &sqr2,
        &ns1,
        &ns2
    };
```

They'll also need the hpp and cpp for whatever NEW_SHAPE is. It doesn't have to be complicated.
Shape ideas:
- Right triangle (easy b/c it's really just half a square in terms of area)
- Circle (they might want to use fixed point to make their calculations more accurate, then round back down)
The example used in the answer guide is a Circle, but that doesn't mean it's the only answer.

## Step 8
In phase0/main
```cpp
    uint32_t ratio = (shapeArr[i]->getArea() * 100) / shapeArr[i]->getPerimeter();
    if(ratio >= 50) {
        printf("Shape %u has an area to perimeter ratio of %u.%u", i, ratio%100, ratio/100);
    }
```
They don't have to do it exactly like this, they just need to signal in some way that the ratio is above 0.5

## FAQ
Any commonly asked questions and their answers should be recorded here. Keep track of what questions
you get asked, and if there are common ones make sure to add them to this document.

1.
   - Q: 
   - A: 
