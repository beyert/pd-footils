/***************************************************************************
                          midi_event.h  -  description
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

#ifndef MIDI_EVENT_H
#define MIDI_EVENT_H


#include "dx7_voice.h"
#include "mixer.h"
#include <vector>
#include <hash_map>
/**
  *@author Juan Linietsky
  */

class Midi_Event {

public:
	Mixer *mixer;

	
	struct Bank {
	
		vector<Dx7_Voice::Data*> patch;

	};
	

		
	vector<Bank> bank;

private:	
		
	struct Channel {
	
		int patch;
		int bank;
		
		typedef hash_map<int,int> Voice_List;
	
		Voice_List voice_list;
		
		Channel() {
		
			patch=0;
			bank=0;
		};		
			
	};

	Channel channel[16];
	
public:

	void note_on(char p_chan,char p_note,char p_velocity);
	void note_off(char p_chan,char p_note,char p_velocity);
	void controller(char p_chan,char p_ctrl,char p_param);
	void program_change(char p_chan,char p_program);

	
		
	Midi_Event();
	~Midi_Event();
};

#endif
