/**
	Author: Sun, Qin. 
	Email: sqlxx@sina.com
*/
#include "common.h"

void delayUs2x(byte t)
{
	while (--t);
}
void delayMs(byte t)
{
	while(t--)
	{
		delayUs2x(245);
		delayUs2x(245);
	}
}