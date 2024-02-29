#include <alef.h>
#include <sys/syscall.h>

#define _STANDALONE
#include <errno.h>

#include "run.h"

/* From <fcntl.h>. */
#define	O_CREAT		0x0200		/* create if nonexistent */

/* From <sys/signal.h>. */
#define	SIGABRT	6

/* From <sys/ipc.h>. */
#define	IPC_CREAT	001000
#define	IPC_NOWAIT	004000
#define	IPC_R		000400
#define	IPC_W		000200
#define	IPC_RMID	0

aggr Sembuf
{
	usint	num;
	sint	op;
	sint	flg;
};


aggr Timespec
{
	int	sec;
	int	nsec;
};


Lock	RendezLock;

enum
{
	EPLAN9 = 0x19283745,
};

int	_errno;
intern byte	_syserrstr[ERRLEN];

byte*	strerror(int);

int	semctl(int, int, int);
int	semget(int, int, int);
int	semop(int, Sembuf*, uint);


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
rendezvous(void *a, uint b)
{
	Sembuf ops;
	int	id;

	check b == 0, "rendezvous only supports exchanging zeros";

	RendezLock.lock();
	id = semget((int)a, 1, IPC_R | IPC_W);
	if (id >= 0) {
		RendezLock.unlock();
		return semctl(id, 0, IPC_RMID);
	}

	id = semget((int)a, 1, IPC_CREAT | IPC_R | IPC_W);
	RendezLock.unlock();

	ops.num = 0;
	ops.op = -1;
	ops.flg = 0;
	return semop(id, &ops, 1);
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
semctl(int semid, int semnum, int cmd)
{
	int	r1;
	(r1, nil, _errno) = syscall6(SYS___semctl, semid, semnum, cmd, 0, 0, 0);
	return r1;
}


int
semget(int key, int nsems, int flag)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_semget, key, nsems, flag);
	return r1;
}


int
semop(int semid, Sembuf *array, uint nops)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_semop, semid, (int)array, nops);
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


