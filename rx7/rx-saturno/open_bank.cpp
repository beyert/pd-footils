/***************************************************************************
                          open_bank.cpp  -  description
                             -------------------
    begin                : Sun Jan 27 2002
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

#include "open_bank.h"

vector<Dx7_Voice::Data> Open_Bank::file(string p_filename) {

	Properties props;
	vector<Dx7_Voice::Data> data;
	int i,j;

	printf("open file %s\n",p_filename.c_str());
	props.load_from_text(p_filename.c_str());
	
	for (i=0;i<32;i++) {
	
		string section;
		char auxchr[400];
		Dx7_Voice::Data *samp;
		sprintf(auxchr,"Sample %i",i);
		section=auxchr;
		data.resize(data.size()+1);
		samp=&data[i];

		
		for (j=0;j<6;j++) {
		
			string varbase;
			sprintf(auxchr,"operator_%i_",j+1);
			varbase=auxchr;
			
			samp->operators[j].envelope.rate[0]=props.get_int_property(section,varbase+"envelope_rate_1");
			samp->operators[j].envelope.rate[1]=props.get_int_property(section,varbase+"envelope_rate_2");
			samp->operators[j].envelope.rate[2]=props.get_int_property(section,varbase+"envelope_rate_3");
			samp->operators[j].envelope.rate[3]=props.get_int_property(section,varbase+"envelope_rate_4");
			samp->operators[j].envelope.level[0]=props.get_int_property(section,varbase+"envelope_level_1");
			samp->operators[j].envelope.level[1]=props.get_int_property(section,varbase+"envelope_level_2");
			samp->operators[j].envelope.level[2]=props.get_int_property(section,varbase+"envelope_level_3");
			samp->operators[j].envelope.level[3]=props.get_int_property(section,varbase+"envelope_level_4");
			
			samp->operators[j].envelope.level[3]=props.get_int_property(section,varbase+"envelope_level_4");
             	
             		samp->operators[j].kb_scale_bkpoint=props.get_int_property(section,varbase+"keyboard_scaling_breakpoint");
			samp->operators[j].kb_scaling_l_depth=props.get_int_property(section,varbase+"keyboard_scaling_left_depth");
			samp->operators[j].kb_scaling_r_depth=props.get_int_property(section,varbase+"keyboard_scaling_right_depth");
			samp->operators[j].kb_scaling_l_curve=props.get_int_property(section,varbase+"keyboard_scaling_left_curve");
			samp->operators[j].kb_scaling_r_curve=props.get_int_property(section,varbase+"keyboard_scaling_breakpoint");
			
			samp->operators[j].rate_scale=props.get_int_property(section,varbase+"oscilator_rate_scale");
			samp->operators[j].detune=props.get_int_property(section,varbase+"oscilator_detune");
			samp->operators[j].amp_modulation_sens=props.get_int_property(section,varbase+"amp_modulation_sens");
			samp->operators[j].key_vel_sens=props.get_int_property(section,varbase+"key_velocity_sensitivity");
			
			samp->operators[j].output_level=props.get_int_property(section,varbase+"output_level");
			samp->operators[j].osc_mode=props.get_int_property(section,varbase+"oscillator_mode");
			samp->operators[j].coarse_tune=props.get_int_property(section,varbase+"freq_coarse_tuning");
			samp->operators[j].fine_tune=props.get_int_property(section,varbase+"freq_fine_tuning");
		}
		
       		samp->pitch_envelope.rate[0]=props.get_int_property(section,"pitch_envelope_rate_1");
       		samp->pitch_envelope.rate[1]=props.get_int_property(section,"pitch_envelope_rate_2");
       		samp->pitch_envelope.rate[2]=props.get_int_property(section,"pitch_envelope_rate_3");
       		samp->pitch_envelope.rate[3]=props.get_int_property(section,"pitch_envelope_rate_4");
       		samp->pitch_envelope.level[0]=props.get_int_property(section,"pitch_envelope_level_1");
       		samp->pitch_envelope.level[1]=props.get_int_property(section,"pitch_envelope_level_2");
       		samp->pitch_envelope.level[2]=props.get_int_property(section,"pitch_envelope_level_3");
       		samp->pitch_envelope.level[3]=props.get_int_property(section,"pitch_envelope_level_4");
		
		samp->algorithm=props.get_int_property(section,"algorithm");
		samp->feedback_level=props.get_int_property(section,"feedback_level");
		samp->oscilator_key_sync=props.get_int_property(section,"oscilator_key_sync");
		
		samp->lfo.speed=props.get_int_property(section,"lfo_speed");
		samp->lfo.delay=props.get_int_property(section,"lfo_delay");
		samp->lfo.pitch_modulation_depth=props.get_int_property(section,"lfo_pitch_modulation_depth");
		samp->lfo.pitch_amplitude_depth=props.get_int_property(section,"lfo_pitch_amplitude_depth");
		samp->lfo.sync=props.get_int_property(section,"lfo_sync");
		samp->lfo.wave=props.get_int_property(section,"lfo_wave");
		
		samp->transpose=props.get_int_property(section,"transpose");;
		
		samp->name=props.get_str_property(section,"name");	
	}
	
	return data;
}

Open_Bank::Open_Bank(){
}
Open_Bank::~Open_Bank(){
}
