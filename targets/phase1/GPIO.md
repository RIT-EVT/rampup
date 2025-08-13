### NOTE: If you were not directed here by the `Instructions.md`, read that first.

# The GPIO.hpp Guide
## Quick Glossary Terms
A logic level (or logic state) is the voltage the microcontroller sees or drives on a pin, interpreted as either:
- High → Voltage present & near or at maximum (3v3 or 5v).
- Low → No voltage present.
- Floating → randomly reads as HIGH or LOW because it’s picking up electrical noise.
  That’s why we use pull-up or pull-down resistors to hold the pin to a stable default voltage when nothing else is controlling it.

When talking about GPIO:
- Write → The microcontroller sets the pin to HIGH or LOW.
- Read → The microcontroller checks whether the pin is HIGH or LOW.

## Template Functions
A template in C++ is like a blueprint for code, it lets you write a function or class once and then reuse 
it with different types or values without rewriting it.

In EVT's case, we mainly will use them for initializing things like GPIO independent of platform (aka, no matter what
microcontroller it is on, the same template call will work on it, assuming the uC is supported by EVT).

We will be using the following template function to create a GPIO, found on line 191 of the `manager.hpp`.

```cpp
/**
 * Get an instance of a GPIO pin.
 *
 * @param[in] pin The pin to attach to the GPIO
 * @param[in] direction The direction, either input or output
 * @param[in] pull The direction of the internal pull resistor
 */
template<Pin pin>
GPIO& getGPIO(GPIO::Direction direction = GPIO::Direction::OUTPUT, GPIO::Pull pull = GPIO::Pull::PULL_DOWN) {
    #ifdef STM32F3xx
    static GPIOf3xx gpioPin(pin, direction, pull);
    return gpioPin;
    #endif
    #ifdef STM32F4xx
    static GPIOf4xx gpioPin(pin, direction);
    return gpioPin;
    #endif
}
```

The important things here are that the template takes 3 parameters as input, the pin you want to use, the 
direction of the pin, and the pull of the pin.

The direction and pull of the pin both have a default variable, seen by the 
`GPIO::Direction direction = GPIO::Direction::OUTPUT, GPIO::Pull pull = GPIO::Pull::PULL_DOWN`. This means if 
we just give a pin to use, the template will work fine. 


You have probably noticed that there are `#ifdef`'s in this, and that is what allows us to have a single 
function that creates a GPIO instance that works on f3 or f4 uC's (our two currently supported microcontroller 
generations). If the current uC is a f3 generation, the first `#ifdef` occurs, creating a f3 compatible GPIO 
instance, and if the uC is a f4 generation, the second `#ifdef` occurs, creating a f4 compatible GPIO instance.

### Usage
The last thing you need to know about templates are how to use them. 

When you call the template, the parameters in the declarations `< >` that follow "template" will go after 
the usage call in `< >`, and any values in the templates parameter parenthesis after the function name, 
in this case "getGPIO", will follow in parentheses of their own in the usage, like this:

```cpp
// Declaration
template<Pin pin>
GPIO& getGPIO(GPIO::Direction direction = GPIO::Direction::OUTPUT, GPIO::Pull pull = GPIO::Pull::PULL_DOWN) 
{ ... }

// Usage
GPIO& gpio = getGPIO<pinHere>(directionHere, pullHere)
```

Note that the direction and pull can be skipped in this case, as they have default values.


## Follow along
Open [`libs/EVT-core/include/core/utils/GPIO.hpp`](libs/EVT-core/include/core/io/GPIO.hpp) and split the screen 
between these instructions and GPIO.hpp.

This GPIO.hpp is an abstract class that all uC specific implementations of the GPIO class **MUST** follow, meaning 
any functions found in `GPIO.hpp` are guaranteed to be supported by all uC specific versions, making it safe to use any 
of these functions no matter the uC.

### Using the GPIO instance

Now that we know how we are going to create the GPIO instance using the template function, we need to
figure out how to use the created GPIO instance to turn the LED on and off.

Glance through `GPIO.hpp` quickly and see if any functions catch your eye as potentially useful.

As you skim through the file, two class functions stand out:
`writePin()` on line 90, and `readPin()` on line 97. 

Here, as we want to control something else (an LED), we are going to want to write to the pin, so we can forget about 
`readPin()`. The writePin function takes a State as an argument, where State is a special enum (a set of named constants) 
created in the `GPIO.hpp` on line 29. We see that the only options are LOW and HIGH, which makes sense as digital 
logic is either 0 or 1.

So, if you want to set a gpio Instance to low (0 volt output), you would call the writePin() function with 
State Enums LOW variable (State::LOW), and HIGH to set the pin to high (3v3 volt output). 

### Implementation

To implement this GPIO class back in the `phase1/main.cpp`, we first need to let the code know we 
want to use something from another file using an `#include` statement. We can see that this has been 
done for us on line 5 `#include <core/io/GPIO.hpp>`, meaning we can now reference the GPIO class.

To create the GPIO instance, we will use the template function we mentioned earlier. Next, we want 
to have a variable that stores the state of the GPIO (High or Low). Then, in an infinite loop, we
want to call the `writePin()` method with our state variable as a parameter, and then change the state 
variable to the opposite of whatever it was on. Lastly, inside the loop, make sure to call the `wait()` 
function you learned about in `Time.md`.