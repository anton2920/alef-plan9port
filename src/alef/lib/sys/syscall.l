#include <alef.h>
#include <sys/syscall.h>

#define _STANDALONE
#include <errno.h>

#include "run.h"

/* From <fcntl.h>. */
#define	O_CREAT		0x0200		/* create if nonexistent */

/* From <sys/signal.h>. */
#define	SIGABRT	6

/* From <sys/umtx.h>. */
#define	UMTX_OP_WAKE		3
#define	UMTX_OP_WAIT_UINT	11

#define	RENDMAX	(1 << 5)

aggr RendP
{
	void * tag;
	uint	value;
};


intern RendP	RendezList[RENDMAX];
intern Lock	RendezLock;

aggr Timespec
{
	int	sec;
	int	nsec;
};


enum
{
	EPLAN9 = 0x19283745,
};

intern int	_errno;
intern byte	_syserrstr[ERRLEN];

byte*	strerror(int);


intern byte *
getsyserr(void)
{
	byte * syserrstr;

	syserrstr = PROC.syserrstr;
	if (syserrstr == nil) {
		syserrstr = _syserrstr;
	}
	return syserrstr;
}


intern void
_exit(int code)
{
	syscall(SYS_exit, code, 0, 0);
}


intern int
nanosleep(Timespec *rqtp, Timespec *rmtp)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_nanosleep, (int)rqtp, (int)rmtp, 0);
	return r1;
}


intern void
rerrstr(byte *err, uint n)
{
	byte * syserr;

	syserr = getsyserr();
	if (_errno != EPLAN9)
		strcpy(syserr, strerror(_errno));
	strncpy(err, syserr, n - 1);
}


void
_exits(byte *s)
{
	if ((s == nil) || (*s == 0)) {
		_exit(0);
	}
	_exit(1);
}


int
_umtx_op(void *obj, int op, int val, void *uaddr, void *uaddr2)
{
	int	r1;
	(r1, nil, _errno) = syscall6(SYS__umtx_op, (int)obj, op, val, 0, (int)uaddr, (int)uaddr2);
	return r1;
}


void
abort()
{
	kill(getpid(), SIGABRT);
}


int
close(int fd)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_close, fd, 0, 0);
	return r1;
}


int
create(byte *path, int flags, uint mode)
{
	int	r1;

	flags |= O_CREAT;
	(r1, nil, _errno) = syscall(SYS_open, (int)path, flags, mode);
	return r1;
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


int
getpid()
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_getpid, 0, 0, 0);
	return r1;
}


int
kill(int pid, int sig)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_kill, pid, sig, 0);
	return r1;
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	int	r1;
	(r1, nil, _errno) = syscall9(SYS_mmap, (int)addr, len, prot, flags, fd, offset, 0, 0, 0);
	return (void * )r1;
}


int
open(byte *path, int flags)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_open, (int)path, flags, 0);
	return r1;
}


int
read(int fd, void *buf, int n)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_read, fd, (int)buf, n);
	return r1;
}


int
rendezvous(void *tag, uint value)
{
	int	i, rvalue;
	RendP * p;

	p = nil;

	RendezLock.lock();
	for (i = 0; i < RENDMAX; ++i) {
		if ((p == nil) && (RendezList[i].tag == nil)) {
			p = &RendezList[i];
			continue;
		}
		if (RendezList[i].tag == tag) {
			/* NOTE(anton2920): somebody is waiting, exchange values and wake them up. */
			rvalue = RendezList[i].value;
			RendezList[i].value = value;
			RendezList[i].tag = nil;

			_umtx_op(&RendezList[i].tag, UMTX_OP_WAKE, 1, nil, nil);
			RendezLock.unlock();
			return rvalue;
		}
	}

	/* NOTE(anton2920): going to sleep here. */
	p->tag = tag;
	p->value = value;
	RendezLock.unlock();
	if (_umtx_op(&p->tag, UMTX_OP_WAIT_UINT, (int)tag, nil, nil) < 0) {
		return - 1;
	}
	return p->value;
}


int
sched_yield()
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_yield, 0, 0, 0);
	return r1;
}


int
seek(int filedes, uint offset, int whence)
{
	int	r1;
	(r1, nil, _errno) = syscall6(SYS_lseek, filedes, offset, 0, whence, 0, 0);
	return r1;
}


int
sleep(int msecs)
{
	Timespec tv;
	tv.sec = msecs / 1000;
	tv.nsec = (msecs % 1000) * 1000;
	return nanosleep(&tv, nil);
}


int
write(int fd, void *buf, int n)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_write, fd, (int)buf, n);
	return r1;
}


