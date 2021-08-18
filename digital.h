#ifndef __DIGITAL_H__
#define __DIGITAL_H__

#define DIGI_COUNT 3

#define DIGI_NULL 11
#define DIGI_C 10

#define HOUR_SEG 0
#define MIN_SEG 1

extern byte led_buffer[4];

void led_display(void);

void led_disable();

void led_enable();

void led_flashDp();

void led_noDp();
#endif