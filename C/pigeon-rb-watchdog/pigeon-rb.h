/* 
 * File:    pigeon-rb.h
 * Date:    25 March 2016   
 * 
 * GPIO library for Pigeon RB100 and RB300 
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

#ifndef PIGOEN_RB_H
#define PIGOEN_RB_H

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

#endif /* PIGOEN_RB_H */

