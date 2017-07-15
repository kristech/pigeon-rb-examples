/* 
 * File:    example-rb300.c
 * 
 * Example for Pigeon RB300
 * 
 * Copyright (C) 2017 KRISTECH 
 * www.pigeoncomputers.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 * 
 * You should have received a copy of the GNU General Lesser Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0.html>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "pigeonRB.h"

int main(int argc, char** argv)
{
	int i;
	uint8_t out_val = 1;
	uint8_t out_nr = 1;
	bool bo_val[8] = {0,};  //binary outputs values
	bool bi_val[8] = {0,}; 	//optoisolated binary inputs values
	bool di_val[4] = {0,}; 	//dry contact inputs values
	float ai_val[4] = {0,}; //analog inputs values
	uint16_t ao_val[2]= {500, 1000};   //analog outputs values 5.00V, 10.00V
	uint8_t firm[4]; //firmware version
	const char* separator = "----------------------\n\r";

	pigeonSetup(RB300);
	readFirmwareVer(firm);	
	turnOffAllBinOutputs();
		
	//initial values of outputs
	writeBinOutputs(bo_val);
	writeAnalogOutputs(ao_val);
	
	//main loop
	while (1)
	{
		//read inputs
		readBinInputs(bi_val, di_val);
		readAnalogInputs(ai_val);

		//print inputs states
		printf("\033[H\033[J");  //clear terminal
		printf("\033[1;1H");	 //move cursor to (1,1)
		printf(separator);
		printf("Pigeon RB300\n\r");
		printf("Firm ver.: %.2X%.2X%.2X.%.2X\n\r", firm[3], firm[2], firm[1], firm[0]);	
		printf(separator);
		
		for (i=0; i<8; i++)
			printf("I%i  = %i\n\r", i+1, bi_val[i]);
		printf(separator);
		
		for (i=0; i<4; i++)
			printf("ID%i = %i\n\r", i+1, di_val[i]);
		printf(separator);
		
		for (i=0; i<4; i++)
			printf("AI%i = %5.2f V\n\r", i+1, ai_val[i]);
		printf(separator);

		//write outputs
		writeBinOutput(out_nr++, out_val);
		writeAnalogOutputs(ao_val);
		
		//calculate next values of outputs
		if (out_nr == 9)
		{
			out_nr = 1;
			out_val = 1- out_val;
		}
				
		ao_val[0] += 100; //add 1V
		if (ao_val[0] > 1000)
			ao_val[0]=0;
		
		ao_val[1] += 100; //add 1V
		if (ao_val[1] > 1000)
			ao_val[1]=0;		
			
		sleep(1);
	}
	
	pigeonClose();	
	
	return 0;	
}