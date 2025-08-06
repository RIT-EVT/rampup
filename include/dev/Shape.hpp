// this #ifndef _SHAPE_ is the include guard- try to think of how this works to prevent the shape class from being
// included twice in the same project.
#ifndef _SHAPE_
    #define _SHAPE_

    #include <stdint.h>

// everything in this set of brackets is in the rampup namespace.
// To access Shape outside the namespace, you will have to use rampup::Shape.
namespace rampup {

/**
 * Represents a 2D shape with an area and perimeter.
 */
class Shape {
public:
    /**
     * Gets the area of the shape.
     *
     * @return area of the shape
     */
    virtual uint32_t getArea() = 0;
    // the above method is marked virtual, which means that it is overridable. Subclasses
    //  (classes that inherit from this class) can OVERRIDE this method with their own implementation of it.

    // Setting this function equal to 0 makes it a "pure virtual" function. This means that subclasses MUST override
    // this function, and that the Shape class itself is an abstract class-- no object can be just a Shape. An object
    // could be a Rectangle, which is also a Shape through inheritance, but there will never be an object that is just
    // a Shape and nothing else.

    /**
     * Gets the perimeter of the shape.
     *
     * @return perimeter of the shape.
     */
    virtual uint32_t getPerimeter() = 0;

    // there are no private variables or methods in this class, so the private section is empty
    // it's not strictly necessary to have the 'private: ' header, but it helps to keep the same structure
    // for all header files.
private:
};

} // namespace rampup
// the comment next to the closing bracket notates what the bracket corresponds to- this one closes the namespace rampup

#endif // _SHAPE_
// Just like the closing brackets, the #endif macros are notated with which statement they are closing

// All files should have an empty line as the last line in the file. Certain tools and standards require this.
