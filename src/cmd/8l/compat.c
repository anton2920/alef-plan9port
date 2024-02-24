#include	"l.h"

void*
mysbrk(ulong size)
{
	return sbrk(size);
}

void
setmalloctag(void *v, ulong pc)
{
	USED(v);
	USED(pc);
}

int
fileexists(char *s)
{
	return access(s, F_OK);
}
