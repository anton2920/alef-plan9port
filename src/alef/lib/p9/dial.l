#include	<alef.h>
#include	"sys.h"

#undef unix
#define unix xunix


intern int
isany(Sockaddr_storage *ss)
{
	In6_addr zaddr;

	switch (ss->family) {
	case AF_INET:
		return (((SockaddrIn *)ss)->addr == INADDR_ANY);
	case AF_INET6:
		memset(&zaddr, 0, sizeof zaddr);
		return (memcmp(&((SockaddrIn6 *)ss)->addr, &zaddr, sizeof (In6_addr)) == 0);
	}
	return 0;
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


int
dial(byte *addr, byte *local, byte *dir, int *cfdp)
{
	byte *buf;
	byte *net, *unix;
	int	port;
	int	proto;
	uint sn;
	int	n;
	Sockaddr_storage ss, ssl;
	int	s;

	if (dir || cfdp) {
		werrstr("cannot handle extra arguments in dial");
		return -1;
	}

	buf = strdup(addr);
	if (buf == nil)
		return -1;

	if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
		free(buf);
		return -1;
	}
	if (strcmp(net, "unix") != 0 && isany(&ss)) {
		werrstr("invalid dial address 0.0.0.0 (aka *)");
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

	if (local) {
		buf = strdup(local);
		if (buf == nil) {
			close(s);
			return -1;
		}
		if (p9dialparse(buf, &net, &unix, &ss, &port) < 0) {
badlocal:
			free(buf);
			close(s);
			return -1;
		}
		if (unix) {
			werrstr("bad local address %s for dial %s", local, addr);
			goto badlocal;
		}
		sn = sizeof n;
		if (port && getsockopt(s, SOL_SOCKET, SO_TYPE, (void *)&n, &sn) >= 0 && n == SOCK_STREAM) {
			n = 1;
			setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (byte *)&n, sizeof n);
		}
		if (_bind(s, (Sockaddr *)&ssl, addrlen(&ssl)) < 0)
			goto badlocal;
		free(buf);
	}

	n = 1;
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, &n, sizeof n);
	if (!isany(&ss)) {
		if (connect(s, (Sockaddr *)&ss, addrlen(&ss)) < 0) {
			close(s);
			return -1;
		}
	}
	if (proto == SOCK_STREAM) {
		int	one;
		one = 1;
		setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (byte *)&one, sizeof one);
	}
	return s;

Unix:
	if (local) {
		werrstr("local address not supported on unix network");
		free(buf);
		return -1;
	}
	/* Allow regular files in addition to Unix sockets. */
	if ((s = open(unix, ORDWR)) >= 0) {
		free(buf);
		return s;
	}
	free(buf);
	if ((s = socket(ss.family, SOCK_STREAM, 0)) < 0) {
		werrstr("socket: %r");
		return -1;
	}
	if (connect(s, (Sockaddr *)&ss, addrlen(&ss)) < 0) {
		werrstr("connect %s: %r", ((Sockaddr_un * ) & ss)->path);
		close(s);
		return -1;
	}
	return s;
}
