/* 
 * File:    pigeon-rb-watchdog.c
 * Date:    25 March 2016   
 * 
 * Example for Pigeon RB100 and RB300 computers
 * Feed watchdog connected to GPIO
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
#include <stdbool.h>
#include  <signal.h>
#include <wiringPi.h>
#include "pigeon-rb.h"

volatile bool keepRunning = true;

void intHandler(int sig)
{
    keepRunning = false;
}

int main(int argc, char** argv)
{
    printf("GPIO watchdog is active \n\rPress Ctrl+C to stop\n");

    signal(SIGINT, intHandler);

    if (wiringPiSetupGpio() != 0)
    {
        printf("ERROR: wiringPiSetupGpio\n");
        return EXIT_FAILURE;
    }

    pinMode(OUTE, WATCHDOG_EN);
    pinMode(OUT1, WATCHDOG_IN);

    //GPIO watchdog enable
    digitalWrite(WATCHDOG_EN, 0);

    while (keepRunning)
    {
        //feed the watchdog
        digitalWrite(WATCHDOG_IN, 0);
        delay(200);

        digitalWrite(WATCHDOG_IN, 1);
        delay(200);
    }

    //GPIO watchdog disable
    digitalWrite(WATCHDOG_EN, 1);

    return (EXIT_SUCCESS);
}

