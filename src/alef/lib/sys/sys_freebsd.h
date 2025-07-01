#define	_STANDALONE
#include	<errno.h>


/* From <fcntl.h>. */
#define	O_RDONLY	0x00000		/* open for reading only */
#define	O_NONBLOCK	0x00004		/* no delay */
#define	O_APPEND	0x00008		/* set append mode */
#define	O_CREAT		0x00200		/* create if nonexistent */
#define	O_TRUNC		0x00400		/* truncate to zero length */
#define	O_EXCL		0x00800		/* error if already exists */

#define	O_DIRECT	0x10000

#define	FD_CLOEXEC	1		/* close-on-exec flag */

#define	F_RDLCK		1		/* shared or read lock */
#define	F_UNLCK		2		/* unlock */
#define	F_WRLCK		3		/* exclusive or write lock */

#define	F_SETFL		4		/* set file status flags */
#define	F_SETLK		12		/* set record locking information */

#define	AT_FDCWD				-100
#define	AT_SYMLINK_NOFOLLOW	0x0200	/* Do not follow symbolic links */

aggr Flock
{
	int	start[2];	/* starting offset */
	int	len[2];	/* len = 0 means until end of file */
	int	pid;		/* lock owner */
	sint	type;		/* lock type: read/write, etc. */
	sint	whence;	/* type of start */
	int	sysid;	/* remote system id or zero for local */
};


/* From <netinet/in.h>. */
#define	INADDR_ANY		0
#define	IPPROTO_TCP		6		/* tcp */


/* From <netinet6/in6.h>. */
aggr In6_addr
{
	union {
		byte	__u6_addr8[16];
		usint	__u6_addr16[8];
		uint	__u6_addr32[4];
	} __u6_addr;			/* 128-bit IP6 address */
};


aggr SockaddrIn6
{
	byte	len;	/* length of this struct */
	byte	family;	/* AF_INET6 */
	usint	port;	/* Transport layer port # */
	uint	flowinfo;	/* IP6 flow information */
	In6_addr	addr;	/* IP6 address */
	uint	scope_id;	/* scope zone index */
};


/* From <netinet/tcp.h>. */
#define	TCP_NODELAY	1	/* don't delay send to coalesce packets */


/* From <stdio.h>. */
#define	SEEK_SET		0		/* set file offset to offset */
#define	SEEK_CUR		1	/* set file offset to current plus offset */


/* From <sys/_clock_id.h>. */
#define CLOCK_REALTIME		0


/* From <sys/dirent.h>. */
aggr Dirent
{
	uint	fileno[2];	/* file number of entry */
	int	off[2];	/* directory offset of entry */
	usint	reclen;	/* length of this record */
	byte	type;	/* file type, see below */
	byte	pad0;
	usint	namlen;	/* length of string in name */
	usint	pad1;
#define	MAXNAMLEN	255
	byte	name[MAXNAMLEN + 1];	/* name must be no longer than this */
};


/* From <sys/disk.h>. */
#define	DIOCGMEDIASIZE	_IOC(IOC_OUT, 'd', 129, 8)	/* Get media size in bytes */


/* From <sys/event.h>. */
#define EVFILT_READ		(-1)
#define EVFILT_WRITE		(-2)
#define EVFILT_SIGNAL		(-6)	/* attached to struct proc */
#define EVFILT_TIMER		(-7)	/* timers */
#define EVFILT_USER		(-11)	/* User events */

/* actions */
#define EV_ADD	0x0001		/* add event to kq (implies enable) */
#define EV_DELETE	0x0002		/* delete event from kq */
#define EV_ENABLE	0x0004		/* enable event */
#define EV_DISABLE	0x0008		/* disable event (not reported) */

/* flags */
#define EV_CLEAR	0x0020		/* clear event state after reporting */

/* returned values */
#define EV_EOF		0x8000		/* EOF detected */
#define EV_ERROR	0x4000		/* error, data contains errno */

aggr Kevent
{
	uint	ident;		/* identifier for this event */
	sint	filter;		/* filter for event */
	usint	flags;		/* action flags for kqueue */
	uint	fflags;		/* filter flag value */
	// uint	_;
	int	data[2];		/* filter data value */
	void	*udata;		/* opaque user data identifier */
	uint	ext[8];		/* extensions */
};


/* From <sys/ioccom.h>. */
#define	IOCPARM_SHIFT	13		/* number of bits for ioctl size */
#define	IOCPARM_MASK	((1 << IOCPARM_SHIFT) - 1) /* parameter length mask */

