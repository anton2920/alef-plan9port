#!/bin/sh

set -e

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
	target src/lib9 $1
	target src/libbio $1
	target src/libmach $1
	target src/cmd/8l $1
	target src/cmd/8a $1
	target src/cmd/ar $1

	target src/alef/8 $1
	target src/alef/lib $1
	target src/alef/test $1
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

echo Done $1 in $((ENDTIME-STARTTIME))s
