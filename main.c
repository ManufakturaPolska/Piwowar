/*
 * main.c
 * 	Piwowar Copyright (C) 2015  Marcin
 *			Ten program stanowi wolne oprogramowanie: mo�esz je rozpowszechnia� i/lub modyfikowa� na warunkach GNU
 *			Powszechnej Licencji Publicznej opublikowanej przez Free Software Foundation, wed�ug wersji 3 Licencji
 *			lub (wed�ug uznania) jakiejkolwiek wersji p�niejszej.
 *
 *			Ten program jest rozpowszechniany z nadziej�, �e oka�e si� przydatny, ale BEZ JAKIEJKOLWIEK GWARANCJI,
 *			nawet bez domy�lnej gwarancji PRZYDATNO�CI HANDLOWEJ lub PRZYDATNO�CI DO OKRE�LONYCH ZASTOSOWA�.
 *			Przeczytaj GNU Powszechn� Licencj� Publiczn� w celu zapoznania si� ze szczeg�ami.
 *
 *			Powiniene� otrzyma� kopi� GNU Powszechnej Licencji Publicznej wraz z tym programem.
 *			Je�eli nie otrzyma�e� jej, zobacz na	<http://www.gnu.org/licenses/>.
 *
 *
 *  Created on: 3 sty 2015
 *  
 *
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
#include "BMP/bmp.h"



// poni�sz� linijk� czasami trzeba wpisa� w eclipse przed definicjami
// zmiennych w pami�ci EEPROM, �eby nie podkre�la� sk�adni jako b��dnej
#define EEMEM __attribute__((section(".eeprom")))


int main(void){

	mp_ssd1306_init(SSD1306_SWITCHCAPVCC, REFRESH_MAX,0);
	mp_ssd1306_cmd(0x81);	//kontrast na min
	mp_ssd1306_cmd(0);

	mp_ssd1306_drawBitmap_P (0, 0, pas, 128, 16, 1);
	mp_ssd1306_display();
			_delay_ms(1000);
	mp_ssd1306_drawBitmap_P (112, 0, water_pas, 16, 16, 1);
	mp_ssd1306_display();
	mp_ssd1306_drawBitmap_P (112, 0, water_min, 16, 16, 0);
	mp_ssd1306_display();
			_delay_ms(1000);
	mp_ssd1306_drawBitmap_P (112, 17, termometr, 16, 16, 1);
	mp_ssd1306_display();



	while(1){

	        }
}

