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

      std::hash< std::string > hasher;
      int operator() ( const std::string& S ) const { return hasher( S.c_str() ); };
	};

	struct Property {

      std::string value;
	};

	typedef __gnu_cxx::hash_map<std::string,Property,string_hash> Property_List;

	struct Section {

		Property_List property_list;
	};

	typedef __gnu_cxx::hash_map<std::string,Section,string_hash> Section_List;

	Section_List section_list;

    std::string header_check;

	void remove_trailing_space(std::string *p_string);
	
public:
	void set_header_check(std::string p_header_check);

	void add_section(std::string p_name);
	void add_property(std::string p_section,std::string p_name,std::string p_value);
	void add_property(std::string p_section,std::string p_name,int p_value);
	int get_int_property(std::string p_section,std::string p_name);
    std::string get_str_property(std::string p_section,std::string p_name);
	
	bool section_exists(std::string p_name);
	bool property_exists(std::string p_section,std::string p_name);

	int save_to_file(std::string p_filename);
	int load_from_file(std::string p_filename);

	int save_to_text(std::string p_filename);
	int load_from_text(std::string p_filename);

	Properties();
	~Properties();
};

#endif
