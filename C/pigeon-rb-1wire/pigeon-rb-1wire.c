/*
 * File:    pigeon-rb-1wire.c
 * Date:    25 March 2016
 *
 *  Example for Pigeon RB100 and RB300 computers
 *  DS18B20 read temperature
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
#include <owcapi.h>


int main(int argc, char** argv)
{
    char *buf;
    size_t s;
    const char id_temp[] = "28.D3E93C020000/temperature";
    
    OW_init("/dev/i2c-1");
    OW_set_error_print("2");
    OW_set_error_level("6");
    OW_get(id_temp, &buf, &s);
    printf("Temperature: %s", buf);
    free(buf);
    OW_finish();

    return (EXIT_SUCCESS);
}
