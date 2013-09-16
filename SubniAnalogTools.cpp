/*
  SubniAnalogTools.cpp - SubniAnalogTools library
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

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include "SubniAnalogTools.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors & Inicialization
 ******************************************************************************/
void SubniAnalogTools::init()
{
	_mv_per_count = (float)(_vcc / pow(2,10));
	_analog_avg_factor = (uint8_t)( log10(SANALOG_NUM_READS) / SLOG_2_10 );
}
 
/******************************************************************************
 * Configuracion
 ******************************************************************************/

void SubniAnalogTools::setup(uint16_t vcc, uint16_t vref, uint16_t vref_count, uint16_t adc_res)
{
	_vcc = vcc;
	_vref = vref;
	_vref_count = vref_count;
	_adc_res = adc_res;
	init();
}

void SubniAnalogTools::set_vref_count(uint16_t vref_count)
{
	_vref_count = vref_count;
}
 
/******************************************************************************
 * User API
 ******************************************************************************/

uint16_t SubniAnalogTools::read(uint8_t pin)
{
	uint16_t value = 0;
	for(int i = 0; i < SANALOG_NUM_READS; i++)
	{    
		value += analogRead(pin); 
		delay(SANALOG_READS_DELAY);
	}
	return (uint16_t)(value >> _analog_avg_factor);
}

uint16_t SubniAnalogTools::read_mv(uint8_t pin)
{
	return calculate_mv(read(pin));
}

uint16_t SubniAnalogTools::read_mv_compensated(uint8_t pin)
{
	return calculate_mv_compensated(read(pin));
}

uint16_t SubniAnalogTools::calculate_mv(uint16_t value)
{
	return (uint16_t)round( (value * _mv_per_count) );
}

uint16_t SubniAnalogTools::calculate_mv_compensated(uint16_t value)
{
	return (uint16_t)round( ((value * (float)_vref) / (float)_vref_count) );
}

SubniAnalogTools AnalogTools;