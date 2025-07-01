#include	<alef.h>
#include	"sys.h"

#define	RENDMAX	(1 << 5)


aggr RendP
{
	void * tag;
	uint	value;
};


intern RendP	RendezList[RENDMAX];
intern Lock	RendezLock;


/* TODO(anton2920): make it work even in separate address spaces (i.e. after fork(2)). */
int
rendezvous(void *tag, uint value)
{
	int	i, rvalue;
	RendP *p;

	p = nil;

	RendezLock.lock();
	for (i = 0; i < RENDMAX; ++i) {
		if ((p == nil) && (RendezList[i].tag == nil)) {
			p = &RendezList[i];
			continue;
		}
		if (RendezList[i].tag == tag) {
			/* Somebody is waiting, exchange values and wake them up. */
			rvalue = RendezList[i].value;
			RendezList[i].value = value;
			RendezList[i].tag = nil;

			_umtx_op(&RendezList[i].tag, UMTX_OP_WAKE, 1, nil, nil);
			RendezLock.unlock();
			return rvalue;
		}
	}

	/* Going to sleep here. */
	p->tag = tag;
	p->value = value;
	RendezLock.unlock();
	if (_umtx_op(&p->tag, UMTX_OP_WAIT_UINT, (int)tag, nil, nil) < 0) {
		return -1;
	}
	return p->value;
}


