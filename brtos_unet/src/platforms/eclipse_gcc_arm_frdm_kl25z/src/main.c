//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

/* MCU and OS includes */
#include "BRTOS.h"
#include "xwdt.h"

/* Config. files */
#include "BoardConfig.h"
#include "tasks.h"        /* for tasks prototypes */
#include "xsysctl.h"
#include "xhw_ints.h"
#include "MemMapPtr_KL25Z4.h"

void main_app(void);

// ----------------------------------------------------------------------------
//
// KL25 led blink sample (trace via DEBUG).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//


// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(void)
{
  // Init system clock
  //xSysCtlClockSet(48000000, xSYSCTL_XTAL_8MHZ | xSYSCTL_OSC_MAIN);
  SystemInit();

  // Initialize system and tasks
  main_app();

  // Infinite loop
  while (1)
    {
    }
  // Infinite loop, never return.
}

volatile unsigned int HighFrequencyTimer = 0;
#define TPM_SC_TOF_MASK                          0x80u
void TimerHandler(void){
  TPM0_SC |= TPM_SC_TOF_MASK;

  HighFrequencyTimer++;
}

void OSConfigureTimerForRuntimeStats( void )
{
	SysCtlPeripheralClockSourceSet(SYSCTL_PERIPH_TPM_S_MCGPLLCLK_2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TMR0);
	TPM0_SC = 0;
	TPM0_MOD = (configCPU_CLOCK_HZ / 100000) - 1;
	TPM0_SC = 0x48;

    void xIntEnable(unsigned long ulInterrupt);
    xIntEnable(INT_FTM0);
}

uint32_t OSGetTimerForRuntimeStats(void)
{
	return HighFrequencyTimer;
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
