#include <alef.h>

int	_p9dir(Stat*, Stat*, byte*, Dir*, byte**, byte*);

Dir*
dirfstat(int fd)
{
	byte	 * str, tmp[100];
	int	nstr;
	Stat st;
	Dir * d;

	if (fstat(fd, &st) < 0)
		return nil;

	snprint(tmp, sizeof tmp, "/dev/fd/%d", fd);
	nstr = _p9dir(&st, &st, tmp, nil, nil, nil);
	d = malloc(sizeof(Dir) + nstr);
	if (d == nil)
		return nil;
	str = (byte * ) & d[1];
	_p9dir(&st, &st, tmp, d, &str, str + nstr);
	return d;
}


