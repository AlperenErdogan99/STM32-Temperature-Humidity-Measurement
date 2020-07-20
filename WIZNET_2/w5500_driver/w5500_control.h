#ifndef w5500_control
#define w5500_control

/***************************************************************************
 * 							APIs supported by this driver
 * 					For more information about the APIs check the function definitions
 ***************************************************************************/


#include "main.h"

/*
 * CS pin macros
 */
#define Wiznet_CS_Pin 					GPIO_PIN_0
#define Wiznet_CS_GPIO_Port 			GPIOB

/*
 * socket API's counter
 */
uint8_t  rbuf ;

/*
 * w5500 handle structure
 */
typedef struct
{
	uint8_t  connect_cnt ;
	uint8_t  socket_num  ;					/*!<counter for socket()		*/
	uint8_t  close_cnt   ;					/*!<counter for close()			*/
	uint8_t  socket_cnt  ;					/*!<counter for socket port		*/
	uint16_t server_port ;					/*!<counter for server port		*/
	uint16_t socket_port ;					/*!<counter for socket number	*/
	uint8_t  rbuf        ;					/*!<counter for connect()		*/
} W5500_Handle_t;


/*
 * note: Use this 4 functions for SPI configuration
 */

void cs_sel()       ; 						//SPI CS pin select
void cs_desel()     ; 						//SPI CS pin deselect
uint8_t spi_rb(void);						//SPI read 1byte
void spi_wb(uint8_t);						//SPI write 1byte


/*
 * note: Use this function for timeout configuration
 */
void timeout_config(void);

/*
 * use this function for configuration client's(w5500) IP and etc .
 */

void client_config(void);

/*
 * note: use this 2 functions for connect and disconnect
 * note: configure server IP in connect_server function
 * note: configure connection and disconnection parameters in this 2 functions
 */
void Close_Server(W5500_Handle_t *w5500_ports);
void Connect_Server(W5500_Handle_t *w5500_ports);


#endif
