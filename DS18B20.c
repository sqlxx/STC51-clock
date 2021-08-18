/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include <reg52.h>
#include <intrins.h>
#include "common.h"
#include "DS18B20.h"

sbit TEMP_SENSOR = P2^3;

void ds18b20_reset()
{
	//byte presence = 0;
	TEMP_SENSOR = 0;
	delayUs2x(255);
	TEMP_SENSOR = 1;
	//Don't care about the presence pluse
	//delayUs2x(15);
	//presence = TEMP_SENSOR;
	
	delayUs2x(250);

}

void ds18b20_writebit(bit a)
{
	TEMP_SENSOR = 0;
	//delayUs2x(1);
	if (a) //write 1
	{
		TEMP_SENSOR = 1;
	}
	else  //write 0
	{
		TEMP_SENSOR = 0;
	}

	delayUs2x(30);
	TEMP_SENSOR = 1;
}

bit ds18b20_readbit()
{
	bit output = 0;
	TEMP_SENSOR = 0;
	_nop_();
	TEMP_SENSOR = 1;
    delayUs2x(3);
	output = TEMP_SENSOR;
	delayUs2x(25);
	TEMP_SENSOR = 1;
	
	return output;
}

void ds18b20_writebyte(byte input)
{
	bit current = 0;
	int i = 0;
	for (i = 0; i < 8; i ++) 
	{
		current = 0x01 & input;
		ds18b20_writebit(current);
		input >>= 1;
	}
	
}

byte ds18b20_readbyte()
{
	byte output = 0;
	bit currentbit = 0;
	int i = 0;
	byte temp = 0;
	for (i = 0; i < 8; i ++)
	{
		currentbit = ds18b20_readbit();
		output >>= 1;
		if (currentbit)
		{
			output |= 0x80;
		}

	}

	return output;
}

void ds18b20_checkTemp()
{
	ds18b20_reset();
	ds18b20_writebyte(0xCC);
	ds18b20_writebyte(0x44);
}


int ds18b20_readTemp()
{
	int temp;
	byte lsb;
	byte msb;

 	ds18b20_reset();
	ds18b20_writebyte(0xCC); //skip rom
	ds18b20_writebyte(0xBE); //read rom

	lsb = ds18b20_readbyte();
	msb = ds18b20_readbyte();
	temp = (msb<<8 | lsb );

	return temp;
}

void ds18b20_setLowResolution()
{

	ds18b20_reset();
	ds18b20_writebyte(0xCC); //skip rom
	ds18b20_writebyte(0x4E); //写寄存器
	ds18b20_writebyte(0x00);
	ds18b20_writebyte(0xFF);
	ds18b20_writebyte(0x1F);			  //设置精度为0.5
}
