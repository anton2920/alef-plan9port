#include <alef.h>

int
sleep(int msecs)
{
	Timespec tv;

	if (msecs == 0) {
		return sched_yield();
	}

	tv.sec = msecs / 1000;
	tv.nsec = (msecs % 1000) * 1000000;
	return nanosleep(&tv, nil);
}


