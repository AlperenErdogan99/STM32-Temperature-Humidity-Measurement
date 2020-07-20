#include "lcd_20x4.h"
#include "main.h"


/* HY2004A8 structure */
typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} HY2004A8_Options_t;



static void HY2004A8_InitPins(void);
static void HY2004A8_Cmd(uint8_t cmd);
static void HY2004A8_Cmd4bit(uint8_t cmd);
static void HY2004A8_Data(uint8_t data);
static void HY2004A8_CursorSet(uint8_t col, uint8_t row);



static HY2004A8_Options_t HY2004A8_Opts;

/* Pin Configuration*/

#define HY2004A8_RS_LOW              HAL_GPIO_WritePin(HY2004A8_RS_GPIO_Port, HY2004A8_RS_Pin,GPIO_PIN_RESET);
#define HY2004A8_RS_HIGH             HAL_GPIO_WritePin(HY2004A8_RS_GPIO_Port, HY2004A8_RS_Pin,GPIO_PIN_SET);
#define HY2004A8_E_LOW               HAL_GPIO_WritePin(HY2004A8_E_GPIO_Port, HY2004A8_E_Pin,GPIO_PIN_RESET);
#define HY2004A8_E_HIGH              HAL_GPIO_WritePin(HY2004A8_E_GPIO_Port, HY2004A8_E_Pin,GPIO_PIN_SET);

#define HY2004A8_Delay(x)            HAL_Delay(x/1000)
#define HY2004A8_E_BLINK             HY2004A8_E_HIGH; HY2004A8_Delay(20); HY2004A8_E_LOW; HY2004A8_Delay(20)


/* Command Set*/
#define HY2004A8_CLEARDISPLAY        0x01
#define HY2004A8_ENTRYMODESET        0x04
#define HY2004A8_DISPLAYCONTROL      0x08
#define HY2004A8_CURSORSHIFT         0x10
#define HY2004A8_FUNCTIONSET         0x20
#define HY2004A8_SETCGRAMADDR        0x40
#define HY2004A8_SETDDRAMADDR        0x80

/* Görüntü giris modu flags */
#define HY2004A8_ENTRYLEFT           0x02
#define HY2004A8_ENTRYSHIFTDECREMENT 0x00

/* Görüntü açma / kapama kontrolü için flags */
#define HY2004A8_DISPLAYON           0x04
#define HY2004A8_CURSORON            0x02
#define HY2004A8_BLINKON             0x01

/* Gösterge / imleç durum flags*/
#define HY2004A8_DISPLAYMOVE         0x08
#define HY2004A8_CURSORMOVE          0x00
#define HY2004A8_MOVERIGHT           0x04
#define HY2004A8_MOVELEFT            0x00

/* Fonksiyon setleri için flags */
#define HY2004A8_4BITMODE            0x00
#define HY2004A8_2LINE               0x08
#define HY2004A8_1LINE               0x00
#define HY2004A8_5x8DOTS             0x00



void HY2004A8_Init(uint8_t cols, uint8_t rows) {

	/* Pinout Aktivasyonu */
	HY2004A8_InitPins();

	/* En az 40ms */
	HY2004A8_Delay(45000);

	/* LCD Genislik ve yükseklik ayarlama */
	HY2004A8_Opts.Rows = rows;
	HY2004A8_Opts.Cols = cols;

	/* Imleci baslangica getirmek */
	HY2004A8_Opts.currentX = 0;
	HY2004A8_Opts.currentY = 0;

	HY2004A8_Opts.DisplayFunction = HY2004A8_4BITMODE | HY2004A8_5x8DOTS | HY2004A8_1LINE;
	if (rows > 1) {
		HY2004A8_Opts.DisplayFunction |= HY2004A8_2LINE;
	}

	/* 4bit mod aktivasyon 1 */
	HY2004A8_Cmd4bit(0x03);
	HY2004A8_Delay(4500);

	/* 4bit mod aktivasyon 2 */
	HY2004A8_Cmd4bit(0x03);
	HY2004A8_Delay(4500);

	/* 4bit mod aktivasyon 3 */
	HY2004A8_Cmd4bit(0x03);
	HY2004A8_Delay(4500);

	/* 4-bit arayüzü ayarlama */
	HY2004A8_Cmd4bit(0x02);
	HY2004A8_Delay(100);

	/* Satir, yazi tipi ayarlari */
	HY2004A8_Cmd(HY2004A8_FUNCTIONSET | HY2004A8_Opts.DisplayFunction);

	/* Cursorsuz ekran defaultu ayarlama */
	HY2004A8_Opts.DisplayControl = HY2004A8_DISPLAYON;
	HY2004A8_DisplayOn();

	/* LCD Temizleme */
	HY2004A8_Clear();

	/* Varsayilan yazitipi yönergeleri */
	HY2004A8_Opts.DisplayMode = HY2004A8_ENTRYLEFT | HY2004A8_ENTRYSHIFTDECREMENT;
	HY2004A8_Cmd(HY2004A8_ENTRYMODESET | HY2004A8_Opts.DisplayMode);

	/* 4,5ms delay */
	HY2004A8_Delay(4500);
}

void HY2004A8_Clear(void) {
	HY2004A8_Cmd(HY2004A8_CLEARDISPLAY);
	HY2004A8_Delay(3000);
}

