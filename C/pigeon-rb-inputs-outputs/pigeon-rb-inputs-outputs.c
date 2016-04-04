/*
 * File:    pigeon-rb-inputs-outputs.c
 * Date:    25 March 2016
 *
 * Example for Pigeon RB100 and RB300 computers
 * Control outputs by inputs:
 * OUT5 = IN1,
 * OUT6 = IN1 OR IN2,
 * OUT7 = IN1 AND IN2,
 * OUT8 = IN1 XOR IN2.
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
    int in1, in2;
    int out5, out6, out7, out8;

    if (wiringPiSetupGpio() != 0)
    {
        printf("ERROR: wiringPiSetupGpio\n");
        return EXIT_FAILURE;
    }

    pinMode(IN1, INPUT);
    pinMode(OUTE, OUTPUT);
    pinMode(OUT5, OUTPUT);
    pinMode(OUT6, OUTPUT);
    pinMode(OUT7, OUTPUT);
    pinMode(OUT8, OUTPUT);

    digitalWrite(OUTE, 0);

    while (1)
    {
        in1 = 1-digitalRead(IN1);
        in2 = 1-digitalRead(IN2);

        out5 = in1;
        out6 = in1 | in2;
        out7 = in1 & in2;
        out8 = in1 ^ in2;

        digitalWrite(OUT5, out5);
        digitalWrite(OUT6, out6);
        digitalWrite(OUT7, out7);
        digitalWrite(OUT8, out8);
    }

    return (EXIT_SUCCESS);
}