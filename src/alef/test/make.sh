#!/bin/sh

PROJECT=test

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

prog()
{
	NAME=$1
	shift
	ALEFFILES=$@
	OFILES=""
	for file in `echo $ALEFFILES`; do
		OFILES="$OFILES `echo $file | sed s/\.l/.8/`"
	done
	run ../../../bin/8al -I../386 -I../../../include/alef $ALEFFILES
	run ../../../bin/8l -L../../../lib/alef -o $NAME $OFILES -lbio -lA
	run brandelf -t FreeBSD $NAME
}

STARTTIME=`date +%s`

case $1 in
	'')
		prog pstest "ps.l pstest.l"
		prog sieve "sieve.l"
		prog test "test.l"
		prog test2 "test2.l"
		prog test3 "test3.l"
		prog test4 "test4.l"
		prog test6 "test6.l"
		prog test7 "test7.l"
		prog test12 "test12.l"
		prog test13 "test13.l"
		prog test14 "test14.l"
		prog test15 "test15.l"
		prog test16 "test16.l"
		prog test17 "test17.l"
		prog test18 "test18.l stack.l"
		prog test19 "test19.l"
		prog tstbio "tstbio.l"
		;;
	clean)
		run rm -f *.8 `ls | grep test[0-9]*$` sieve tstbio xx*
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
