/*
 * File:    pigeon-rb-inputs.c
 * Date:    25 March 2016
 *
 *  Example for Pigeon RB100 and RB300 computers
 *  Print digital inputs states
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

    pinMode(IN1, INPUT);
    pinMode(IN2, INPUT);
    pinMode(IN3, INPUT);
    pinMode(IN4, INPUT);
    pinMode(IN5, INPUT);
    pinMode(IN6, INPUT);
    pinMode(IN7, INPUT);
    pinMode(IN8, INPUT);

    pinMode(IND1, INPUT);
    pinMode(IND2, INPUT);
    pinMode(IND3, INPUT);
    pinMode(IND4, INPUT);

    printf("Opto-isolated inputs:\n\r");
    printf("I1 = %i\n\r", 1-digitalRead(IN1));
    printf("I2 = %i\n\r", 1-digitalRead(IN2));
    printf("I3 = %i\n\r", 1-digitalRead(IN3));
    printf("I4 = %i\n\r", 1-digitalRead(IN4));
    printf("I5 = %i\n\r", 1-digitalRead(IN5));
    printf("I6 = %i\n\r", 1-digitalRead(IN6));
    printf("I7 = %i\n\r", 1-digitalRead(IN7));
    printf("I8 = %i\n\r", 1-digitalRead(IN8));

    printf("Dry contact inputs:\n\r");
    printf("ID1 = %i\n\r", digitalRead(IND1));
    printf("ID2 = %i\n\r", digitalRead(IND2));
    printf("ID3 = %i\n\r", digitalRead(IND3));
    printf("ID4 = %i\n\r", digitalRead(IND4));

    return (EXIT_SUCCESS);
}