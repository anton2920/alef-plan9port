#include <alef.h>

/* From <sys/_clock_id.h>. */
#define CLOCK_REALTIME		0

int
time(int *tp)
{
	Timespec tv;

	if (clock_gettime(CLOCK_REALTIME, &tv) < 0) {
		return - 1;
	}
	if (tp) {
		*tp = tv.sec;
	}
	return tv.sec;
}


