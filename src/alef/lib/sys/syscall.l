#include <alef.h>
#include <sys/syscall.h>

(int, int, int)
syscall(int, int, int, int);

(int, int, int)
syscall6(int, int, int, int, int, int, int);

(int, int, int)
syscall9(int, int, int, int, int, int, int, int, int, int);

byte*	strerror(int);

intern int	_errno;
intern byte	_syserr[ERRLEN];

intern byte *
getsyserr(void)
{
	return _syserr;
}


void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		syscall(SYS_exit, 0, 0, 0);
	}
	syscall(SYS_exit, 1, 0, 0);
}


void
rerrstr(byte *err, uint n)
{
	byte * syserr;

	syserr = getsyserr();
	strcpy(syserr, strerror(_errno));
	strncpy(err, syserr, n);
}


int
errstr(byte *err, uint n)
{
	byte tmp[ERRLEN];
	byte * syserr;

	strncpy(tmp, err, n);
	rerrstr(err, n);
	syserr = getsyserr();
	strncpy(syserr, tmp, ERRLEN);
	_errno = 0;
	return 0;
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	int	r1, errno;

	(r1, nil, errno) = syscall9(SYS_mmap, (int)addr, len, prot, flags, fd, offset, 0, 0, 0);
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


