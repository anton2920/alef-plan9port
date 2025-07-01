#include	<alef.h>
#include	"run.h"


int
errstr(byte *err, uint n)
{
	byte tmp[ERRLEN];
	byte *syserr;

	strncpy(tmp, err, n -1);
	rerrstr(err, n);
	syserr = PROC.syserrstr;
	strncpy(syserr, tmp, ERRLEN -1);
	return 0;
}


void
rerrstr(byte *err, uint n)
{
	byte *syserr;

	syserr = PROC.syserrstr;
	strncpy(err, syserr, n -1);
}


