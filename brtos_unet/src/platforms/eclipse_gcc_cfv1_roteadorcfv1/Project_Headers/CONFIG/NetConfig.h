#ifndef NET_CONFIG_H
#define NET_CONFIG_H

#include "BRTOS.h"


// Define network support
#define NETWORK_ENABLE                      1
#define RUN_TESTS							FALSE
#define UNET_HEADER_PRINT_ENABLE   			0
#define EXPERIMENTAL						0
#define DEBUG_PRINTF						0
#define print_addr64(addr) PRINTF("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n\r", ((uint8_t *)addr)[0], ((uint8_t *)addr)[1], ((uint8_t *)addr)[2], ((uint8_t *)addr)[3], ((uint8_t *)addr)[4], ((uint8_t *)addr)[5], ((uint8_t *)addr)[6], ((uint8_t *)addr)[7])

#define USE_BITMASK							1

#define UNET_DEFAULT_STACKSIZE  	(336)
#define UNET_RADIO_STACKSIZE   		(UNET_DEFAULT_STACKSIZE) - 16
#define UNET_LINK_STACKSIZE    		(UNET_DEFAULT_STACKSIZE) + 32
#define UNET_ACK_STACKSIZE     		(UNET_DEFAULT_STACKSIZE) + 16
#define UNET_ROUTER_STACKSIZE  		(UNET_DEFAULT_STACKSIZE) + 32

#define UNET_STACKS   (UNET_RADIO_STACKSIZE + UNET_LINK_STACKSIZE + 2*(UNET_ACK_STACKSIZE + UNET_ROUTER_STACKSIZE))



/* available radios */
#include "../uNET/radio/mrf24j40.h"
#include "../uNET/radio/radio_null.h"
#define NEIGHBOURHOOD_SIZE   				(8)
#define UNET_RADIO 							mrf24j40_driver

// Network device types
#define   PAN_COORDINATOR                   0
#define   ROUTER                            1
#define   INSTALLER                         2

// Network device type: see options above
#ifndef 	UNET_DEVICE_TYPE
#define   	UNET_DEVICE_TYPE                ROUTER
#endif

// CPU memory alignment
#define CPU_32_BITS                         1
#define CPU_16_BITS                         0
#define CPU_8_BITS                          0

// Reactive up route - 1 = on, 0 = off
#define USE_REACTIVE_UP_ROUTE               0

// GPSNET Tasks Priorities
#define RF_EventHandlerPriority     31
#define Timer_Priority     			28
#define UNET_Mutex_Priority         27
#define MAC_HandlerPriority         21
#define NWK_HandlerPriority         22
#define APP0_Priority               24
#define APP1_Priority               25
#define APP2_Priority               26
#define APP3_Priority               23

#define MAX_SEQUENCES_NUM  			16


// APPs signals 
#define SIGNAL_APP1       App1_event
//#define SIGNAL_APP2       App1_event

// UNET Tasks Stacks
#if !SIMULATOR
#if ((UNET_DEVICE_TYPE == PAN_COORDINATOR) || (UNET_DEVICE_TYPE == INSTALLER))
#define UNET_RF_Event_StackSize    (384)
#define UNET_MAC_StackSize         (384)
#define UNET_NWK_StackSize         (1280)
#else
#define ContikiMAC_StackSize       (384)
#define UNET_RF_Event_StackSize    (256)
#define UNET_MAC_StackSize         (384)
#define UNET_NWK_StackSize         (1088)
#endif
#else
#define ContikiMAC_StackSize       (8)
#define UNET_RF_Event_StackSize    (8)
#define UNET_MAC_StackSize         (8)
#define UNET_NWK_StackSize         (8)
#endif

#define TX_TIMEOUT       500


#define BRTOS_MUTEX       0
#define EMULATED_MUTEX    1
#define NWK_MUTEX_TYPE    BRTOS_MUTEX

/// RF Buffer Size
#define RFBufferSize      (INT16U)768      // max. 6 packets (128B)

/// Memory locations for network address and configurations
#if (UNET_DEVICE_TYPE == PAN_COORDINATOR)
  #define LAT_MEM_ADDRESS    0x0001FC00
  #define LON_MEM_ADDRESS    0x0001FC04
  #define MAC16_MEM_ADDRESS
  #define MAC64_MEM_ADDRESS  0x00001FF0
  #define PANID_MEM_ADDRESS
  #define PANID_INIT_VALUE   0x47,0x42
  #define MAC16_INIT_VALUE   0x00,0x00
  #define ROUTC_INIT_VALUE   0x01  
#else 
  //#define LAT_MEM_ADDRESS    0x000021C0
  //#define LON_MEM_ADDRESS    0x000021C4
  //#define MAC16_MEM_ADDRESS  0x000021C8
  #define LAT_MEM_ADDRESS    0x00001000
  #define LON_MEM_ADDRESS    0x00001004
  #define MAC16_MEM_ADDRESS  0x00001008
  #define PANID_MEM_ADDRESS  0x0000100C
  #define MAC64_MEM_ADDRESS  0x00000FF0
  //#define MAC64_MEM_ADDRESS  0x00001FF0
  //#define PANID_MEM_ADDRESS  0x000021CC
  #define PANID_INIT_VALUE   0x47,0x42
  #define MAC16_INIT_VALUE   0x12,0x42
  #define ROUTC_INIT_VALUE   0x00  
#endif

// IEEE EUI - globally unique number
#define EUI_7 0xCA
#define EUI_6 0xBA
#define EUI_5 0x60                       
#define EUI_4 0x89
#define EUI_3 0x50
#define EUI_2 0x16
#define EUI_1 0x77
#define EUI_0 0x84


/// Configuration for tests only
//#define GPSNET_TEST_POSITION

#ifdef GPSNET_TEST_POSITION
  #define TEST_POSITION_X       (20600)
  #define TEST_POSITION_Y       (5700)
 
  #define TEST_LAT_GPS_DEG      0x00
  #define TEST_LAT_GPS_MIN      0x00
  #define TEST_LAT_GPS_SEC      0x50
  #define TEST_LAT_GPS_DECSEC   0x78               

  #define TEST_LONG_GPS_DEG     0x00            
  #define TEST_LONG_GPS_MIN     0x00
  #define TEST_LONG_GPS_SEC     0x16
  #define TEST_LONG_GPS_DECSEC  0x44
#endif

#ifndef CHANNEL_INIT_VALUE
#define CHANNEL_INIT_VALUE	(26)
#endif

#define MULTICHANNEL_SUPPORT 1
#define NUM_ALLOWED_CHANNELS 1

#define FORCE_NO_MULTICHANNEL_SUPPORT 0


#endif









