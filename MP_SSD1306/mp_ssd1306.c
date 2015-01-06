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

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "mp_ssd1306.h"


uint8_t ssd1306_buf [ BUF_SIZE ]= {

};

#if USE_CS2 == 1
uint8_t display_nr;
#endif

#if USE_SPI_OR_I2C == 1

static void SPIwrite ( uint8_t dat ) {
        uint8_t i;
        for ( i=0x80 ; i ; i >>=1 ) {
                SCK_LO;
                if ( dat & i ) MOSI_HI;
                else MOSI_LO; SCK_HI;
        }
}

void ssd1306_InitSpi (void) {

        MOSI_DDR 	|= MOSI;
        SCK_DDR 		|= SCK;
        SCK_PORT 	|= SCK;

#if USE_RST == 1
        RST_DDR 		|= RST;
        RST_PORT 	|= RST;
#endif

        DC_DDR 		|=DC;

#if USE_CS == 1
        CS_DDR 		|= CS;
        CS_PORT 		|= CS;
#endif

#if USE_CS2 == 1
        CS2_DDR 		|= CS2;
        CS2_PORT 	|= CS2;
#endif

}
#endif

//***********I2C*****************
#if USE_SPI_OR_I2C == 0

void i2cSetBitrate ( uint16_t bitrateKHz ) {
        uint8_t bitrate_div;

        bitrate_div = (( F_CPU/1000l)/bitrateKHz );
        if ( bitrate_div >= 16 )
                bitrate_div = ( bitrate_div-16 ) / 2;

        TWBR = bitrate_div;
}

void TWI_start (void) {
        TWCR = ( 1<<TWINT ) | ( 1<<TWEN ) | ( 1<<TWSTA );
        while ( ! ( TWCR&(1<<TWINT )));
}

static void TWI_stop (void) {
        TWCR = ( 1<<TWINT ) | ( 1<<TWEN ) | ( 1<<TWSTO );
        while (( TWCR & ( 1<<TWSTO )));
}

static void TWI_write ( uint8_t bajt ) {
        TWDR = bajt;
        TWCR = ( 1<<TWINT ) | ( 1<<TWEN );
        while ( !( TWCR & ( 1<<TWINT )));
}

static void TWI_write_buf ( uint8_t SLA, uint8_t adr, uint16_t len, uint8_t *buf ) {
        TWI_start ();
        TWI_write ( SLA );
        TWI_write ( adr );
        while (len--) TWI_write ( *buf++ );
        TWI_stop ();
}
#endif

void mp_ssd1306_cmd ( uint8_t cmd ) {

#if USE_SPI_OR_I2C == 1

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

        DC_LO;

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_LO;
        #else
        if ( !display_nr ) CS_LO;
        else CS2_LO;
        #endif
#endif

        SPIwrite ( cmd);

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

#else

        uint8_t control = 0x00;
        TWI_start ();
        TWI_write ( OLED_I2C_ADDRESS );
        TWI_write ( control );
        TWI_write ( cmd );
        TWI_stop ();

#endif
}

void mp_ssd1306_data ( uint8_t dat ) {

#if USE_SPI_OR_I2C == 1

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

        DC_HI;

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_LO;
        #else
        if ( !display_nr ) CS_LO;
        else CS2_LO;
        #endif
#endif

        SPIwrite ( dat );

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

#else
        uint8_t control = 0x40;
        TWI_start ();
        TWI_write ( OLED_I2C_ADDRESS );
        TWI_write ( control );
        TWI_write ( dat );
        TWI_stop ();
#endif
}



void mp_ssd1306_display ( void ) {
        mp_ssd1306_cmd ( SSD1306_SETLOWCOLUMN 	| 0x0 );
        mp_ssd1306_cmd ( SSD1306_SETHIGHCOLUMN 	| 0x0 );
        mp_ssd1306_cmd ( SSD1306_SETSTARTLINE		| 0x0 );

#if USE_SPI_OR_I2C == 1

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

        DC_HI;

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_LO;
        #else
        if ( !display_nr ) CS_LO;
        else CS2_LO;
        #endif
#endif

        for ( uint16_t i = 0; i < BUF_SIZE; i++ ) {
                SPIwrite ( ssd1306_buf [i] );
        }

#if USE_CS == 1
        #if USE_CS2 == 0
        CS_HI;
        #else
        if ( !display_nr ) CS_HI;
        else CS2_HI;
        #endif
#endif

#else

        TWI_write_buf ( OLED_I2C_ADDRESS, 0x40, BUF_SIZE, ssd1306_buf );

#endif
}



void mp_ssd1306_drawPixel ( int x, int y, uint8_t bw ) {
        if (( x<0 ) || ( x>=SSD1306_WIDTH ) || ( y<0 ) || ( y>=SSD1306_HEIGHT ))
        	return;

        if ( bw ) ssd1306_buf[x+( y/8 )*SSD1306_WIDTH ] |= ( 1<<( y%8 )); //zapal
        else ssd1306_buf [ x+( y/8 )*SSD1306_WIDTH ] &= ~ ( 1<<(y%8 )); // zgas
}