#define	IOC_OUT		0x40000000	/* copy out parameters */

#define	_IOC(inout,group,num,len)	((uint) ((inout) | (((len) & IOCPARM_MASK) << 16) | ((group) << 8) | (num)))


/* From <sys/mman.h>. */
#define	PROT_NONE	0x00
#define	PROT_READ	0x01
#define	PROT_WRITE	0x02

#define	MAP_SHARED	0x0001		/* share changes */
#define	MAP_PRIVATE	0x0002		/* changes are private */
#define	MAP_FIXED	0x0010
#define	MAP_ANON	0x1000
#define	MAP_EXCL	0x4000

#define	MAP_FAILED ((void*)-1)

#define	SHM_ANON		((byte *)1)


/* From <sys/_timespec.h>. */
aggr Timespec
{
	int	sec;
	int	nsec;
};


/* From <sys/_timeval.h>. */
aggr Timeval
{
	int	sec;
	int	usec;
};


/* From <sys/resource.h>. */
#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

aggr Rusage
{
	Timeval	utime;	/* user time used */
	Timeval	stime;	/* system time used */
	int	maxrss;	/* max resident set size */
	int	ixrss;	/* integral shared memory size */
	int	idrss;	/* integral unshared data " */
	int	isrss;		/* integral unshared stack " */
	int	minflt;	/* page reclaims */
	int	majflt;	/* page faults */
	int	nswap;	/* swaps */
	int	inblock;	/* block input operations */
	int	oublock;	/* block output operations */
	int	msgsnd;	/* messages sent */
	int	msgrcv;	/* messages received */
	int	nsignals;	/* signals received */
	int	nvcsw;	/* voluntary context switches */
	int	nivcsw;	/* involuntary " */
};


/* From <sys/_sigset.h>. */
#define	_SIG_WORDS	4

aggr Sigset
{
	uint bits[_SIG_WORDS];
};


/* From <sys/signal.h> */
#define	SIGINT		2	/* interrupt */
#define	SIGABRT		6	/* abort() */
#define	SIGTERM		15	/* software termination signal from kill */

#define	SIG_IGN		(void *)1

#define	SA_ONSTACK	0x0001	/* take signal on signal stack */
#define	SA_RESTART	0x0002	/* restart system call on signal return */
#define	SA_SIGINFO	0x0040	/* signal handler with SA_SIGINFO args */

aggr Sigaction {
	void *handler;
	int	flags;		/* see signal options below */
	Sigset	mask;		/* signal mask to apply */
};


/* From <sys/_Sockaddr_storage.h>. */
#define	_SS_MAXSIZE	128
#define	_SS_ALIGNSIZE	(2*sizeof(int))
#define	_SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof(byte) - sizeof(byte))
#define	_SS_PAD2SIZE	(_SS_MAXSIZE - sizeof(byte) - sizeof(byte) - _SS_PAD1SIZE - _SS_ALIGNSIZE)


aggr Sockaddr_storage
{
	byte	len;		/* address length */
	byte	family;	/* address family */
	byte	pad1[_SS_PAD1SIZE];
	int	align[2];	/* force desired alignment */
	byte	pad2[_SS_PAD2SIZE];
};


/* From <sys/socket.h>. */
#define	AF_UNIX		1		/* standardized name for AF_LOCAL */
#define	AF_INET		2		/* internetwork: UDP, TCP, etc. */
#define	AF_INET6		28		/* IPv6 */

#define	PF_INET		AF_INET

#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */

#define	SOL_SOCKET		0xffff		/* options for socket level */
#define	SO_REUSEADDR	0x00000004	/* allow local address reuse */
#define	SO_BROADCAST	0x00000020	/* permit sending of broadcast msgs */
#define	SO_TYPE			0x1008		/* get socket type */

aggr Sockaddr
{
	byte	len;
	byte	family;
	byte	data[20];
};

aggr SockaddrIn
{
	byte	len;
	byte	family;
	usint	port;
	uint	addr;
	byte	zero[8];
};


/* From <netdb.h>. */
/*
 * Structures returned by network data base library.  All addresses are
 * supplied in host order, and returned in network order (suitable for
 * use in system calls).
 */
aggr Hostent
{
	byte	 * name;	/* official name of host */
	byte	 **aliases;	/* alias list */
	int	addrtype;	/* host address type */
	int	length;	/* length of address */
	byte	 **addr_list;	/* list of addresses from name server */
};

