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
 *			Ten program stanowi wolne oprogramowanie: mo¿esz je rozpowszechniaæ i/lub modyfikowaæ na warunkach GNU
 *			Powszechnej Licencji Publicznej opublikowanej przez Free Software Foundation, wed³ug wersji 3 Licencji
 *			lub (wed³ug uznania) jakiejkolwiek wersji póŸniejszej.
 *			Ten program jest rozpowszechniany z nadziej¹, ¿e oka¿e siê przydatny, ale BEZ JAKIEJKOLWIEK GWARANCJI,
 *			nawet bez domyœlnej gwarancji PRZYDATNOŒCI HANDLOWEJ lub PRZYDATNOŒCI DO OKREŒLONYCH ZASTOSOWAÑ.
 *			Przeczytaj GNU Powszechn¹ Licencjê Publiczn¹ w celu zapoznania siê ze szczegó³ami.
 *			Powinieneœ otrzymaæ kopiê GNU Powszechnej Licencji Publicznej wraz z tym programem.
 *			Je¿eli nie otrzyma³eœ jej, zobacz na <http://www.gnu.org/licenses/>.
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



// poni¿sz¹ linijkê czasami trzeba wpisaæ w eclipse przed definicjami
// zmiennych w pamiêci EEPROM, ¿eby nie podkreœla³ sk³adni jako b³êdnej
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




