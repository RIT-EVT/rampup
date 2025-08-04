## Phase 0: C++ Basics

### Learning Objectives
- C++ syntax
- Classes and Objects in C++
- Compiling C++ code via command line.

### Summary
This phase is a broad introduction to C++ syntax. Not every aspect of C++ will be covered, 
but the primary key features will be. Most of C++ will feel familiar if you already know
another programming language, especially Java or C, but just like any other language
it has its own quirks and idiosyncrasies.

### Task Breakdown
1. Read through the [C++ and Object Oriented Programming](https://sites.google.com/g.rit.edu/evt-home-page/firmware-team/getting-started/object-oriented-programming-and-c) writeup on the EVT website.
2. Look through the hpp files found in the rampup/include/dev folder that have to do with phase 0. 
There are three classes, Shape, Square, and Rectangle. These classes relate to one another via _inheritance_.
A Square is a subclass of Rectangle, and a Rectangle is a subclass of Shape.
3. Take a close look at rampup/include/dev/Shape.hpp; this hpp file is heavily annotated with information
about the structure of an hpp file.
4. Now, move on to rampup/include/dev/Rectangle.hpp. This is a concrete (i.e. non-abstract) class
that inherits from Shape. You will need to add two variable to the private section of the class. These variables should
store all the necessary information needed to describe a Rectangle.
5. Move over to rampup/src/dev/Rectangle.cpp. This is the cpp file that implements the methods
described in Rectangle.hpp (Note that Shape does not have a corresponding cpp. This is because
Shape is an abstract class, and so has no real implementation). You must implement all the methods
from Rectangle inside this  (right now they all return -1). If you're not sure what a method is supposed to do, hover 
over the name of the method with your cursor, and a documentation window should pop up.
6. Move over to phase0/main.cpp; inside this main method, construct 2 square objects, and then add them to the array
7. Go back to src/dev and include/dev and create another type of Shape (from scratch). Anything goes- Circles, Ovals, Pentagons.
When making your class, think about what values are required to represent each instance of the class, and make sure to override
the getArea() and getPerimeter() methods from Shape. Once your class is created, go back to phase0/main.cpp and add one or two
instances of your class to the shapeArr. Don't forget to increase the size of the shapeArr!
8. After creating this other type of Shape, add an if statement to the for loop that checks for a shape with a 
area to perimeter ratio of greater than or equal to 0.5. 

**Note:** We are still just using uint32_t values, so you will not be able
   to directly represent a ratio of 0.5. Instead, you should use "fixed point numbers". Unlike the 
   classic floating point numbers, fixed point numbers are fundamentally still just integers. Imagine a square with side 
   lengths of 2: the square has a perimeter of 8 and an area of 4.
   This means that area/perimeter = 0.5. We could not represent this with an integer in meters, it would end up being 0:


    floor(8/4) = floor(0.5) = 0. 

   Now imagine that we instead represent the perimeter and area in centimeters. This is an issue,
   because we want to know the ratio more exactly than that. Lets say that we only cared about the ratio in terms of the nearest
   one-hundredth (0.01): we could multiply by 100: 

    floor((8*100)/4) = 50.
   
   As long as we understand that the "50" is really
   _50 hundredths_, we can now deal with decimal values to a certain level of accuracy, without compromising the accuracy
   of non-floating point numbers. You can think of this as just changing the unit we are using: it's really the difference
   between measuring something in meters or measuring something in centimeters.



### Suggestions
- If you're ever confused about anything in this rampup, first try to just mess around with whatever it is you're
trying to get working. Programming is an intensely iterative process, and the sooner you get used to trying and failing,
the better. However, if you are still stuck, ask someone! Anyone on the team would love to help out with your question
or, if they can't, point you to someone who can.
- You might notice how the methods in Rectangle.cpp return -1, even though they are uint32_t, and thus unsigned.
If this code was run, you would find that the methods do not really return -1, but instead 4294967295. This is not an arbitrary
number- it's the maximum number possible for a uint32_t (2^31-1). The -1 in this case is really a shorthand for 
"biggest possible number".

### Completion
