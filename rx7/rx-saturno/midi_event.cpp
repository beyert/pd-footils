/***************************************************************************
                          midi_event.cpp  -  description
                             -------------------
    begin                : Mon Feb 4 2002
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

#include "midi_event.h"


void Midi_Event::note_on(char p_chan,char p_note,char p_velocity) {

	Channel::Voice_List::iterator I;
        int chan;
	
        I=channel[p_chan].voice_list.find(p_note);


	if (I!=channel[p_chan].voice_list.end()) {
	
	        if ( (mixer->voice[I->second].get_channel()!=p_chan) || (mixer->voice[I->second].get_note()!=p_note)) {
	
			chan=mixer->find_aviable_voice();
			channel[p_chan].voice_list[p_note]=chan;	
	
	        } else {
	
			chan=I->second;
	        		
	        }
		
	} else {

		chan=mixer->find_aviable_voice();
		channel[p_chan].voice_list[p_note]=chan;	

	}
	

	mixer->voice[chan].set_data(bank[ channel[p_chan].bank ].patch[ channel[p_chan].patch ] );
	mixer->voice[chan].set_note(p_note,p_velocity);
	mixer->voice[chan].set_channel(p_chan);

		
}

void Midi_Event::note_off(char p_chan,char p_note,char p_velocity) {

	Channel::Voice_List::iterator I;
        int chan;
	
        I=channel[p_chan].voice_list.find(p_note);

	
	if (I==channel[p_chan].voice_list.end()) {

		printf("I dun have this voice sanca\n");
		//we done have this note	
		return;	
	}
	
	chan=I->second;


	mixer->voice[chan].set_note_off(p_velocity);

}


void Midi_Event::controller(char p_chan,char p_ctrl,char p_param) {



}


void Midi_Event::program_change(char p_chan,char p_program) {

	Channel::Voice_List::iterator I;

	



	for (I=channel[p_chan].voice_list.begin();I!=channel[p_chan].voice_list.end();I++) {

		
		mixer->voice[I->second].kill();
        }

        channel[p_chan].patch=p_program;
}


Midi_Event::Midi_Event(){

	bank.resize(1);
}
Midi_Event::~Midi_Event(){
}
