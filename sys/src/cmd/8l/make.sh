#!/bin/sh

PROJECT=8l

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

CFLAGS="-I../../../../386/include -I../../../include -I../ld -I../8l -ggdb -O0 -fno-inline"
LDFLAGS="-L../../../lib -lbio -l9 -lm -static"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-parentheses -Wno-dangling-else -Wno-constant-conversion -Wno-switch"

STARTTIME=`date +%s`

case $1 in
	'')
		run sh mkenam

		for file in `echo ../ld/*.c *.c`; do
			run cc -c $CFLAGS $file
		done

		run cc -o $PROJECT *.o $LDFLAGS
		run mkdir -p ../../../../386/bin
		run cp $PROJECT ../../../../386/bin
		;;
	clean)
		run rm -f *.o $PROJECT enam.c
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
