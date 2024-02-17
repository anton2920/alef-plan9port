#!/bin/sh

PROJECT=alef

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

	# TODO(anton2920): remove after all source files are here.
	chmod +x ./make.sh

	./make.sh $VERBOSITYFLAGS $2

	cd $OLDPWD
}

targets()
{
	target sys/src/lib9 $1
	target sys/src/libbio $1
	target sys/src/libmach $1
	target sys/src/cmd/cc $1
	target sys/src/cmd/8l $1
	target sys/src/cmd/8a $1
}

STARTTIME=`date +%s`

case $1 in
	'')
		targets $1

		# Build 8c and 8l
		# Build alef
		;;
	clean)
		targets $1

		run rm -rf sys/lib
		run rm -rf 386/bin
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
