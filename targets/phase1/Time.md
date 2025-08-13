### NOTE: If you were not directed here by the `Instructions.md`, read that first.

# The Time.hpp Guide

Unlike GPIO.hpp, time.hpp is not a class, it is instead a collection
of related functions and structs that are useful when working with time.

## Follow along
Open [`libs/EVT-core/include/core/utils/time.hpp`](libs/EVT-core/include/core/utils/time.hpp) and split the screen between these instructions and time.hpp

The first thing to notice when finding the functions and tools you want to use is the namespace, as this is how
you will be able to call these functions.

On line 12, we see it says:
```cpp
namespace core::time {
```
This means that the following functions are contained in this namespace. So whenever we want to use a time function
we need to reference the full namespace followed by the function name.

For example `core::time::getTime();` would call a (fake) function named getTime in the core::time namespace.

We want to figure out how to pause for .5 seconds after turning the LED on/off. 
As we look through `time.hpp`, we see that there is a function called `wait(uint32_t ms)`, which has the 
comment above function declaration that states the purpose of wait is to "have the program hold for a set amount 
of time before continuing" which is exactly what we want. We also can see from the line
`@param ms The number of milliseconds to wait for` that the parameter is the length of the wait.



Now that we know the function we want to use, as well as the namespace it is declared in, we can go back 
to our phase1/main.cpp and use it like so:
```cpp
core::time::wait(500); // Wait .5 seconds
```



### Quick sidenote:
Oftentimes, especially the more nested we go, you won't want to use `core::io::GPIO::State` every time you want 
to reference the GPIO's state enum type, so we can make nicknames for the namespace path.

```cpp
namespace time = core::time;
time::wait(500); // This does the same thing as above
```