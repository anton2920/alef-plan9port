#include <alef.h>

/* From <netinet/in.h>. */
#define	INADDR_ANY		0
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
#define	SO_BROADCAST	0x00000020	/* permit sending of broadcast msgs */
#define	SO_TYPE			0x1008		/* get socket type */


aggr sockaddr
{
	byte	len;		/* total length */
	byte	family;	/* address family */
	byte	data[14];	/* actually longer; address value */
};


/* From <sys/un.h>. */
#define	SUNPATHLEN	104


aggr sockaddr_un
{
	byte	len;	/* sockaddr len including null */
	byte	family;	/* AF_UNIX */
	byte	path[SUNPATHLEN];	/* path name (gag) */
};


#undef unix
#define unix xunix


int
p9dialparse(byte *addr, byte **pnet, byte **punix, void *phost, int *pport);


intern int
isany(sockaddr_storage *ss)
{
	in6_addr zaddr;

	switch (ss->family) {
	case AF_INET:
		return (((sockaddr_in * )ss)->addr == INADDR_ANY);
	case AF_INET6:
		memset(&zaddr, 0, sizeof zaddr);
		return (memcmp(&((sockaddr_in6 * )ss)->addr, &zaddr, sizeof (in6_addr)) == 0);
	}
	return 0;
}


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


int
dial(byte *addr, byte *local, byte *dir, int *cfdp)
{
	byte * buf;
	byte * net, *unix;
	int	port;
	int	proto;
	uint sn;
	int	n;
	sockaddr_storage ss, ssl;
	int	s;

	if (dir || cfdp) {
		werrstr("cannot handle extra arguments in dial");
		return - 1;
	}

	buf = strdup(addr);
	if (buf == nil)
		return - 1;

	if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
		free(buf);
		return - 1;
	}
	if (strcmp(net, "unix") != 0 && isany(&ss)) {
		werrstr("invalid dial address 0.0.0.0 (aka *)");
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

	if (local) {
		buf = strdup(local);
		if (buf == nil) {
			close(s);
			return - 1;
		}
		if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
badlocal:
			free(buf);
			close(s);
			return - 1;
		}
		if (unix) {
			werrstr("bad local address %s for dial %s", local, addr);
			goto badlocal;
		}
		sn = sizeof n;
		if (port && getsockopt(s, SOL_SOCKET, SO_TYPE, (void * ) & n, &sn) >= 0 && n == SOCK_STREAM) {
			n = 1;
			setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (byte * ) & n, sizeof n);
		}
		if (_bind(s, (sockaddr * ) & ssl, addrlen(&ssl)) < 0)
			goto badlocal;
		free(buf);
	}

	n = 1;
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, &n, sizeof n);
	if (!isany(&ss)) {
		if (connect(s, (sockaddr * ) & ss, addrlen(&ss)) < 0) {
			close(s);
			return - 1;
		}
	}
	if (proto == SOCK_STREAM) {
		int	one;
		one = 1;
		setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (byte * ) & one, sizeof one);
	}
	return s;

Unix:
	if (local) {
		werrstr("local address not supported on unix network");
		free(buf);
		return - 1;
	}
	/* Allow regular files in addition to Unix sockets. */
	if ((s = open(unix, ORDWR)) >= 0) {
		free(buf);
		return s;
	}
	free(buf);
	if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0) {
		werrstr("socket: %r");
		return - 1;
	}
	if (connect(s, (sockaddr * ) & ss, addrlen(&ss)) < 0) {
		werrstr("connect %s: %r", ((sockaddr_un * ) & ss)->path);
		close(s);
		return - 1;
	}
	return s;
}


