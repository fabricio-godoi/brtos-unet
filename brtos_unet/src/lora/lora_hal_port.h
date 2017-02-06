/*
 * lora_hal_port.h
 */

#ifndef LORA_LORA_HAL_PORT_H_
#define LORA_LORA_HAL_PORT_H_

#include "BRTOS.h"

#if BRTOS_PLATFORM == BOARD_FRDM_KL25Z
#include "xhw_memmap.h"
#include "xhw_types.h"
#include "xsysctl.h"
#include "xgpio.h"
#include "xhw_gpio.h"
#include "xhw_ints.h"
#include "xcore.h"
#include "spi_cox.h"
#endif

#define hal_delay(x)    OSDelayTask(x)
#define hal_get_ticks()  OSGetTickCount()
#define noInterrupts()	UserEnterCritical()
#define interrupts()	UserExitCritical()
#include "pcg_basic.h"
#define random(x)		pcg32_boundedrand(x)
// SPI pins - SPI0
// SCK - PTD1
// MISO - PTD3
// MOSI - PTD2
// SS - PTE31

#define NSS_PIN_CFG     GPIO_PE31_PE31
#define NSS_BASE  	    GPIOE_BASE
#define NSS_PIN         GPIO_PIN_31
#define NSS_PIN_CLOCK	SYSCTL_PERIPH_GPIOE

#define NSS_PIN_CLOCK_INIT SysCtlPeripheralEnable(NSS_PIN_CLOCK)
#define NSS_AS_IO		GPIOPinConfigure(NSS_PIN_CFG)								///< Defines NSS pin as IO
#define NSS_DS			GPIOPadConfigSet(NSS_BASE, NSS_PIN, PORT_TYPE_DSE_HIGH)///< Defines NSS pin drive strength to high
#define NSS_LOW       	GPIOPinReset(NSS_BASE, NSS_PIN)     					///< NSS pin = 0
#define NSS_HIGH     	GPIOPinSet(NSS_BASE, NSS_PIN)     						///< NSS pin = 1
#define NSS_DIR_IN    	xGPIODirModeSet(NSS_BASE, NSS_PIN, xGPIO_DIR_MODE_IN)	///< NSS direction pin = in
#define NSS_DIR_OUT   	xGPIODirModeSet(NSS_BASE, NSS_PIN, xGPIO_DIR_MODE_OUT)	///< NSS direction pin = out

#define NSS_PIN_INIT()        		    \
do {                                    \
   NSS_PIN_CLOCK_INIT;					\
   NSS_AS_IO;							\
   NSS_DS;								\
   NSS_HIGH;							\
   NSS_DIR_OUT;							\
} while(0)

#define DIO0_PIN_CFG     GPIO_PA16_PA16
#define DIO0_BASE  	     GPIOA_BASE
#define DIO0_PIN         GPIO_PIN_16
#define DIO0_PIN_CLOCK	 SYSCTL_PERIPH_GPIOA

#define DIO0_PIN_CLOCK_INIT SysCtlPeripheralEnable(DIO0_PIN_CLOCK)
#define DIO0_AS_IO		GPIOPinConfigure(DIO0_PIN_CFG)								///< Defines DIO0 pin as IO
#define DIO0_DIR_IN    	xGPIODirModeSet(DIO0_BASE, DIO0_PIN, xGPIO_DIR_MODE_IN)	    ///< DIO0 direction pin = in

#define DIO0_PIN_INIT()        		    \
do {                                    \
   DIO0_PIN_CLOCK_INIT;					\
   DIO0_AS_IO;							\
   DIO0_DIR_IN;							\
} while(0)

#define DIO0_INTERRUPT_FLAG_CLR()       GPIOPinIntClear(DIO0_BASE, DIO0_PIN) //xHWREG(DIO0_BASE+PORT_ISFR) |= xHWREG(DIO0_BASE+PORT_ISFR)  // Limpa flag da interrupção externa
#define DIO0_INTERRUPT_ENABLE_CLR()		GPIOPinIntDisable(DIO0_BASE, DIO0_PIN)  					// desabilita interrupção externa
#define DIO0_INTERRUPT_ENABLE_SET()		GPIOPinIntEnable(DIO0_BASE, DIO0_PIN, GPIO_RISING_EDGE)   // habilita interrupção externa

#ifndef DIO0_INT_INIT
#define DIO0_INT_INIT   1

#define Enable_DIO0_INT_Pin()    \
   do{                                 \
	SysCtlPeripheralEnable(DIO0_PIN_CLOCK); 	\
	PORTA_PCR16 = (uint32_t)((PORTA_PCR16 & (uint32_t)~(uint32_t)(  \
				  PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x06))) | (uint32_t)(PORT_PCR_MUX(0x01) | PORT_PCR_PS_MASK )); \
	GPIOPinIntEnable(DIO0_BASE, DIO0_PIN, GPIO_RISING_EDGE);  \
	xIntEnable(INT_PORTA);   \
   }while(0);               \

#define DIO0_INT_ENABLE()				Enable_DIO0_INT_Pin()
#endif

#endif /* LORA_LORA_HAL_PORT_H_ */
