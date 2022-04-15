/***************************************************************************
                          properties.h  -  description
                             -------------------
    begin                : Wed Sep 26 2001
    copyright            : (C) 2001 by Juan Sebastian Linietsky
    email                : reduz@anime.com.ar
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "typedefs.h"
#include <hash_map>
#include <stdio.h>


/**
  *@author Juan Sebastian Linietsky
  */

class Properties {

	enum Chunk_Type{

		CHUNK_SECTION,
		CHUNK_VARIABLE
	};

	struct string_hash {

		hash< char* > hasher;
		int operator() ( const string& S ) const { return hasher( S.c_str() ); };
	};

	struct Property {

		string value;
	};

	typedef hash_map<string,Property,string_hash> Property_List;

	struct Section {

		Property_List property_list;
	};

	typedef hash_map<string,Section,string_hash> Section_List;

	Section_List section_list;

	string header_check;

	void remove_trailing_space(string *p_string);
	
public:
	void set_header_check(string p_header_check);

	void add_section(string p_name);
	void add_property(string p_section,string p_name,string p_value);
	void add_property(string p_section,string p_name,int p_value);
	int get_int_property(string p_section,string p_name);
	string get_str_property(string p_section,string p_name);
	
	bool section_exists(string p_name);
	bool property_exists(string p_section,string p_name);

	int save_to_file(string p_filename);
	int load_from_file(string p_filename);

	int save_to_text(string p_filename);
	int load_from_text(string p_filename);

	Properties();
	~Properties();
};

#endif
