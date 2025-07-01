#include	<alef.h>
#include	"sys.h"

#undef sun
#define sun sockun

#undef unix
#define unix sockunix


int
_p9netfd(byte *dir)
{
	int	fd;

	if (strncmp(dir, "/dev/fd/", 8) != 0)
		return -1;
	fd = strtoi(dir + 8, &dir, 0);
	if (*dir != 0)
		return -1;
	return fd;
}


intern void
putfd(byte *dir, int fd)
{
	snprint(dir, NETPATHLEN, "/dev/fd/%d", fd);
}


intern int
addrlen(Sockaddr_storage *ss)
{
	switch (ss->family) {
	case AF_INET:
		return sizeof(SockaddrIn);
	case AF_INET6:
		return sizeof(SockaddrIn6);
	case AF_UNIX:
		return sizeof(Sockaddr_un);
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
	byte *buf, *unix;
	byte *net;
	int	port, s;
	int	n;
	uint	sn;
	Sockaddr_storage ss;
	byte error[ERRLEN];

	buf = strdup(addr);
	if (buf == nil)
		return -1;

	if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
		free(buf);
		return -1;
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
		return -1;
	}
	free(buf);

	if ((s = socket(ss.family, proto, 0)) < 0)
		return -1;
	sn = sizeof n;
	if (port && getsockopt(s, SOL_SOCKET, SO_TYPE, (void *)&n, &sn) >= 0 && n == SOCK_STREAM) {
		n = 1;
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (byte *)&n, sizeof n);
	}
	if (_bind(s, (Sockaddr *)&ss, addrlen(&ss)) < 0) {
		close(s);
		return -1;
	}
	if (proto == SOCK_STREAM) {
		_listen(s, 8);
		putfd(dir, s);
	}
	return s;

Unix:
	if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0)
		return -1;
	if (_bind(s, (Sockaddr *)&ss, addrlen(&ss)) < 0) {
		rerrstr(error, sizeof error);
		if (strcmp(error, strerror(EADDRINUSE)) == 0) {
			if (connect(s, (Sockaddr *)&ss, addrlen(&ss)) < 0) {
				rerrstr(error, sizeof error);
				if (strcmp(error, strerror(ECONNREFUSED)) == 0) {
					/* dead socket, so remove it */
					remove(unix);
					close(s);
					if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0)
						return -1;
					if (_bind(s, (Sockaddr *)&ss, addrlen(&ss)) >= 0)
						goto Success;
				}
			}
		}
		close(s);
		return -1;
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
		return -1;
	}

	if ((fd = _accept(fd, nil, nil)) < 0)
		return -1;

	one = 1;
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (byte *)&one, sizeof one);

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
		return -1;
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
	return -1;
}
