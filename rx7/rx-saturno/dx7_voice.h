/***************************************************************************
                          dx7_voice.h  -  description
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

#ifndef DX7_VOICE_H
#define DX7_VOICE_H

#include "typedefs.h"
#include "tables.h"

/**
  *@author Juan Linietsky
  */

class Dx7_Voice {
public:
	enum Status {
	
		DEAD,
		ATTACKING,
		RELEASING,
		FINISHED_ON_VOLUME
	};
		
       	struct Data {
	
		struct Envelope {
		
			char rate[4];
			char level[4];
				
		};
	
		struct Operator {
		
			Envelope envelope;		
				
			char kb_scale_bkpoint;
			char kb_scaling_l_depth;
			char kb_scaling_r_depth;
			char kb_scaling_l_curve;
			char kb_scaling_r_curve;
			
			char rate_scale;
			char detune;
			char amp_modulation_sens;
			char key_vel_sens;
			
			char output_level;
			char osc_mode;
			char coarse_tune;
			char fine_tune;
			
	
		} operators[6];
		
		
		Envelope pitch_envelope;
		
		
		char algorithm;
		char feedback_level;
		char oscilator_key_sync;
		
		struct LFO {
			
			char speed;
			char delay;
			char pitch_modulation_depth;
			char pitch_amplitude_depth;
			char sync;
			char wave;
		} lfo;
		
		char transpose;
		
        std::string name;
	};
	
	static int base_freq;

        Uint32 feedback_multiplier;
        float ffeedback_multiplier;
        Status status;
        char channel_in_use;
        char note_in_use;

        enum {


       		FRAC_SHIFT=18,
       		FRAC_LENGTH=(1<<FRAC_SHIFT),
       		FRAC_MASK=(FRAC_LENGTH-1),

       		ENV_LENGTH=100,
       		LEV_LENGTH=100,
       		
		SINE_BITS=12,
		SINE_LENGTH=(1<<SINE_BITS),
        	SINE_MASK=(SINE_LENGTH-1),
        	
        	MATRIX_FRAC_SHIFT=18,
        	MATRIX_FRAC_LENGTH=(1<<MATRIX_FRAC_SHIFT),
        	
        	
        	AMP_BITS=(SINE_BITS),
        	AMP_LENGTH=(1<<AMP_BITS),
        	AMP_MASK=(AMP_LENGTH-1),
        	
       		MODULATION_BITS=(FRAC_SHIFT-SINE_BITS),		        	
        	FRAC_TO_SINETABLE_SHIFT=(FRAC_SHIFT-SINE_BITS),

        	FDBK_MULT_BITS=4,
        	FDBK_MULT_LENGTH=(1<<FDBK_MULT_BITS),   	
       	
        };


        enum Ops {

		OP_1=0,
		OP_2,
		OP_3,
		OP_4,
		OP_5,
		OP_6,
		MAX_OPERATORS
        };

       	struct Eg { //envelope generator
		
       		enum Phase {
       		
       			ATTACK,
       			SUSTAIN,
       			RELEASE,
       			FINISHED
       		};
	
       		Uint16 rate[4];
       	        Uint16 level[4];
				
                int index;
       	        Sint8 current_node;
       	        Sint32 val;
       	        Sint32 climb_rate;
       	        Phase phase;

		void set_release_phase();
		void setup_next_node();
       	
       	        void set_climb_rate(Uint16 p_rate,Uint16 p_level_l,Uint16 p_level_r);
       	        void reset();
       	
       	        inline void process() {
       	        	
       	        	if ((phase==SUSTAIN) || (phase==FINISHED)) return;

       	        	
			val+=climb_rate;
		
			//if (phase==RELEASE) printf("I GOT RILISD - %i, %i!\n",val,climb_rate);
			
			if (climb_rate>0) {
	
				if ((val>>FRAC_SHIFT)>level[current_node]) setup_next_node();
				
			} else {
	
				if ((val>>FRAC_SHIFT)<level[current_node]) setup_next_node();	
			}
       	        }
       	
       	        inline Uint16 get_val() {

			return val>>FRAC_SHIFT;
		}

                Eg();
       	};


	struct Op {

       	        Uint8 index;	
		
		Eg eg;

		Data::Envelope eg_base;
		
	        Uint32 velocity;
	        Uint32 velocity_sens;
	       	Uint32 phase_count;
		Uint32 phase_increment;
		Uint32 eg_level;
		Uint16 coarse;
		Uint32 fine;
		Uint32 freq;
		Uint8 detune;
		
		Sint32 *in,*out; // where to take the input from, where to put the output
      		
      		Sint32 zero;
      		Sint32 selfout;

                Uint8 output_level;

		inline void increment() {
		
			phase_count+=phase_increment;
			eg.process();
		}
		
		
		void set_velocity(Uint8 p_velocity);		
		void set_velocity_sens(Uint8 p_velocity);		
		void set_coarse(Uint8 p_coarse);
		void set_fine(Uint8 p_detune);
		void set_detune(Uint8 p_detune);
		void set_freq(Uint32 p_freq);
		void recalculate_increment();
		void set_output_level(Uint8 p_level);
		void prepare_envelope();
		void reset();
	
		
		Op();

	} op[MAX_OPERATORS];
	
	inline void calculate_op(Op& p_op) {
	
		Sint64 mult;
		
		mult = sin_table[((p_op.phase_count>>FRAC_TO_SINETABLE_SHIFT) + (*p_op.in)) & SINE_MASK];
	
		mult*=eg_amp_table[p_op.eg.get_val()];
		
		mult>>=MATRIX_FRAC_SHIFT;	
		
		p_op.selfout=mult;
		
		*p_op.out+=mult;
	}

        struct Joints {

		Sint32 zero; //take zero from here
		Sint32 feedback; //take feedback from here
		Sint32 *feedback_ptr; //point where feedback goes
		Sint32 inter[MAX_OPERATORS]; //interoperator joints
                Sint32 out;
                Sint32 out_feedback;

        } joint;


        void connect_op(int p_op_from,int p_op_to,int p_cn_through);
        void set_algorithm(int p_algo);
        void init_tables();
        void set_carrier(int p_op);
        void set_feedback(int p_op_from,int p_op_to);

	static Sint32 eg_amp_table[ENV_LENGTH];
	static Sint32 sin_table[SINE_LENGTH];

	
	static bool tables_created;
	
public:	
	

	Status get_status();
	
	void poll_for_dead_staus();	
	

        void set_note(char p_note,char p_velocity);
	void set_note_off(char p_velocity);
        void set_data(Data *p_data);
	void calculate();
	
	void set_channel(char p_chan); //check purposes only
	char get_note(); //check purposes only
 	char get_channel(); //check purposes only
	
 	void kill();
 	
	Sint32 get_output() {

		return joint.out >> 3;
	}
	

	Dx7_Voice();
	~Dx7_Voice();
};

#endif
