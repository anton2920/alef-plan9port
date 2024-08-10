#include <alef.h>

/* From <fcntl.h>. */
#define	AT_FDCWD				-100
#define	AT_SYMLINK_NOFOLLOW	0x0200	/* Do not follow symbolic links */


int
lstat(byte *path, Stat *sb)
{
	return fstatat(AT_FDCWD, path, sb, AT_SYMLINK_NOFOLLOW);
}


int
stat(byte *path, Stat *sb)
{
	return fstatat(AT_FDCWD, path, sb, 0);
}


