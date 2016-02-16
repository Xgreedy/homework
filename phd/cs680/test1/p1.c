/*
 * test1.c - for CS680 course
 *
 * Weiwei Jia <wj47@njit.edu> 2016
 */

#include <stdio.h>

int asm_sum(int x, int y) {
	int result = x;
	int _x = x;
	//int _y = y;
	int i = 0;
	int j = y - x;

	__asm __volatile__ (
			"cld\n\t"
			"loop:"
			"add %%ebx, %%eax;"
			"add $1, %%ecx;"
			"add %%ecx, %%eax;"
			"cmp %%ecx, %%edx;"
			"jne loop;"
			: "=a" (result) 
			: "a" (result), "b" (_x), "c" (i), "d" (j)
			:
			);

	return result;
}

int main(int argc, char **argv) {
	int y = 5;
	int x = 1;

	int result = asm_sum(1, 5);
	printf("result is %d\n", result);
	return 0;
}
