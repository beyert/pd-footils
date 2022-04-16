/***************************************************************************
                          dxt_voice_algorithm.cpp  -  description
                             -------------------
    begin                : Thu Jan 31 2002
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
#include "dx7_voice.h"

void Dx7_Voice::connect_op(int p_op_from,int p_op_to,int p_cn_through) {

	op[p_op_from].out=&joint.inter[p_cn_through];
	op[p_op_to].in=&joint.inter[p_cn_through];
	
}

void Dx7_Voice::set_carrier(int p_op) {

	op[p_op].out=&joint.out;
//	op[p_op].translation_table=Dx7_Tables::carrier_modifier;

}

void Dx7_Voice::set_feedback(int p_op_from,int p_op_to) {


	op[p_op_to].in=&joint.feedback;
	joint.feedback_ptr=&op[p_op_from].selfout;

}

void Dx7_Voice::set_algorithm(int p_algo) {

	p_algo++;
	for (int i=0;i<6;i++) {
	
		op[i].reset();
		joint.out_feedback=0;
		joint.feedback=0;
			
	}
        printf("got algorithm %i\n",p_algo);
	set_carrier(OP_1); // operator 1 is almost allways carrier
	
	joint.feedback_ptr=&joint.inter[5]; //dont bother me

			
	switch(p_algo) {


	
	case 1: {

			
		
		connect_op(OP_2,OP_1,0);		
		
		set_carrier(OP_3);
		
		connect_op(OP_4,OP_3,1);
		connect_op(OP_5,OP_4,2);
		connect_op(OP_6,OP_5,3);
	
		set_feedback(OP_6,OP_6);		

	
	} break;
	
	case 2: {

			
		
		connect_op(OP_2,OP_1,0);		
		
		set_carrier(OP_3);
		
		connect_op(OP_4,OP_3,1);
		connect_op(OP_5,OP_4,2);
		connect_op(OP_6,OP_5,3);
		
		set_feedback(OP_2,OP_2);		
		
	} break;
	case 3: {

			
		
		connect_op(OP_2,OP_1,0);		
		connect_op(OP_3,OP_2,1);		
		
		set_carrier(OP_4);		
		
		connect_op(OP_5,OP_4,3);
		connect_op(OP_6,OP_5,4);
		
		
	        set_feedback(OP_6,OP_6);
		
	} break;
	case 4: {

			
		
		connect_op(OP_2,OP_1,0);		
		connect_op(OP_3,OP_2,1);		
		
		set_carrier(OP_4);				
		
		connect_op(OP_5,OP_4,2);
		connect_op(OP_6,OP_5,3);
		
	        set_feedback(OP_4,OP_6);	
		
	} break;
	case 5: {

			
		connect_op(OP_2,OP_1,0);		
		
		set_carrier(OP_3);
							
		connect_op(OP_4,OP_3,1);
		set_carrier(OP_5);								
		
		connect_op(OP_6,OP_5,2);		
		
	        set_feedback(OP_6,OP_6);			
		
	
	} break;
	case 6: {

			
		connect_op(OP_2,OP_1,0);		
		set_carrier(OP_3);										
		connect_op(OP_4,OP_3,1);		

		set_carrier(OP_5);		
		connect_op(OP_6,OP_5,2);		
		
		set_feedback(OP_5,OP_6);
		
		
	} break;
	case 7: {

			
		connect_op(OP_2,OP_1,0);		
		set_carrier(OP_3);
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_3,1);		

		connect_op(OP_6,OP_5,2);		
		
		set_feedback(OP_6,OP_6);
		
	} break;
	case 8: {

			
		connect_op(OP_2,OP_1,0);		
		set_carrier(OP_3);		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_3,1);		

		connect_op(OP_6,OP_5,2);		
		
		set_feedback(OP_4,OP_4);	
		
	} break;
	case 9: {

		set_carrier(OP_2);
		set_carrier(OP_4);
		set_carrier(OP_5);
		connect_op(OP_6,OP_5,0);		
		
		set_feedback(OP_2,OP_2);			
	
		
	} break;
	case 10: {
	
		set_carrier(OP_2);
		set_carrier(OP_6);
		set_carrier(OP_5);
		
		connect_op(OP_3,OP_2,0);		
		
		set_feedback(OP_3,OP_3);					
	
	
	} break;
	case 11: {

		set_carrier(OP_2);
		set_carrier(OP_6);
		set_carrier(OP_5);
		
		connect_op(OP_3,OP_2,0);		
		
		set_feedback(OP_6,OP_6);							
		
	} break;
	case 12: {

		
		connect_op(OP_2,OP_1,0);				
		
		set_carrier(OP_3);		
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_3,1);		
		connect_op(OP_6,OP_3,1);		

		set_feedback(OP_2,OP_2);							
	
	
	} break;
	case 13: {

		
		connect_op(OP_2,OP_1,0);				
		
		set_carrier(OP_3);				
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_3,1);		
		connect_op(OP_6,OP_3,1);		
		
		set_feedback(OP_6,OP_6);									
	
		
	} break;
	case 14: {
	
		
		connect_op(OP_2,OP_1,0);				
		
		set_carrier(OP_3);						
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_4,2);		
		connect_op(OP_6,OP_4,2);		
		
		set_feedback(OP_6,OP_6);										
	
	} break;
	case 15: {

	
		
		connect_op(OP_2,OP_1,0);				
		
		set_carrier(OP_3);								
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_4,2);		
		connect_op(OP_6,OP_4,2);		
		

		set_feedback(OP_2,OP_2);
		
	} break;
	case 16: {

		
		connect_op(OP_2,OP_1,0);				
		connect_op(OP_3,OP_1,0);				
		connect_op(OP_5,OP_1,0);				
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_6,OP_5,2);		
		
		set_feedback(OP_6,OP_6);										
		
	
	} break;
	case 17: {
	
		
		connect_op(OP_2,OP_1,0);				
		connect_op(OP_3,OP_1,0);				
		connect_op(OP_5,OP_1,0);				
		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_6,OP_5,2);		
		
       		set_feedback(OP_2,OP_2);
	
	} break;
	case 18: {

		connect_op(OP_2,OP_1,0);				
		connect_op(OP_3,OP_1,0);				
		connect_op(OP_4,OP_1,0);				
		
		connect_op(OP_5,OP_4,1);		
		connect_op(OP_6,OP_5,2);		
		
       		set_feedback(OP_3,OP_3);
		
	} break;
	case 19: {

		connect_op(OP_2,OP_1,0);				
		connect_op(OP_3,OP_2,1);				
		
		
		set_carrier(OP_4);										
		
		connect_op(OP_5,OP_4,2);				
		connect_op(OP_6,OP_5,3);		
		
       		set_feedback(OP_6,OP_6);
		
	} break;
	case 20: {
	
		connect_op(OP_3,OP_1,0);				
		connect_op(OP_3,OP_2,0);				

		set_carrier(OP_2);										
		set_carrier(OP_3);												
		
		connect_op(OP_5,OP_4,1);				
		connect_op(OP_6,OP_4,1);		
		
		set_feedback(OP_3,OP_3);

	
	} break;
	case 21: {

		connect_op(OP_3,OP_1,0);				
		connect_op(OP_3,OP_2,0);				

		set_carrier(OP_2);										
		set_carrier(OP_4);		
		set_carrier(OP_5);										


		
		connect_op(OP_6,OP_4,1);				
		connect_op(OP_6,OP_5,1);		
		
		set_feedback(OP_3,OP_3);		
		
	} break;
	case 22: {

		connect_op(OP_2,OP_1,0);				
		
		set_carrier(OP_3);										
		set_carrier(OP_4);		
		set_carrier(OP_5);										
		
		connect_op(OP_6,OP_3,1);						
		connect_op(OP_6,OP_4,1);				
		connect_op(OP_6,OP_5,1);		
		

		set_feedback(OP_6,OP_6);				
		
	} break;
	case 23: {
	
		connect_op(OP_3,OP_2,0);				

		set_carrier(OP_2);										
		set_carrier(OP_4);		
		set_carrier(OP_5);										
		
		
		connect_op(OP_6,OP_4,1);				
		connect_op(OP_6,OP_5,1);		
		
		set_feedback(OP_6,OP_6);				
	
	
	} break;
	case 24: {
	

		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_4);
		set_carrier(OP_5);
		
		
		connect_op(OP_6,OP_3,1);						
		connect_op(OP_6,OP_4,1);				
		connect_op(OP_6,OP_5,1);		
		
		set_feedback(OP_6,OP_6);				

	
	
	} break;
	case 25: {
	
		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_4);
		set_carrier(OP_5);
		

		connect_op(OP_6,OP_4,1);				
		connect_op(OP_6,OP_5,1);		
		
		set_feedback(OP_6,OP_6);						
	
	
	} break;
	case 26: {
	
	

		connect_op(OP_3,OP_2,0);				

		set_carrier(OP_2);
		set_carrier(OP_4);
		
		connect_op(OP_5,OP_4,1);				
		connect_op(OP_6,OP_4,1);		
		
		set_feedback(OP_6,OP_6);						
	
	
	} break;
	case 27: {

		connect_op(OP_3,OP_2,0);				

		set_carrier(OP_2);
		set_carrier(OP_4);
		
		connect_op(OP_5,OP_4,1);				
		connect_op(OP_6,OP_4,1);		
		
		set_feedback(OP_6,OP_6);						
		
	
	} break;
	case 28: {
	
		connect_op(OP_2,OP_1,0);		
		
		set_carrier(OP_3);

		
		connect_op(OP_4,OP_3,1);		
		connect_op(OP_5,OP_4,2);		
		
		set_carrier(OP_6);
		
		

		set_feedback(OP_5,OP_5);						
		
	
	} break;
	case 29: {
	

		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_5);
		
		connect_op(OP_4,OP_3,0);		
		connect_op(OP_6,OP_5,1);		
		

		set_feedback(OP_6,OP_6);						
	
	} break;
	case 30: {
	
		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_6);
		
		connect_op(OP_4,OP_3,0);		
		connect_op(OP_5,OP_4,1);		
		



		set_feedback(OP_5,OP_5);						
	
	} break;
	case 31: {
	
		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_4);
		set_carrier(OP_5);
		
		connect_op(OP_6,OP_5,0);		

		set_feedback(OP_6,OP_6);						
	
	
	} break;

	case 32: {
	
		set_carrier(OP_1);	
		set_carrier(OP_2);
		set_carrier(OP_3);
		set_carrier(OP_4);
		set_carrier(OP_5);
		
		set_feedback(OP_6,OP_6);						
	
	
	} break;

    }

}

