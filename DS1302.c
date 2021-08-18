/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include <reg52.h>
#include "common.h"
#include "DS1302.h"

sbit RST = P2^2;
sbit SCLK = P2^0;
sbit IO = P2^1; 


byte ds1302_readByte()
{
	byte value = 0;
	byte current;
	for (current = 0; current < 8; current ++)
	{
		value = value >> 1;
		if (IO)
		{
			value |= 0x80;
		}
		else 
		{
			value &= 0x7F;	
		}
		SCLK = 1;
		SCLK = 0;

	}

	return value;
}

void ds1302_writeByte(byte input)
{
	byte current;
	for (current = 0; current < 8; current ++) 
	{
		input = (input >> 1);
		IO = CY;
		SCLK = 1;
		SCLK = 0;
	}	
}
byte ds1302_readData(byte addr)
{
	
	byte value;
	
	addr = addr | 0x01;
	RST = 1;

	ds1302_writeByte(addr);

	value = ds1302_readByte();

	RST = 0;
	return value;
}
void ds1302_writeData(byte addr, byte value)
{
	RST = 1;
	
	addr = addr & 0xFE;

	ds1302_writeByte(addr);
	ds1302_writeByte(value);

	RST = 0;

}

byte ds1302_readMin()
{
	return ds1302_readData(DS1302_MIN_ADDR);
}
byte ds1302_readSec()
{
	return ds1302_readData(DS1302_SEC_ADDR);
}
byte ds1302_readHour()
{
	return ds1302_readData(DS1302_HOUR_ADDR);
}

void ds1302_writeHour(byte value)
{
	ds1302_writeData(DS1302_HOUR_ADDR, value);
}

void ds1302_writeSec(byte value)
{
	ds1302_writeData(DS1302_SEC_ADDR, value);
}
void ds1302_writeMin(byte value)
{
	ds1302_writeData(DS1302_MIN_ADDR, value);
}

void ds1302_clearWP()
{
	ds1302_writeData(DS1302_CONTROL_ADDR, 0x00);	
}

void ds1302_enableWP()
{
	ds1302_writeData(DS1302_CONTROL_ADDR, 0x80);		
}

void ds1302_init()
{
	RST = 0;
	SCLK = 0;
	
}
