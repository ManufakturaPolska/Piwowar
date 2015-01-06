/*/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************
**
 * ze szczególnymi podziêkowaniami Mirkowi Kardaœ
 *
 * mp_ssd1306.c
 *
 *  Created on: 20 gru 2014
 *      Author: Marcin
 */

#ifndef AA_OLED_II_MP_SSD1306_MP_SSD1306_H_
#define AA_OLED_II_MP_SSD1306_MP_SSD1306_H_


																								//definicje preprocesora

										//rozdzielczosc OLED
#define SSD1306_128_64
// #define SSD1306_128_32

#define USE_SPI_OR_I2C  1     																													//1-SPI  0- I2C

#if USE_SPI_OR_I2C == 0

#define OLED_I2C_ADDRESS 0x78
//#define OLED_I2C_ADDRESS 0x7A

#define I2C_DIR 		DDRC
#define SCL     			PC0
#define SDA     		PC1

#endif

#if USE_SPI_OR_I2C==1																															//SPI

#define USE_CS			0																															//  0 - nie uzywany, 1 gdy uzywamy CS
#define USE_CS2			0 				 																											//  0 - nie uzywany, 1 gdy uzywamy CS2
#define USE_RST			1

#define SCK			(1<<7)
#define MOSI		(1<<6)
#define CS           (1<<5)
#define CS2         (1<<2)
#define DC           (1<<4)
#define RST         (1<<5)


#define SCK_PORT 	PORTC
#define SCK_DDR 		DDRC

#define MOSI_PORT 	PORTC
#define MOSI_DDR  	DDRC

#define CS_PORT 	PORTC
#define CS_DDR  		DDRC

#define CS2_PORT 	PORTC
#define CS2_DDR  	DDRC

#define DC_PORT 	PORTC
#define DC_DDR  		DDRC

#define RST_PORT 	PORTC
#define RST_DDR  	DDRC
#endif

#define SCK_LO 		SCK_PORT &= ~SCK
#define SCK_HI 		SCK_PORT |= SCK

#define MOSI_LO 		MOSI_PORT &= ~MOSI
#define MOSI_HI 		MOSI_PORT |= MOSI

#define CS_LO 			CS_PORT &= ~CS
#define CS_HI 			CS_PORT |= CS

#define CS2_LO 		CS2_PORT &= ~CS2
#define CS2_HI 		CS2_PORT |= CS2

#define DC_LO 			DC_PORT &= ~DC
#define DC_HI 			DC_PORT |= DC

#define RST_LO 		RST_PORT &= ~RST
#define RST_HI 		RST_PORT |= RST



#if defined SSD1306_128_64

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#endif

#if defined SSD1306_128_32

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 32

#endif

#define BUF_SIZE ( SSD1306_WIDTH * SSD1306_HEIGHT / 8 )

#define REFRESH_MIN 0x80
#define REFRESH_MID 0xB0
#define REFRESH_MAX 0xF0

typedef enum { page0, page1, page2, page3, page4, page5, page6, page7 } TPAGE;

#define SSD1306_SETCONTRAST                     	0x81
#define SSD1306_DISPLAYALLON_RESUME     	0xA4
#define SSD1306_DISPLAYALLON                    	0xA5
#define SSD1306_NORMALDISPLAY                  	0xA6
#define SSD1306_INVERTDISPLAY                   	0xA7
#define SSD1306_DISPLAYOFF                          0xAE
#define SSD1306_DISPLAYON                           	0xAF
#define SSD1306_SETDISPLAYOFFSET               0xD3
#define SSD1306_SETCOMPINS                         0xDA
#define SSD1306_SETVCOMDETECT                  0xDB
#define SSD1306_SETDISPLAYCLOCKDIV            0xD5
#define SSD1306_SETPRECHARGE                    	0xD9
#define SSD1306_SETMULTIPLEX                    	0xA8
#define SSD1306_SETLOWCOLUMN                   0x00
#define SSD1306_SETHIGHCOLUMN                   0x10
#define SSD1306_SETSTARTLINE                    	0x40
#define SSD1306_MEMORYMODE                      	0x20
#define SSD1306_COMSCANINC 						0xC0
#define SSD1306_COMSCANDEC 						0xC8
#define SSD1306_SEGREMAP                            0xA0
#define SSD1306_CHARGEPUMP                        0x8D
#define SSD1306_EXTERNALVCC                     	0x1
#define SSD1306_SWITCHCAPVCC                    0x2

																										// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 										0x2F
#define SSD1306_DEACTIVATE_SCROLL 									0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 						0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 							0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 							0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 	0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 	0x2A


