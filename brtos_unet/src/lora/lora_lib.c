/*
 * lora_lib.c
 *
 */


/*******************************************************************************
 * Copyright (c) 2015 Matthijs Kooijman
 *
 * Permission is hereby granted, free of charge, to anyone
 * obtaining a copy of this document and accompanying files,
 * to do whatever they want with them without any restriction,
 * including, but not limited to, copying, modification and redistribution.
 * NO WARRANTY OF ANY KIND IS PROVIDED.
 *
 * This example transmits data on hardcoded channel and receives data
 * when not transmitting. Running this sketch on two nodes should allow
 * them to communicate.
 *******************************************************************************/

#include "lora_config.h"
#include "lmic/lmic.h"
#include "lora_hal.h"
#include "lora_hal_port.h"

#if !defined(DISABLE_INVERT_IQ_ON_RX)
#error This example requires DISABLE_INVERT_IQ_ON_RX to be set. Update \
       config.h in the lmic library to set it.
#endif

// How often to send a packet. Note that this sketch bypasses the normal
// LMIC duty cycle limiting, so when you change anything in this sketch
// (payload length, frequency, spreading factor), be sure to check if
// this interval should not also be increased.
// See this spreadsheet for an easy airtime and duty cycle calculator:
// https://docs.google.com/spreadsheets/d/1voGAtQAjC1qBmaVuP1ApNKs1ekgUjavHuVQIXyYSvNc
#define TX_INTERVAL 2000

// Pin mapping

const struct lmic_pinmap lmic_pins = {
    .nss = NSS_PIN,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN,
    .dio = {DIO0_PIN, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};


// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

void onEvent (ev_t ev) {
}

osjob_t txjob;
osjob_t timeoutjob;
static void tx_func (osjob_t* job);

// Transmit the given string and call the given function afterwards
void tx(const char *str, osjobcb_t func) {
  os_radio(RADIO_RST); // Stop RX first
  hal_delay(1); // Wait a bit, without this os_radio below asserts, apparently because the state hasn't changed yet
  LMIC.dataLen = 0;
  while (*str)
    LMIC.frame[LMIC.dataLen++] = *str++;
  LMIC.osjob.func = func;
  os_radio(RADIO_TX);
}

// Enable rx mode and call func when a packet is received
void rx(osjobcb_t func) {
  LMIC.osjob.func = func;
  LMIC.rxtime = os_getTime(); // RX _now_
  // Enable "continuous" RX (e.g. without a timeout, still stops after
  // receiving a packet)
  os_radio(RADIO_RXON);
}

static void rxtimeout_func(osjob_t *job) {

}

static void rx_func (osjob_t* job) {

  // Timeout RX (i.e. update led status) after 3 periods without RX
  os_setTimedCallback(&timeoutjob, os_getTime() + ms2osticks(3*TX_INTERVAL), rxtimeout_func);

  // Reschedule TX so that it should not collide with the other side's
  // next TX
  os_setTimedCallback(&txjob, os_getTime() + ms2osticks(TX_INTERVAL/2), tx_func);

//  Serial.print("Got ");
//  Serial.print(LMIC.dataLen);
//  Serial.println(" bytes");
//  Serial.write(LMIC.frame, LMIC.dataLen);
//  Serial.println();

  // Restart RX
  rx(rx_func);
}

static void txdone_func (osjob_t* job) {
  rx(rx_func);
}

// log text to USART and toggle LED
static void tx_func (osjob_t* job) {
  // say hello
  tx("Hello, world!", txdone_func);
  // reschedule job every TX_INTERVAL (plus a bit of random to prevent
  // systematic collisions), unless packets are received, then rx_func
  // will reschedule at half this time.
  os_setTimedCallback(job, os_getTime() + ms2osticks(TX_INTERVAL + random(500)), tx_func);
}

static void rx_pkt (osjob_t* job) {

  // Timeout RX (i.e. update led status) after 3 periods without RX
  // os_setTimedCallback(&timeoutjob, os_getTime() + ms2osticks(3*TX_INTERVAL), rxtimeout_func);

//  Serial.print("Got ");
  	(void)LMIC.dataLen;
//  Serial.println(" bytes");
    (void)LMIC.frame;

  // Restart RX
  rx(rx_pkt);
}

// application entry point
void lora_setup() {

  // initialize runtime env
  os_init();

  // Set up these settings once, and use them for both TX and RX

#if defined(CFG_eu868)
  // Use a frequency in the g3 which allows 10% duty cycling.
  LMIC.freq = 869525000;
#elif defined(CFG_us915)
  LMIC.freq = 902300000;
#endif

  // Maximum TX power
  LMIC.txpow = 20;
  // Use a medium spread factor. This can be increased up to SF12 for
  // better range, but then the interval should be (significantly)
  // lowered to comply with duty cycle limits as well.
  LMIC.datarate = DR_SF12CR;
  // This sets CR 4/5, BW125 (except for DR_SF7B, which uses BW250)
  LMIC.rps = updr2rps(LMIC.datarate);


  // setup initial job
  os_setCallback(&txjob, tx_func);
}

static uint16_t timer;

#include "BRTOS.h"

BRTOS_Sem *lora_isr;


void Lora_Net_Task(void *p)
{
	(void)p;
	lora_setup();

#if LORA_RX == 1
	ASSERT(OSSemCreate(0,&lora_isr) == ALLOC_EVENT_OK);
	rx(rx_pkt);
#endif

#if LORA_RX == 0
	DIO0_INTERRUPT_ENABLE_CLR();
#endif

	while(1)
	{

#if LORA_RX == 1
		OSSemPend(lora_isr, 0);
#else
		tx("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?", NULL);
#endif

		OSDelayTask(5000);
	}
}

void PORTA_IRQHandler(void)
{

	DIO0_INTERRUPT_FLAG_CLR();

	radio_irq_handler(0);
	OSSemPost(lora_isr);

	#if PROCESSOR == ARM_Cortex_M0
	OS_INT_EXIT_EXT();
	#endif
}
