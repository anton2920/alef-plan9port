#include <alef.h>

/* From <sys/resource.h>. */
#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

int
times(int *t)
{
	Rusage ru, cru;

	if (getrusage(RUSAGE_SELF, &ru) < 0 || getrusage(RUSAGE_CHILDREN, &cru) < 0) {
		return - 1;
	}

	t[0] = ru.utime.sec * 1000 + ru.utime.usec / 1000;
	t[1] = ru.stime.sec * 1000 + ru.stime.usec / 1000;
	t[2] = cru.utime.sec * 1000 + cru.utime.usec / 1000;
	t[3] = cru.stime.sec * 1000 + cru.stime.usec / 1000;

	/* BUG */
	return t[0] + t[1] + t[2] + t[3];
}


