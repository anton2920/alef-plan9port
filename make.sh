#!/bin/sh

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

target()
{
	run cd $1
	./make.sh $VERBOSITYFLAGS $2
}

STARTTIME=`date +%s`

case $1 in
	'')
		target sys/src/libc $1

		# Build 8c and 8l
		# Build alef
		;;
	clean)
		target sys/src/libc $1
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $1 in $((ENDTIME-STARTTIME))s