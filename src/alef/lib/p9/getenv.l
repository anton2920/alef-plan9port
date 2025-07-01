#include	<alef.h>


extern byte**	environ;


byte*
getenv(byte *name)
{
	byte *env;
	int	n;
	int	i;

	n = strlen(name);
	for (i = 0; environ[i] != nil; ++i) {
		env = environ[i];

		if (memcmp(env, name, n) == 0) {
			return &env[n] + 1;
		}
	}

	return nil;
}
