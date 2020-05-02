/* 
 * File: palindrome.c 
 *
 *
 * Description: 1st Assignment for "Microprocessors and Peripherals" course 
 *
 *
 * Authors: Christoforidis Savvas, schristo@ece.auth.gr
 *          Portokalidis Stavros , stavport@ece.auth.gr
 *    
 *
 * Date: 3 May 2020
 *
 * 
*/

#include <stdio.h>


__asm void palindrome(const char* str, int* result) {

	MOV r2, #0

init_loop
	LDRB  r3, [r0]       // Load byte into r3 from memory pointed to by r0 (str pointer)
	ADDS  r0, #1         // Increment str pointer
	ADDS  r2, #1         // Increment size counter
	CMP   r3, #0         // Was the byte 0?
	BNE   init_loop	     // If not, repeat the loop
	SUBS r2, r2, #2	     // r2 holds the size-1 of the string (without \0)
	SUBS r0, r0, #2	     // r0 points the final position of str (before "\0")

 	MOV r4, r0           // r4 points the final position of str (before "\0")
	SUBS r0, r0, r2      // r0 points the first character of str

	
palindrome_loop
	
	LDRB r3, [r4]        // Load byte into r3 from memory pointed to by r4 
	LDRB r2, [r0]        // Load byte into r2 from memory pointed to by r0

	CMP r0, r4           
	BGE palindrome_exit  // if r0 >= r4 go to palindrome_exit label
                       
                             // Else											 
	ADDS r0, r0, #1      // r0 points to next memory address
	SUBS r4, r4, #1      // r4 points to previous memory address  

	CMP r3, r2
	BEQ palindrome_loop  // if r3 == r2 go to palindrome_loop label

                             // Else												
	MOV r2, #0           // r2 take the value 0
	STR r2, [r1]         // Store byte in r2 into memory pointed to by r1 (result)
	
	BX lr                // Return from subroutine

palindrome_exit
	MOV r2, #1           // r2 take the value 1
	STR r2, [r1]         // Store byte in r2 into memory pointed to by r1 (result)
	
	BX lr                // Return from subroutine
}


int main() {
	
	int result[1];
	volatile int flag = 0;
	int counter = 0;
	
	/*#####################  1st  ##################################### */
	
	counter++;
	const char str[] = "SEBARANARABES";
	
	palindrome(str, result);
	
	if(result[0] == 1) {
		flag = 1;
	}
	else if(result[0] == 0){
		flag = 0;
	}
	
	/*#####################  2nd  ##################################### */
	
	counter++;
	const char str2[] = "NO PALINDROME";
	
	palindrome(str2, result);
	
	if(result[0] == 1) {
		flag = 1;
	}
	else if(result[0] == 0){
		flag = 0;
	}
	
	/*#####################  3rd  ##################################### */
	
	counter++;
	const char str3[] = "SAVVAS";
	
	palindrome(str3, result);
	
	if(result[0] == 1) {
		flag = 1;
	}
	else if(result[0] == 0){
		flag = 0;
	}
	
	palindrome(str3, result);
	
	while (1) {
	}
}
