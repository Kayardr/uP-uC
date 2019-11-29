#ifndef _TIMER_2_H
#define _TIMER_2_H
#include <inttypes.h>
#define FREC_CLK    32768

#define COMPARE_VALUE(fclk, prescaler, mTime) ((fclk / (2*prescaler)) * mTime) - 1 

void Timer2_Ini ( void );
uint8_t Timer2_SecFlag(void);

#endif