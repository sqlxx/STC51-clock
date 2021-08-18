/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include <reg52.h>
#include "common.h"
#include "digital.h"

#define DIGI_DP 0x80
sbit DISP_BIT = P3^4;

byte DIGI_NUMBER[12] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, 0x58, 0x00};
byte led_buffer[4];
bit DP_FLASH = 0;
bit DISPLAY_FLAG = 0;
extern char currentDigital;

void led_display(void)
{
	static byte count = 0;
	static byte current = 0;

	//led_disable();
	byte P3_H = P3 & 0xE0;
	P3 = P3_H | current ;


	if (currentDigital >= 0) { //In the setup mode
		
		if (++count == 50) {
			count = 0;
			DISPLAY_FLAG = !DISPLAY_FLAG;
		}

		if (currentDigital == HOUR_SEG) {
			if (current <=1) { //HOUR_SEG

				if (DISPLAY_FLAG) {
					P1 = DIGI_NUMBER[led_buffer[current]] | DIGI_DP;
				} else {
					P1 = DIGI_NUMBER[DIGI_NULL] | DIGI_DP;
				} 
			
			} else {
				P1 = DIGI_NUMBER[led_buffer[current]];
			}		
		} else if (currentDigital == MIN_SEG) {
			if (current > 1) { //MIN_SEG
				if (DISPLAY_FLAG) {
					P1 = DIGI_NUMBER[led_buffer[current]];
				} else {
					P1 = DIGI_NUMBER[DIGI_NULL];
				} 
			} else {
				P1 = DIGI_NUMBER[led_buffer[current]] | DIGI_DP; 
			}
		} 
		
	} else {
		if (current == 1 && DP_FLASH) {	   
			P1 = DIGI_NUMBER[led_buffer[current]] | DIGI_DP; 	
		}else {
			P1 = DIGI_NUMBER[led_buffer[current]];
		} 		
	}
	led_enable();
	current = ((current == DIGI_COUNT) ? 0 : current + 1);
}

void led_disable()
{
	DISP_BIT = 0;	
}

void led_enable()
{
	DISP_BIT = 1;
}

void led_flashDp()
{
	DP_FLASH = !DP_FLASH;
}

void led_noDp()
{
	DP_FLASH = 0;
}
