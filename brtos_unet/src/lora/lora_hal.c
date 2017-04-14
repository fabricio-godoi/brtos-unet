/*******************************************************************************
 * Copyright (c) 2015 Matthijs Kooijman
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * This the HAL to run LMIC on top of the BRTOS.
 *******************************************************************************/

#include "lora_config.h"
#include "lmic/lmic.h"
#include "hal.h"
#include "lora_hal.h"
#include "lora_hal_port.h"
#include <stdio.h>


// -----------------------------------------------------------------------------
// I/O

static void hal_io_init () {
    // NSS and DIO0 are required, DIO1 is required for LoRa, DIO2 for FSK
    ASSERT(lmic_pins.nss != LMIC_UNUSED_PIN);
    ASSERT(lmic_pins.dio[0] != LMIC_UNUSED_PIN);
//    ASSERT(lmic_pins.dio[1] != LMIC_UNUSED_PIN || lmic_pins.dio[2] != LMIC_UNUSED_PIN);

    NSS_PIN_INIT();
    //DIO0_PIN_INIT();
    DIO0_INT_ENABLE();

//    if (lmic_pins.rxtx != LMIC_UNUSED_PIN)
//        pinMode(lmic_pins.rxtx, OUTPUT);
//    if (lmic_pins.rst != LMIC_UNUSED_PIN)
//        pinMode(lmic_pins.rst, OUTPUT);
//
//    pinMode(lmic_pins.dio[0], INPUT);
//    if (lmic_pins.dio[1] != LMIC_UNUSED_PIN)
//        pinMode(lmic_pins.dio[1], INPUT);
//    if (lmic_pins.dio[2] != LMIC_UNUSED_PIN)
//        pinMode(lmic_pins.dio[2], INPUT);
}

// val == 1  => tx 1
void hal_pin_rxtx (u1_t val)
{
//    if (lmic_pins.rxtx != LMIC_UNUSED_PIN)
//        digitalWrite(lmic_pins.rxtx, val);
}

// set radio RST pin to given value (or keep floating!)
void hal_pin_rst (u1_t val) {
    if (lmic_pins.rst == LMIC_UNUSED_PIN)
        return;

//    if(val == 0 || val == 1) { // drive pin
//        pinMode(lmic_pins.rst, OUTPUT);
//        digitalWrite(lmic_pins.rst, val);
//    } else { // keep pin floating
//        pinMode(lmic_pins.rst, INPUT);
//    }
}

static bool dio_states[NUM_DIO] = {0};
volatile uint8_t x;
static void hal_io_check() {
    uint8_t i;

    for (i = 0; i < NUM_DIO; ++i) {
        if (lmic_pins.dio[i] == LMIC_UNUSED_PIN)
            continue;

        if (i==0)
        {
        	x = GPIOPinRead(DIO0_BASE,DIO0_PIN);
        	if(dio_states[i] != x)
        	{
        		dio_states[i] = !dio_states[i];
        		if (dio_states[i])
        		    radio_irq_handler(i);
        	}
        }


        /*
        if (dio_states[i] != digitalRead(lmic_pins.dio[i]))
        {
            dio_states[i] = !dio_states[i];
            if (dio_states[i])
                radio_irq_handler(i);
        }
        */
    }
}

// -----------------------------------------------------------------------------
// SPI
static void hal_spi_init ()
{
	  init_SPI(0,1);
}

void hal_pin_nss (u1_t val) {


    if (!val)
    	NSS_LOW;
    else
    	NSS_HIGH;
}

// perform SPI transaction with radio
u1_t hal_spi (u1_t out) {
    u1_t res = 0;

    SPI0_TransferChar(&out);
    res = out;
    return res;
}

// -----------------------------------------------------------------------------
// TIME
#include "BRTOS.h"

static clock_t  ticks;

#if !NETWORK_ENABLE && LORA_NET
void BRTOS_TimerHook(void)
{
	ticks++;
}
#endif

static void hal_time_init () {
    // Nothing to do
	ticks = 0;
}

u4_t hal_ticks () {

    return ticks;
}

void hal_waitUntil (u4_t time)
{
    hal_delay(time);
}

// check and rewind for target time
u1_t hal_checkTimer (u4_t time)
{
    return 0;
}

static uint8_t irqlevel = 0;

void hal_disableIRQs () {
	noInterrupts();
    irqlevel++;
}

void hal_enableIRQs () {
    if(--irqlevel == 0) {
        interrupts();

        // Instead of using proper interrupts (which are a bit tricky
        // and/or not available on all pins on AVR), just poll the pin
        // values. Since os_runloop disables and re-enables interrupts,
        // putting this here makes sure we check at least once every
        // loop.
        //
        // As an additional bonus, this prevents the can of worms that
        // we would otherwise get for running SPI transfers inside ISRs
        // hal_io_check();
    }
}

void hal_sleep () {
    // Not implemented
}

// -----------------------------------------------------------------------------

#if defined(LMIC_PRINTF_TO)
static int uart_putchar (char c, FILE *)
{
    LMIC_PRINTF_TO.write(c) ;
    return 0 ;
}

void hal_printf_init() {
    // create a FILE structure to reference our UART output function
    static FILE uartout;
    memset(&uartout, 0, sizeof(uartout));

    // fill in the UART file descriptor with pointer to writer.
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

    // The uart is the standard output device STDOUT.
    stdout = &uartout ;
}
#endif // defined(LMIC_PRINTF_TO)

void hal_init () {
    // configure radio I/O and interrupt handler
    hal_io_init();
    // configure radio SPI
    hal_spi_init();
    // configure timer and interrupt handler
    hal_time_init();
#if defined(LMIC_PRINTF_TO)
    // printf support
    hal_printf_init();
#endif
}

void hal_failed (void)
{
#if defined(LMIC_FAILURE_TO)
	const char *file, u2_t line;
    LMIC_FAILURE_TO.println("FAILURE ");
    LMIC_FAILURE_TO.print(file);
    LMIC_FAILURE_TO.print(':');
    LMIC_FAILURE_TO.println(line);
    LMIC_FAILURE_TO.flush();
#endif
    hal_disableIRQs();
    while(1);
}
