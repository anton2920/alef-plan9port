#!/bin/sh

PROJECT=lib9

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

CFLAGS=" -m32 -I../../../386/include -I../../include -ggdb -O0 -fno-inline"

STARTTIME=`date +%s`

case $1 in
	'')
		# libc
		for file in `echo _p9dir.c _exits.c argv0.c atoi.c await.c cleanname.c create.c dirfstat.c dirfwstat.c dirstat.c dirwstat.c dup.c errstr.c exec.c execl.c exitcode.c exits.c getenv.c getfields.c getwd.c main.c nan.c nulldir.c open.c readn.c seek.c strecpy.c sysfatal.c time.c tokenize.c`; do
			run cc -c $CFLAGS $file
		done
		run cc -c $CFLAGS -DGOOS='"freebsd"' -DGOARCH='"386"' -DGOROOT='"stub"' -DGOVERSION='"v1-anton2920"' goos.c

		# fmt
		for file in `echo dofmt.c fltfmt.c fmt.c fmtfd.c fmtfdflush.c fmtlocale.c fmtnull.c fmtprint.c fmtquote.c fmtrune.c fmtstr.c fmtvprint.c fprint.c nan64.c print.c seprint.c smprint.c snprint.c sprint.c strtod.c vfprint.c vseprint.c vsmprint.c vsnprint.c charstod.c pow10.c`; do
			run cc -c $CFLAGS -DPLAN9PORT -Ifmt fmt/$file
		done
		run cc -c $CFLAGS -DPLAN9PORT -Ifmt fmtlock2.c

		# utf
		for file in `echo rune.c utfecpy.c utflen.c utfnlen.c utfrrune.c utfrune.c utfutf.c runetype.c`; do
			run cc -c $CFLAGS utf/$file
		done

		run ar rsc $PROJECT.a *.o
		run mkdir -p ../../lib
		run cp $PROJECT.a ../../lib
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
