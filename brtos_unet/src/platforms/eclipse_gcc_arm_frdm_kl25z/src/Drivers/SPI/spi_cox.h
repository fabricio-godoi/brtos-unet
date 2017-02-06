/**
* \file SPI.h
* \brief Serial peripheral interface driver function prototypes.
*
*
**/

#include "MKL25Z4.h"
#include "xhw_types.h"
#include "xsysctl.h"
#include "MemMapPtr_KL25Z4.h"
#include <stdint.h>

#define ENABLE_SPI0   TRUE
#define ENABLE_SPI1   TRUE

void init_SPI(uint8_t spi, uint8_t port);


#if (ENABLE_SPI0 == TRUE)
void SPI0_SendChar(uint8_t *data, int size);
void SPI0_GetChar(uint8_t *data, int size);
void SPI0_TransferChar(INT8U *data);
#endif


#if (ENABLE_SPI1 == TRUE)
void SPI1_SendChar(unsigned char data);
unsigned char SPI1_GetChar(void);
void SPI1_TransferChar(INT8U *data);
#endif

