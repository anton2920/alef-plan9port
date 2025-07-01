#include	<alef.h>
#include	"sys.h"

#define	nelem(x)	(sizeof(x)/sizeof((x)[0]))
#define	CLASS(p)	((*(ubyte*)(p))>>6)


intern byte	*nets[] = { "tcp", "udp", nil };

aggr NetTable
{
	byte	 *net;
	byte	 *service;
	int	port;
};

intern NetTable porttbl[] = {
	{ "tcp", 	"9fs", 	564 },
	{ "tcp", 	"whoami", 	565 },
	{ "tcp", 	"guard", 	566 },
	{ "tcp", 	"ticket", 	567 },
	{ "tcp", 	"exportfs", 	17007 },
	{ "tcp", 	"rexexec", 	17009 },
	{ "tcp", 	"ncpu", 	17010 },
	{ "tcp", 	"cpu", 	17013 },
	{ "tcp", 	"venti", 	17034 },
	{ "tcp", 	"wiki", 	17035 },
	{ "tcp", 	"secstore", 	5356 },
	{ "udp", 	"dns", 	53 },
	{ "tcp", 	"dns", 	53 },
};


intern usint
htons(usint port)
{
	return ((port & 0xFF) << 8) | ((port & 0xFF00) >> 8);
}


intern usint
ntohs(usint port)
{
	return htons(port);
}


intern Hostent *
gethostbyname(byte *)
{
	werrstr("not implemented");
	return nil;
}


intern Servent *
getservbyname(byte *, byte *)
{
	werrstr("not implemented");
	return nil;
}


intern int
getaddrinfo(byte *, byte *, Addrinfo *, Addrinfo **res)
{
	werrstr("not implemented");
	*res = nil;
	return -1;
}


intern int
setport(Sockaddr_storage *ss, int port)
{
	switch (ss->family) {
	case AF_INET:
		((SockaddrIn * )ss)->port = htons(port);
		break;
	case AF_INET6:
		((SockaddrIn6 * )ss)->port = htons(port);
		break;
	default:
		errstr("unknown protocol family %d", ss->family);
		return -1;
	}
	return 0;
}


int
p9dialparse(byte *addr, byte **pnet, byte **punix, void *phost, int *pport)
{
	byte	 * net, *host, *port, *e;
	int	i;
	Servent * se;
	Hostent * he;
	Sockaddr_storage * ss;
	Addrinfo * result;

	ss = phost;

	memset(ss, 0, sizeof * ss);

	*punix = nil;
	net = addr;
	if ((host = strchr(net, '!')) == nil) {
		werrstr("malformed address");
		return -1;
	}
	*host++ = 0;
	if ((port = strchr(host, '!')) == nil) {
		if (strcmp(net, "unix") == 0 || strcmp(net, "net") == 0) {
Unix:
			if (strlen(host) + 1 > sizeof ((Sockaddr_un *)ss)->path) {
				werrstr("unix socket name too long");
				return -1;
			}
			*punix = host;
			*pnet = "unix";
			ss->family = AF_UNIX;
			strcpy(((Sockaddr_un *)ss)->path, host);
			*pport = 0;
			return 0;
		}
		werrstr("malformed address");
		return -1;
	}
	*port++ = 0;

	if (*host == 0) {
		werrstr("malformed address (empty host)");
		return -1;
	}
	if (*port == 0) {
		werrstr("malformed address (empty port)");
		return -1;
	}

	if (strcmp(net, "unix") == 0)
		goto Unix;

	if (strcmp(net, "tcp") != 0 && strcmp(net, "udp") != 0 && strcmp(net, "net") != 0) {
		werrstr("bad network %s!%s!%s", net, host, port);
		return -1;
	}

	/* translate host */
	if (strcmp(host, "*") == 0) {
		ss->family = AF_INET6;
		memset(&((SockaddrIn6 * )ss)->addr, 0, sizeof(((SockaddrIn6 * )ss)->addr));
	} else if ((he = gethostbyname(host)) != nil && he->addr_list[0] != nil) {
		ss->family = he->addrtype;
		switch (ss->family) {
		case AF_INET:
			((SockaddrIn *)ss)->addr = *(uint *) * (he->addr_list);
			break;
		case AF_INET6:
			((SockaddrIn6 *)ss)->addr = *(In6_addr *) * (he->addr_list);
			break;
		default:
			errstr("unknown protocol family %d", ss->family);
			return -1;
		}
	} else if (getaddrinfo(host, nil, nil, &result) == 0) {
		switch (result->family) {
		case AF_INET:
			memmove((SockaddrIn *)ss, result->addr, result->addrlen);
			break;
		case AF_INET6:
			memmove((SockaddrIn6 *)ss, result->addr, result->addrlen);
			break;
		default:
			errstr("unknown protocol family %d", ss->family);
			return -1;
		}
	} else {
		werrstr("unknown host %s", host);
		return -1;
	}

	/* translate network and port; should return list rather than first */
	if (strcmp(net, "net") == 0) {
		for (i = 0; nets[i]; i++) {
			if ((se = getservbyname(port, nets[i])) != nil) {
				*pnet = nets[i];
				*pport = ntohs(se->port);
				return setport(ss, *pport);
			}
		}
	}

	for (i = 0; i < nelem(porttbl); i++) {
		if (strcmp(net, "net") == 0 || strcmp(porttbl[i].net, net) == 0)
			if (strcmp(porttbl[i].service, port) == 0) {
				*pnet = porttbl[i].net;
				*pport = porttbl[i].port;
				return setport(ss, *pport);
			}
	}

	if (strcmp(net, "net") == 0) {
		werrstr("unknown service net!*!%s", port);
		return -1;
	}

	if (strcmp(net, "tcp") != 0 && strcmp(net, "udp") != 0) {
		werrstr("unknown network %s", net);
		return -1;
	}

	*pnet = net;
	i = strtoi(port, &e, 0);
	if (*e == 0) {
		*pport = i;
		return setport(ss, *pport);
	}

	if ((se = getservbyname(port, net)) != nil) {
		*pport = ntohs(se->port);
		return setport(ss, *pport);
	}
	werrstr("unknown service %s!*!%s", net, port);
	return -1;
}
