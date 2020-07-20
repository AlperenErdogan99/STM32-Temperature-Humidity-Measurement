#include "w5500_control.h"
#include "main.h"


extern SPI_HandleTypeDef hspi3;


void cs_sel() {
	HAL_GPIO_WritePin(Wiznet_CS_GPIO_Port, Wiznet_CS_Pin, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(Wiznet_CS_GPIO_Port, Wiznet_CS_Pin, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	HAL_SPI_Receive(&hspi3, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi3, &b, 1, 0xFFFFFFFF);
}

void timeout_config(void)
{
	wiz_NetTimeout gWIZNETTIME = {.retry_cnt = 3,       		    //RCR = 3
	      	                        .time_100us = 2000};     		//RTR = 2000

	  ctlnetwork(CN_SET_TIMEOUT,(void*)&gWIZNETTIME); 				//set timeout w5500
	  ctlnetwork(CN_GET_TIMEOUT,(void*)&gWIZNETTIME); 				//set timeout w5500
}
void client_config(void)
{

	  wiz_NetInfo netInfo = { .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef},		// Mac address
	                           .ip 	= {192, 168, 1, 10},						// w5500's IP address
	                           .sn 	= {255, 255, 255,0},						// Subnet mask
	                           .gw 	= {192, 168, 1,1}};							// Gateway address

	  wizchip_setnetinfo(&netInfo); //set IP address
	  wizchip_getnetinfo(&netInfo); //set IP address

}
void Close_Server(W5500_Handle_t *w5500_ports)
{
	w5500_ports->close_cnt  = 0;
	w5500_ports->socket_num = 0;


	while(SOCK_OK != w5500_ports->close_cnt)
		{
			w5500_ports->close_cnt = close(w5500_ports->socket_num); 							//close to server
		}

	HAL_Delay(2500);
}
void Connect_Server(W5500_Handle_t *w5500_ports)
{


	w5500_ports->close_cnt = 10 ;
	w5500_ports->connect_cnt = 0 ;
	w5500_ports->server_port = 5656 ;
	w5500_ports->socket_cnt = 10 ;
	w5500_ports->socket_num = 0 ;
	w5500_ports->socket_port = 5656 ;

	uint8_t server_ip[4] = {192,168,1,6} ; 							// Server's IP Address


	if((w5500_ports->socket_cnt = socket(w5500_ports->socket_num,Sn_MR_TCP,w5500_ports->socket_port,SF_TCP_NODELAY))==w5500_ports->socket_num)
		{
			HAL_Delay(250);
			while(w5500_ports->connect_cnt != SOCK_OK ) 								// When Return == SOCK_OK
				{

					w5500_ports->connect_cnt = connect((uint8_t )w5500_ports->socket_num,(uint8_t *)server_ip,(uint16_t )w5500_ports->server_port); // Connect to server
					HAL_Delay(250);
				}
		}



}
