/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include <reg52.h>
#include "common.h"
#include "digital.h"
#include "DS1302.h"
#include "DS18B20.h"
#include "simpleKeyBoard.h"

#define LED_REFRESH_TASK_INT 3
#define READ_TIME_INT 500
#define READ_TEMP_INT 2000
#define KEY_SCAN_INT 50

#define STATE_TEMP  0
#define STATE_CLOCK	1
#define STATE_SETUP 2


//sbit SENSOR = P2^3;

int tasks[]= {READ_TIME_INT, LED_REFRESH_TASK_INT, READ_TEMP_INT, KEY_SCAN_INT};

byte status;
char currentDigital = -1; //用于调整时钟的时候表示当前调整的位数

void initTimer()
{
	 TMOD |= 0x00; //采用模式0
	 TH0 = (8192 - 1000)/32;
	 TL0 = (8192 - 1000)%32;
	 EA = 1;
	 ET0 = 1; //开计时器0中断允许
	 TR0 = 1; //启动计时器0
}

void readDS1302(){
	static byte count = 0;
	byte min;
	byte hour;

	if (status == STATE_CLOCK) {
		led_flashDp();
		
		min = ds1302_readMin();
		led_buffer[2] = min/16;
		led_buffer[3] = min%16;
		hour = ds1302_readHour();
		
		led_buffer[0] = hour/16;
		led_buffer[1] = hour%16;
		count ++;
		if (count >= 20) {
			count = 0;
			status = STATE_TEMP;
		}
	}	
}
void readDS18B20() {
	static byte count = 0;
	static byte countCT = 0;	
	int temp;
	byte tempStr;
	if (status == STATE_TEMP) {
		EA = 0;
		temp = ds18b20_readTemp();
		EA = 1;
		tempStr = temp >> 4;
		led_noDp();
		led_buffer[2] = DIGI_C;
		led_buffer[3] = DIGI_NULL;
		//tempStr = temp&0x00FF;
		led_buffer[0] = (tempStr)/10%10;
		led_buffer[1] = tempStr%10;
		count ++;
		if (count >= 4) {
			count = 0;
			status = STATE_CLOCK;
		}

	} else {
		countCT++;
		if (countCT >= 4) {
			ds18b20_checkTemp();
			countCT = 0;
		}	
	} 
}
void refreshLed() {
	
	led_display();

}

void readKeyboard() {
	byte keyCode;
	char newNumber;

	keyCode = keySacn();

	switch(keyCode) {
		case KEY_MODE_PRESSED:
			if (status != STATE_SETUP) {
				status = STATE_CLOCK; //in case current led buffer is displaying temperature.
				readDS1302();
				status = STATE_SETUP;
				currentDigital = HOUR_SEG;
			} else {
				currentDigital = 1 - currentDigital;
			} 
			break;
		case KEY_UP_LONG_PRESSED:
		case KEY_UP_PRESSED:
			if (status == STATE_SETUP) {
				
				if (currentDigital == HOUR_SEG) {
					newNumber = led_buffer[0]*10 + led_buffer[1] + 1;
					if (newNumber == 24) {
						newNumber = 0;
					}
					led_buffer[0] = newNumber/10;
					led_buffer[1] = newNumber%10;
				} else {
					newNumber = led_buffer[2]*10 + led_buffer[3] + 1;
					if (newNumber == 60) {
						newNumber = 0;
					}
					led_buffer[2] = newNumber/10;
					led_buffer[3] = newNumber%10;
				}
			}
		break;
		case KEY_DOWN_LONG_PRESSED:
		case KEY_DOWN_PRESSED:
			if (status == STATE_SETUP) {
				
	
				if (currentDigital == HOUR_SEG) {
					newNumber = led_buffer[0]*10 + led_buffer[1] - 1;
					if (newNumber < 0) {
						newNumber = 23;
					}
					led_buffer[0] = newNumber/10;
					led_buffer[1] = newNumber%10;
				} else {
					newNumber = led_buffer[2]*10 + led_buffer[3] - 1;
					if (newNumber < 0) {
						newNumber = 59;
					}
					led_buffer[2] = newNumber/10;
					led_buffer[3] = newNumber%10;
				}
			}
		break;
		case KEY_OK_PRESSED:
			if (status == STATE_SETUP) {
				ds1302_init();
				ds1302_clearWP();
				ds1302_writeHour((led_buffer[0] << 4) | led_buffer[1]);
				ds1302_writeMin((led_buffer[2] <<4 ) | led_buffer[3]);
				ds1302_writeSec(0x00);
				ds1302_enableWP();
				status = STATE_CLOCK;
				currentDigital = -1;
			} else {
				status = STATE_TEMP;
				
			}
		break;

		
	}
}
void main(void) {

	ds1302_init();
//	ds1302_clearWP();
//	ds1302_writeHour(0x21);
//	ds1302_writeMin(0x56);
//	ds1302_writeSec(0x00);
//	ds1302_enableWP();

	ds18b20_setLowResolution();
	
	led_buffer[0] = 0;
	led_buffer[1] = 1;
	led_buffer[2] = 2;
	led_buffer[3] = 3;
	status = STATE_CLOCK;
	initTimer();

	
	while(1) {

		if (tasks[0] == 0) {
			readDS1302();
			tasks[0] = READ_TIME_INT;
		}
		if (tasks[1] == 0) { 
			refreshLed();
			tasks[1] = LED_REFRESH_TASK_INT;
		}
		if (tasks[2] == 0) {
			readDS18B20();
			tasks[2] = READ_TEMP_INT;
		}
		if (tasks[3] == 0) {
			readKeyboard();
			tasks[3] = KEY_SCAN_INT;
		}
	}
	
}

void timer0_isr() interrupt 1
{
	//重装定时器值
  	 TH0 = (8192 - 1000)/32;
	 TL0 = (8192 - 1000)%32;

	 if (tasks[0] > 0) {
	 	tasks[0] --	;
	 }

	 if (tasks[1] > 0) {
	 	tasks[1] --;
	 }
	 if (tasks[2] > 0) {
	 	tasks[2] --;
	 }

	 if (tasks[3] > 0) {
	 	tasks[3] --;
	 }


}