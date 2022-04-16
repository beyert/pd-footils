/***************************************************************************
                          dx7_voice_envelope.cpp  -  description
                             -------------------
    begin                : Thu Jan 31 2002
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

void Dx7_Voice::Eg::reset() {

	
	val=level[0];

	current_node=-1;
	setup_next_node();	
	
}

void Dx7_Voice::Eg::set_climb_rate(Uint16 p_rate,Uint16 p_level_l,Uint16 p_level_r) {

       	float *duration_table,*percent_table,length_modif;
       	double duration,increment;

	
       	duration_table=(p_level_r>p_level_l) ? Dx7_Tables::EG_rate_rise_duration : Dx7_Tables::EG_rate_decay_duration;
       	percent_table=(p_level_r>p_level_l) ? Dx7_Tables::EG_rate_rise_percent : Dx7_Tables::EG_rate_decay_percent;
	
       	duration=duration_table[p_rate];
		
       	length_modif=percent_table[p_level_r]-percent_table[p_level_l];
       	length_modif=sqrt(length_modif*length_modif);// make it positive
		
       	duration*=length_modif;
       	duration=duration==0?0.001:duration;
       	duration*=base_freq;
       	//duration*=(p_level_r>p_level_r)?5:1;
       	
       	increment=((p_level_r<<FRAC_SHIFT)-(p_level_l<<FRAC_SHIFT))/duration;
       	
//	increment*=(float)FRAC_MASK;
//	increment/=base_freq;
	climb_rate=increment;
	if (climb_rate==0) climb_rate=1;

}



void Dx7_Voice::Eg::setup_next_node() {


	val=level[(4+current_node)%4] << FRAC_SHIFT; // so we'll get 3 if current_node==-1
	current_node++;

        if (current_node==4) {

        	phase=FINISHED;
        	return;
        } else {
		
		if (current_node==0) {
		
			phase=ATTACK;
		} else if (current_node==2) {
			phase=SUSTAIN;
		}
		
//		printf("Eg %i, set climb rate between %i(%i) and %i(%i), rate %i ",index,((current_node+3)%4),level[(current_node+3)%4],current_node,level[current_node],rate[current_node]);
		set_climb_rate(rate[current_node],level[(current_node+3)%4],level[current_node]);
		
        }
}

void Dx7_Voice::Eg::set_release_phase() {

	current_node=3;
	phase=RELEASE;
	set_climb_rate(rate[current_node],(val>>FRAC_SHIFT),level[current_node]);

}

Dx7_Voice::Eg::Eg() {

	memset(rate,0,sizeof(Uint16)*4);
	memset(level,0,sizeof(Uint16)*4);
        val=99<<FRAC_SHIFT;
	phase=FINISHED;

}
