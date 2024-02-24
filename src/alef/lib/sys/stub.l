#include <alef.h>
#include <sys/syscall.h>

int	Syscall(int, int, int, int);
int	Syscall6(int, int, int, int, int, int, int);

void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		Syscall(SYS_exit, 0, 0, 0);
	}
	Syscall(SYS_exit, 1, 0, 0);
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	return (void * )Syscall6(SYS_mmap, (int)addr, len, prot, flags, fd, offset);
}


int
errstr(byte *err)
{
	return 0;
}


int
rendezvous(void *a, uint b)
{
	return 0;
}


int
write(int fd, void *buf, int n)
{
	return Syscall(SYS_write, fd, (int)buf, n);
}


