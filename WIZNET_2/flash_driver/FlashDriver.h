/*
 * yeni_driver.h
 *
 *  Created on: May 12, 2020
 *      Author: alperen
 */

/**********************************************************************************
 * 							yeni_driver supported by  memory map
 * 					For more information about the yeni_driver check the datasheet
 **********************************************************************************/

#ifndef FlashDriver
#define FlashDriver

#include "main.h"

/*
 * @brief:base address of pages
 * note: one block 64kb , one address 4kb memory
 */
#define block0_add0			0x000000
#define block1_add0			0x010000
#define block2_add0			0x020000
#define block3_add0			0x030000
#define block4_add0			0x040000
#define block5_add0			0x050000
#define block6_add0			0x060000
#define block7_add0			0x070000
#define block8_add0			0x080000
#define block9_add0			0x090000
#define block10_add0		0x0A0000
#define block11_add0		0x0B0000
#define block12_add0		0x0C0000
#define block13_add0		0x0D0000
#define block14_add0		0x0E0000
#define block15_add0		0x0F0000

/*
 * note:use offset value for calculate all pages address
 */
#define mem_offset				0x001000

/*
 * CS Pin Macros
 */
#define FLASH_CS_GPIO_Port					GPIOA
#define FLASH_CS_Pin						GPIO_PIN_0
#define RxBufferSize 						260

/*
 * Cs Select Deselect macros
 */
#define EXTFLASHCSPIN_HIGH HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);
#define EXTFLASHCSPIN_LOW HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);

unsigned char spi_rx_buf[RxBufferSize];
unsigned char spi_tx_buf[RxBufferSize];

typedef struct {
	unsigned char Status;
	unsigned short Sector;
	unsigned char Page;
} ExtFlash_t;

typedef struct {
	unsigned char WIP; //write in progress
	unsigned char WEL; //Write Enable Latch
	unsigned char BPbits; //block protect
	unsigned char QE; //quad enable bit
	unsigned char SRWD; //status register write disable bit
} StatusRegister_t;

typedef struct {
	unsigned char SOTP;
	unsigned char LDSO;
	unsigned char PSB;
	unsigned char ESB;
	unsigned char PFAIL;
	unsigned char EFAIL;
} SecurityRegister_t;

typedef struct {

	unsigned int block[16][16];
	unsigned char tx_buf[260];
	uint8_t page_counter;
	uint8_t block_counter;

} Mem_Handle_t;

unsigned char WriteCommand(unsigned char command, unsigned short size);
unsigned char FlashInit(Mem_Handle_t *Mem_Control);
unsigned char FlashIsReady(void);
/*
 * Enable Write
 */
unsigned char WREN(void);
/*
 * @brief:Goes to different memory points
 */
void NextPage(Mem_Handle_t *Mem_Control, SHT21_Handle_t *SHT21_1);
/*
 * @brief:clears the address
 */
unsigned char SectorErase(unsigned int Add);
/*
 * -----------------------------
 */
unsigned char PageProgram(unsigned Add, unsigned char *buf);
unsigned char CheckPage(unsigned int Add);
/*
 * @brief:Read Status and Security Register
 * note:use it when reviewing an error.
 */
unsigned char ReadStatusRegister(StatusRegister_t *Status);
unsigned char ReadSecurityRegister(SecurityRegister_t *Status);
/*
 * @brief : Write and Read 4kb page .
 * note:Use with NextPage function .
 */
uint8_t ReadFlash(Mem_Handle_t *Mem_Control, SHT21_Handle_t *SHT21_1);//Read one page
uint8_t WriteFlash(Mem_Handle_t *Mem_Control, SHT21_Handle_t *SHT21_1);	//Write one page
/*
 * @brief:Buffer pauses to write until it is full.
 *        it is allowed to send when the time comes.
 * note:Use two functions together
 */
void Accumulation(SHT21_Handle_t *SHT21_1, Mem_Handle_t *Mem_Control);
void Accumulation_Init(SHT21_Handle_t *SHT21_1);

/*
 * @brief: Writing and Reading sensor data
 * note: you can use just this function write for send data to memory
 */
void Send_Flash(Mem_Handle_t *Mem_Control, SHT21_Handle_t *SHT21_1);

#endif
