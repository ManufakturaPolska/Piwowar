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
	mp_ssd1306_cmd (0x81);	//kontrast na min
	mp_ssd1306_cmd (0);

	// mp_narZnak (20,20, , 1, 0, 4 ); do poprawy
	// mp_wysText ( 20, 20, "Ania", 2, 0, 1 ) ;
	// mp_wysLiczbe ( 20, 20, 15, 3, 1, 0);
//	mp_narProst ( 20, 20, 20, 40, 1 );
//	mp_wypProst ( 20, 20, 16, 36, 1);
//	mp_narProstOkrag ( 20, 20, 30, 30, 3, 1);
//	mp_wypProstOkrag ( 20, 20, 30, 30, 5, 1 ); // do poprawy
//	mp_narLiniePoz (20, 20, 30, 1 );
//	mp_narLiniePion (20, 20, 30, 1);
//	mp_narLinieDow ( 20, 20, 10, 40, 1 );
//	mp_narOkrag ( 20, 20, 30, 1 ); // do poprawy
//	mp_wypOkrag ( 20, 20, 30, 1 ) ; // do poprawy
//	mp_narTrojkat (10, 60, 50, 10, 60, 60, 1 );
//	mp_ssd1306_display ();
//	_delay_ms(1000);
//	mp_narTrojkat (10, 60, 50, 10, 60, 60, 0 );
//	mp_mrugajEkran ( 1 ) ;
//	mp_ssd1306_display ();
//_delay_ms(1000);
//	mp_mrugajEkran (0 ) ;
//	mp_narTrojkat (10, 60, 50, 10, 60, 60, 1 );
//
//	 mp_wysText ( 10, 20, "Ania", 2, 0, 1 ) ;
//	 mp_startPrzewPrawo ( 1, 7 );
//	mp_ssd1306_display ();


//	mp_rinse (90);

	while(1){

	        }
}




