/*                  e-gadget.header
 * fun.c
 *
 *  Created on: 2015-01-04
 *     Modyfied: 2015-01-04 12:59:07
 *        Author: Marcin
 *
 * Project name: "Piwowar"
 *
 *		Piwowar Copyright (C) 2015  Marcin
 *			Ten program stanowi wolne oprogramowanie: mo�esz je rozpowszechnia� i/lub modyfikowa� na warunkach GNU
 *			Powszechnej Licencji Publicznej opublikowanej przez Free Software Foundation, wed�ug wersji 3 Licencji
 *			lub (wed�ug uznania) jakiejkolwiek wersji p�niejszej.
 *
 *			Ten program jest rozpowszechniany z nadziej�, �e oka�e si� przydatny, ale BEZ JAKIEJKOLWIEK GWARANCJI,
 *			nawet bez domy�lnej gwarancji PRZYDATNO�CI HANDLOWEJ lub PRZYDATNO�CI DO OKRE�LONYCH ZASTOSOWA�.
 *			Przeczytaj GNU Powszechn� Licencj� Publiczn� w celu zapoznania si� ze szczeg�ami.
 *
 *			Powiniene� otrzyma� kopi� GNU Powszechnej Licencji Publicznej wraz z tym programem.
 *			Je�eli nie otrzyma�e� jej, zobacz na <http://www.gnu.org/licenses/>.
 *
 *         	 MCU: ATmega32
 *           F_CPU: 11 059 200 Hz
 *
 *             Flash: 2 324 bytes   [ 7,1 % ]
 *              RAM: 1 072 bytes   [ 52,3 % ]
 *         EEPROM:  0 bytes   [ 0,0 % ]
 *
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "fun.h"
#include "MP_SSD1306/mp_ssd1306.h"


const uint8_t rinse[] PROGMEM = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xF0,
	0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x03,0xFF,0xFF,0x80,0x00,0x00,0x0F,
	0xFF,0xFF,0xE0,0x00,0x00,0x1F,0xFF,0xFF,0xF0,0x00,0x00,0x7F,0xFF,0xFF,0xFC,0x00,
	0x00,0xFF,0xFF,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xFF,
	0xFF,0x80,0x03,0xFF,0xF9,0xFF,0xFF,0x80,0x07,0xFF,0xF8,0x7F,0xFF,0xC0,0x07,0xFF,
	0xFC,0x3F,0xFF,0xC0,0x0F,0xFF,0xFC,0x3F,0xFF,0xE0,0x0F,0xFF,0xFC,0x1F,0xFF,0xE0,
	0x1F,0xFF,0xF8,0x1F,0xFF,0xF0,0x1F,0xFF,0xF8,0x0F,0xFF,0xF0,0x1F,0xFF,0xF8,0x0F,
	0xFF,0xF0,0x3F,0xFF,0xF0,0x07,0xFF,0xF8,0x3F,0xFF,0xF0,0x07,0xFF,0xF8,0x3F,0xFF,
	0xE0,0x03,0xFF,0xF8,0x3F,0xFF,0xE0,0x03,0xFF,0xF8,0x3F,0xFF,0xC0,0x03,0xFF,0xF8,
	0x3F,0xFF,0xC0,0x01,0xFF,0xF8,0x3F,0xFF,0x80,0x01,0xFF,0xF8,0x3F,0xFF,0x80,0x01,
	0xFF,0xF8,0x3F,0xFF,0x00,0x01,0xFF,0xF8,0x1F,0xFF,0x00,0x01,0xFF,0xF0,0x1F,0xFF,
	0x00,0x01,0xFF,0xF0,0x1F,0xFF,0x00,0x01,0xFF,0xF0,0x0F,0xFF,0x00,0x01,0xFF,0xE0,
	0x0F,0xFF,0x80,0x03,0xFF,0xE0,0x07,0xFF,0xC0,0x07,0xFF,0xC0,0x07,0xFF,0xE0,0x0F,
	0xFF,0xC0,0x03,0xFF,0xF8,0x3F,0xFF,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x01,0xFF,
	0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x7F,0xFF,0xFF,0xFC,0x00,
	0x00,0x1F,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0xFF,0xFF,0xE0,0x00,0x00,0x03,0xFF,0xFF,
	0x80,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x1F,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};




void mp_rinse (uint8_t time_rinse) {
	uint8_t tr = time_rinse;

		if (tr > 0) {
			WVALVE_ON;
			_delay_ms (1000);
			mp_wysBitmap_P (48, 48, rinse, 16, 16, 1);
			mp_ssd1306_display ();

			tr --;} 			//w��cz przep�ukiwanie
		else WVALVE_OFF; 														//wy��cz


}

