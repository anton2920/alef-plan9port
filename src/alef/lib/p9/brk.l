#include	<alef.h>
#include	"sys.h"


aggr Mem
{
	Lock;
	byte*	addr;
};


intern Mem bloc;

void*
sbrk(uint n)
{
	void * base;

	/* NOTE(anton2920): rounding up to the page boundary. */
	n = (n + (4096 -1)) & ~(4096 -1);

	bloc.lock();
	rescue {
		bloc.unlock();
		return (void * )-1;
	}

	if (bloc.addr == nil) {
		bloc.addr = mmap(nil, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		if (bloc.addr == MAP_FAILED)
			raise;
		base = bloc.addr;
	} else {
		base = mmap(bloc.addr, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_EXCL, -1, 0);
		if (base == MAP_FAILED) {
			raise;
		}
	}

	bloc.addr += n;
	bloc.unlock();

	return base;
}


