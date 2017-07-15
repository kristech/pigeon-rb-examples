/* 
 * File:    pigeonRB.c
 * 
 * Library for Pigeon computers
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
#include <stdint.h>
#include <wiringPi.h>
#include <stdbool.h>
#include "common.h"
#include "pigeonRB.h"
#include "pigeonSPI.h"

static const int optoinputs_vec[] = {IN1, IN2, IN3, IN4, IN5, IN6, IN7, IN8};
static const int dryinputs_vec[] = {IND1, IND2, IND3, IND4};
static const int outputs_vec[] = {OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8};
static model_t model = UNKNOWN;

/*
 *  Enable/disable all outputs
 *  en = true  - enable outputs
 *  en = false - disable outputs
 */
void enableOutputs(bool en)
{
	if (en)
	{
		digitalWrite(OUTE, 0);
	}
	else
	{
		digitalWrite(OUTE, 1);
	}
}

/*
 *  pigeonSetup function must be called at the start of program 
 *  mod = {RB100, RB100_CM3, RB300, RB300_CM3}
 */
void pigeonSetup(model_t mod)
{
	model = mod;
	
	if (wiringPiSetupGpio() != 0)
    {
        printExit("ERROR: wiringPi setup GPIO\n");
    }
	
	//binary outputs
	pinMode(OUTE, OUTPUT);
	pinMode(OUT1, OUTPUT);
	pinMode(OUT2, OUTPUT);
	pinMode(OUT3, OUTPUT);
	pinMode(OUT4, OUTPUT);
	pinMode(OUT5, OUTPUT);
	pinMode(OUT6, OUTPUT);
	pinMode(OUT7, OUTPUT);
	pinMode(OUT8, OUTPUT);
	//enable all outputs
	enableOutputs(true);
	
	//binary optoisolated inputs
	pinMode(IN1, INPUT);
	pinMode(IN2, INPUT);
	pinMode(IN3, INPUT);
	pinMode(IN4, INPUT);
	pinMode(IN5, INPUT);
	pinMode(IN6, INPUT);
	pinMode(IN7, INPUT);
	pinMode(IN8, INPUT);
	
	//dry contact inputs
	pinMode(IND1, INPUT);
	pinMode(IND2, INPUT);
	pinMode(IND3, INPUT);
	pinMode(IND4, INPUT);
	
	//watchdog
	pinMode(WATCHDOG_EN, OUTPUT);
	pinMode(WATCHDOG_IN, OUTPUT);

	//powercontrol
	pinMode(CTRL_3V3, OUTPUT);
	pinMode(CTRL_5V, OUTPUT);
	pinMode(FAULT_5V,INPUT);

	//LAN9514
	pinMode(LAN_RESET, OUTPUT);
	
	//LED
	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);
	
	switch (model)
	{
		case RB100:
		case RB100_CM3:
			break;
		
		case RB300:
		case RB300_CM3:
			spiOpen();
			break;
	
		default:		
			printExit("wrong model definition\n");
	}
}

/*
 *  pigeonClose function must be called at the end of program 
 */
void pigeonClose(void)
{
	switch (model)
	{
		case RB100:
		case RB100_CM3:
			break;
		
		case RB300:
		case RB300_CM3:
			spiClose();
			break;
	
		default:		
			printExit("wrong model definition\n");
	}
}

/*
 *  Read optoisolated input
 *  input_nr - number of input 1..8
 */
bool readOptoInput(uint8_t input_nr)
{
	return (bool)(1 - digitalRead(optoinputs_vec[input_nr-1])); 
}

/*
 *	Read dry contact input
 *  input_nr - number of input 1..4
 */
bool readDryInput(uint8_t input_nr)
{
	return (bool)digitalRead(dryinputs_vec[input_nr-1]); 
}

/*
 *  Read all binary inputs (optoisolated and dry contact)
 *  bi[8] - values of optoisolated inputs
 *  di[4] - values of dry contact inputs
 */
void readBinInputs(bool bi[8], bool di[4])
{
	int i;
	
	for (i=1; i<=8; i++)
	{
		bi[i-1] = readOptoInput(i);
	}		
	
	for (i=1; i<=4; i++)
	{
		di[i-1] = readDryInput(i);
	}
}


/*
 *  Write binary output
 *  input_nr - number of output
 *  value - value to write
 */
void writeBinOutput(uint8_t input_nr, bool value)
{
	digitalWrite(outputs_vec[input_nr-1], value);
}

/*
 *  Write all binary outputs
 *  values[8] - values to write
 */
void writeBinOutputs(bool values[8])
{
	int i;
	
	for (i=1; i<=8; i++)
	{
		writeBinOutput(i, values[i-1]);
	}
}

/*
 *  Turn off all binary outputs
 */
void turnOffAllBinOutputs(void)
{
	int i;
	
	enableOutputs(false);
	for (i=0; i<8; i++)
	{
		writeBinOutput(outputs_vec[i], false);
	}
	enableOutputs(true);
}
 
/*
 *  Read of analog inputs
 *  ai[4] - read values
 */
void readAnalogInputs(float ai[4])
{
	int i;
	uint16_t ai_ui[4];

	if ((model == RB300) || (model == RB300_CM3))
	{
		spiReadAI(ai_ui);
		for (i=0; i<4; i++)
		{
			ai[i] = ((float) ai_ui[i] * 10.065) / 1023.0;
		}
	}
}

/*
 *  Write analog outputs 
 *  ao[2] - write values 0 (0V) ... 1000 (10.00V)
 */
void writeAnalogOutputs(uint16_t ao[2])
{
	if ((model == RB300) || (model == RB300_CM3))
	{
		spiWriteAO(ao);
	}
}

/*
 *  read firmware version
 */
void readFirmwareVer(uint8_t firm[4])
{
	uint8_t i;
	
	if ((model == RB300) || (model == RB300_CM3))
	{
		spiReadFirmwareVer(firm);
	}
	else
	{
		for (i=0; i<4; i++)
			firm[i] = 0x00;
	}
}