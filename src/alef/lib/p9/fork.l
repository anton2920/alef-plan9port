#include	<alef.h>
#include	"run.h"

int
fork()
{
	int	ppid, pid;
	Proc * p;

	ppid = getpid();

	pid = _fork();
	if (pid == 0) {
		p = ALEF_getproc(ppid);
		p->pid = getpid();
	}

	return pid;
}


