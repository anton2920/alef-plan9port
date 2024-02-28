#include <alef.h>

/* See <sys/mman.h>. */
#define	PROT_READ	0x01
#define	PROT_WRITE	0x02

#define	MAP_SHARED	0x0001		/* share changes */
#define	MAP_PRIVATE	0x0002		/* changes are private */
#define	MAP_FIXED	0x0010
#define	MAP_ANON	0x1000
#define	MAP_EXCL	0x4000

#define MAP_FAILED ((void*)-1)


aggr Mem
{
	Lock;
	byte * 	addr;
};


intern Mem bloc;

void*
sbrk(uint n)
{
	void * base;

	/* NOTE(anton2920): rounding up to the page boundary. */
	n = (n + (4096 - 1)) & ~(4096 - 1);

	bloc.lock();
	rescue {
		bloc.unlock();
		return (void * ) - 1;
	}

	if (bloc.addr == nil) {
		bloc.addr = mmap(nil, n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
		if (bloc.addr == MAP_FAILED)
			raise;
		base = bloc.addr;
	} else {
		base = mmap(bloc.addr, n, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON | MAP_FIXED | MAP_EXCL, -1, 0);
		if (base == MAP_FAILED) {
			raise;
		}
	}

	bloc.addr += n;
	bloc.unlock();

	return base;
}


