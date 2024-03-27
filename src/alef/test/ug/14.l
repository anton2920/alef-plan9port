#include	<alef.h>

byte*
findfile(byte *dirname, byte *string)
{
	int n, dirfd, fd, i, ndirs;
	byte *buf, buf2[512];
	Dir *d, *dirs;

	n = strlen(string);
	buf = malloc(n);
	rescue {
		unalloc buf;
		return nil;
	}
	dirfd = open(dirname, OREAD);
	if(dirfd < 0)
		raise;
	rescue {
		close(dirfd);
		raise;
	}

	dirs = nil;
	ndirs = dirreadall(dirfd, &dirs);
	rescue freedirs {
		free(dirs);
		raise;
	}
	if (ndirs < 0) {
		raise;
	}

	for (i = 0; i < ndirs; ++i) {
		d = &dirs[i];
		sprint(buf2, "%s/%s", dirname, d->name);
		fd = open(buf2, OREAD);
		if(fd < 0)
			continue;
		rescue {
			close(fd);
			continue;
		}
		if(read(fd, buf, n) <= 0)
			raise;
		close(fd);
		if(strncmp(buf, string, n) == 0) {
			close(dirfd);
			unalloc buf;
			buf = malloc(strlen(d->name)+1);
			strcpy(buf, d->name);
			return buf;
		}
	}
	werrstr("no match");
	raise freedirs;
	return nil;		/* needed to fool compiler */
}

void
main(int argc, byte **argv)
{
	byte *c;

	if(argc < 3) {
		fprint(2, "give dirname and string as args\n");
		exits("usage");
	}
	c = findfile(argv[1], argv[2]);
	if(c == nil)
		print("not found: %r\n");
	else
		print("found in %s\n", c);
}
