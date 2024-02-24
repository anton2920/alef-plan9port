#!/bin/sh

PROJECT=8al

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

CFLAGS="-m32 -I../../../include -I../../cmd/8l -I../port -I. -ggdb -O0 -fno-inline"
LDFLAGS="-L../../../lib -lbio -l9 -lm -static"

# TODO(anton2920): silence warnings for later.
CFLAGS="$CFLAGS -Wno-gnu-designator -Wno-implicit-int -Wno-incompatible-function-pointer-types -Wno-parentheses -Wno-switch-bool -Wno-comment -Wno-implicit-const-int-float-conversion -Wno-incompatible-pointer-types"

STARTTIME=`date +%s`

case $1 in
	'')
		run yacc -v -y -d ../port/parl.y

		for file in `echo *.c ../port/*.c`; do
			run cc -c $CFLAGS $file
		done

		run cc -o $PROJECT -m32 *.o $LDFLAGS
		run mkdir -p ../../../bin
		run cp $PROJECT ../../../bin
		;;
	clean)
		run rm -f *.[oS] y.tab.? y.debug y.output $PROJECT ../port/y.tab.? ../port/*.[oS]
		;;
	*)
		echo "Target is not supported!"
		;;
esac

ENDTIME=`date +%s`

echo Done $PROJECT $1 in $((ENDTIME-STARTTIME))s
