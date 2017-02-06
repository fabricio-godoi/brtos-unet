/*
 ============================================================================
 Name        : brtos_win32.c
 Author      : Carlos H. Barriquello
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

extern int main_app(void);

int main(void) {

	main_app();
	return EXIT_SUCCESS;
}
