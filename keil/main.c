#include<reg51.h>

/*void main(void){

	unsigned char x,y,z;
	x=0x12;
	y=0x34;
	P0 = 0x00;
	z=x+y;
	P0=z;

}*/


/*void main(void) {
    unsigned char num1 = 0x55; // 01010101 in binary
    unsigned char num2 = 0x50; // 10101010 in binary
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
	*/
/*sbit P1_0 = P1^0;

void main(void) {
    unsigned char num1 = 0x55; // First number
    unsigned char num2 = 0x5; // Second number

    if (num1 == num2) {
        P1_0 = 1;  // Set P1.0 if numbers are equal
    } else {
        P1_0 = 0;  // Clear P1.0 if numbers are not equal
    }

    while (1); // Infinite loop to keep the program running
}*/

/*void main(void){
	unsigned char num1 = 0x50;
	unsigned char num2 = 0x54;
	P0=0x00;
	if(num1>=num2){
		P0=num1;
	}
	else{
		P0=num2;
	}
}*/


void main(void){
	com();
}
	

