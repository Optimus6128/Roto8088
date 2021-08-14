#include <i86.h>
#include "timer.h"

int getTime()
{
	static int __far *clock = (int __far*)MK_FP(0x0000, 0x046C);
    return *clock;
}

void sleep(int secs)
{
    int timeDiff = 0;
    int timeEnd = (int)(secs * TIME_FREQ);
    int startTime  = getTime();
    while(timeDiff < timeEnd)
    {
        timeDiff = getTime() - startTime;
    }
}
