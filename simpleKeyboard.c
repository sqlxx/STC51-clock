/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include <reg52.h>
#include "common.h"
#include "simpleKeyboard.h"

#define LONG_PRESS_CYCLE 20

sbit KEY_MODE = P2^4;
sbit KEY_UP = P2^5;
sbit KEY_DOWN = P2^6;
sbit KEY_OK = P2^7;

//有很多重复代码，是否可以更优化？
byte keySacn(){
	static byte currentStatus = KEY_NULL;
	static int count = 0;

	byte confirmedStatus = KEY_NULL;

	if (!KEY_MODE) {
		if (currentStatus == KEY_MODE_TEMP) {
			confirmedStatus = KEY_MODE_PRESSED;
			currentStatus = KEY_MODE_PRESSED;
			
		} else if (currentStatus == KEY_MODE_PRESSED) {		   //Press doens't change.
			currentStatus = KEY_MODE_PRESSED;
			confirmedStatus = KEY_NULL;
		} else {
			currentStatus = KEY_MODE_TEMP;
			confirmedStatus = KEY_NULL;
			
		}
	} else if (!KEY_UP) {
		if (currentStatus == KEY_UP_TEMP) { //消抖
			confirmedStatus = KEY_UP_PRESSED;
			currentStatus = KEY_UP_PRESSED;
			count = 0;
		} else if (currentStatus == KEY_UP_PRESSED) { //The button is already pressed.
			if (++count > LONG_PRESS_CYCLE) {					  //达到长按的阙值。
				confirmedStatus = KEY_UP_LONG_PRESSED;
				currentStatus = KEY_UP_LONG_PRESSED;
			} else {
				confirmedStatus = KEY_NULL;
				//currentStatus not change in this case
			}
		} else if (currentStatus == KEY_UP_LONG_PRESSED) {
			confirmedStatus = KEY_UP_LONG_PRESSED;  //long press not changed.
		} else {
			currentStatus = KEY_UP_TEMP;
			confirmedStatus = KEY_NULL;
			
		}

	} else if (!KEY_DOWN) {

		if (currentStatus == KEY_DOWN_TEMP) { //消抖
			confirmedStatus = KEY_DOWN_PRESSED;
			currentStatus = KEY_DOWN_PRESSED;
			count = 0;
		} else if (currentStatus == KEY_DOWN_PRESSED) { //The button is already pressed.
			if (++count > LONG_PRESS_CYCLE) {					  //达到长按的阙值。
				confirmedStatus = KEY_DOWN_LONG_PRESSED;
				currentStatus = KEY_DOWN_LONG_PRESSED;
			} else {
				confirmedStatus = KEY_NULL;
				//currentStatus not change in this case
			}

		} else if (currentStatus == KEY_DOWN_LONG_PRESSED) {
			confirmedStatus = KEY_DOWN_LONG_PRESSED;  //long press not changed.
		} else {
			currentStatus = KEY_DOWN_TEMP;
			confirmedStatus = KEY_NULL;
		}

	} else if (!KEY_OK){
		if (currentStatus == KEY_OK_TEMP) {
			confirmedStatus = KEY_OK_PRESSED;
			currentStatus = KEY_OK_PRESSED;
			
		} else if (currentStatus == KEY_OK_PRESSED) {		   //Press doens't change.
			currentStatus = KEY_OK_PRESSED;
			confirmedStatus = KEY_NULL;
		} else {
			currentStatus = KEY_OK_TEMP;
			confirmedStatus = KEY_NULL;
			
		}
	} else {
		confirmedStatus = KEY_NULL;
		currentStatus = KEY_NULL;
	}

	return confirmedStatus;
}


