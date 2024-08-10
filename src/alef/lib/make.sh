#!/bin/sh

set -e

PROJECT=lib

VERBOSITY=0
VERBOSITYFLAGS=""
while test "$1" = "-v"; do
	VERBOSITY=$((VERBOSITY+1))
	VERBOSITYFLAGS="$VERBOSITYFLAGS -v"
	shift
done

OLDPWD=`pwd`

run()
{
	if test $VERBOSITY -gt 0; then echo "$@"; fi
	"$@" || exit 1
}

target()
{
	run cd $1
	./make.sh $VERBOSITYFLAGS $2
	cd $OLDPWD
}

targets()
{
	target rt $1
	target libbio $1
}

STARTTIME=`date +%s`

case $1 in
	'')
		targets $1
		;;
	clean)
		targets $1
		run rm -rf bin lib
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
