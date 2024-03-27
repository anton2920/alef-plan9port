#include <alef.h>

/* From <sys/stat.h>. */
#define	S_IFMT	 0170000		/* type of file mask */
#define	S_IFLNK	 0120000		/* symbolic link */

int	_p9dir(Stat*, Stat*, byte*, Dir*, byte**, byte*);

Dir*
dirstat(byte *file)
{
	Stat st, lst;
	byte * str;
	int	nstr;
	Dir * d;

	if (lstat(file, &lst) < 0)
		return nil;
	st = lst;
	if ((lst.mode & S_IFMT) == S_IFLNK)
		stat(file, &st);

	nstr = _p9dir(&lst, &st, file, nil, nil, nil);
	d = malloc(sizeof(Dir) + nstr);
	if (d == nil)
		return nil;
	str = (byte * ) & d[1];
	_p9dir(&lst, &st, file, d, &str, str + nstr);
	return d;
}


