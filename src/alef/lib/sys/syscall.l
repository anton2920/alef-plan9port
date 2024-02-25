#include <alef.h>
#include <sys/syscall.h>

#include "run.h"

/* From <sys/signal.h>. */
#define	SIGABRT	6

(int, int, int)
syscall(int, int, int, int);

(int, int, int)
syscall6(int, int, int, int, int, int, int);

(int, int, int)
syscall9(int, int, int, int, int, int, int, int, int, int);

byte*	strerror(int);

enum
{
	EPLAN9 = 0x19283745,
};

intern int	_errno;
intern byte	_syserrstr[ERRLEN];

intern byte *
getsyserr(void)
{
	if (PROC.syserrstr) {
		return PROC.syserrstr;
	}
	return _syserrstr;
}


void
_exit(int code)
{
	syscall(SYS_exit, code, 0, 0);
}


void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		_exit(0);
	}
	_exit(1);
}


void
abort()
{
	int	pid;

	(pid, nil, nil) = syscall(SYS_getpid, 0, 0, 0);
	syscall(SYS_kill, pid, SIGABRT, 0);
}


void
rerrstr(byte *err, uint n)
{
	byte * syserr;

	syserr = getsyserr();
	if (_errno != EPLAN9)
		strcpy(syserr, strerror(_errno));
	strncpy(err, syserr, n - 1);
}


int
errstr(byte *err, uint n)
{
	byte tmp[ERRLEN];
	byte * syserr;

	strncpy(tmp, err, n - 1);
	rerrstr(err, n);
	syserr = getsyserr();
	strncpy(syserr, tmp, ERRLEN - 1);
	_errno = EPLAN9;
	return 0;
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	int	r1;
	(r1, nil, _errno) = syscall9(SYS_mmap, (int)addr, len, prot, flags, fd, offset, 0, 0, 0);
	return (void * )r1;
}


int
rendezvous(void *a, uint b)
{
	werrstr("not implemented");
	check 0, "not implemented";
	return - 1;
}


int
rfork(int flags)
{
	int	r1, errno;
	(r1, nil, _errno) = syscall(SYS_rfork, flags, 0, 0);
	return r1;
}


int
write(int fd, void *buf, int n)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_write, fd, (int)buf, n);
	return r1;
}


