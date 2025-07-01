#include	<alef.h>
#include	"sys.h"


aggr DirMap
{
	Lock;
	int	*fds;
	int	nd;
};


aggr DirBuild
{
	Dir * d;
	int	nd;
	int	md;
	byte	 * str;
	byte	 * estr;
};


intern DirMap dirs;


intern
int
dirput(int fd)
{
	int	i, nd;
	int	*tmp;

	if (fd < 0) {
		werrstr("invalid fd");
		return -1;
	}

	dirs.lock();
	if (fd >= dirs.nd) {
		nd = dirs.nd * 2;
		if (nd <= fd) {
			nd = fd + 1;
		}

		tmp = realloc(dirs.fds, nd * sizeof dirs.fds[0]);
		if (tmp == nil) {
			werrstr("out of memory");
			dirs.unlock();
			return -1;
		}

		for (i = dirs.nd; i < nd; i++) {
			tmp[i] = -1;
		}
		dirs.fds = tmp;
		dirs.nd = nd;
	}
	dirs.fds[fd] = fd;
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
	if ((fd >= 0) && (fd < dirs.nd)) {
		d = dirs.fds[fd];
	}
	dirs.unlock();
	return d;
}


intern
int
dirdel(int fd)
{
	int	d;

	d = -1;
	dirs.lock();
	if ((fd >= 0) && (fd < dirs.nd)) {
		d = dirs.fds[fd];
		dirs.fds[fd] = -1;
	}
	dirs.unlock();
	return d;
}


int
remove(byte *path)
{
	Stat st;

	if (_stat(path, &st) >= 0 && S_ISDIR(st.mode)) {
		return rmdir(path);
	} else {
		return unlink(path);
	}
}


int
create(byte *path, int mode, uint perm)
{
	int	fd, cexec, umode, rclose, lock, rdwr;
	Flock fl;

	rdwr = mode & 3;
	lock = mode & OLOCK;
	cexec = mode & OCEXEC;
	rclose = mode & ORCLOSE;
	mode &= ~(ORCLOSE | OCEXEC | OLOCK);

	/* XXX should get mode mask right? */
	fd = -1;
	if (perm & DMDIR) {
		if (mode != OREAD) {
			werrstr("bad mode in directory create");
			goto out;
		}
		if (mkdir(path, perm & 0777) < 0)
			goto out;
		fd = open(path, OREAD);
	} else {
		umode = (mode & 3) | O_CREAT | O_TRUNC;
		mode &= ~(3 | OTRUNC);
		if (mode & ODIRECT) {
			umode |= O_DIRECT;
			mode &= ~ODIRECT;
		}
		if (mode & OEXCL) {
			umode |= O_EXCL;
			mode &= ~OEXCL;
		}
		if (mode & OAPPEND) {
			umode |= O_APPEND;
			mode &= ~OAPPEND;
		}
		if (mode) {
			werrstr("unsupported mode in create");
			goto out;
		}
		fd = _open(path, umode, perm);
		if (fd >= 0) {
			if (lock) {
				if (rdwr == OREAD) {
					fl.type = F_RDLCK;
				} else {
					fl.type = F_WRLCK;
				}
				fl.whence = SEEK_SET;
				(fl.start[0], fl.start[1]) = (0, 0);
				(fl.len[0], fl.len[1]) = (0, 0);
				if (fcntl(fd, F_SETLK, &fl) < 0) {
					close(fd);
					werrstr("lock: %r");
					return -1;
				}
			}
			if (cexec)
				fcntl(fd, F_SETFL, FD_CLOEXEC);
			if (rclose)
				remove(path);
		}
	}
out:
	return fd;
}


int
open(byte *name, int mode)
{
	int	cexec, rclose;
	int	fd, umode, lock, rdwr;
	Flock fl;
	Stat st;

	rdwr = mode & 3;
	umode = rdwr;
	cexec = mode & OCEXEC;
	rclose = mode & ORCLOSE;
	lock = mode & OLOCK;
	mode &= ~(3 | OCEXEC | ORCLOSE | OLOCK);
	if (mode & OTRUNC) {
		umode |= O_TRUNC;
		mode ^= OTRUNC;
	}
	if (mode & ODIRECT) {
		umode |= O_DIRECT;
		mode ^= ODIRECT;
	}
	if (mode & ONONBLOCK) {
		umode |= O_NONBLOCK;
		mode ^= ONONBLOCK;
	}
	if (mode & OAPPEND) {
		umode |= O_APPEND;
		mode ^= OAPPEND;
	}
	if (mode) {
		werrstr("mode 0x%x not supported", mode);
		return -1;
	}
	fd = _open(name, umode, 0);
	if (fd >= 0) {
		if (lock) {
			if (rdwr) {
				fl.type = F_RDLCK;
			} else {
				fl.type = F_WRLCK;
			}
			fl.whence = SEEK_SET;
			(fl.start[0], fl.start[1]) = (0, 0);
			(fl.len[0], fl.len[1]) = (0, 0);
			if (fcntl(fd, F_SETLK, &fl) < 0) {
				close(fd);
				werrstr("lock: %r");
				return -1;
			}
		}
		if (cexec)
			fcntl(fd, F_SETFL, FD_CLOEXEC);
		if (_fstat(fd, &st) >= 0 && S_ISDIR(st.mode)) {
			if (dirput(fd) < 0) {
				return -1;
			}
		}
		if (rclose)
			remove(name);
	}
	return fd;
}


int
seek(int fd, uint offset, int whence)
{
	return lseek(fd, offset, 0, whence);
}


int
close(int fd)
{
	dirdel(fd);
	return _close(fd);
}


intern
int
dirbuild1(DirBuild *b, Stat *lst, Stat *st, byte *name)
{
	int	i, nstr;
	Dir *d;
	int	md, mstr;
	byte	 *lo, *hi, *newlo;

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
			return -1;
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
		return -1;
	}

	memset(&b, 0, sizeof b);
	for (i = 0; (max == -1) || (i < max); i++) { // max = not too many, not too few
		if (getdirentries(fd, (byte * ) & de, sizeof(de), nil) <= 0) {
			if (b.nd == 0) {
				print("Error: %r\n");
				return -1;
			}
			break;
		}
		if (de.off[0] != 0) {
			if (seek(fd, de.off[0], SEEK_SET) < 0) {
				print("lseek error: %r\n");
				return -1;
			}
		}

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


