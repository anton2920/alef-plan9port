#include	<alef.h>
#include	"run.h"

intern Lock	block;

aggr Parrend
{
	int	nproc;
	Rendez;
};

int
ALEF_pfork(int n, byte **stack, Parrend *b)
{
	Task *t;
	Tdb *tdb;
	byte *st, *syserrstr;
	int *semap;
	int id, nid, sema;

	memset(b, 0, sizeof(Parrend));
	b->nproc = n;

	id = 0;
	while(n) {
		st = ALEFalloc(ALEFstack+sizeof(Task)+sizeof(Tdb)+ERRLEN, 0);
		*stack++ = st+ALEFstack;

		memset(st, 0, sizeof(Task)+sizeof(Tdb));
		t = (Task*)st;
		t->stack = st;
		st += sizeof(Task);

		tdb = (Tdb*)st;
		st += sizeof(Tdb);
		tdb->ntask = 1;
		tdb->runhd = nil;
		tdb->ctask = t;
		t->tdb = tdb;

		syserrstr = st;
		syserrstr[0] = '\0';

		sema = 1;
		/*
		 * Using &sema is required to prevent the optimiser
		 * from removing the assignment to sema
		 */
		semap = &sema;
		nid = id;
		if(rfork(ALEFrfflag) == 0) {
			ALEF_setproc(getpid(), tdb, syserrstr);
			*semap = 0;
			return nid;
		}
		while(*semap)
			;
		n--;
		id++;
	}
	*stack = nil;
	return id;
}

void
ALEF_pdone(Parrend *b, byte **stv)
{
	byte *p;

	while(b->nproc)
		b->Sleep(&(void*)b->nproc, 0);

	while(*stv) {
		p = *stv++;
		p -= ALEFstack;
		free(p);
	}
}

void
ALEF_pexit(Parrend *b)
{
	int x;

	block.lock();
	x = --b->nproc;
	block.unlock();
	if(x == 0)
		b->Wakeup();
	_exits(nil);
}
