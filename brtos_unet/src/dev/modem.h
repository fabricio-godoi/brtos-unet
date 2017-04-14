/* The License
 * 
 * Copyright (c) 2015 Universidade Federal de Santa Maria
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

*/


/** \addtogroup devices
 *  @{
 */
 
 
/** \addtogroup modems
 *  @{
 Bibliotecas para acesso a diversos modelos de modems.
 */
 

/*! \file modem.h
 \brief Definicoes de interface para modems.
 
 */
 
#ifndef MODEM_H
#define MODEM_H

typedef enum
{
	MODEM_SETUP,
	MODEM_INIT,
	MODEM_OPEN,
	MODEM_CLOSE
} state_t;


typedef enum
{
	MODEM_OK,
	MODEM_ERR,
	MODEM_STATE_ERR
}modem_ret_t;

typedef uint8_t (*initialize)(void);
typedef uint8_t (*input)(char *, uint16_t*);
typedef uint8_t (*output)(char *, uint16_t);
typedef uint8_t (*set_host)(char *);
typedef uint8_t (*set_ip)(char *);
typedef uint8_t (*get_connect)(void);
typedef uint8_t (*resolve_ip)(char * host, char *_ip);

typedef struct
{
	initialize init;
	input receive;
	output send;
	set_host sethost;
	set_ip   setip;
	get_connect  is_connected;
	resolve_ip  resolveip;
}modem_driver_t;


#endif

/** @}*/
/** @}*/
