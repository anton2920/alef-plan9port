#include <alef.h>

#define DBG(s) s
#define MAXDEPTH	100

intern void namedev(Dir*);
intern int  samefile(Dir*, Dir*);
intern int  crossedmnt(byte*);

byte *
getwd(byte *s , int size)
{
	Dir * p, root, *db;
	int	depth, l;
	byte * x, *v;

	db = malloc(sizeof(Dir) * MAXDEPTH);
	rescue {
		free(db);
		return nil;
	}
	if (db == nil) {
		strcpy(s, "no memory");
		raise;
	}
	x = s;
	p = dirstat("/");
	if (p == nil) {
		strcpy(s, "stat of / failed");
		raise;
	}
	root = *p;
	/* free(p); */

	for (depth = 0; depth < MAXDEPTH; depth++) {
		p = dirstat(".");
		if (p == nil) {
			strcpy(s, "stat of . failed");
			raise;
		}
		db[depth] = *p;
		/* free(p); */
		p = &db[depth];

		DBG(print("stat: %s %lux\n", p->name, p->qid); )

		if (samefile(p, &root)) {
			depth--;
			break;
		}

		if (depth > 1 && samefile(p, &db[depth-1])) {
			p->name[0] = '#';
			p->name[1] = p->type;
			p->name[2] = '\0';
			break;
		}

		if (crossedmnt(p->name))
			namedev(p);

		if (chdir("..") < 0) {
			strcpy(s, "chdir .. failed");
			raise;
		}
	}

	while (depth >= 0) {
		v = db[depth--].name;
		DBG(print("comp: %s\n", v); )
		if (v[0] == '.' && v[1] == '\0')
			continue;
		if (v[0] != '#')
			*x++ = '/';
		l = strlen(v);
		size -= l + 1;
		if (size <= 0) {
			strcpy(s, "buffer too small");
			raise;
		}
		strcpy(x, v);
		x += l;
	}
	if (x == s) {
		*x++ = '/';
		*x = 0;
	}
	DBG(print("chdir %s\n", s); )
	if (chdir(s) < 0) {
		strcpy(s, "failed to return to .");
		raise;
	}
	free(db);
	return s;
}


/*
 * In cases where we have no valid name from the stat we must search .. for an
 * entry which leads back to our current depth. This happens in three ways:
 * when crossing a mount point or when we are in a dev which uses devgen in the
 * kernel to fill in the stat buffer or when we are at slash of a mounted file system
 */
intern void
namedev(Dir *p)
{
	int	i, fd;
	Dir * dirs, *dirb, *tdirb;
	int	ndirs;
	byte sd[NAMELEN*2];

	fd = open("..", OREAD);
	if (fd < 0)
		return;

	ndirs = dirreadall(fd, &dirs);
	if (ndirs < 0) {
		print("%r\n");
		return;
	}
	print("ndirs = %d\n");

	for (i = 0; i < ndirs; ++i) {
		print("Dir: %D\n", dirs[i]);

		dirb = &dirs[i];
		if ((dirb->qid.path[1] & CHDIR) == 0)
			continue;

		sprint(sd, "../%s/.", dirb->name);
		tdirb = dirstat(sd);
		if (tdirb == nil) {
			continue;
		}

		if (!samefile(tdirb, p)) {
			free(tdirb);
			continue;
		}

		free(tdirb);
		free(dirs);
		close(fd);
		DBG(print("%s->%s\n", p->name, dirb->name); )
		strcpy(p->name, dirb->name);
		return;

	}
	free(dirs);
	close(fd);
}


intern int
samefile(Dir *a, Dir *b)
{
	if (a->type != b->type)
		return 0;
	if (a->dev != b->dev)
		return 0;
	if ((a->qid.path[0] != b->qid.path[0]) || (a->qid.path[1] != b->qid.path[1]))
		return 0;
	return 1;
}


/*
 * returns true if we must establish a child which derives the current
 * directory name after stat has failed to account for devices and the
 * mount table
 */
intern int
crossedmnt(byte *elem)
{
	byte junk[sizeof(Stat)];

	if ((elem[0] == '.' || elem[0] == '/') && elem[1] == '\0')
		return 1;

	sprint(junk, "../%s", elem);
	if (stat(junk, (Stat * )junk) < 0)
		return 1;

	return 0;
}


