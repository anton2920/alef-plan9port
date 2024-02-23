#!/bin/sh

PROJECT=8a

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

CFLAGS="-m32 -I../../../../386/include -I../../../include -ggdb -O0 -fno-inline"
LDFLAGS="-L../../../lib -lbio -l9 -lm -static"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-parentheses -Wno-dangling-else"

STARTTIME=`date +%s`

case $1 in
	'')
		run yacc -v -y -d a.y
		run test -f y.tab.c && touch y.tab.c

		for file in `echo *.c`; do
			run cc -c $CFLAGS $file
		done

		run cc -o $PROJECT -m32 *.o ../8l/enam.o $LDFLAGS
		run mkdir -p ../../../../386/bin
		run cp $PROJECT ../../../../386/bin
		;;
	clean)
		run rm -f *.o y.tab.[ch] y.output $PROJECT
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
