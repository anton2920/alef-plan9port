#include <alef.h>

/* From <sys/signal.h>. */
#define	SIGABRT	6

void
abort()
{
	kill(getpid(), SIGABRT);
}


