#ifndef lcd_20x4_h
#define lcd_20x4_h


#include "main.h"
//LCD Pin Macros

#define HY2004A8_RS_Pin GPIO_PIN_2
#define HY2004A8_RS_GPIO_Port GPIOA


#define HY2004A8_E_Pin GPIO_PIN_1
#define HY2004A8_E_GPIO_Port GPIOA

#define HY2004A8_D4_Pin GPIO_PIN_4
#define HY2004A8_D4_GPIO_Port GPIOB

#define HY2004A8_D5_Pin GPIO_PIN_5
#define HY2004A8_D5_GPIO_Port GPIOB

#define HY2004A8_D6_Pin GPIO_PIN_6
#define HY2004A8_D6_GPIO_Port GPIOB

#define HY2004A8_D7_Pin GPIO_PIN_10
#define HY2004A8_D7_GPIO_Port GPIOB

/*
 * @brief:Lcd init
 */

void HY2004A8_Init(uint8_t cols, uint8_t rows);
/*
 * @brief:Use for send data
 */
void HY2004A8_Puts(uint8_t x, uint8_t y, char* str);


void HY2004A8_DisplayOn(void);
void HY2004A8_DisplayOff(void);
void HY2004A8_Clear(void);
void HY2004A8_BlinkOn(void);
void HY2004A8_BlinkOff(void);
void HY2004A8_CursorOn(void);
void HY2004A8_CursorOff(void);
void HY2004A8_ScrollLeft(void);
void HY2004A8_ScrollRight(void);
void HY2004A8_CreateChar(uint8_t location, uint8_t* data);
void HY2004A8_PutCustom(uint8_t x, uint8_t y, uint8_t location);

/*
 * @brief: Send temp and humidity data to 20x4 LCD
 * note: you can use only this funciton for send data to 20x4 LCD
 */
void Send_Lcd(SHT21_Handle_t* sht21_1);
#endif
