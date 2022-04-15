/***************************************************************************
                          mixer.h  -  description
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

#ifndef MIXER_H
#define MIXER_H
#include "dx7_voice.h"

/**
  *@author Juan Linietsky
  */



class Mixer {

	int mixfreq;
	bool mix16;
	bool mixstereo;


public:
		
	Dx7_Voice voice[64];
	int voice_count;


	void set_mix_frequency(int p_freq) {mixfreq=p_freq;}
	void set_mix_stereo(bool p_stereo) {mixstereo=p_stereo;}
	void set_mix_16bits(bool p_16bits) {mix16=p_16bits;}
	
	int write_bytes(void *p_buf,int bytes);
	
	int find_aviable_voice();
	
	Mixer();
	~Mixer();
};

#endif
