/*
  SubniAnalogTools.h - SubniAnalogTools library
  Copyright (c) 2013 MDPS.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SUBNIANALOGTOOLS_h
#define SUBNIANALOGTOOLS_h

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <math.h>

//#define LOG_2_10 0.3010299956639811952137388947244f
#define SLOG_2_10 0.30f
#define SANALOG_READS_DELAY 15 //Milisegundos entre lecturas
#define SANALOG_NUM_READS 8 //Numero de lecturas analogicas para hacer la media tiene que ser una potencia de 2 (2,4,8,16,32...)


class SubniAnalogTools
{
	public:
		SubniAnalogTools(
			uint16_t vcc  = 5000, 
			uint16_t vref = 2500,
			uint16_t vref_count = 512,
			uint16_t adc_res = 10) : 
			_vcc(vcc), 
			_vref(vref),
			_vref_count(vref_count),
			_adc_res(adc_res){
				init();
			};
		void setup(uint16_t vcc, uint16_t vref, uint16_t vref_count, uint16_t adc_res);
		void set_vref_count(uint16_t vref_count);
		uint16_t read(uint8_t pin);
		uint16_t read_mv(uint8_t pin);
		uint16_t read_mv_compensated(uint8_t pin);
		uint16_t calculate_mv(uint16_t adc_count);
		uint16_t calculate_mv_compensated(uint16_t adc_count);
	private:
		double   _mv_per_count;
		uint16_t _vcc;
		uint16_t _vref;
		uint16_t _vref_count;
		uint16_t _adc_res;
		uint8_t  _analog_avg_factor;
		
		void init();
};

extern SubniAnalogTools AnalogTools;

#endif

