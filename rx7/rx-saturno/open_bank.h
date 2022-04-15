/***************************************************************************
                          open_bank.h  -  description
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

#ifndef OPEN_BANK_H
#define OPEN_BANK_H
#include "dx7_voice.h"
#include "properties.h"


/**
  *@author Juan Linietsky
  */

class Open_Bank {
public:

	static vector<Dx7_Voice::Data> file(string p_filename);
	Open_Bank();
	~Open_Bank();
};

#endif
