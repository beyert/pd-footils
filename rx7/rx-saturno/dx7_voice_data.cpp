/***************************************************************************
                          dx7_voice_data.cpp  -  description
                             -------------------
    begin                : Fri Feb 1 2002
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

void Dx7_Voice::set_note(char p_note,char p_velocity) {

	double freq=8.1757989156*pow(2,((float)p_note/12.0)); //get current freq!
	int i;
	//float increment=1.0/freq;
        freq*=FRAC_LENGTH;

	for (i=0;i<MAX_OPERATORS;i++) {
	
		op[i].set_freq(freq);
		op[i].set_velocity(p_velocity);
		op[i].prepare_envelope();
	}
	
	status=ATTACKING;
	note_in_use=p_note;
	
}

void Dx7_Voice::set_note_off(char p_velocity) {


	for (int i=0;i<MAX_OPERATORS;i++) {
	
		op[i].eg.set_release_phase();
	}
	status=RELEASING;
}


static float feedback_scaling[32] = {

      0.2, 0.2, 0.2, 1.0, 0.1, 1.0, 1.0, 0.1,
      0.4, 0.2, 0.2, 0.2, 0.1, 1.0, 0.4, 1.0,
      0.5, 1.0, 0.4, 0.2, 0.2, 0.1, 0.2, 0.6,
      0.2, 0.2, 0.2, 0.2, 0.6, 0.2, 0.6, 0.6
};

void Dx7_Voice::set_data(Data *p_data) {

	int i;
	double aux_feedbk;
	
	
	for (i=0;i<MAX_OPERATORS;i++) {
		
		op[i].reset();
	}	
	
	set_algorithm(p_data->algorithm);
	
	aux_feedbk=p_data->feedback_level;
	aux_feedbk/=(2*M_PI);	
	aux_feedbk*=feedback_scaling[p_data->algorithm];
	
	ffeedback_multiplier=aux_feedbk;
	feedback_multiplier=aux_feedbk*FDBK_MULT_LENGTH;
	
        		
	for (i=0;i<MAX_OPERATORS;i++) {
	
		Data::Operator *t_op = &p_data->operators[i];


		
		op[i].set_output_level(t_op->output_level);

		op[i].set_coarse(t_op->coarse_tune);

		op[i].set_detune(t_op->detune);
		op[i].set_fine(t_op->fine_tune);
		op[i].set_velocity_sens(t_op->key_vel_sens);
		
		for (int j=0;j<4;j++) {
		

			op[i].eg_base.rate[j]=t_op->envelope.rate[j];
			op[i].eg_base.level[j]=t_op->envelope.level[j];
		}
	}
}
			
void Dx7_Voice::poll_for_dead_staus() {

	int checked_carriers=0;
	int dead_carriers=0;
	
	if (status==DEAD) return;

	for (int i=0;i<MAX_OPERATORS;i++) {		
	
		if (op[i].out==&joint.out) {
		
			checked_carriers++;
			if (op[i].eg.phase==Eg::FINISHED) dead_carriers++;
			if ((op[i].eg.phase==Eg::RELEASE) &&
			 ((eg_amp_table[op[i].eg.get_val()]>>MATRIX_FRAC_SHIFT)==0)) dead_carriers++;
		}
	}
	
	if (checked_carriers==dead_carriers) {
	
		status=DEAD;
		channel_in_use=-1;
	}

}

void Dx7_Voice::set_channel(char p_chan) {

	channel_in_use=p_chan;
}

char Dx7_Voice::get_note() {

	return note_in_use;
}

char Dx7_Voice::get_channel() {

	return channel_in_use;
}
void Dx7_Voice::kill() {

	status=DEAD;
}
Dx7_Voice::Status Dx7_Voice::get_status() {

	return status;	

}