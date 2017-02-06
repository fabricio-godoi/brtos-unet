#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H


#include "system.h"
#include "HAL.h"
//#include "MRF24J40.h"

#include "hardware.h"
#include "../uNET/radio/mrf24j40.h"
#if (__GNUC__)
#define Int_TPM1_Ch1_Handler 		Radio_Interrupt
#endif

#define UNET_DEFAULT_STACKSIZE  		(256)

/******************************************************************/
/* ADC channels for voltage, current, temperature, light          */
/* Relay output pin                                               */

#define   PIN_RELAY           PTED_PTED2
#define   CHAN_LIGHT          (INT8U)18
#define   CHAN_VIN            (INT8U)1
#define   CHAN_VLOAD          (INT8U)0
#define   CHAN_ILOAD          (INT8U)19
#define   CORE_TEMP           (INT8U)26
/*********************************************************/

/*********************************************************/
/* EEPROM Config */
#define EEPROM_ADDRESS        0x0001FC00
/*********************************************************/

/*********************************************************/
/* DBG Config */
#define BDM_ENABLE            1
#define BDM_DEBUG_OUT         PTAD_PTAD4
#define TEST_PIN              0
/*********************************************************/

/*************************************************/
/** Radio configuration - used by radio driver   */ 
// #define MAC64_MEM_ADDRESS    0x00001FF0

// Power levels
#define RFTX_0dB    0x00
#define RFTX_m10dB  0x40
#define RFTX_m20dB  0x80
#define RFTX_m30dB  0xC0
#define RFTX_m36dB  0xF8

#define INCLUDE_PRINT		1

#if 0
#define PRINT_PING_INFO()	UARTPutString(0x4006A000, "Ping recebido do nó ");\
							UARTPutString(0x4006A000, PrintDecimal(mac_packet.SrcAddr_16b, buffer));\
							UARTPutString(0x4006A000, " com RSSI ");\
							UARTPutString(0x4006A000, PrintDecimal(mac_packet.Frame_RSSI, buffer));\
							UARTPutString(0x4006A000, "\n\r");
#endif


// Transceiver Configuration
#define RF_INT_TIMER     1
#define RF_INT_KEYB      0
#define RF_INT_TYPE      RF_INT_TIMER

#if PROCESSOR == COLDFIRE_V1
#define RFIF             TPM1C1SC_CH1F = 0  	// Limpa flag da interrupção externa
#define RFINT_ENABLE     TPM1C1SC_CH1IE = 1     // habilita interrupção externa
#define RFINT_DISABLE    TPM1C1SC_CH1IE = 0     // desabilita interrupção externa
#define RFFLAG           TPM1C1SC
#define NEEDS_INIT_TIMER 0
#define RF_TPMSC         TPM1SC
#define RF_MOD           TPM1MOD
#endif

#if PROCESSOR == ARM_Cortex_M0
#define RFIF              xHWREG(PORTD_BASE+PORT_ISFR) |= xHWREG(PORTD_BASE+PORT_ISFR)  // Limpa flag da interrupção externa
#define RFINT_ENABLE      GPIOPinIntEnable(GPIOD_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE)   // habilita interrupção externa
#define RFIINT_DISABLE    GPIOPinIntDisable(GPIOD_BASE, GPIO_PIN_4)  					// desabilita interrupção externa
#define RFFLAG			  0
#define NEEDS_INIT_TIMER  0
#define RF_TPMSC          TPM1SC
#define RF_MOD            TPM1MOD
#endif



//#define ANT_CHIP

#ifdef ANT_CHIP
#define TX_POWER_LEVEL   RFTX_0dB       //RFTX_m30dB   // 6 dB for antenna chip
#else
#define TX_POWER_LEVEL   RFTX_0dB        
#endif

// #define TX_POWER_LEVEL   RFTX_0dB

// Defines the radio pins
#if PROCESSOR == COLDFIRE_V1
#define PHY_CS_LOW       	PTDD_PTDD3 = 0     ///< CS pin = 0
#define PHY_CS_HIGH     	PTDD_PTDD3 = 1     ///< CS pin = 1
#define PHY_CS_DIR_IN    	PTDDD_PTDDD3 = 0   ///< CS direction pin = in
#define PHY_CS_DIR_OUT   	PTDDD_PTDDD3 = 1   ///< CS direction pin = out
#define PHY_RESETn_LOW   	PTED_PTED6 = 0     ///< RESET pin = 0
#define PHY_RESETn_HIGH  	PTED_PTED6 = 1     ///< RESET pin = 1
#define PHY_RESETn_DIR_IN  	PTEDD_PTEDD6 = 0   ///< RESET direction pin = in
#define PHY_RESETn_DIR_OUT  PTEDD_PTEDD6 = 1   ///< RESET direction pin = out
#define PHY_WAKE_LOW     	PTHD_PTHD1 = 0     ///< WAKE pin = 0
#define PHY_WAKE_HIGH    	PTHD_PTHD1 = 1     ///< WAKE pin = 1
#define PHY_WAKE_DIR_IN    	PTHDD_PTHDD1 = 0   ///< WAKE direction pin = in
#define PHY_WAKE_DIR_OUT    PTHDD_PTHDD1 = 1   ///< WAKE direction pin = out

// Defines the tick timer used to compute stocastic address
#define TIMER_ADDR       TPM1CNT          ///< Tick Timer register used in stocastic address generation
#endif

// Defines activity LED pin
//#define ACTIVITY_LED				PTCD_PTCD0
//#define ACTIVITY_LED_AS_IO												///< Defines LED pin as IO
//#define ACTIVITY_LED_DS			PTCDS_PTCDS0 = 1						///< Defines LED pin drive strength to high
//#define ACTIVITY_LED_LOW   		PTCD_PTCD0 = 0     						///< LED pin = 0
//#define ACTIVITY_LED_HIGH  		PTCD_PTCD0 = 1     						///< LED pin = 1
//#define ACTIVITY_LED_TOGGLE  		ACTIVITY_LED = ~ACTIVITY_LED     		///< Toggle LED pin
//#define ACTIVITY_LED_DIR_IN  		PTCDD_PTCDD0 = 0 						///< LED direction pin = in
//#define ACTIVITY_LED_DIR_OUT  	PTCDD_PTCDD0 = 1						///< LED direction pin = out

// Defines SPI port number
#define SPINB            1

#if (SPINB == 1)
#define SPIS             SPI1S
#define SPID             SPI1D
#define SPIC1            SPI1C1
#define SPIC2            SPI1C2
#define SPIBR            SPI1BR
#define SPIC1_SPE        SPI1C1_SPE
#define SPIS_SPTEF       SPI1S_SPTEF
#define SPIS_SPRF        SPI1S_SPRF
#elif (SPINB == 2)
#define SPIS             SPI2S
#define SPID             SPI2D
#define SPIC1            SPI2C1
#define SPIC2            SPI2C2
#define SPIBR            SPI2BR
#define SPIC1_SPE        SPI2C1_SPE
#define SPIS_SPTEF       SPI2S_SPTEF
#define SPIS_SPRF        SPI2S_SPRF
#endif

#define RADIO_DRIVER_WATCHDOG 1
#define RFCTRL1_VAL       0x02
#define PA_LEVEL          0x00  // -0.00 dBm
#define FREQUENCY_BAND    2400   
#define CHANNEL_ERROR     (INT8U)255 
#define RSSI_BUFFER_SIZE  50   //1-100 only

/****************************************************/

#endif
