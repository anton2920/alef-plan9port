#!/bin/sh

PROJECT=libbio

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

STARTTIME=`date +%s`

case $1 in
	'')
		run ../../../../bin/8al -w -I../../../../include/alef *.l
		run ../../../../bin/ar $VERBOSITYFLAGS u $PROJECT.a *.8
		run mkdir -p ../../../../lib/alef
		run cp $PROJECT.a ../../../../lib/alef
		;;
	clean)
		run rm -f *.8 $PROJECT.a
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
