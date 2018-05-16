/* 
 * File:    pigeonSPI.c
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

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include <unistd.h>
#include "common.c"
#include "pigeonSPI.h"

static int fd = 0;

/*
 *  SPI open and configure
 */
void spiOpen(void)
{
	const uint8_t bits = 8;
	const uint32_t speed = 2000000; 
	const char *device = "/dev/spidev0.1";
	const uint8_t mode = SPI_CPHA;
	uint8_t rmode;
	uint8_t rbits;
	uint32_t rspeed;
	int ret = 0;

	fd = open(device, O_RDWR);
	if (fd < 0)
		printExit("SPI: can't open device\n\r");

	//mode
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		printExit("SPI: can't set spi mode\n\r");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &rmode);
	if (ret == -1)
		printExit("SPI: can't get spi mode\n\r");

	if ((rmode) != mode)
		printExit("SPI: set spi mode error\n\r");

	// bits per word
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		printExit("SPI: can't set bits per word\n\r");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &rbits);
	if (ret == -1)
		printExit("SPI: can't get bits per word\n\r");

	if (rbits != bits)
		printExit("SPI: set spi bits error\n\r");

	//speed
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		printExit("SPI: can't set max speed hz\n\r");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &rspeed);
	if (ret == -1)
		printExit("SPI: can't get max speed hz\n\r");

	if (rspeed != speed)
		printExit("SPI: set spi speed error\n\r");
}

/*
 * SPI close
 */
void spiClose(void)
{
	close(fd);
}

/*
 *  SPI transfer
 */
static void spiTransfer(uint8_t *tx, uint8_t *rx, uint8_t length)
{
	int ret;

	struct spi_ioc_transfer tr;

	memset(&tr, 0, sizeof (tr));
	tr.tx_buf = (unsigned long) tx;
	tr.rx_buf = (unsigned long) rx;
	tr.len = length;
	tr.delay_usecs = 0;

	if (length > 8)
		printExit("SPI transfer: length is too high");

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		printExit("SPI transfer: can't send spi message");
}

/*
 *  Write analog outputs
 */
void spiWriteAO(uint16_t ao[2])
{
	uint8_t tx[5];
	uint8_t rx[5];

	tx[0] = 0x4F;
	tx[1] = ao[0] % 256;
	tx[2] = ao[0] / 256;
	tx[3] = ao[1] % 256;
	tx[4] = ao[1] / 256;

	spiTransfer(tx, rx, 5);
}

/*
 *  Read analog inputs
 */
void spiReadAI(uint16_t ai[4])
{
	uint8_t tx[8];
	uint8_t rx[8];
	uint8_t i;

	tx[0] = 0x41;
	spiTransfer(tx, rx, 1);
	
	usleep(100);
	
	for (i = 0; i < 8; i++)
		tx[i] = 0xFF;
	
	spiTransfer(tx, rx, 8);

	for (i = 0; i < 4; i++)
	{
		ai[i] = rx[2 * i] | (rx[2 * i + 1] << 8);
	}
}

/*
 *  Read configuration registers
 */
void spiReadRegs(uint8_t reg[8])
{
	uint8_t tx[8];
	uint8_t rx[8];
	uint8_t i;

	tx[0] = 0x52;
	spiTransfer(tx, rx, 1);
	
	usleep(100);
	
	for (i = 0; i < 8; i++)
		tx[i] = 0xFF;
	
	spiTransfer(tx, rx, 8);
	
	for (i = 0; i < 8; i++)
		reg[i] = rx[i];	
}

/*
 *  Write configuration registers
 */
void spiWriteRegs(uint8_t reg[8])
{
	uint8_t tx[8];
	uint8_t rx[8];
	uint8_t i;

	tx[0] = 0x43;
	spiTransfer(tx, rx, 1);
	
	for (i = 0; i < 8; i++)
		tx[i] = reg[i];
	
	spiTransfer(tx, rx, 8);
}

/*
 *  Read firmware version
 */
void spiReadFirmwareVer(uint8_t firm[4])
{
	uint8_t tx[8];
	uint8_t rx[8];
	uint8_t i;

	tx[0] = 0x46;
	spiTransfer(tx, rx, 1);
	
	usleep(100);
	
	for (i = 0; i < 8; i++)
		tx[i] = 0xFF;

	spiTransfer(tx, rx, 8);
	
	for (i = 0; i < 4; i++)
	firm[i] = rx[i];	
}