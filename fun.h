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

#ifndef FUN_H_
#define FUN_H_


// definicje dla preprocesora
#define WVALVE_PIN (1<<PB1)								// definicja pinu do kt�rego pod��czona jest elektrozawor wody
#define WVALVE_ON PORTB &= ~WVALVE_PIN		// makrodefinicja � za��czenie elektrozaworu wody
#define WVALVE_OFF PORTB |= WVALVE_PIN		// makrodefinicja � wy��czenie elektrozaworu wody




void mp_rinse (uint8_t r_time);												// czas w sekundach

#endif /* FUN_H_ */


