/*
 * yeni_driver.c
 *
 *  Created on: May 12, 2020
 *      Author: alperen
 */


#include "FlashDriver.h"
#include "main.h"
#include "string.h"

extern SPI_HandleTypeDef hspi1;

unsigned char FlashInit(Mem_Handle_t* Mem_Control)
{
 	  EXTFLASHCSPIN_HIGH;

 	 	uint8_t k ;
 	 	for(k=0;k<=16;k++)
 	 	{
 	 		Mem_Control->block[0][k]  = ((unsigned int)block0_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[1][k]  = ((unsigned int)block1_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[2][k]  = ((unsigned int)block2_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[3][k]  = ((unsigned int)block3_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[4][k]  = ((unsigned int)block4_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[5][k]  = ((unsigned int)block5_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[6][k]  = ((unsigned int)block6_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[7][k]  = ((unsigned int)block7_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[8][k]  = ((unsigned int)block8_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[9][k]  = ((unsigned int)block9_add0)+((unsigned int)mem_offset*k)  ;
 	 		Mem_Control->block[10][k] = ((unsigned int)block10_add0)+((unsigned int)mem_offset*k) ;
 	 		Mem_Control->block[11][k] = ((unsigned int)block11_add0)+((unsigned int)mem_offset*k) ;
 	 		Mem_Control->block[12][k] = ((unsigned int)block12_add0)+((unsigned int)mem_offset*k) ;
 	 		Mem_Control->block[13][k] = ((unsigned int)block13_add0)+((unsigned int)mem_offset*k) ;
 	 		Mem_Control->block[14][k] = ((unsigned int)block14_add0)+((unsigned int)mem_offset*k) ;
 	 		Mem_Control->block[15][k] = ((unsigned int)block15_add0)+((unsigned int)mem_offset*k) ;

 	 	}
 	 	Mem_Control->page_counter =  0 ;
 	 	Mem_Control->block_counter = 0 ;
 	 	memset(Mem_Control->tx_buf,0,260);   // clear send buffer

 	 	for(k=0;k<=16;k++){
 	 		SectorErase(Mem_Control->block[0][k]); // Clear all blocks

 	 	}


    return 1;
}
unsigned char FlashIsReady()
{
   unsigned char transferOK;
   memset(spi_rx_buf,0,RxBufferSize);
   transferOK=WriteCommand(0x9F,4);
   if(transferOK==HAL_OK && spi_rx_buf[1]==0xC2 && spi_rx_buf[2]== 0x28 && spi_rx_buf[3]==0x14)
       return 1;
   else return 0;
}

unsigned char WREN()
{
    unsigned char transferOK;
    transferOK=WriteCommand(0x06,1);
    return transferOK;

}

unsigned char WriteCommand(unsigned char command,unsigned short size)
{
    unsigned char transferOK;
    spi_tx_buf[0]=command;


    EXTFLASHCSPIN_LOW;
    HAL_Delay(100);
    //transferOK = SPI_transfer(spi_handle, &spiTransaction);
	  transferOK=HAL_SPI_TransmitReceive(&hspi1,&spi_tx_buf[0],&spi_rx_buf[0],size,500);
	  HAL_Delay(100);
	EXTFLASHCSPIN_HIGH;
    return transferOK;

}
unsigned char ReadStatusRegister(StatusRegister_t* Status)
{
    unsigned char transferOK;
    memset(spi_rx_buf,0,RxBufferSize);
    transferOK=WriteCommand(0x05,2);
    if(transferOK==HAL_OK)
    {
        Status->BPbits=(spi_rx_buf[1]>>2)&0xFF;
        Status->QE=(spi_rx_buf[1]>>6)&0x01;
        Status->SRWD=(spi_rx_buf[1]>>7)&0x01;
        Status->WEL=(spi_rx_buf[1]>>1)&0x01;
        Status->WIP=spi_rx_buf[1]&0x01;
    }
    return transferOK;

}

unsigned char ReadSecurityRegister(SecurityRegister_t* Status)
{
    unsigned char transferOK;
    memset(spi_rx_buf,0,RxBufferSize);
    transferOK=WriteCommand(0x2B,2);
    if(transferOK==HAL_OK)
    {
        Status->EFAIL=(spi_rx_buf[1]>>6)&0x01;
        Status->PFAIL=(spi_rx_buf[1]>>5)&0x01;
        Status->ESB=(spi_rx_buf[1]>>3)&0x01;
        Status->PSB=(spi_rx_buf[1]>>2)&0x01;
        Status->LDSO=(spi_rx_buf[1]>>1)&0x01;
        Status->SOTP=spi_rx_buf[1]&0x01;
    }
    return transferOK;

}
unsigned char SectorErase(unsigned int Add)
{
    StatusRegister_t FlashStatus;
    SecurityRegister_t SecurityReg;
    unsigned char i=0;
    unsigned char transferOK;
    memset(spi_rx_buf,0,RxBufferSize);
    transferOK=WREN();
    FlashStatus.WEL=0;
    while(FlashStatus.WEL==0)
    {
        HAL_Delay(20);
        transferOK=ReadStatusRegister(&FlashStatus);
        i++;
        if(i==200)
        {
            return 0;
        }
    }
    i=0;
    spi_tx_buf[1]=(Add>>16)&0xFF;
    spi_tx_buf[2]=(Add>>8)&0xFF;
    spi_tx_buf[3]=Add&0xFF;

    transferOK=WriteCommand(0x20,4);
    FlashStatus.WIP=1;
    while(FlashStatus.WIP==1)
    {
        HAL_Delay(20);
        transferOK=ReadStatusRegister(&FlashStatus);
        i++;
        if(i==200)
        {
            return 0;
        }
    }
    i=0;
    transferOK=ReadStatusRegister(&FlashStatus);
    transferOK=ReadSecurityRegister(&SecurityReg);
    if(transferOK==HAL_OK && SecurityReg.EFAIL==0 && SecurityReg.PFAIL==0)
    {
        return 1;
    }
    else
        return 0;
}

unsigned char PageProgram(unsigned Add , unsigned char* buf){
	StatusRegister_t FlashStatus;
	SecurityRegister_t SecurityReg;
	uint32_t i ;
	unsigned char transferOK;
	WREN();		// Write mode
	memset(spi_rx_buf,0,RxBufferSize); // sıfır ile dolduruldu rx buffer
	memset(spi_tx_buf,0,RxBufferSize); // sıfır ile dolduruldu rx buffer

	spi_tx_buf[0]= 0x02;
	spi_tx_buf[1]=(Add>>16)&0xFF;
    spi_tx_buf[2]=(Add>>8)&0xFF;
    spi_tx_buf[3]=Add&0xFF;

    for(i=4;i<257;i++)
    {
    	spi_tx_buf[i] = *buf;
    	buf++;
    }

    EXTFLASHCSPIN_LOW; 																// cs select
    transferOK = HAL_SPI_Transmit(&hspi1, &spi_tx_buf[0], 260, HAL_MAX_DELAY);		//komut ve adres
	EXTFLASHCSPIN_HIGH; 															// cs deselect

	FlashStatus.WIP=1;
    while(FlashStatus.WIP==1)
    {
    	HAL_Delay(20);
    	transferOK=ReadStatusRegister(&FlashStatus);
    	i++;
    	if(i==200)
    	{
    		return 0;
    	}
    }
    i=0;
    transferOK=ReadStatusRegister(&FlashStatus);
    transferOK=ReadSecurityRegister(&SecurityReg);
    if(transferOK==HAL_OK && SecurityReg.EFAIL==0 && SecurityReg.PFAIL==0)
    {

    	return 1;
    }
    else
        return 0;
}
unsigned char CheckPage(unsigned Add){
	unsigned char transferOK ;

	memset(spi_rx_buf,0,RxBufferSize); //rx buferı 0 ile dolduruldu
	spi_tx_buf[0]=0x03;
	spi_tx_buf[1]=(Add>>16)&0xFF;
    spi_tx_buf[2]=(Add>>8)&0xFF;
    spi_tx_buf[3]=Add&0xFF;

    EXTFLASHCSPIN_LOW; 									// cs select

    transferOK = HAL_SPI_Transmit(&hspi1, &spi_tx_buf[0], 4, 500);	//komut ve adres
    transferOK = HAL_SPI_Receive(&hspi1, &spi_rx_buf[0], 260, 500);	//read
	EXTFLASHCSPIN_HIGH; // cs deselect
	return transferOK;
}

uint8_t ReadFlash(Mem_Handle_t* Mem_Control,SHT21_Handle_t* SHT21_1){
	if(SHT21_1->Data_Ready==1){


	HAL_Delay(2500);
	uint8_t counter_1 = 0 ;
	uint8_t counter_2 = 0 ;
	uint8_t a=0;

	while(counter_1 != 50){
		if((a = FlashIsReady()) == 1){

			CheckPage((unsigned int )Mem_Control->block[Mem_Control->block_counter][Mem_Control->page_counter]);
			a=0;
			counter_1 = 50;
			counter_2 = 1;
			HAL_Delay(1000);
		}else
		{
			counter_1++;
		}
	}

	if(counter_2){
		return 1 ;
	}else{
		return 0  ;
	}
	}
	return 0 ;
}

uint8_t WriteFlash(Mem_Handle_t* Mem_Control,SHT21_Handle_t* SHT21_1){
	if(SHT21_1->Data_Ready==1){


	HAL_Delay(2500);
	uint8_t counter_1 = 0 ;
	uint8_t counter_2 = 0 ;
	uint8_t b = 0 ;
	while(counter_1 != 50 ) {
		if((b = FlashIsReady()) == 1){
			//SectorErase(Mem_Control->block[Mem_Control->block_counter][Mem_Control->page_counter]);
			PageProgram(Mem_Control->block[Mem_Control->block_counter][Mem_Control->page_counter], &(Mem_Control->tx_buf[0])) ;
			b=0;
			counter_1 = 50 ;
			counter_2 = 1 ;								}
		else{
				counter_1 ++ ;
		    }

			}

if(counter_2)
	{
	return 1 ;

	}else
	{
	return 0 ;
	}

	}
	return 0 ;
}


void NextPage(Mem_Handle_t* Mem_Control , SHT21_Handle_t* SHT21_1){
	if(SHT21_1->Data_Ready==1){

	if((Mem_Control->page_counter < 15) & (Mem_Control->block_counter < 15)){

		Mem_Control->page_counter++;

	}else  if((Mem_Control->page_counter == 15) & (Mem_Control->block_counter < 15))
	{
		Mem_Control->page_counter = 0;
		Mem_Control->block_counter++;

	}else if((Mem_Control->page_counter == 15) & (Mem_Control->block_counter == 15)){

		Mem_Control->page_counter  = 0;
		Mem_Control->block_counter = 0;
	}
	}
}

void Accumulation_Init(SHT21_Handle_t* SHT21_1){
	SHT21_1->FlashData_Cnt=0; // counter 0dan 12 ye kadar sayar ve 12ye(12 dahil) gelinceye kadar arada bir buffera biriktirilir datalar .
	SHT21_1->Data_Ready = 0 ;  // Data dolana kadar 0 kalıcak olan counter .
}
void Accumulation(SHT21_Handle_t *SHT21_1, Mem_Handle_t *Mem_Control) {
	uint16_t i;
	char AraData[10];
	memset(AraData, 0, 10);
	if (SHT21_1->FlashData_Cnt <= 16) {
		sprintf(AraData, "T=%.2lf", SHT21_1->son_sicaklik); //sicaklik ara dataya alındı
		strcat(SHT21_1->FlashData, AraData);		//sicaklik ana dataya alındı
		sprintf(AraData, "H=%.2lf", SHT21_1->son_nem);	 //nem ara dataya alındı
		strcat(SHT21_1->FlashData, AraData);			//nem ana dataya alındı
		SHT21_1->FlashData_Cnt++;//buffer'ı dolduracak sayıda counter arttırıyoruz
		SHT21_1->Data_Ready = 0;						 //biriktirmeye devam et
	} else if (SHT21_1->FlashData_Cnt > 16) {				// doluluğa ulaştı
		SHT21_1->FlashData_Cnt = 0;						    //counter sıfırlandı
		for (i = 0; i < 260; i++) {
			Mem_Control->tx_buf[i] = SHT21_1->FlashData[i];	// tx bufferına biriktirilen veri alındı
		}
		memset(SHT21_1->FlashData, 0, 260);				//datayı geçici olarak saklayan buffer resetlendi
		SHT21_1->Data_Ready = 1; 						//biriktirme yeterli veriyi yolla
	}
}
void Send_Flash(Mem_Handle_t *Mem_Control, SHT21_Handle_t *SHT21_1){

	Accumulation((SHT21_Handle_t *)SHT21_1, (Mem_Handle_t *)Mem_Control); //biriktirme
	WriteFlash((Mem_Handle_t *)Mem_Control, (SHT21_Handle_t *)SHT21_1); //yazma
	ReadFlash((Mem_Handle_t *)Mem_Control, (SHT21_Handle_t *)SHT21_1); //okuma
	NextPage((Mem_Handle_t *)Mem_Control, (SHT21_Handle_t *)SHT21_1);//page ilerleme
}
