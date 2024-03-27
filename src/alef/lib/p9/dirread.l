#include <alef.h>

/* From <fcntl.h>. */
#define	AT_SYMLINK_NOFOLLOW	0x0200	/* Do not follow symbolic links */

/* From <sys/stat.h>. */
#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */

aggr DirBuild
{
	Dir * d;
	int	nd;
	int	md;
	byte * str;
	byte * estr;
};


aggr Dirs
{
	Lock;
	int	*data;
	int	n;
};


intern Dirs dirs;

int	_p9dir(Stat *, Stat *, byte*, Dir*, byte**, byte*);


int
dirput(int fd)
{
	int	newn, i;
	int	*tmp;

	if (fd < 0) {
		werrstr("invalid fd");
		return - 1;
	}

	dirs.lock();
	if (fd >= dirs.n) {
		newn = dirs.n * 2;
		if (newn <= fd) {
			newn = fd + 1;
		}
		tmp = realloc(dirs.data, newn * sizeof(fd));
		if (tmp == nil) {
			werrstr("out of memory");
			dirs.unlock();
			return - 1;
		}

		for (i = dirs.n; i < newn; ++i) {
			tmp[i] = -1;
		}
		dirs.n = newn;
		dirs.data = tmp;
	}
	dirs.data[fd] = fd;
	dirs.unlock();
	return 0;
}


intern
int
dirget(int fd)
{
	int	d;

	d = -1;
	dirs.lock();
	if ((fd >= 0) && (fd <= dirs.n)) {
		d = dirs.data[fd];
	}
	dirs.unlock();
	return d;
}


int
dirdel(int fd)
{
	int	d;

	d = -1;
	dirs.lock();
	if ((fd >= 0) && (fd <= dirs.n)) {
		d = dirs.data[fd];
		dirs.data[fd] = -1;
	}
	dirs.unlock();
	return d;
}


intern
int
dirbuild1(DirBuild *b, Stat *lst, Stat *st, byte *name)
{
	int	i, nstr;
	Dir * d;
	int	md, mstr;
	byte * lo, *hi, *newlo;

	nstr = _p9dir(lst, st, name, nil, nil, nil);
	if (b->md - b->nd < 1 || b->estr - b->str < nstr) {
		// expand either d space or str space or both.
		md = b->md;
		if (b->md - b->nd < 1) {
			md *= 2;
			if (md < 16)
				md = 16;
		}
		mstr = b->estr - (byte * ) & b->d[b->md];
		if (b->estr - b->str < nstr) {
			mstr += nstr;
			mstr += mstr / 2;
		}
		if (mstr < 512)
			mstr = 512;
		d = realloc(b->d, md * sizeof d[0] + mstr);
		if (d == nil)
			return - 1;
		// move strings and update pointers in Dirs
		lo = (byte * ) & b->d[b->md];
		newlo = (byte * ) & d[md];
		hi = b->str;
		memmove(newlo, lo + ((byte * )d - (byte * )b->d), hi - lo);
		for (i = 0; i < b->nd; i++) {
			if (lo <= d[i].name && d[i].name < hi)
				d[i].name += newlo - lo;
			if (lo <= d[i].uid && d[i].uid < hi)
				d[i].uid += newlo - lo;
			if (lo <= d[i].gid && d[i].gid < hi)
				d[i].gid += newlo - lo;
			if (lo <= d[i].muid && d[i].muid < hi)
				d[i].muid += newlo - lo;
		}
		b->d = d;
		b->md = md;
		b->str += newlo - lo;
		b->estr = newlo + mstr;
	}
	_p9dir(lst, st, name, &b->d[b->nd], &b->str, b->estr);
	b->nd++;
	return 0;
}


intern
int
dirreadmax(int fd, Dir **dp, int max)
{
	int	i;
	DirBuild b;
	Dirent de;
	Stat st, lst;

	if (dirget(fd) == -1) {
		werrstr("not a directory");
		return - 1;
	}

	memset(&b, 0, sizeof b);
	for (i = 0; max == -1 || i < max; i++) { // max = not too many, not too few
		if (getdirentries(fd, (byte * ) & de, sizeof(de), nil) <= 0) {
			if (b.nd == 0) {
				return - 1;
			}
			break;
		}
		print("Dirent: %s\n", de.name);

		// Note: not all systems have namlen. Assume NUL-terminated.
		if (de.name[0] == '.' && de.name[1] == 0)
			continue;
		if (de.name[0] == '.' && de.name[1] == '.' && de.name[2] == 0)
			continue;
		if (fstatat(fd, de.name, &lst, AT_SYMLINK_NOFOLLOW) < 0)
			continue;
		st = lst;
		if (S_ISLNK(lst.mode))
			fstatat(fd, de.name, &st, 0);
		dirbuild1(&b, &lst, &st, de.name);
	}
	*dp = b.d;
	return b.nd;
}


int
dirread(int fd, Dir **dp)
{
	return dirreadmax(fd, dp, 10);
}


int
dirreadall(int fd, Dir **dp)
{
	return dirreadmax(fd, dp, -1);
}


