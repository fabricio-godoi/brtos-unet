#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H


#define UNET_DEFAULT_STACKSIZE  		(384)

/*************************************************/
/** Radio configuration - used by radio driver   */ 
// #define MAC64_MEM_ADDRESS    0x00001FF0

// Power levels
#define RFTX_0dB    0x00
#define RFTX_m10dB  0x40
#define RFTX_m20dB  0x80
#define RFTX_m30dB  0xC0
#define RFTX_m36dB  0xF8

#define INCLUDE_PRINT		0

#if 1
#define PRINT_PING_INFO()
#else
#define PRINT_PING_INFO()	UARTPutString(0x4006A000, "Ping recebido do no ");\
							UARTPutString(0x4006A000, PrintDecimal(mac_packet.SrcAddr_16b, buffer));\
							UARTPutString(0x4006A000, " com RSSI ");\
							UARTPutString(0x4006A000, PrintDecimal(mac_packet.Frame_RSSI, buffer));\
							UARTPutString(0x4006A000, "\n\r");
#endif
//#define ANT_CHIP
#if ANT_CHIP
#define TX_POWER_LEVEL   RFTX_0dB       //RFTX_m30dB   // 6 dB for antenna chip
#else
#define TX_POWER_LEVEL   RFTX_0dB        
#endif

#if 0
#define ACTIVITY_LED
#define ACTIVITY_LED_AS_IO		GPIOPinConfigure(GPIO_PD1_PD1)								///< Defines LED pin as IO
#define ACTIVITY_LED_DS			GPIOPadConfigSet(GPIOD_BASE, GPIO_PIN_1, PORT_TYPE_DSE_HIGH)///< Defines LED pin drive strength to high
#define ACTIVITY_LED_LOW   		GPIOPinReset(GPIOD_BASE, GPIO_PIN_1)     					///< LED pin = 0
#define ACTIVITY_LED_HIGH  		GPIOPinSet(GPIOD_BASE, GPIO_PIN_1)     						///< LED pin = 1
#define ACTIVITY_LED_TOGGLE  	GPIOPinToggle(GPIOD_BASE, GPIO_PIN_1)     					///< Toggle LED pin
#define ACTIVITY_LED_DIR_IN  	xGPIODirModeSet(GPIOD_BASE, GPIO_PIN_1, xGPIO_DIR_MODE_IN) 	///< LED direction pin = in
#define ACTIVITY_LED_DIR_OUT  	xGPIODirModeSet(GPIOD_BASE, GPIO_PIN_1, xGPIO_DIR_MODE_OUT)	///< LED direction pin = out

#endif
#define RSSI_BUFFER_SIZE  50   //1-100 only

/****************************************************/
#endif
