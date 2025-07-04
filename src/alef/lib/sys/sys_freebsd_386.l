#include	<alef.h>
#include	"sys.h"
#include	"run.h"

#include	<sys/syscall.h>


(int, int, int)	RawSyscall(int, int, int, int);
(int, int, int)	RawSyscall6(int, int, int, int, int, int, int);
(int, int, int)	RawSyscall9(int, int, int, int, int, int, int, int, int, int);


intern
void error(int errno)
{
	byte * syserrstr;

	syserrstr = PROC.syserrstr;
	strncpy(syserrstr, strerror(errno), ERRLEN - 1);
	syserrstr[ERRLEN-1] = '\0';
}


int
_accept(int s, Sockaddr *addr, uint *addrlen)
{
	return syscall(SYS_accept, s, (int)addr, (int)addrlen);
}


int
_bind(int s, Sockaddr *addr, uint addrlen)
{
	return syscall(SYS_bind, s, (int)addr, addrlen);
}


int
_close(int fd)
{
	return syscall(SYS_close, fd, 0, 0);
}


int
_dup(int fd)
{
	return syscall(SYS_dup, fd, 0, 0);
}


void
_exit(int code)
{
	RawSyscall(SYS_exit, code, 0, 0);
}


int
_listen(int s, int backlog)
{
	return syscall(SYS_listen, s, backlog, 0);
}


int
_open(byte *path, int flags, usint mode)
{
	return syscall(SYS_open, (int)path, flags, mode);
}


int
_umtx_op(void *obj, int op, int val, void *uaddr, void *uaddr2)
{
	return syscall6(SYS__umtx_op, (int)obj, op, val, 0, (int)uaddr, (int)uaddr2);
}


int
chdir(byte *path)
{
	return syscall(SYS_chdir, (int)path, 0, 0);
}


int
clock_gettime(int clock_id, Timespec *tp)
{
	return syscall(SYS_clock_gettime, clock_id, (int)tp, 0);
}


int
connect(int s, Sockaddr *addr, uint addrlen)
{
	return syscall(SYS_connect, s, (int)addr, addrlen);
}


int
fchmod(int fd, usint mode)
{
	return syscall(SYS_fchmod, fd, mode, 0);
}


int
fcntl(int fd, int cmd, ...)
{
	return syscall(SYS_fcntl, fd, cmd, (int)...);
}


int
_fork()
{
	return syscall(SYS_fork, 0, 0, 0);
}


int
_fstat(int fd, Stat *sb)
{
	return syscall(SYS_fstat, fd, (int)sb, 0);
}


int
fstatat(int fd, byte *path, Stat *sb, int flag)
{
	return syscall6(SYS_fstatat, fd, (int)path, (int)sb, flag, 0, 0);
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
getdirentries(int fd, byte *buf, uint nbytes, byte *basep)
{
	return syscall6(SYS_getdirentries, fd, (int)buf, nbytes, (int)basep, 0, 0);
}


int
getpid()
{
	int	pid;
	(pid, nil, nil) = RawSyscall(SYS_getpid, 0, 0, 0);
	return pid;
}


int
getppid()
{
	return syscall(SYS_getppid, 0, 0, 0);
}


int
getrusage(int who, Rusage *rusage)
{
	return syscall(SYS_getrusage, who, (int)rusage, 0);
}


int
getsockopt(int s, int level, int optname, void *optval, uint *optlen)
{
	return syscall6(SYS_getsockopt, s, level, optname, (int)optval, (int)optlen, 0);
}


int
ioctl(int fd, uint request, ...)
{
	return syscall(SYS_ioctl, fd, request, (int)...);
}


int
kevent(int kq, Kevent *changelist, int nchanges, Kevent *eventlist, int nevents, Timespec *timeout)
{
	return syscall6(SYS_kevent, kq, (int)changelist, nchanges, (int)eventlist, nevents, (int)timeout);
}


int
kqueue()
{
	return syscall(SYS_kqueue, 0, 0, 0);
}


int
kill(int pid, int sig)
{
	return syscall(SYS_kill, pid, sig, 0);
}


int
lseek(int filedes, uint offset_lo, uint offset_hi, int whence)
{
	return syscall6(SYS_lseek, filedes, offset_lo, offset_hi, whence, 0, 0);
}


int
mkdir(byte *path, usint mode)
{
	return syscall(SYS_mkdir, (int)path, mode, 0);
}


void*
mmap(void *addr, uint len, int prot, int flags, int fd, int offset)
{
	return (void * )syscall9(SYS_mmap, (int)addr, len, prot, flags, fd, offset, 0, 0, 0);
}


int
munmap(void *addr, uint len)
{
	return syscall(SYS_munmap, (int)addr, len, 0);
}


int
nanosleep(Timespec *rqtp, Timespec *rmtp)
{
	return syscall(SYS_nanosleep, (int)rqtp, (int)rmtp, 0);
}


int
read(int fd, void *buf, int n)
{
	return syscall(SYS_read, fd, (int)buf, n);
}


int
rmdir(byte *path)
{
	return syscall(SYS_rmdir, (int)path, 0, 0);
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
sigaction(int sig, Sigaction *act, Sigaction *oact)
{
	return syscall(SYS_sigaction, sig, (int)act, (int)oact);
}


int
setsockopt(int s, int level, int optname, void *optval, uint optlen)
{
	return syscall6(SYS_setsockopt, s, level, optname, (int)optval, optlen, 0);
}


int
shm_open2(byte *path, int flags, usint mode, int shmflags, byte *name)
{
	return syscall6(SYS_shm_open2, (int)path, flags, mode, shmflags, (int)name, 0);
}


int
socket(int domain, int type, int protocol)
{
	return syscall(SYS_socket, domain, type, protocol);
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


int
unlink(byte *path)
{
	return syscall(SYS_unlink, (int)path, 0, 0);
}


