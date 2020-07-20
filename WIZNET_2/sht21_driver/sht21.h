#ifndef sht21
#define sht21
#include "main.h"

/*****************************************************************************************
 * 							APIs supported by this driver
 * 					For more information about the APIs check the function definitions
 *****************************************************************************************/

/*
 * Command Set
 */

#define START_TEMP_HM 					0xE3			/*!<start hold master temperature measurement 		*/
#define START_HUM_HM    				0xE5			/*!<start hold master humanity measurement     		*/
#define START_TEMP_NHM					0xF3			/*!<start no hold master temperature measurement 	*/
#define START_HUM_NHM					0xF5			/*!<start no hold master humidity measurement		*/
#define WRITE_REGISTER					0xE6			/*!<write user register								*/
#define READ_REGISTER					0xE7			/*!<read user register								*/
#define SOFT_RESET						0xFE			/*!<soft reset										*/
#define LSB_CONFIG     	  				0xFFF0			/*!<LSB configuration command						*/


/*
 * Write and read address
 */
#define WRITE_ADDRESS     0X80							/*!<write address for command						*/
#define READ_ADDRESS      0x81							/*!<read address for data							*/


/*
 * Handle structure for control
 */
typedef struct {

	uint8_t  RH_DATA[2] ;								/*!<raw temperature sensor data						*/
	uint8_t  T_DATA[2] ; 								/*!<raw humidity sensor data						*/
	uint16_t Temperature_Value[2] ;
	uint16_t Humidity_Value[2] ;
	uint16_t Temperature ; 								/*!<processed temperature sensor data				*/
	uint16_t Humidity ;    								/*!<processed humidity sensor data					*/
	char data_T[20]; 	  								/*!<final temperature for LCD  and WIZNET			*/
	char data_H[20]; 	  								/*!<final humidity for LCD and WIZNET				*/
	double son_sicaklik ; 								/*!<final temperature								*/
	double son_nem ; 	  								/*!<final humidity									*/
	char FlashData[260];
	uint8_t FlashData_Cnt;
	uint8_t Data_Ready;

}SHT21_Handle_t;

/*
 * note : use this 3 functions for temperature measurement(alternative selection)
 */
void sht21_start_T_HM(void);							/*!<Start Measurement Temperature (Hold Master Mode) */
void sht21_read_T_HM(SHT21_Handle_t *sht21_1);			/*!<Read Humidity (Hold Master Mode)				 */
void sht21_cal_temp(SHT21_Handle_t *sht21_1);			/*!<Calculate raw temperature data					 */

/*
 * note: you can use only this function for temperature measurement
 */
void Temp_Measure(SHT21_Handle_t *sht21_1);

/*
 * note:use this 3 functions for humidity measurement (alternative selection)
 */
void sht21_start_RH_HM(void);							/*!<Start Measurement Humidity (Hold Master Mode)	*/
void sht21_read_RH_HM(SHT21_Handle_t *sht21_1);			/*!<Read Temperature (Hold Master Mode)				*/
void sht21_cal_hum(SHT21_Handle_t *sht21_1);			/*!<Calculate raw humidity data						*/

/*
 * note: you can use only this funciton for humidity measurement
 */
void Hum_Measure(SHT21_Handle_t *sht21_1);


#endif
