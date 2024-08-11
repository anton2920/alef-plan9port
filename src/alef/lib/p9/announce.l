#include <alef.h>

#define _STANDALONE
#include <errno.h>

/* From <netinet/in.h>. */
#define	IPPROTO_TCP		6		/* tcp */

aggr sockaddr_in
{
	byte	len;
	byte	family;
	usint	port;
	uint	addr;
	byte	zero[8];
};


/* From <netinet/tcp.h>. */
#define	TCP_NODELAY	1	/* don't delay send to coalesce packets */


/* From <netinet6/in6.h>. */
aggr in6_addr {
	union {
		byte		__u6_addr8[16];
		usint	__u6_addr16[8];
		uint	__u6_addr32[4];
	} __u6_addr;			/* 128-bit IP6 address */
};


aggr sockaddr_in6 {
	byte	len;	/* length of this struct */
	byte	family;	/* AF_INET6 */
	usint	port;	/* Transport layer port # */
	uint	flowinfo;	/* IP6 flow information */
	in6_addr	addr;	/* IP6 address */
	uint	scope_id;	/* scope zone index */
};


/* From <sys/_sockaddr_storage.h>. */
#define	_SS_MAXSIZE	128
#define	_SS_ALIGNSIZE	(2*sizeof(int))
#define	_SS_PAD1SIZE	(_SS_ALIGNSIZE - sizeof(byte) - sizeof(byte))
#define	_SS_PAD2SIZE	(_SS_MAXSIZE - sizeof(byte) - sizeof(byte) - _SS_PAD1SIZE - _SS_ALIGNSIZE)


aggr sockaddr_storage
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

#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_RAW	3		/* raw-protocol interface */

#define	SOL_SOCKET		0xffff		/* options for socket level */
#define	SO_REUSEADDR	0x00000004	/* allow local address reuse */
#define	SO_TYPE			0x1008		/* get socket type */

/* From <sys/un.h>. */
#define	SUNPATHLEN	104


aggr sockaddr_un
{
	byte	len;	/* sockaddr len including null */
	byte	family;	/* AF_UNIX */
	byte	path[SUNPATHLEN];	/* path name (gag) */
};


#undef sun
#define sun sockun

int
p9dialparse(byte *addr, byte **pnet, byte **punix, void *phost, int *pport);


int
_p9netfd(byte *dir)
{
	int	fd;

	if (strncmp(dir, "/dev/fd/", 8) != 0)
		return - 1;
	fd = strtoi(dir + 8, &dir, 0);
	if (*dir != 0)
		return - 1;
	return fd;
}


intern void
putfd(byte *dir, int fd)
{
	snprint(dir, NETPATHLEN, "/dev/fd/%d", fd);
}


#undef unix
#define unix sockunix

intern int
addrlen(sockaddr_storage *ss)
{
	switch (ss->family) {
	case AF_INET:
		return sizeof(sockaddr_in);
	case AF_INET6:
		return sizeof(sockaddr_in6);
	case AF_UNIX:
		return sizeof(sockaddr_un);
	}
	return 0;
}


/*
 *  announce a network service.
 */
int
announce(byte *addr, byte *dir)
{
	int	proto;
	byte * buf, *unix;
	byte * net;
	int	port, s;
	int	n;
	uint	sn;
	sockaddr_storage ss;
	byte error[ERRLEN];

	buf = strdup(addr);
	if (buf == nil)
		return - 1;

	if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
		free(buf);
		return - 1;
	}
	if (strcmp(net, "tcp") == 0)
		proto = SOCK_STREAM;
	else if (strcmp(net, "udp") == 0)
		proto = SOCK_DGRAM;
	else if (strcmp(net, "unix") == 0)
		goto Unix;
	else {
		werrstr("can only handle tcp, udp, and unix: not %s", net);
		free(buf);
		return - 1;
	}
	free(buf);

	if ((s = socket(ss.family, proto, 0)) < 0)
		return - 1;
	sn = sizeof n;
	if (port && getsockopt(s, SOL_SOCKET, SO_TYPE, (void * ) & n, &sn) >= 0
	     && n == SOCK_STREAM) {
		n = 1;
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (byte * ) & n, sizeof n);
	}
	if (_bind(s, (Sockaddr * ) & ss, addrlen(&ss)) < 0) {
		close(s);
		return - 1;
	}
	if (proto == SOCK_STREAM) {
		_listen(s, 8);
		putfd(dir, s);
	}
	return s;

Unix:
	if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0)
		return - 1;
	if (_bind(s, (Sockaddr * ) & ss, addrlen(&ss)) < 0) {
		rerrstr(error, sizeof error);
		if (strcmp(error, strerror(EADDRINUSE)) == 0) {
			if (connect(s, (Sockaddr * ) & ss, addrlen(&ss)) < 0) {
				rerrstr(error, sizeof error);
				if (strcmp(error, strerror(ECONNREFUSED)) == 0) {
					/* dead socket, so remove it */
					remove(unix);
					close(s);
					if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0)
						return - 1;
					if (_bind(s, (Sockaddr * ) & ss, addrlen(&ss)) >= 0)
						goto Success;
				}
			}
		}
		close(s);
		return - 1;
	}
Success:
	_listen(s, 8);
	putfd(dir, s);
	return s;
}


/*
 *  listen for an incoming call
 */
int
listen(byte *dir, byte *newdir)
{
	int	fd, one;

	if ((fd = _p9netfd(dir)) < 0) {
		werrstr("bad 'directory' in listen: %s", dir);
		return - 1;
	}

	if ((fd = _accept(fd, nil, nil)) < 0)
		return - 1;

	one = 1;
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (byte * ) & one, sizeof one);

	putfd(newdir, fd);
	return fd;
}


/*
 *  accept a call, return an fd to the open data file
 */
int
accept(int, byte *dir)
{
	int	fd;

	if ((fd = _p9netfd(dir)) < 0) {
		werrstr("bad 'directory' in accept");
		return - 1;
	}
	/* need to dup because the listen fd will be closed */
	return _dup(fd);
}


/*
 *  reject a call, tell device the reason for the rejection
 */
int
reject(int, byte *, byte *)
{
	werrstr("not implemented");
	return - 1;
}


