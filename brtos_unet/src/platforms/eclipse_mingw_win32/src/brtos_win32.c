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

/* BRTOS includes. */
#include "BRTOS.h"
#include "tasks.h"
#include "terminal.h"
#include "unet_api.h"

#if WINNT
#include "assert.h"
#endif


BRTOS_TH th1, th2, th3;

extern void  task_run_tests(void *);
extern void terminal_test(void);

int main(void) {

	  //terminal_test();
	  task_run_tests(NULL);

	  BRTOS_Init();

#define TERMINAL_ENABLE  0
#if TERMINAL_ENABLE
	  assert(OSInstallTask(&Terminal_Task,"Terminal",16,2,NULL,NULL) == OK);
#endif

	  UNET_Init();

	  assert(BRTOSStart() == OK);
	  return EXIT_SUCCESS;
}
