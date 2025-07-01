#include	<alef.h>
#include	"sys.h"


int
lstat(byte *path, Stat *sb)
{
	return fstatat(AT_FDCWD, path, sb, AT_SYMLINK_NOFOLLOW);
}


int
_stat(byte *path, Stat *sb)
{
	return fstatat(AT_FDCWD, path, sb, 0);
}
