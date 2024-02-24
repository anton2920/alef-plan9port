#include <alef.h>

void	_exit(int);

void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		_exit(0);
	}
	_exit(1);
}


int
errstr(byte *err)
{
	return 0;
}


int
rendezvous(void *a, uint b)
{
	return 0;
}


