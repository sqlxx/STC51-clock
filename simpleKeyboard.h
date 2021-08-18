#ifndef __SIMPLE_KEYBOARD_H__
#define __SIMPLE_KEYBOARD_H__

#define KEY_NULL 0
#define KEY_MODE_PRESSED 1
#define KEY_UP_PRESSED 2
#define KEY_DOWN_PRESSED 3
#define KEY_OK_PRESSED 4

#define KEY_MODE_LONG_PRESSED 10
#define KEY_UP_LONG_PRESSED 11
#define KEY_DOWN_LONG_PRESSED 12
#define KEY_OK_LONG_PRESSED 13

#define KEY_MODE_TEMP 20
#define KEY_UP_TEMP 21
#define KEY_DOWN_TEMP 22
#define KEY_OK_TEMP 23


byte keyScan();			  

#endif