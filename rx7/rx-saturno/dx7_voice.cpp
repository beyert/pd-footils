/***************************************************************************
                          dx7_voice.cpp  -  description
                             -------------------
    begin                : Mon Jan 28 2002
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

Sint32 Dx7_Voice::sin_table[SINE_LENGTH];
Sint32 Dx7_Voice::eg_amp_table[ENV_LENGTH];
bool Dx7_Voice::tables_created=false;


int Dx7_Voice::base_freq;





void Dx7_Voice::calculate() {

        if (status==DEAD) return;

	int i;

        joint.out=0;	
        joint.feedback=((Uint64)*joint.feedback_ptr*(Uint64)feedback_multiplier)>>FDBK_MULT_BITS;

	memset(joint.inter,0,sizeof(Sint32)*MAX_OPERATORS);
			

	for (i=5;i>=0;i--) {
		calculate_op(op[i]);

		op[i].increment();
	}		

}

void Dx7_Voice::init_tables() {

	if (tables_created) return;

	signed int i,x;
	signed int n;
	double o,m;



	for (i=0; i<SINE_LENGTH; i++) {
	
		double sine_val;
		
		sine_val=sin( ((i)*(2*M_PI)) / SINE_LENGTH ); // index * radian cycle / index max
		sine_val*=SINE_LENGTH/(2*M_PI); //quite a big table yes		
		sin_table[i]=sine_val;
	}
	

	
	for (i=0; i<ENV_LENGTH; i++) {

       		double multiplier;
			
       		multiplier=Dx7_Tables::EG_amp_to_peak[i];
       		multiplier*=MATRIX_FRAC_LENGTH;
       		eg_amp_table[i]=multiplier;
	}			
	
//	i/=0;

	tables_created=true;	
}



Dx7_Voice::Dx7_Voice(){

	joint.feedback=0;
	joint.feedback_ptr=&joint.feedback;	
	for (int i=0;i<MAX_OPERATORS;i++) {
		op[i].eg.index=op[i].index=i+1;
		
	}	
	
	channel_in_use=-1;
	
	init_tables();
	status=DEAD;
}
Dx7_Voice::~Dx7_Voice(){
}
