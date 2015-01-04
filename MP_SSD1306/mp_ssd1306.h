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

//rozdzielczosc LCD/<span class="posthilit">OLED</span>
#define SSD1306_128_64
// #define SSD1306_128_32

#define USE_SPI_OR_I2C  1     //1-SPI  0- I2C

#if USE_SPI_OR_I2C==0

#define OLED_I2C_ADDRESS 0x78  //0x7A

#define I2C_DIR DDRC
#define SCL     PC0
#define SDA     PC1

#endif

#if USE_SPI_OR_I2C==1 //SPI

#define USE_CS         0 //0 to nie uzywany, 1 gdy uzywamy CS
#define USE_CS2         0 //0 to nie uzywany, 1 gdy uzywamy CS2

#define USE_RST 1

#define SCK     (1<<7)
#define MOSI    (1<<6)
#define CS              (1<<5)
#define DC              (1<<4)
#define RST     (1<<5)
#define CS2             (1<<2)

#define SCK_PORT PORTC
#define SCK_DDR  DDRC

#define MOSI_PORT PORTC
#define MOSI_DDR  DDRC

#define CS_PORT PORTC
#define CS_DDR  DDRC

#define CS2_PORT PORTC
#define CS2_DDR  DDRC

#define DC_PORT PORTC
#define DC_DDR  DDRC

#define RST_PORT PORTC
#define RST_DDR  DDRC

#endif

#define SCK_LO SCK_PORT &= ~SCK
#define SCK_HI SCK_PORT |= SCK

#define MOSI_LO MOSI_PORT &= ~MOSI
#define MOSI_HI MOSI_PORT |= MOSI

#define CS_LO CS_PORT &= ~CS
#define CS_HI CS_PORT |= CS

#define CS2_LO CS2_PORT &= ~CS2
#define CS2_HI CS2_PORT |= CS2

#define DC_LO DC_PORT &= ~DC
#define DC_HI DC_PORT |= DC

#define RST_LO RST_PORT &= ~RST
#define RST_HI RST_PORT |= RST

#define SSD1306_WIDTH 128

#if defined SSD1306_128_64

#define SSD1306_HEIGHT 64

#endif

#if defined SSD1306_128_32

#define SSD1306_HEIGHT 32

#endif

#define BUF_SIZE (SSD1306_WIDTH*SSD1306_HEIGHT/8)

#define REFRESH_MIN 0x80
#define REFRESH_MID 0xB0
#define REFRESH_MAX 0xF0

#define SSD1306_SETCONTRAST                     0x81
#define SSD1306_DISPLAYALLON_RESUME     0xA4
#define SSD1306_DISPLAYALLON                    0xA5
#define SSD1306_NORMALDISPLAY                   0xA6
#define SSD1306_INVERTDISPLAY                   0xA7
#define SSD1306_DISPLAYOFF                              0xAE
#define SSD1306_DISPLAYON                               0xAF

#define SSD1306_SETDISPLAYOFFSET                0xD3
#define SSD1306_SETCOMPINS                              0xDA

#define SSD1306_SETVCOMDETECT                   0xDB

#define SSD1306_SETDISPLAYCLOCKDIV              0xD5
#define SSD1306_SETPRECHARGE                    0xD9

#define SSD1306_SETMULTIPLEX                    0xA8

#define SSD1306_SETLOWCOLUMN                    0x00
#define SSD1306_SETHIGHCOLUMN                   0x10
#define SSD1306_SETSTARTLINE                    0x40

#define SSD1306_CHARGEPUMP                              0x8D

#define SSD1306_EXTERNALVCC                     0x1

#define SSD1306_SEGREMAP                                0xA0

#define SSD1306_COMSCANDEC                              0xC8

#define SSD1306_MEMORYMODE                              0x20

#define SSD1306_SWITCHCAPVCC                    0x2

//deklaracje zmiennych



#if USE_CS2==1
extern uint8_t display_nr;
#endif




//deklaracje funkcji
void mp_ssd1306_init( uint8_t vcc, uint8_t refresh, uint8_t rst_disable);
void mp_ssd1306_cmd( uint8_t cmd);
void mp_ssd1306_data( uint8_t dat);
void mp_ssd1306_display(void);
void mp_ssd1306_setPixel(int x, int y, uint8_t bw);
void mp_ssd1306_cls(void);
void mp_ssd1306_drawBitmap_P(int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);
//void oled_write_data(int x, int y, uint8_t *c);
//void oled_defchar(int x, int y, uint8_t *def_znak);

#endif /* AA_OLED_II_MP_SSD1306_MP_SSD1306_H_ */
