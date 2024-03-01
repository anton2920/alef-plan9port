#include <alef.h>

int
dirfwstat(int fd, Dir *dir)
{
	int	ret;
	Timeval tv[2];

	ret = 0;
	if (~dir->mode != 0) {
		if (fchmod(fd, dir->mode) < 0)
			ret = -1;
	}
	if (~dir->mtime != 0) {
		tv[0].sec = dir->mtime;
		tv[0].usec = 0;
		tv[1].sec = dir->mtime;
		tv[1].usec = 0;
		if (futimes(fd, tv) < 0)
			ret = -1;
	}
	if (~dir->length != 0) {
		if (ftruncate(fd, dir->length) < 0)
			ret = -1;
	}
	return ret;
}


