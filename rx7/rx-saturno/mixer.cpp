/***************************************************************************
                          mixer.cpp  -  description
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

#include "mixer.h"
#include "math.h"

int Mixer::write_bytes(void *p_buf,int bytes) {

	Uint16 *buff16=((Uint16*)p_buf);
	int thing=0;
	int amount=bytes;///2;
	int i=0;
	float sum=0;
	//printf("mixfreq is %i,16bits is %s n",mixfreq,(mix16?"true":"false"));
	
	for(i=0;i<voice_count;i++) voice[i].poll_for_dead_staus();
	
	while (amount) {

	        thing=0;
	
		for (i=0;i<voice_count;i++) {
		 	
		 	voice[i].calculate();
		 	thing+=voice[i].get_output();

		}


		*buff16=thing;
		buff16++;
		amount-=2;		
	}
	
	return bytes;//bytes-amount;
}		
		
int Mixer::find_aviable_voice() {

        int i;

	for(i=0;i<voice_count;i++) if (voice[i].get_status()==Dx7_Voice::DEAD) return i;


	return 0;
}

Mixer::Mixer(){
}
Mixer::~Mixer(){
}
