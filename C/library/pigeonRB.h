/* 
 * File:    pigeonRB.h
 * 
 * Library for Pigeon computers 
 * 
 * Copyright (C) 2016 KRISTECH Krzysztof Kajstura 
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

#ifndef PIGOENRB_H
#define PIGOENRB_H

/*
 *  GPIO symbols
 */
enum {
    //Digital opto-isolated inputs
    IN1 = 12,
    IN2 = 13,
    IN3 = 18,
    IN4 = 19,
    IN5 = 20,
    IN6 = 21,
    IN7 = 22,
    IN8 = 23,

    //Dry contact inputs
    IND1 = 30,
    IND2 = 31,
    IND3 = 32,
    IND4 = 33,

    //Digital outputs
    OUTE = 34,
    OUT1 = 35,
    OUT2 = 36,
    OUT3 = 37,
    OUT4 = 38,
    OUT5 = 39,
    OUT6 = 40,
    OUT7 = 41,
    OUT8 = 42,

    //LEDs    
    LED0 = 45,
    LED1 = 47,

    //WATCHDOG
    WATCHDOG_EN = 5,
    WATCHDOG_IN = 44,

    //Powercontrol
    CTRL_3V3 = 28,
    CTRL_5V = 29,
    FAULT_5V = 43,
           
    //LAN9514
    LAN_RESET = 6        
};

/*
 *  Pigeon model type
 */
typedef enum
{
	UNKNOWN,
	RB100,
	RB100_CM3,
	RB300,
	RB300_CM3
} model_t;

/*
 *  Functions
 */
extern void pigeonSetup(model_t mod);
extern void pigeonClose(void);
extern bool readOptoInput(uint8_t input_nr);
extern bool readDryInput(uint8_t input_nr);
extern void readBinInputs(bool bi[8], bool di[4]);
extern void writeBinOutput(uint8_t input_nr, bool value);
extern void writeBinOutputs(bool values[8]);
extern void turnOffAllBinOutputs(void);
extern void readAnalogInputs(float ai[4]);
extern void writeAnalogOutputs(uint16_t ao[2]);
extern void readFirmwareVer(uint8_t firm[4]);

#endif /* PIGOENRB_H */

