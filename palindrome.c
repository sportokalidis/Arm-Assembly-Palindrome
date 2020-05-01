#include <stdio.h>


__asm void palindrome(const char* str, int* result) {

	MOV r2, #0

init_loop
	LDRB  r3, [r0]       // Load byte into r3 from memory pointed to by r0 (str pointer)
	ADDS  r0, #1         // Increment str pointer
	ADDS  r2, #1         // Increment size counter
	CMP   r3, #0         // Was the byte 0?
	BNE   init_loop	     // If not, repeat the loop
	SUBS r2, r2, #2			 // r2 holds the size-1 of the string (without \0)
	SUBS r0, r0, #2			 // r0 points the final position of str (before "\0")

 	MOV r4, r0			 		 // r4 points "\0"
	SUBS r0, r0, r2			 // r0 points the first character

	
palindrome_loop
	
	LDRB r3, [r4]
	LDRB r2, [r0]

	CMP r0, r4
	BGE palindrome_exit
	
	ADDS r0, r0, #1
	SUBS r4, r4, #1

	CMP r3, r2
	BEQ palindrome_loop

	MOV r2, #0
	STR r2, [r1]
	
	BX lr

palindrome_exit
	MOV r2, #1
	STR r2, [r1]
	
	BX lr
}


int main() {
	
	int result[1];
	volatile int flag = 0;
	int counter = 0;
	
	/*#####################  1st  ##################################### */
	
	counter++;
	const char str[] = "SAVVAS";
	
	// result = (int*) malloc(sizeof(int)); 
	palindrome(str, result);
	
	if(result[0] == 1) {
		// printf("%s: is a palindrome string !", str);
		// char flag1[] =  "Is palindrome" ;
		flag = 1;
	}
	else if(result[0] == 0){
		// printf("%s: is not a palindrome string !", str);
		// char flag2[] = "No Palindrome";
		flag = 0;
	}
	
	/*#####################  2nd  ##################################### */
	
	counter++;
	const char str2[] = "SAVVAS";
	
	palindrome(str2, result);
	
	if(result[0] == 1) {
		// printf("%s: is a palindrome string !", str);
		// char flag1[] =  "Is palindrome" ;
		flag = 1;
	}
	else if(result[0] == 0){
		// printf("%s: is not a palindrome string !", str);
		// char flag2[] = "No Palindrome";
		flag = 0;
	}
	
	/*#####################  3rd  ##################################### */
	
	counter++;
	const char str3[] = "No Palindrome";
	
	palindrome(str3, result);
	
	if(result[0] == 1) {
		// printf("%s: is a palindrome string !", str);
		// char flag1[] =  "Is palindrome" ;
		flag = 1;
	}
	else if(result[0] == 0){
		// printf("%s: is not a palindrome string !", str);
		// char flag2[] = "No Palindrome";
		flag = 0;
	}
	
	palindrome(str3, result);
	
	while (1) {
	}
}
