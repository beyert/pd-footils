/***************************************************************************
                          dx7_voice_operator.cpp  -  description
                             -------------------
    begin                : Sun Feb 3 2002
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

#include "dx7_voice.h"
#include <math.h>

void Dx7_Voice::Op::recalculate_increment() {

	double aux_freq;
	
	aux_freq=freq;
	aux_freq+=((detune-7.0)/4.0)*FRAC_LENGTH/8;
	aux_freq=(((aux_freq*coarse)/2))/base_freq;
        aux_freq*=(1.0+((float)fine/100.0));
        phase_increment=aux_freq;
	
	


}
void Dx7_Voice::Op::set_velocity(Uint8 p_velocity) {

	velocity=p_velocity;

}

void Dx7_Voice::Op::set_velocity_sens(Uint8 p_velocity) {

	velocity_sens=p_velocity;
}

void Dx7_Voice::Op::prepare_envelope() {

 	int i;
 	float amp;
 	float sens;
 	
 	amp=sin ( (M_PI/2) * ((float)velocity / 127.0) );
 	sens=velocity_sens;
 	sens/=7;

	
	
 	for (i=0;i<4;i++) {
 	
 		float level;
 		
 		level=(float)output_level*(float)eg_base.level[i]/(LEV_LENGTH-1);
 		
 		level=(level*(1-sens))+(level*sens*amp);
 	
		eg.rate[i]=eg_base.rate[i];
		eg.level[i]=level;
		eg.reset(); 	
 	}
}

void Dx7_Voice::Op::set_coarse(Uint8 p_coarse) {

	coarse=(p_coarse)?p_coarse*2:1;
	recalculate_increment();
}

void Dx7_Voice::Op::set_fine(Uint8 p_detune) {

	fine=p_detune;
	recalculate_increment();
}

void Dx7_Voice::Op::set_detune(Uint8 p_detune) {

	detune=p_detune;
	recalculate_increment();
}

void Dx7_Voice::Op::set_freq(Uint32 p_freq) {

	freq=p_freq;	
	recalculate_increment();
}

void Dx7_Voice::Op::set_output_level(Uint8 p_level) {

	output_level=p_level;
}

void Dx7_Voice::Op::reset() {

	phase_count=0;
	phase_increment=0;
	eg_level=99;
	coarse=2;
	fine=0;
	freq=50;
	zero=0; //doh
	in=&zero;
	out=&selfout;
//	translation_table=Dx7_Tables::modulator_modifier;

        eg.reset();
}

Dx7_Voice::Op::Op() {

	reset();	
}

