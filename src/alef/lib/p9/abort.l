#include	<alef.h>
#include	"sys.h"


void
abort()
{
	kill(getpid(), SIGABRT);
}
