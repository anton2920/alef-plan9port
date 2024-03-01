#include	<alef.h>

intern int fd = -1;
int	_time(void);

void
t(void)
{
	print("time: %lux\n", _time());
}

int
_time(void)
{
	int t;
	byte b[20];

	memset(b, 0, sizeof(b));
	!{
		if(fd < 0)
			fd = open("/dev/time", OREAD|OCEXEC);
		if(fd >= 0) {
			seek(fd, 0, 0);
			read(fd, b, sizeof(b));
		}
	}
	t = atoi(b);
	return t;
}

void
main(void)
{
	proc t(), t(); t();

	t();
}
