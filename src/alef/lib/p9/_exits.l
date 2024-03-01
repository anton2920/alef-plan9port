#include <alef.h>

void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		_exit(0);
	}
	_exit(1);
}


