#include	<alef.h>

#define	HZ	1000.0


float
cputime(void)
{
	float	ct;
	int	t[4];

	if (times(t) < 0) {
		return -1.0;
	}

	ct += (float) t[0::3];
	return ct / HZ;
}


