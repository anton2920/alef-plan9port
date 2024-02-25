#include <sys/syscall.h>

(int, int, int)
syscall(int, int, int, int);

(int, int, int)
syscall6(int, int, int, int, int, int, int);

intern int _errno;

void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		syscall(SYS_exit, 0, 0, 0);
	}
	syscall(SYS_exit, 1, 0, 0);
}


int
errstr(byte *err)
{
	return 0;
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	int	r1, errno;

	(r1, nil, errno) = syscall6(SYS_mmap, (int)addr, len, prot, flags, fd, offset);
	_errno = errno;

	return (void * )r1;
}


int
rendezvous(void *a, uint b)
{
	return 0;
}


int
write(int fd, void *buf, int n)
{
	int	r1, errno;

	(r1, nil, errno) = syscall(SYS_write, fd, (int)buf, n);
	_errno = errno;

	return r1;
}


