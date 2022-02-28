#include <stdio.h>
#include "reprintf.h"
#include "lcd.h"

PUTCHAR_PROTOTYPE{
	lcd_Data_Write((u8)ch);
	return ch;
}
