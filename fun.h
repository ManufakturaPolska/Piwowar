/*                  e-gadget.header
 * fun.h
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

#ifndef FUN_H_
#define FUN_H_


// definicje dla preprocesora
#define WVALVE_PIN (1<<PB1)								// definicja pinu do którego pod³¹czona jest elektrozawor wody
#define WVALVE_ON PORTB &= ~WVALVE_PIN		// makrodefinicja – za³¹czenie elektrozaworu wody
#define WVALVE_OFF PORTB |= WVALVE_PIN		// makrodefinicja – wy³¹czenie elektrozaworu wody




void mp_rinse (uint8_t r_time);												// czas w sekundach

#endif /* FUN_H_ */


