#include <alef.h>
#include <sys/syscall.h>
#include "run.h"

/* From <fcntl.h>. */
#define	O_CREAT		0x0200		/* create if nonexistent */

(int, int, int)
RawSyscall(int, int, int, int);
(int, int, int)
RawSyscall6(int, int, int, int, int, int, int);
(int, int, int)
RawSyscall9(int, int, int, int, int, int, int, int, int, int);

byte*	strerror(int);

intern
void error(int errno)
{
	byte * syserrstr;

	syserrstr = PROC.syserrstr;
	strncpy(syserrstr, strerror(errno), ERRLEN - 1);
	syserrstr[ERRLEN-1] = '\0';
}


void
_exit(int code)
{
	syscall(SYS_exit, code, 0, 0);
}


int
_umtx_op(void *obj, int op, int val, void *uaddr, void *uaddr2)
{
	return syscall6(SYS__umtx_op, (int)obj, op, val, 0, (int)uaddr, (int)uaddr2);
}


int
clock_gettime(int clock_id, Timespec *tp)
{
	return syscall(SYS_clock_gettime, clock_id, (int)tp, 0);
}


int
close(int fd)
{
	return syscall(SYS_close, fd, 0, 0);
}


int
create(byte *path, int flags, uint mode)
{
	return syscall(SYS_open, (int)path, flags, mode);
}


int
fchmod(int fd, usint mode)
{
	return syscall(SYS_fchmod, fd, mode, 0);
}


int
fstat(int fd, Stat *sb)
{
	return syscall(SYS_fstat, fd, (int)sb, 0);
}


int
ftruncate(int fd, int length)
{
	return syscall(SYS_ftruncate, fd, length, 0);
}


int
futimes(int fd, Timeval *times)
{
	return syscall(SYS_futimes, fd, (int)times, 0);
}


int
getpid()
{
	int	r1;
	(r1, nil, nil) = RawSyscall(SYS_getpid, 0, 0, 0);
	return r1;
}


int
getrusage(int who, Rusage *rusage)
{
	return syscall(SYS_getrusage, who, (int)rusage, 0);
}


int
ioctl(int fd, uint request, ...)
{
	return syscall(SYS_ioctl, fd, request, (int)...);
}


int
kill(int pid, int sig)
{
	return syscall(SYS_kill, pid, sig, 0);
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	return (void * )syscall9(SYS_mmap, (int)addr, len, prot, flags, fd, offset, 0, 0, 0);
}


int
nanosleep(Timespec *rqtp, Timespec *rmtp)
{
	return syscall(SYS_nanosleep, (int)rqtp, (int)rmtp, 0);
}


int
open(byte *path, int flags)
{
	return syscall(SYS_open, (int)path, flags, 0);
}


int
read(int fd, void *buf, int n)
{
	return syscall(SYS_read, fd, (int)buf, n);
}


int
rfork(int flags)
{
	if ((flags & RFMEM) == RFMEM) {
		werrstr("RFMEM flag is not supported");
		return - 1;
	}
	return syscall(SYS_rfork, flags, 0, 0);
}


int
sched_yield()
{
	return syscall(SYS_yield, 0, 0, 0);
}


int
seek(int filedes, uint offset, int whence)
{
	return syscall6(SYS_lseek, filedes, offset, 0, whence, 0, 0);
}


int
syscall(int trap, int a1, int a2, int a3)
{
	int	r1, errno;
	(r1, nil, errno) = RawSyscall(trap, a1, a2, a3);
	if (r1 < 0) {
		error(errno);
	}
	return r1;
}


int
syscall6(int trap, int a1, int a2, int a3, int a4, int a5, int a6)
{
	int	r1, errno;
	(r1, nil, errno) = RawSyscall6(trap, a1, a2, a3, a4, a5, a6);
	if (r1 < 0) {
		error(errno);
	}
	return r1;
}


int
syscall9(int trap, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
	int	r1, errno;
	(r1, nil, errno) = RawSyscall9(trap, a1, a2, a3, a4, a5, a6, a7, a8, a9);
	if (r1 < 0) {
		error(errno);
	}
	return r1;
}


int
write(int fd, void *buf, int n)
{
	return syscall(SYS_write, fd, (int)buf, n);
}