aggr Servent
{
	byte	 * name;	/* official service name */
	byte	 **aliases;	/* alias list */
	int	port;		/* port # */
	byte	 *proto;	/* protocol to use */
};

aggr Addrinfo
{
	int	flags;	/* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
	int	family;	/* AF_xxx */
	int	socktype;	/* SOCK_xxx */
	int	protocol;	/* 0 or IPPROTO_xxx for IPv4 and IPv6 */
	uint addrlen;	/* length of ai_addr */
	byte	 *canonname;	/* canonical name for hostname */
	Sockaddr *addr;	/* binary address */
	Addrinfo *next;	/* next structure in linked list */
};


/* From <sys/stat.h>. */
#define	S_IFMT	 0170000		/* type of file mask */
#define	S_IFLNK	 0120000		/* symbolic link */

#define	S_ISDIR(m)	(((m) & 0170000) == 0040000)	/* directory */
#define	S_ISCHR(m)	(((m) & 0170000) == 0020000)	/* char special */
#define	S_ISBLK(m)	(((m) & 0170000) == 0060000)	/* block special */
#define	S_ISFIFO(m)	(((m) & 0170000) == 0010000)	/* fifo or socket */
#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */
#define	S_ISSOCK(m)	(((m) & 0170000) == 0140000)	/* socket */

aggr Stat
{
	uint	dev[2];	/* inode's device */
	uint	ino[2];	/* inode's number */
	uint	nlink[2];	/* number of hard links */
	usint	mode;	/* inode protection mode */
	sint;
	uint	uid;	/* user ID of the file's owner */
	uint	gid;	/* group ID of the file's group */
	int;
	uint	rdev[2];	/* device type */
	int	atim_ext;
	Timespec	atim;	/* time of last access */
	int	mtim_ext;
	Timespec	mtim;	/* time of last data modification */
	int	ctim_ext;
	Timespec	ctim;	/* time of last file status change */
	int birthtim_ext;
	Timespec	birthtim;	/* time of file creation */
	int	size[2];	/* file size, in bytes */
	int	blocks[2];	/* blocks allocated for file */
	int	blksize;	/* optimal blocksize for I/O */
	uint	flags;	/* user defined flags for file */
	uint	gen[2];	/* file generation number */
	int	spare[20];
};


/* From <sys/umtx.h>. */
#define	UMTX_OP_WAKE		3
#define	UMTX_OP_WAIT_UINT	11


/* From <sys/un.h>. */
#define	SUNPATHLEN	104

aggr Sockaddr_un
{
	byte	len;	/* Sockaddr len including null */
	byte	family;	/* AF_UNIX */
	byte	path[SUNPATHLEN];	/* path name (gag) */
};


byte*	strerror(int);

int	_accept(int, Sockaddr*, uint*);
int	_bind(int, Sockaddr*, uint);
int	_dup(int);
void	_exit(int);
int	_close(int);
int	_listen(int, int);
int	_open(byte*, int, usint);
int	_umtx_op(void*, int, int, void*, void*);
int	clock_gettime(int, Timespec*);
int	connect(int, Sockaddr*, uint);
int	fchmod(int, usint);
int	fcntl(int, int, ...);
int	_fork();
int	_fstat(int, Stat*);
int	fstatat(int, byte*, Stat*, int);
int	ftruncate(int, int);
int	futimes(int, Timeval*);
int	getdirentries(int, byte*, uint, byte*);
int	getrusage(int, Rusage*);
int	getsockopt(int, int, int, void*, uint*);
int	ioctl(int, uint, ...);
int	kill(int, int);
int	kevent(int, Kevent*, int, Kevent*, int, Timespec*);
int	kqueue();
int	lseek(int, uint, uint, int);
int	lstat(byte*, Stat*);
int	mkdir(byte*, usint);
void*	mmap(void*, uint, int, int, int, int);
int	munmap(void*, uint);
int	nanosleep(Timespec*, Timespec*);
int	rmdir(byte*);
int	sched_yield();
int	setsockopt(int, int, int, void*, uint);
int	shm_open2(byte*, int, usint, int, byte*);
int	sigaction(int, Sigaction*, Sigaction*);
int	socket(int, int, int);
int	_stat(byte*, Stat*);
int	syscall(int, int, int, int);
int	syscall6(int, int, int, int, int, int, int);
int	syscall9(int, int, int, int, int, int, int, int, int, int);
int	unlink(byte*);

int	_p9dir(Stat*, Stat*, byte*, Dir*, byte**, byte*);
int	p9dialparse(byte *addr, byte **pnet, byte **punix, void *phost, int *pport);