void mp_ssd1306_cls ( void ) {
        memset ( ssd1306_buf, 0x00, ( BUF_SIZE ));
}

void mp_ssd1306_init ( uint8_t vcc, uint8_t refresh, uint8_t rst_disable ) {

#if USE_SPI_OR_I2C == 1
        ssd1306_InitSpi ();

if ( !rst_disable ) {
        #if USE_RST == 1
                RST_HI;
                _delay_ms ( 25 );
                RST_LO;
                _delay_ms ( 25 );
                RST_HI;
#endif
}
#else
        i2cSetBitrate ( 400 );
        I2C_DIR |= ( 1<< SCL ) | ( 1<<SDA );
        _delay_ms ( 50 );
#endif

        mp_ssd1306_cmd ( SSD1306_DISPLAYOFF );										//0xAE
        mp_ssd1306_cmd ( SSD1306_SETDISPLAYCLOCKDIV );							// 0xD5
        mp_ssd1306_cmd ( refresh);

        mp_ssd1306_cmd ( SSD1306_SETMULTIPLEX );									// 0xA8
        mp_ssd1306_cmd ( 0x3F );

        mp_ssd1306_cmd ( SSD1306_SETDISPLAYOFFSET );							// 0xD3
        mp_ssd1306_cmd ( 0x0 );																	// no offset
        mp_ssd1306_cmd ( SSD1306_SETSTARTLINE | 0x0 );							// line #0
        mp_ssd1306_cmd ( SSD1306_CHARGEPUMP );										// 0x8D

        if (vcc== SSD1306_EXTERNALVCC)  mp_ssd1306_cmd ( 0x10 );
        else    mp_ssd1306_cmd ( 0x14 );

        mp_ssd1306_cmd ( SSD1306_MEMORYMODE );									// 0x20
        mp_ssd1306_cmd  ( 0x00 );																// 0x0 act like ks0108
        mp_ssd1306_cmd ( SSD1306_SEGREMAP | 0x1 );
        mp_ssd1306_cmd ( SSD1306_COMSCANDEC );

        mp_ssd1306_cmd ( SSD1306_SETCOMPINS );										 // 0xDA BRAKOWALO
        mp_ssd1306_cmd ( 0x12 );
        mp_ssd1306_cmd ( SSD1306_SETCONTRAST );									//0x81

        if (vcc== SSD1306_EXTERNALVCC)  mp_ssd1306_cmd ( 0x9F );
        else    mp_ssd1306_cmd ( 0xCF );

        mp_ssd1306_cmd(SSD1306_SETPRECHARGE);										// 0xd9

        if (vcc == SSD1306_EXTERNALVCC) mp_ssd1306_cmd ( 0x22 );
        else mp_ssd1306_cmd ( 0xF1 );

#if defined SSD1306_128_32

        mp_ssd1306_cmd ( SSD1306_SETMULTIPLEX );
        mp_ssd1306_cmd ( 0x1F );

        mp_ssd1306_cmd ( SSD1306_SETCOMPINS );
        mp_ssd1306_cmd ( 0x02 );
#endif
        //dla 128 x 64
#if defined SSD1306_128_64

        mp_ssd1306_cmd ( SSD1306_SETMULTIPLEX );
        mp_ssd1306_cmd ( 0x3F );

        mp_ssd1306_cmd ( SSD1306_SETCOMPINS );
        mp_ssd1306_cmd ( 0x12 );
#endif

        mp_ssd1306_cmd ( SSD1306_SETVCOMDETECT ); 								// 0xDB
        mp_ssd1306_cmd ( 0x40 );

        mp_ssd1306_cmd ( SSD1306_DISPLAYALLON_RESUME );						// 0xA4
        mp_ssd1306_cmd ( SSD1306_NORMALDISPLAY );									// 0xA6

        mp_ssd1306_cmd ( SSD1306_DISPLAYON );

        mp_ssd1306_display ();
}

void mp_ssd1306_refresh_pages ( uint8_t page_nr, uint8_t pages_cnt, uint8_t col_start, uint8_t col_end ) {

	uint8_t  page_cnt, col_cnt;
	uint8_t * ram_buf_start;

	for ( page_cnt = page_nr; page_cnt < ( page_nr + pages_cnt); page_cnt ++) {

		mp_ssd1306_cmd ( SSD1306_SETLOWCOLUMN | ( col_start & 0X0f) );
		mp_ssd1306_cmd ( SSD1306_SETHIGHCOLUMN | col_start >> 4 );
		mp_ssd1306_cmd ( 0xB0 + pages_cnt );

		ram_buf_start = &ssd1306_buf [ ( page_cnt * 128 ) + col_start ];

		DC_HI ;

		#if USE_CS == 1
			#if USE_CS2 == 0
			CS_LO;
			#else
			if ( !display_nr ) CS_LO;
			else CS2_LO;
			#endif
		#endif

		for ( page_cnt = col_start; page_cnt < col_end; col_cnt ++) {
			SPIwrite ( *ram_buf_start ++);
		}

	}

}
