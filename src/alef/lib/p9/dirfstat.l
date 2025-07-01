#include	<alef.h>
#include	"sys.h"


Dir*
dirfstat(int fd)
{
	byte	 *str, tmp[100];
	int	nstr;
	Stat st;
	Dir *d;

	if (_fstat(fd, &st) < 0)
		return nil;

	snprint(tmp, sizeof tmp, "/dev/fd/%d", fd);
	nstr = _p9dir(&st, &st, tmp, nil, nil, nil);
	d = malloc(sizeof(Dir) + nstr);
	if (d == nil)
		return nil;
	str = (byte *) & d[1];
	_p9dir(&st, &st, tmp, d, &str, str + nstr);
	return d;
}
