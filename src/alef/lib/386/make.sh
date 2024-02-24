#!/bin/sh

PROJECT=libA

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
		for file in `echo *.l ../port/*.l ../p9/*.l`; do
			run ../../../../../386/bin/8al -I../../../../include/alef $file
		done
		cp ../port/crypt.8.save crypt.8

		for file in `echo *.s`; do
			run ../../../../../386/bin/8a $file
		done

		run ../../../../../386/bin/ar rsc $PROJECT.a *.8
		run mkdir -p ../../../../../386/lib/alef
		run cp $PROJECT.a ../../../../../386/lib/alef
		;;
	clean)
		run rm -f *.o $PROJECT.a
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
