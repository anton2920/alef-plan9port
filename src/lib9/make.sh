#!/bin/sh

PROJECT=lib9

VERBOSITY=0
VERBOSITYFLAGS=""
while test "$1" = "-v"; do
	VERBOSITY=$((VERBOSITY+1))
	VERBOSITYFLAGS="$VERBOSITYFLAGS -v"
	shift
done

run()
{
	if test $VERBOSITY -gt 0; then echo "$@"; fi
	"$@" || exit 1
}

CFLAGS=" -m32 -I../../include -ggdb -O0 -fno-inline"

STARTTIME=`date +%s`

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-parentheses"

case $1 in
	'')
		for file in `echo *.c fmt/*.c utf/*.c`; do
			run cc -c $CFLAGS $file
		done

		run ar rsc $PROJECT.a *.o
		run mkdir -p ../../lib
		run cp $PROJECT.a ../../lib
		;;
	clean)
		run rm -f *.o $PROJECT.a
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
