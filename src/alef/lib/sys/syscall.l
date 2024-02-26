#include <alef.h>
#include <sys/syscall.h>

#define _STANDALONE
#include <errno.h>

#include "run.h"

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

	syserrstr = ALEF_getproc(getpid())->syserrstr;
	if (syserrstr == nil) {
		syserrstr = _syserrstr;
	}
	return syserrstr;
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
	syscall(SYS_kill, getpid(), SIGABRT, 0);
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


int
getpid()
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_getpid, 0, 0, 0);
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
rendezvous(void *a, uint b)
{
	Sembuf ops;
	int	id;

	check b == 0, "rendezvous only supports exchanging zeros";

	RendezLock.lock();
	id = semget((int)a, 1, IPC_R | IPC_W);
	if (id > 0) {
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
rfork(int flags)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_rfork, flags, 0, 0);
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
write(int fd, void *buf, int n)
{
	int	r1;
	(r1, nil, _errno) = syscall(SYS_write, fd, (int)buf, n);
	return r1;
}


