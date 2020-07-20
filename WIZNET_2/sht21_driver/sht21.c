#include "main.h"
#include "sht21.h"

extern I2C_HandleTypeDef hi2c1;

void sht21_start_RH_HM(void) {

	uint8_t data[] = { START_HUM_HM };
	HAL_I2C_Master_Transmit(&hi2c1, (uint8_t) WRITE_ADDRESS, data, 1,
	HAL_MAX_DELAY);
	HAL_Delay(200);

}
void sht21_start_T_HM(void) {

	uint8_t data[] = { START_TEMP_HM };
	HAL_I2C_Master_Transmit(&hi2c1, (uint8_t) WRITE_ADDRESS, data, 1,
	HAL_MAX_DELAY);
	HAL_Delay(200);

}
void sht21_read_RH_HM(SHT21_Handle_t *sht21_1) {
	uint8_t data[1];
	data[1] = READ_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1, (uint8_t) WRITE_ADDRESS, (uint8_t*) data, 1,
			1000);
	HAL_I2C_Master_Receive(&hi2c1, (uint8_t) READ_ADDRESS, sht21_1->RH_DATA, 2,
			1000);
	HAL_Delay(200);

	sht21_1->Humidity_Value[0] = sht21_1->RH_DATA[0]; //MSB
	sht21_1->Humidity_Value[0] = sht21_1->Humidity_Value[0] << 8;
	sht21_1->Humidity_Value[1] = sht21_1->RH_DATA[1]; //LSB
	sht21_1->Humidity_Value[1] = sht21_1->Humidity_Value[1]
			& ((uint16_t) LSB_CONFIG);
	sht21_1->Humidity = sht21_1->Humidity_Value[0] | sht21_1->Humidity_Value[1];

}

void sht21_read_T_HM(SHT21_Handle_t *sht21_1) {

	uint8_t data[1];
	data[1] = READ_ADDRESS;
	HAL_I2C_Master_Transmit(&hi2c1, (uint8_t) WRITE_ADDRESS, (uint8_t*) data, 1,
			1000);
	HAL_I2C_Master_Receive(&hi2c1, (uint8_t) READ_ADDRESS, sht21_1->T_DATA, 2,
			1000);
	HAL_Delay(200);

	sht21_1->Temperature_Value[0] = sht21_1->T_DATA[0]; //MSB
	sht21_1->Temperature_Value[0] = sht21_1->Temperature_Value[0] << 8;
	sht21_1->Temperature_Value[1] = sht21_1->T_DATA[1]; //LSB
	sht21_1->Temperature_Value[1] = sht21_1->Temperature_Value[1]
			& ((uint16_t) LSB_CONFIG);
	sht21_1->Temperature = sht21_1->Temperature_Value[0]
			| sht21_1->Temperature_Value[1];

}

void sht21_cal_temp(SHT21_Handle_t *sht21_1) {
	sht21_1->son_sicaklik = (-46.85)
			+ (175.2 * (double) sht21_1->Temperature / 65536); //Calculate Temperature
}

void sht21_cal_hum(SHT21_Handle_t *sht21_1) {
	sht21_1->son_nem = (125 * sht21_1->Humidity / 65536) - 6; //Calculate Humanity
}

void Temp_Measure(SHT21_Handle_t *sht21_1){

	sht21_start_T_HM();
	sht21_read_T_HM((SHT21_Handle_t *)sht21_1);
	sht21_cal_temp ((SHT21_Handle_t *)sht21_1);

}

void Hum_Measure(SHT21_Handle_t *sht21_1){

	sht21_start_RH_HM();
	sht21_read_RH_HM((SHT21_Handle_t *)sht21_1);
	sht21_cal_hum((SHT21_Handle_t *)sht21_1);

}
