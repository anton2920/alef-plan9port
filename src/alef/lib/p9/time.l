#include	<alef.h>
#include	"sys.h"


int
_time(int *tp)
{
	Timespec tv;

	if (clock_gettime(CLOCK_REALTIME, &tv) < 0) {
		return -1;
	}
	if (tp) {
		*tp = tv.sec;
	}
	return tv.sec;
}


int
time()
{
	return _time(nil);
}
