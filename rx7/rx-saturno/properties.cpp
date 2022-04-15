/***************************************************************************
                          properties.cpp  -  description
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

#include "properties.h"

void Properties::add_section(string p_name) {

	Section new_section;

	if (section_exists(p_name)) return;

	section_list[p_name]=new_section;
}

void Properties::add_property(string p_section,string p_name,string p_value) {

	section_list[p_section].property_list[p_name].value=p_value;
}

void Properties::add_property(string p_section,string p_name,int p_value) {

	Property new_prop;
	char name[40];
	string svalue;

	if (property_exists(p_section,p_name)) return;

	sprintf(name,"%i",p_value);
	svalue=name;

	section_list[p_section].property_list[p_name].value=svalue;
}

int Properties::get_int_property(string p_section,string p_name) {

	if (!property_exists(p_section,p_name)) return 0;

	return atoi(section_list[p_section].property_list[p_name].value.c_str());
}

string Properties::get_str_property(string p_section,string p_name) {

	if (!property_exists(p_section,p_name)) return " ";

	return section_list[p_section].property_list[p_name].value;
}

bool Properties::section_exists(string p_name) {

	return section_list.find(p_name)!=section_list.end();
}

bool Properties::property_exists(string p_section,string p_name) {

	if (!section_exists(p_section)) return false;

	return section_list[p_section].property_list.find(p_name)!=section_list[p_section].property_list.end();
}

void Properties::set_header_check(string p_header_check) {

	header_check=p_header_check;
}

int Properties::save_to_file(string p_filename) {


	return 1;
}

int Properties::load_from_file(string p_filename) {

	return 0;
}


int Properties::save_to_text(string p_filename) {


}

void Properties::remove_trailing_space(string *p_string) {

	while ((p_string->length()>0) && ((*p_string)[0]==' ')) {
	
		*p_string=p_string->substr(1,p_string->length()-1);
	}

	while ((p_string->length()>0) && ((*p_string)[p_string->length()-1]==' ')) {
	
		*p_string=p_string->substr(0,p_string->length()-1);
	}
	
}

int Properties::load_from_text(string p_filename) {

	string section="";

	FILE *f;

/*
	tmp_check=reader.get_pascal_string();
	if (tmp_check!=header_check) {

		reader.close();
		return ERROR_INVALID_FILE;
	}
*/


	if ( !(f=fopen(p_filename.c_str(),"rb")) ) return -1;
	
	

	while(1) {

		string auxstring;
		char axloadzone[500];
		
		fscanf(f," %[^\n]",axloadzone);
		
		if (feof(f)) break;
		
		
		auxstring=axloadzone;

		
		
		auxstring=auxstring.substr(0,auxstring.find(";"));
		
		if (auxstring.length()==0) continue;
		
		remove_trailing_space(&auxstring);
		
		if (auxstring[0]=='[') {

			auxstring=auxstring.substr(1,auxstring.length()-2);

			section=auxstring;			
			add_section(section);			
		} else if (auxstring.find("=")<auxstring.length()) {
			
			string key,data;
		
			key=auxstring.substr(0,auxstring.find("=")-1);

			remove_trailing_space(&key);
			data=auxstring.substr(auxstring.find("=")+1,(auxstring.length()-auxstring.find("="))-1);

			remove_trailing_space(&data);

			add_property(section,key,data);
		}		
	}

	fclose(f);

	return 0;
}


Properties::Properties(){
}
Properties::~Properties(){
}
