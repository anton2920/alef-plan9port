#include <alef.h>

#define _HAVESTGEN

/* From <sys/stat.h>. */
#define	S_ISDIR(m)	(((m) & 0170000) == 0040000)	/* directory */
#define	S_ISCHR(m)	(((m) & 0170000) == 0020000)	/* char special */
#define	S_ISBLK(m)	(((m) & 0170000) == 0060000)	/* block special */
#define	S_ISFIFO(m)	(((m) & 0170000) == 0010000)	/* fifo or socket */
#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */
#define	S_ISSOCK(m)	(((m) & 0170000) == 0140000)	/* socket */


/* From <sys/ioccom.h>. */
#define	IOCPARM_SHIFT	13		/* number of bits for ioctl size */
#define	IOCPARM_MASK	((1 << IOCPARM_SHIFT) - 1) /* parameter length mask */

#define	IOC_OUT		0x40000000	/* copy out parameters */

#define	_IOC(inout,group,num,len)	((uint) ((inout) | (((len) & IOCPARM_MASK) << 16) | ((group) << 8) | (num)))

/* From <sys/disk.h>. */
#define	DIOCGMEDIASIZE	_IOC(IOC_OUT, 'd', 129, 8)	/* Get media size in bytes */

intern
int
disksize(int fd)
{
	int	mediasize[2];

	if (ioctl(fd, DIOCGMEDIASIZE, mediasize) >= 0)
		return mediasize[0];
	return 0;
}


/*
 * Caching the last group and passwd looked up is
 * a significant win (stupidly enough) on most systems.
 * It's not safe for threaded programs, but neither is using
 * getpwnam in the first place, so I'm not too worried.
 */
int
_p9dir(Stat *lst, Stat *st, byte *name, Dir *d, byte **str, byte *estr)
{
	byte * s;
	byte tmp[20];
	int	sz;

	sz = 0;
	if (d)
		memset(d, 0, sizeof * d);

	/* name */
	s = strrchr(name, '/');
	if (s)
		s++;
	if (!s || !*s)
		s = name;
	if (*s == '/')
		s++;
	if (*s == 0)
		s = "/";
	if (d) {
		if (*str + strlen(s) + 1 > estr)
			d->name = "oops";
		else {
			strcpy(*str, s);
			d->name = *str;
			*str += strlen(*str) + 1;
		}
	}
	sz += strlen(s) + 1;

	/* user */
	snprint(tmp, sizeof tmp, "%d", (int)st->uid);
	s = tmp;
	sz += strlen(s) + 1;
	if (d) {
		if (*str + strlen(s) + 1 > estr)
			d->uid = "oops";
		else {
			strcpy(*str, s);
			d->uid = *str;
			*str += strlen(*str) + 1;
		}
	}

	/* group */
	snprint(tmp, sizeof tmp, "%d", (int)st->gid);
	s = tmp;
	sz += strlen(s) + 1;
	if (d) {
		if (*str + strlen(s) + 1 > estr)
			d->gid = "oops";
		else {
			strcpy(*str, s);
			d->gid = *str;
			*str += strlen(*str) + 1;
		}
	}

	if (d) {
		d->type = 'M';

		d->muid = "";
		d->qid.path = st->ino[0];
		/*
		 * do not include st->dev in path, because
		 * automounters give the same file system different
		 * dev values for successive mounts, causing
		 * spurious write warnings in acme and sam.
		d->qid.path |= (uvlong)st->dev<<32;
		 */
#ifdef _HAVESTGEN
		d->qid.vers = st->gen[0];
#endif
		if (d->qid.vers == 0)
			d->qid.vers = st->mtim.sec + st->ctim.sec;
		d->mode = st->mode & 0777;
		d->atime = st->atim.sec;
		d->mtime = st->mtim.sec;
		d->length = st->size[0];

		if (S_ISLNK(lst->mode)) {	/* yes, lst not st */
			d->mode |= DMSYMLINK;
			d->length = lst->size[0];
		} else if (S_ISDIR(st->mode)) {
			d->length = 0;
			d->mode |= DMDIR;
			d->qid.type = QTDIR;
		} else if (S_ISFIFO(st->mode))
			d->mode |= DMNAMEDPIPE;
		else if (S_ISSOCK(st->mode))
			d->mode |= DMSOCKET;
		else if (S_ISBLK(st->mode)) {
			d->mode |= DMDEVICE;
			d->qid.path = ('b' << 16) | st->rdev[0];
		} else if (S_ISCHR(st->mode)) {
			d->mode |= DMDEVICE;
			d->qid.path = ('c' << 16) | st->rdev[0];
		}
		/* fetch real size for disks */
		if (S_ISBLK(lst->mode)) {
			int	fd;
			if ((fd = open(name, OREAD)) >= 0) {
				d->length = disksize(fd);
				close(fd);
			}
		}
	}

	return sz;
}


