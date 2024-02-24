#!/bin/sh

PROJECT=ar

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

CFLAGS="-m32 -I../../../include -ggdb -O0 -fno-inline"
LDFLAGS="-L../../../lib -l9 -lbio  -lmach -static"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-parentheses -Wno-int-conversion"

STARTTIME=`date +%s`

case $1 in
	'')
		run cc -o $PROJECT $CFLAGS *.c $LDFLAGS
		run mkdir -p ../../../bin
		run cp $PROJECT ../../../bin
		;;
	clean)
		run rm -f *.o $PROJECT
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
