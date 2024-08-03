#include <reg51.h>

// Define Port 1 pin
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;

void com(void) {
    unsigned char num1 = 0x55; // First number
    unsigned char num2 = 0x60; // Second number

    if (num1 == num2) {
        P1_0 = 1;  // Set P1.0 if numbers are equal
        P1_1 = 0;  // Clear P1.1
        P1_2 = 0;  // Clear P1.2
    } else if (num1 > num2) {
        P1_0 = 0;  // Clear P1.0
        P1_1 = 1;  // Set P1.1 if num1 is greater than num2
        P1_2 = 0;  // Clear P1.2
    } else {
        P1_0 = 0;  // Clear P1.0
        P1_1 = 0;  // Clear P1.1
        P1_2 = 1;  // Set P1.2 if num1 is less than num2
    }

    while (1); // Infinite loop to keep the program running
}
