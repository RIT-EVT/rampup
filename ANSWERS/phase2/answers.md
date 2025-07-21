# Phase 2 Answers
The objectives of phase 2 is to become familiar with EVT-core and working with a nucleo to create a UART interface.

## targets/phase2/main.cpp
- Initialize system
```cpp
core::platform::init();
```

- Set up UART
```cpp
io::UART& uart = io::getUART<io::Pin::UART_TX, io::Pin::UART_RX>(9600);
```

- Declare two arrays of characters to store user input.
```cpp
char userInput1[100];
char userInput2[100];
```

- Read user input
```cpp
uart.printf("\n\rEnter first number: ");
uart.gets(userInput1, 100);
uart.printf("\n\rEnter second number: ");
uart.gets(userInput2, 100);
```

- Convert the two character arrays to uint64_t
```cpp
uint64_t num1 = static_cast<uint64_t>(userInput1[0] - '0');
uint64_t num2 = static_cast<uint64_t>(userInput2[0] - '0');
```

- Output the sum of the two numbers
```cpp
uint64_t num3 = num1 + num2;
uart.printf("\n\r%u\n\r", num3);
```