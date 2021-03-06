/* 
 * File:    pigeon-rb-led.c
 * Date:    25 March 2016   
 * 
 * Example for Pigeon RB100 and RB300 computers
 * Blinking LED1
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

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "pigeon-rb.h"

int main(int argc, char** argv)
{
    if (wiringPiSetupGpio() != 0)
    {
        printf("ERROR: wiringPiSetupGpio\n");
        return EXIT_FAILURE;
    }    
    
    pinMode(LED1, OUTPUT);

    while (1)
    {
        digitalWrite(LED1, 0);
        delay(500);
        digitalWrite(LED1, 1);
        delay(500);
    }

    return (EXIT_SUCCESS);
}