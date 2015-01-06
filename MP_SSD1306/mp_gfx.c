/*                  e-gadget.header
 * mp_gfx.c
 *
 *  Created on: 2015-01-04
 *     Modyfied: 2015-01-04 22:22:52
 *        Author: Marcin
 *
 * Project name: "Piwowar"
 *
 *	Piwowar Copyright (C) 2015  Marcin
 *		Ten program stanowi wolne oprogramowanie: mo¿esz je rozpowszechniaæ i/lub modyfikowaæ na warunkach GNU
 *		Powszechnej Licencji Publicznej opublikowanej przez Free Software Foundation, wed³ug wersji 3 Licencji
 *		lub (wed³ug uznania) jakiejkolwiek wersji póŸniejszej.
 *		Ten program jest rozpowszechniany z nadziej¹, ¿e oka¿e siê przydatny, ale BEZ JAKIEJKOLWIEK GWARANCJI,
 *		nawet bez domyœlnej gwarancji PRZYDATNOŒCI HANDLOWEJ lub PRZYDATNOŒCI DO OKREŒLONYCH ZASTOSOWAÑ.
 *		Przeczytaj GNU Powszechn¹ Licencjê Publiczn¹ w celu zapoznania siê ze szczegó³ami.
 *		Powinieneœ otrzymaæ kopiê GNU Powszechnej Licencji Publicznej wraz z tym programem.
 *		Je¿eli nie otrzyma³eœ jej, zobacz na <http://www.gnu.org/licenses/>.
 *
 *          MCU: ATmega32
 *        F_CPU: 11 059 200 Hz
 *
 *       Flash: 2 668 bytes   [ 8,1 % ]
 *        RAM: 1 072 bytes   [ 52,3 % ]
 *   EEPROM:  0 bytes   [ 0,0 % ]
 *
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "mp_ssd1306.h"

int cursor_x, cursor_y;

void mp_wysBitmap_P (int x, int y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color ) {
        int i, j, byteWidth = ( w+7 ) / 8;
        for ( j=0; j<h; j++ ) {
                for ( i=0; i<w; i++ ) {
                        if ( pgm_read_byte( bitmap + j*byteWidth + i / 8 ) & ( 128>>( i & 7 ))) {
                        	mp_ssd1306_drawPixel ( x+i, y+j, color );
                        }
                }
        }
}

void mp_wysText ( int x, int y, char * str, uint8_t txt_size, uint8_t color, uint8_t bg ) {

	cursor_x = x; cursor_y = y;

	while ( * str) {
		mp_narZnak (cursor_x, cursor_y, *str++, color, bg, txt_size );
		cursor_x += txt_size * 6;
	}
}

void mp_wysText_P ( int x, int y, const char * str, uint8_t txt_size, uint8_t color, uint8_t bg ) {

	cursor_x = x; cursor_y = y;

	register char c;
	while ( * str) {
		c = pgm_read_byte ( str++ );
		mp_narZnak (cursor_x, cursor_y, c, color, bg, txt_size );
		cursor_x += txt_size * 6;
	}
}

void mp_wysLiczbe ( int x, int y, int data, uint8_t txt_size, uint8_t color, uint8_t bg) {

	char buf[16];
	mp_wysText ( x, y, itoa (data, buf, 10 ), txt_size, color, bg );


}

void mp_narZnak (int x, int y, char c, uint8_t color, uint8_t bg, uint8_t size ) {

	if (( x >= SSD1306_WIDTH) || ( y >=  SSD1306_HEIGHT) || (( x + 6 * size - 1) < 0 ) || (( y + 8 * size - 1) < 0)) return;

	uint8_t line;

	for (int8_t i=0; i<6; i++ ) {

	    if (i == 5)
	      line = 0x0;
	    else
	      line = pgm_read_byte ( font + ( c * 5 ) + i );
	    for ( int8_t j = 0; j<8; j++ ) {
	      if ( line & 0x1 ) {
	        if ( size == 1 ) // default size
	        	mp_ssd1306_drawPixel ( x+i, y+j, color );
	        else {  // big size
	        	mp_wypProst (x+(i*size), y+(j*size), size, size, color);
	        }
	      } else if (bg != color) {
	        if (size == 1) // default size
	        	mp_ssd1306_drawPixel (x+i, y+j, bg);
	        else {  // big size
	        	mp_wypProst (x+i*size, y+j*size, size, size, bg);
	        }
	      }
	      line >>= 1;
	    }
	  }
}

void mp_narLiniePoz ( int x, int y, int h, uint8_t color ) {
	mp_narLinieDow ( x, y, x, y + h - 1, color );

}

void mp_narLiniePion ( int x, int y, int w, uint8_t color) {
  // Update in subclasses if desired!
	mp_narLinieDow ( x, y, x+w-1, y, color );
}

// Bresenham's algorithm - thx wikpedia
void mp_narLinieDow ( int x0, int y0, int x1, int y1, uint8_t color ) {

	int steep = abs (y1 - y0) > abs (x1 - x0);
	  if (steep) {
	    swap (x0, y0);
	    swap (x1, y1);
	  }

	  if (x0 > x1) {
	    swap (x0, x1);
	    swap (y0, y1);
	  }

	  int dx, dy;
	  dx = x1 - x0;
	  dy = abs (y1 - y0);

	  int err = dx / 2;
	  int ystep;

	  if (y0 < y1) {
	    ystep = 1;
	  } else {
	    ystep = -1;
	  }

	  for (; x0<=x1; x0++) {
	    if (steep) {
	    	mp_ssd1306_drawPixel (y0, x0, color);
	    } else {
	    	mp_ssd1306_drawPixel (x0, y0, color);
	    }
	    err -= dy;
	    if (err < 0) {
	      y0 += ystep;
	      err += dx;
	    }
	  }


}

void mp_narOkrag ( int x, int y, uint8_t r, uint8_t bw) {
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int xa = 0;
	int ya = r;

	mp_ssd1306_drawPixel ( x, y + r, bw );
	mp_ssd1306_drawPixel ( x, y - r, bw );
	mp_ssd1306_drawPixel ( x + r, y, bw );
	mp_ssd1306_drawPixel ( x - r, y, bw );

	while (x<y) {
	    if (f >= 0) {
	      y--;
	      ddF_y += 2;
	      f += ddF_y;
	    }
	    x++;
	    ddF_x += 2;
	    f += ddF_x;

	    mp_ssd1306_drawPixel (x + xa, y + ya, bw);
	    mp_ssd1306_drawPixel (x - xa, y + ya, bw);
	    mp_ssd1306_drawPixel (x + xa, y - ya, bw);
	    mp_ssd1306_drawPixel (x - xa, y - ya, bw);
	    mp_ssd1306_drawPixel (x + ya, y + xa, bw);
	    mp_ssd1306_drawPixel (x - ya, y + xa, bw);
	    mp_ssd1306_drawPixel (x + ya, y - xa, bw);
	    mp_ssd1306_drawPixel (x - ya, y - xa, bw);
	  }
}

void mp_wypOkrag ( int x, int y, uint8_t r, uint8_t color ) {
	mp_narLiniePoz ( x, y - r, 2*r+1, color );
	mp_wypOkragPomoc ( x, y, r, 3, 0, color );


}

void mp_wypOkragPomoc ( int x, int y, int r, uint8_t cornername, int delta, uint8_t color ) {

	int f 			= 1 - r;
	int ddF_x 	= 1;
	int ddF_y 	= -2 * r;
	int x0     		= 0;
	int y0     		= r;

	  while (x<y) {
	    if (f >= 0) {
	      y--;
	      ddF_y += 2;
	      f     += ddF_y;
	    }
	    x++;
	    ddF_x += 2;
	    f     += ddF_x;

	    if (cornername & 0x1) {
	    	mp_narLiniePoz ( x0+x, y0-y, 2*y+1+delta, color);
	    	mp_narLiniePoz ( x0+y, y0-x, 2*x+1+delta, color);
	    }
	    if (cornername & 0x2) {
	    	mp_narLiniePoz (x0-x, y0-y, 2*y+1+delta, color);
	    	mp_narLiniePoz ( x0-y, y0-x, 2*x+1+delta, color);
	    }
	  }
}

void mp_narProst (int x, int y, int w, int h, uint8_t color) {
	mp_narLiniePion ( x, y, w, color );
	mp_narLiniePion ( x, y+h-1, w, color );
	mp_narLiniePoz ( x, y, h, color );
	mp_narLiniePoz ( x+w-1, y, h, color );
}

void mp_wypProst ( int x, int y, int w, int h, uint8_t color) {

	for (int16_t i=x; i < x + w; i++ ) {
		mp_narLiniePoz ( i, y, h, color );
	  }
}

void mp_narProstOkrag ( int x, int y, int w, int h, int r, uint8_t color) {

	mp_narLiniePion ( x + r  , y    , w - 2 * r, color );					// Top
	mp_narLiniePion ( x + r  , y + h - 1, w - 2 * r, color );				// Bottom
	mp_narLiniePoz ( x    , y + r  , h - 2 * r, color );					// Left
	mp_narLiniePoz ( x + w - 1, y + r  , h - 2 * r, color );				// Right

	mp_narOkragPomoc ( x + r    , y + r    , r, 1, color );
	mp_narOkragPomoc ( x + w - r - 1, y + r    , r, 2, color );
	mp_narOkragPomoc ( x + w - r - 1, y + h - r - 1, r, 4, color);
	mp_narOkragPomoc (x + r    , y + h - r - 1, r, 8, color);
}

void mp_narOkragPomoc ( int x0, int y0, int r, uint8_t cornername, uint8_t color) {

  int f     = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x     = 0;
  int y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
    	mp_ssd1306_drawPixel (x0 + x, y0 + y, color);
    	mp_ssd1306_drawPixel (x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
    	mp_ssd1306_drawPixel (x0 + x, y0 - y, color);
    	mp_ssd1306_drawPixel (x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
    	mp_ssd1306_drawPixel (x0 - y, y0 + x, color);
    	mp_ssd1306_drawPixel (x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
    	mp_ssd1306_drawPixel (x0 - y, y0 - x, color);
    	mp_ssd1306_drawPixel (x0 - x, y0 - y, color);
    }
  }
}

void mp_wypProstOkrag (int x, int y, int w, int h, uint8_t r, uint8_t color) {
  // smarter version
	mp_wypProst (x+r, y, w-2*r, h, color);

  // draw four corners
	mp_wypOkragPomoc (x+w-r-1, y+r, r, 1, h-2*r-1, color);
	mp_wypOkragPomoc (x+r    , y+r, r, 2, h-2*r-1, color);
}

void mp_narTrojkat (int x0, int y0, int x1, int y1, int x2, int y2, uint8_t color) {
	mp_narLinieDow (x0, y0, x1, y1, color);
	mp_narLinieDow (x1, y1, x2, y2, color);
	mp_narLinieDow (x2, y2, x0, y0, color);
}

void mp_wypTrojkat ( int x0, int y0, int x1, int y1, int x2, int y2, uint8_t color) {

  int a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    mp_narLiniePion (a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    mp_narLiniePion (a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    mp_narLiniePion (a, y, b-a+1, color);
  }
}

void mp_startPrzewPrawo ( uint8_t start, uint8_t stop ) {
	mp_ssd1306_cmd ( SSD1306_RIGHT_HORIZONTAL_SCROLL );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( start );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( stop );
	mp_ssd1306_cmd ( 0x01 );
	mp_ssd1306_cmd ( 0xFF );
	mp_ssd1306_cmd ( SSD1306_ACTIVATE_SCROLL );
}

void mp_startPrzewLewo ( uint8_t start, uint8_t stop ) {
	mp_ssd1306_cmd ( SSD1306_LEFT_HORIZONTAL_SCROLL );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( start );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( stop );
	mp_ssd1306_cmd ( 0x01 );
	mp_ssd1306_cmd ( 0xFF );
	mp_ssd1306_cmd ( SSD1306_ACTIVATE_SCROLL );
}

void mp_startPrzewUkosPrawo ( uint8_t start, uint8_t stop ) {
	mp_ssd1306_cmd ( SSD1306_SET_VERTICAL_SCROLL_AREA );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( SSD1306_HEIGHT );
	mp_ssd1306_cmd ( SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL );
	mp_ssd1306_cmd ( 0x00);
	mp_ssd1306_cmd ( start );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( stop );
	mp_ssd1306_cmd ( 0x01 );
	mp_ssd1306_cmd ( SSD1306_ACTIVATE_SCROLL );
}


void mp_startPrzewUkosLewo ( uint8_t start, uint8_t stop ) {
	mp_ssd1306_cmd ( SSD1306_SET_VERTICAL_SCROLL_AREA );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( SSD1306_HEIGHT );
	mp_ssd1306_cmd ( SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL );
	mp_ssd1306_cmd ( 0x00);
	mp_ssd1306_cmd ( start );
	mp_ssd1306_cmd ( 0x00 );
	mp_ssd1306_cmd ( stop );
	mp_ssd1306_cmd ( 0x01 );
	mp_ssd1306_cmd ( SSD1306_ACTIVATE_SCROLL );
}

void mp_stopPrzew ( void ) {
	mp_ssd1306_cmd ( SSD1306_DEACTIVATE_SCROLL );
}

void mp_mrugajEkran ( uint8_t i ) {
	if (i) mp_ssd1306_cmd ( SSD1306_INVERTDISPLAY );
	else mp_ssd1306_cmd ( SSD1306_NORMALDISPLAY );
}