void HY2004A8_Puts(uint8_t x, uint8_t y, char* str) {
	HY2004A8_CursorSet(x, y);
	while (*str) {
		if (HY2004A8_Opts.currentX >= HY2004A8_Opts.Cols) {
			HY2004A8_Opts.currentX = 0;
			HY2004A8_Opts.currentY++;
			HY2004A8_CursorSet(HY2004A8_Opts.currentX, HY2004A8_Opts.currentY);
		}
		if (*str == '\n') {
			HY2004A8_Opts.currentY++;
			HY2004A8_CursorSet(HY2004A8_Opts.currentX, HY2004A8_Opts.currentY);
		} else if (*str == '\r') {
			HY2004A8_CursorSet(0, HY2004A8_Opts.currentY);
		} else {
			HY2004A8_Data(*str);
			HY2004A8_Opts.currentX++;
		}
		str++;
	}
}

void HY2004A8_DisplayOn(void) {
	HY2004A8_Opts.DisplayControl |= HY2004A8_DISPLAYON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_DisplayOff(void) {
	HY2004A8_Opts.DisplayControl &= ~HY2004A8_DISPLAYON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_BlinkOn(void) {
	HY2004A8_Opts.DisplayControl |= HY2004A8_BLINKON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_BlinkOff(void) {
	HY2004A8_Opts.DisplayControl &= ~HY2004A8_BLINKON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_CursorOn(void) {
	HY2004A8_Opts.DisplayControl |= HY2004A8_CURSORON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_CursorOff(void) {
	HY2004A8_Opts.DisplayControl &= ~HY2004A8_CURSORON;
	HY2004A8_Cmd(HY2004A8_DISPLAYCONTROL | HY2004A8_Opts.DisplayControl);
}

void HY2004A8_ScrollLeft(void) {
	HY2004A8_Cmd(HY2004A8_CURSORSHIFT | HY2004A8_DISPLAYMOVE | HY2004A8_MOVELEFT);
}

void HY2004A8_ScrollRight(void) {
	HY2004A8_Cmd(HY2004A8_CURSORSHIFT | HY2004A8_DISPLAYMOVE | HY2004A8_MOVERIGHT);
}

void HY2004A8_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* Özel karakterler için 8 konum vardir 0-7 */
	location &= 0x07;
	HY2004A8_Cmd(HY2004A8_SETCGRAMADDR | (location << 3));

	for (i = 0; i < 8; i++) {
		HY2004A8_Data(data[i]);
	}
}

void HY2004A8_PutCustom(uint8_t x, uint8_t y, uint8_t location) {
	HY2004A8_CursorSet(x, y);
	HY2004A8_Data(location);
}

/* Özel fonksyionlar */
static void HY2004A8_Cmd(uint8_t cmd) {
	/* Komut Modu */
	HY2004A8_RS_LOW;

	/* High nibble */
	HY2004A8_Cmd4bit(cmd >> 4);
	/* Low nibble */
	HY2004A8_Cmd4bit(cmd & 0x0F);
}

static void HY2004A8_Data(uint8_t data) {
	/* Data Modu */
	HY2004A8_RS_HIGH;

	/* High nibble */
	HY2004A8_Cmd4bit(data >> 4);
	/* Low nibble */
	HY2004A8_Cmd4bit(data & 0x0F);
}

static void HY2004A8_Cmd4bit(uint8_t cmd) {
	/* Çikis portlari */
	if((cmd & 0x08))HAL_GPIO_WritePin(HY2004A8_D7_GPIO_Port, HY2004A8_D7_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(HY2004A8_D7_GPIO_Port, HY2004A8_D7_Pin, GPIO_PIN_RESET);
	if((cmd & 0x04))HAL_GPIO_WritePin(HY2004A8_D6_GPIO_Port, HY2004A8_D6_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(HY2004A8_D6_GPIO_Port, HY2004A8_D6_Pin, GPIO_PIN_RESET);
	if((cmd & 0x02))HAL_GPIO_WritePin(HY2004A8_D5_GPIO_Port, HY2004A8_D5_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(HY2004A8_D5_GPIO_Port, HY2004A8_D5_Pin, GPIO_PIN_RESET);
	if((cmd & 0x01))HAL_GPIO_WritePin(HY2004A8_D4_GPIO_Port, HY2004A8_D4_Pin, GPIO_PIN_SET); else HAL_GPIO_WritePin(HY2004A8_D4_GPIO_Port, HY2004A8_D4_Pin, GPIO_PIN_RESET);
	HY2004A8_E_BLINK;
}

static void HY2004A8_CursorSet(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};

	/* Baslangica dön */
	if (row >= HY2004A8_Opts.Rows) {
		row = 0;
	}

	/* satir/sütun atama */
	HY2004A8_Opts.currentX = col;
	HY2004A8_Opts.currentY = row;

	/* location adress atama */
	HY2004A8_Cmd(HY2004A8_SETDDRAMADDR | (col + row_offsets[row]));
}

static void HY2004A8_InitPins(void) {
	/* low seviye pin atama */
	HAL_GPIO_WritePin(HY2004A8_RS_GPIO_Port, HY2004A8_RS_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HY2004A8_E_GPIO_Port, HY2004A8_E_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HY2004A8_D4_GPIO_Port, HY2004A8_D4_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HY2004A8_D5_GPIO_Port, HY2004A8_D5_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HY2004A8_D6_GPIO_Port, HY2004A8_D6_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(HY2004A8_D7_GPIO_Port, HY2004A8_D7_Pin,GPIO_PIN_RESET);
}
/*
 * @brief: sending data to lcd
 * note: Testini yapmadın. YAP
 */
void Send_Lcd(SHT21_Handle_t* sht21_1){
	sprintf(sht21_1->data_T, "Sicaklik :%.2lf\n", sht21_1->son_sicaklik);
	HY2004A8_Puts(1, 0, sht21_1->data_T);				//send data to LCD
	HAL_Delay(500);

	sprintf(sht21_1->data_H, "Nem :%% %.2lf\n ", sht21_1->son_nem);
	HY2004A8_Puts(1, 1, sht21_1->data_H);				//send data to LCD
	HAL_Delay(500);

}
