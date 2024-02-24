#include <alef.h>

/* See <sys/mman.h>. */
#define PROT_READ	0x01
#define PROT_WRITE	0x02

#define MAP_PRIVATE	0x0002
#define MAP_FIXED	0x0010
#define MAP_ANON	0x1000
#define MAP_EXCL	0x4000

#define MAP_FAILED ((void*)-1)


aggr Mem
{
	Lock;
	byte * 	addr;
};


intern Mem bloc;

void*	mmap(void*, uint, int, int, int, int);

void*
sbrk(uint n)
{
	void * base;

	n = n + (n & (4096 - 1));

	bloc.lock();
	rescue {
		bloc.unlock();
		return (void * ) - 1;
	}

	if (bloc.addr == nil) {
		bloc.addr = mmap(nil, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		if (bloc.addr == MAP_FAILED)
			raise;
		base = bloc.addr;
	} else {
		base = mmap(bloc.addr, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_EXCL, -1, 0);
		if (base == MAP_FAILED)
			raise;
	}

	bloc.addr += n;
	bloc.unlock();

	return base;
}


