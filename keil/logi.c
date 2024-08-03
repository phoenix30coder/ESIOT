#include <reg51.h>

void logi(void) {
    unsigned char num1 = 0x55; // 01010101 in binary
    unsigned char num2 = 0xAA; // 10101010 in binary
    unsigned char and_result, or_result, xor_result, not_result;
    
    
        and_result = num1 & num2;
        or_result = num1 | num2;
        xor_result = num1 ^ num2;
        not_result = ~num1;
		
		P0 = and_result;
		P1 = or_result;
		P2 = xor_result;
		P3 = not_result;
        
        
}