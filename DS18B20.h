#ifndef __DS18B20_H__
#define __DS18B20_H__

void ds18b20_reset();

void ds18b20_writebit(bit a);

bit ds18b20_readbit();

void ds18b20_writebyte(byte input);

byte ds18b20_readbyte();

void ds18b20_checkTemp();

int ds18b20_readTemp();

void ds18b20_setLowResolution();

#endif