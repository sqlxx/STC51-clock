#ifndef __DS1302_H__
#define __DS1302_H__

#define DS1302_SEC_ADDR 0x80
#define DS1302_MIN_ADDR 0x82
#define DS1302_HOUR_ADDR 0x84
#define DS1302_DATE_ADDR 0x86
#define DS1302_MONTH_ADDR 0x88
#define DS1302_DAY_ADDR 0x8a
#define DS1302_YEAR_ADDR 0x8c
#define DS1302_CONTROL_ADDR 0x8e
#define DS1302_CHARGER_ADDR 0x90
#define DS1302_CLKBURST_ADDR 0xbe

byte ds1302_readByte();

void ds1302_writeByte(byte input);

byte ds1302_readData(byte addr);

void ds1302_writeData(byte addr, byte value);

byte ds1302_readSec();

byte ds1302_readMin();

byte ds1302_readHour();

void ds1302_writeSec(byte value);

void ds1302_writeMin(byte value);

void ds1302_writeHour(byte value);

void ds1302_init();

void ds1302_clearWP();

void ds1302_enableWP();

#endif 