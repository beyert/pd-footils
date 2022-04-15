/***************************************************************************
                          tables.h  -  description
                             -------------------
    begin                : Fri Jan 11 2002
    copyright            : (C) 2002 by Juan Linietsky
    email                : coding@reduz.com.ar
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DX7_TABLES_H
#define DX7_TABLES_H

#include "typedefs.h"


#define CYCLE_SIZE 4096
#define TABLE_SIZE CYCLE_SIZE


class Dx7_Tables {
public:
	static int output_level_conversion[100];   //chowning/bristow table
	
	static float EG_rate_rise_duration[128];
	static float EG_rate_decay_duration[128];

	static float EG_rate_rise_percent[128];
	static float EG_rate_decay_percent[128];
	
	static float Dx7_Tables::EG_level_to_peak[128]; // for modulatoros
	static float Dx7_Tables::EG_amp_to_peak[128]; //for carriers
	static Sint32 carrier_modifier[100];
	static Sint32 modulator_modifier[100];	
	
	
	
	Dx7_Tables();	
	

};

class SineTable {
public:

	/* Sine table, 4k of 7:24 (signed) fixed point samples. Maybe i should use a smaller one so
	it can take more advantage of L2 caches? Tho i'm not sure how much the quality loss is.
	I'm going to change this to a generated table later*/
//private:
	static int table[TABLE_SIZE];

public:	
	inline int sine(Uint64 p_ofs) { // p_ofs == 48:24 fixed - no interpolation yet, returns 7:24 (signed) fixed point
		
		return table[(p_ofs >> 24) % TABLE_SIZE];
	
	}

	inline int cosine(Uint64 p_ofs) { // p_ofs == 48:24 fixed - no interpolation yet
		
		return sine(p_ofs-(TABLE_SIZE >> 2));
	}
		

};

#endif DX7_TABLES_H
