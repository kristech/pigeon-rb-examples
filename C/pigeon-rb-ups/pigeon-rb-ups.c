/*
 * File:    pigeon-rb-ups.c
 * Date:    7 September 2016
 *
 *  Pigeon RB300 UPS support
 *
 * Copyright (C) 2016 KRISTECH Krzysztof Kajstura
 * www.pigeoncomputers.com
 *
 * Build:
 * gcc -o pigeon-rb-ups pigeon-rb-ups.c -lwiringPi -pthread
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
#include <sys/time.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <semaphore.h>

const int shutdown_pin = 27;
static sem_t staticSem;
int state;

//
// GPIO interrupt
//
void gpio_int(void) 
{
	usleep(100);  //minimal low state time is 100us		
	state = digitalRead(shutdown_pin);

	if (state == LOW) 
	{
		sem_post(&staticSem);
	}
}

//
//  main function
//
int main(void) 
{
	if (wiringPiSetupGpio() != 0)
    {
        printf("UPS service: wiringPiSetupGpio ERROR\n");
		fflush(stdout);
        return EXIT_FAILURE;
    }

	pinMode(shutdown_pin, INPUT);

	if (wiringPiISR(shutdown_pin, INT_EDGE_FALLING, &gpio_int))
    {
        printf("UPS service: wiringPiISR ERROR\n");
		fflush(stdout);
        return EXIT_FAILURE;
    }	

	state = digitalRead(shutdown_pin);
	
	if (state == LOW) 
	{
        printf("UPS service: shutdown signal active\n");
		fflush(stdout);
		system("shutdown -h now");
		return 0;
	}
	
	while (1) 
	{
		sem_wait( &staticSem );
		printf("UPS service: shutdown system\n");
		fflush(stdout);
		system("shutdown -h now");
		return 0;
	}
}
