/*                  e-gadget.header
 * main.c
 *
 *  Created on: 2015-01-04
 *    Modyfied: 2015-01-04 12:59:07
 *      Author: Marcin
 *
 * Project name: "Piwowar"
 *
 *		Piwowar Copyright (C) 2015  Marcin
 *			Ten program stanowi wolne oprogramowanie: mo�esz je rozpowszechnia� i/lub modyfikowa� na warunkach GNU
 *			Powszechnej Licencji Publicznej opublikowanej przez Free Software Foundation, wed�ug wersji 3 Licencji
 *			lub (wed�ug uznania) jakiejkolwiek wersji p�niejszej.
 *			Ten program jest rozpowszechniany z nadziej�, �e oka�e si� przydatny, ale BEZ JAKIEJKOLWIEK GWARANCJI,
 *			nawet bez domy�lnej gwarancji PRZYDATNO�CI HANDLOWEJ lub PRZYDATNO�CI DO OKRE�LONYCH ZASTOSOWA�.
 *			Przeczytaj GNU Powszechn� Licencj� Publiczn� w celu zapoznania si� ze szczeg�ami.
 *			Powiniene� otrzyma� kopi� GNU Powszechnej Licencji Publicznej wraz z tym programem.
 *			Je�eli nie otrzyma�e� jej, zobacz na <http://www.gnu.org/licenses/>.
 *
 *          MCU: ATmega32
 *        F_CPU: 11 059 200 Hz
 *
 *    Flash: 2 324 bytes   [ 7,1 % ]
 *      RAM: 1 072 bytes   [ 52,3 % ]
 *   EEPROM:  0 bytes   [ 0,0 % ]
 *
 */


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "1Wire/ds18x20.h"
#include "MP_SSD1306/mp_ssd1306.h"
#include "fun.h"



// poni�sz� linijk� czasami trzeba wpisa� w eclipse przed definicjami
// zmiennych w pami�ci EEPROM, �eby nie podkre�la� sk�adni jako b��dnej
#define EEMEM __attribute__((section(".eeprom")))


int main(void){

		mp_ssd1306_init(SSD1306_SWITCHCAPVCC, REFRESH_MAX, 0);
//	mp_ssd1306_cmd(0x81);	//kontrast na min
//	mp_ssd1306_cmd(0);
		mp_ssd1306_display();


//	mp_rinse (90);

	while(1){

	        }
}




