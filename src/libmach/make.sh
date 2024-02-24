#!/bin/sh

PROJECT=libmach

VERBOSITY=0
VERBOSITYFLAGS=""
while test "$1" = "-v"; do
	VERBOSITY=$((VERBOSITY+1))
	VERBOSITYFLAGS="$VERBOSITYFLAGS -v"
	shift
done

run()
{
	if test $VERBOSITY -gt 1; then echo "$@"; fi
	"$@" || exit 1
}

CFLAGS=" -m32 -I../../include -ggdb -O0 -fno-inline"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-gnu-designator -Wno-sizeof-pointer-memaccess -Wno-dangling-else -Wno-parentheses -Wno-shift-negative-value -Wno-return-type"

STARTTIME=`date +%s`

case $1 in
	'')
		run cc -c $CFLAGS *.c
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
