# Phase 3 Answers
Phase 3 is about learning basics of I2C communication and driver development.

## targets/phase3/main.cpp
The main things that need to be seen in here is just that they:
- Create/Setup I2C
```cpp
i2c = IO::getI2C<...>()
```

- Create/Setup the TMP117 `tmp(...)`
```cpp

```

- Call the readTemp(...)
```cpp
tmp.readTemp(temp)
```

- Print result
```cpp

```


Look at targets/phase3/main.cpp for completed implementation.

## src/dev/TMP117.cpp readTemp() Implementation
The main things that need to be checked in the code is that they are:
- Reading from i2c
```cpp
i2cStatus = i2c.read()
``` 

- Combining the raw output from the sensor
```cpp
rawOutput = (outputBuffer[0] << 8) | outputBuffer[1]
```

- Converting raw output into either centi-celsius (preferred) or celsius
```cpp
output = rawOutput * 78125 / 10000 // centi-celsius
// Or
output = rawOutput * 78125 / 1000000 // celsius
```

Look at src/dev/TMP117.cpp for completed implementation.

## Expected UART output
IMAGE TO BE ADDED!

## Saleae Expected Image
IMAGE TO BE ADDED!