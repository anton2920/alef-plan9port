#!/bin/sh

PROJECT=test/ug

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
	run ../../../../bin/8al -I../../../../include/alef $ALEFFILES
	run ../../../../bin/8l -L../../../../lib/alef -o $NAME $OFILES -lbio -lA
	run brandelf -t FreeBSD $NAME
}

STARTTIME=`date +%s`

case $1 in
	'')
		for test in `seq 1 20`; do
			prog $test "$test.l"
		done
		;;
	clean)
		run rm -f *.8 `seq 1 20`
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