#define swap(a, b) { int16_t t = a; a = b; b = t; }																						// makro zamienia bajty

																								//deklaracje zmiennych

#if USE_CS2==1
extern uint8_t display_nr;
#endif

extern const uint8_t font [] ;
extern int cursor_x, cursor_y;

																								//deklaracje funkcji sprzêtowych
void mp_ssd1306_init ( uint8_t vcc, uint8_t refresh, uint8_t rst_disable);
void mp_ssd1306_cmd ( uint8_t cmd);
void mp_ssd1306_data ( uint8_t dat);
void mp_ssd1306_drawPixel ( int x, int y, uint8_t bw );																			//	narysuj Piksel mp_ssd1306_setPixel
void mp_ssd1306_display ( void );
void mp_ssd1306_refresh_pages ( uint8_t page_nr, uint8_t pages_cnt, uint8_t col_start, uint8_t col_end ) ;
void mp_ssd1306_cls (void);

																								//deklaracje funkcji graficznych
void mp_narZnak (int x, int y, char c, uint8_t color, uint8_t bg, uint8_t size );												// rysuj znak mp_ssd1306_drawChar

void mp_wysText ( int x, int y, char * str, uint8_t txt_size, uint8_t color, uint8_t bg ) ;									// wyœwietl tekst mp_ssd1306_puts
void mp_wysText_P ( int x, int y, const char * str, uint8_t txt_size, uint8_t color, uint8_t bg );                   // wyœwietl tekst z flash mp_ssd1306_puts_P

void mp_wysLiczbe ( int x, int y, int data, uint8_t txt_size, uint8_t color, uint8_t bg) ;									// wyœwietl liczbê mp_ssd1306_put_int

void mp_wysBitmap_P (int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);					// rysuj bitmapê mp_ssd1306_drawBitmap_P

void mp_narProst (int x, int y, int w, int h, uint8_t color);																			// rysuj pusty prostok¹t mp_ssd1306_drawRect
void mp_wypProst ( int x, int y, int w, int h, uint8_t color);															    		// wype³nij prostok¹t mp_ssd1306_fillRect
void mp_narProstOkrag ( int x, int y, int w, int h, int r, uint8_t color);														// rysuj pusty prostok¹t zaokr¹glone rogi mp_ssd1306_drawRoundRect
void mp_wypProstOkrag (int x, int y, int w, int h, uint8_t r, uint8_t color);												// wype³nij prostokont zaokr¹glony mp_ssd1306_fillRoundRect


void mp_narLiniePoz ( int x, int y, int h, uint8_t color );																			// rysuj poziom¹ liniê mp_ssd1306_drawFastVLine
void mp_narLiniePion ( int x, int y, int w, uint8_t color);																			// rysuj pionow¹ liniê mp_ssd1306_drawFastHLine
void mp_narLinieDow ( int x0, int y0, int x1, int y1, uint8_t color );															// rysuj dowoln¹ liniê

void mp_narOkrag ( int x, int y, uint8_t r, uint8_t bw) ;																				// rysuj pusty okr¹g mp_ssd1306_circle
void mp_wypOkrag ( int x, int y, uint8_t r, uint8_t color ) ;																			// wype³nij okr¹g mp_ssd1306_fillCircle
void mp_narOkragPomoc ( int x0, int y0, int r, uint8_t cornername, uint8_t color);										// rysuj okr¹g pomocniczy mp_ssd1306_drawCircleHelper
void mp_wypOkragPomoc ( int x, int y, int r, uint8_t cornername, int delta, uint8_t color );						// wype³nienie okrêg pomocniczy mp_ssd1306_fillCircleHelper

void  mp_narTrojkat ( int x0, int y0, int x1, int y1, int x2, int y2, uint8_t color );										// narysuj pusty trójk¹t mp_ssd1306_drawTriangle
void  mp_wypTrojkat ( int x0, int y0, int x1, int y1, int x2, int y2, uint8_t color );										// wype³nij trójk¹t mp_ssd1306_fillTriangle

																									// przewijanie
void mp_startPrzewPrawo ( uint8_t start, uint8_t stop );
void mp_startPrzewLewo ( uint8_t start, uint8_t stop );
void mp_startPrzewUkosPrawo ( uint8_t start, uint8_t stop );
void mp_startPrzewUkosLewo ( uint8_t start, uint8_t stop );
void mp_stopPrzew ( void );

void mp_mrugajEkran ( uint8_t i ) ;

#endif /* AA_OLED_II_MP_SSD1306_MP_SSD1306_H_ */
