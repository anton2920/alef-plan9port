#!/bin/sh

PROJECT=cc

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

CFLAGS="-I../../../../386/include -I../../../include -ggdb -O0 -fno-inline"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-parentheses -Wno-comment"

STARTTIME=`date +%s`

case $1 in
	'')
		run yacc -v -y -d cc.y
		run test -f y.tab.c && touch y.tab.c

		for file in `echo y.tab.c lex.c mac.c dcl.c acid.c pickle.c bits.c com.c scon.c funct.c sub.c com64.c dpchk.c omachcap.c`; do
			run cc -c $CFLAGS $file
		done

		run ar rsc $PROJECT.a *.o
		run mkdir -p ../../lib
		run cp $PROJECT.a ../../../lib
		;;
	clean)
		run rm -f *.o y.tab.[ch] y.output $PROJECT.a
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $1 in $((ENDTIME-STARTTIME))s
