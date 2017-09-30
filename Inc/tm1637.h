#ifndef __TM1637_H
#define __TM1637_H

#define TM1637_BRIGHTNESS 8

void tm1637_init(void);
void tm1637_display_dec(int v, int separator);

#endif

