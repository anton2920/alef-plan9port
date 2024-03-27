/*
 * This routine converts time as follows.
 * The epoch is 0000 Jan 1 1970 GMT.
 * The argument time is in seconds since then.
 * The localtime(t) entry returns a pointer to an array
 * containing
 *
 *	seconds (0-59)
 *	minutes (0-59)
 *	hours (0-23)
 *	day of month (1-31)
 *	month (0-11)
 *	year-1970
 *	weekday (0-6, Sun is 0)
 *	day of the year
 *	daylight savings flag
 *
 * The routine gets the daylight savings time from the environment.
 *
 * asctime(tvec))
 * where tvec is produced by localtime
 * returns a ptr to a byteacter string
 * that has the ascii time in the form
 *
 *	                            \\
 *	Thu Jan 01 00:00:00 GMT 1970n0
 *	012345678901234567890123456789
 *	0	  1	    2
 *
 * ctime(t) just calls localtime, then asctime.
 */

#include <alef.h>

aggr Tinfo
{
	int	t;
	int	tzoff;
	int	dlflag;
	byte	 * zone;
};


intern
byte	dmsize[12] =
{
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};


/*
 * The following table is used for 1974 and 1975 and
 * gives the day number of the first day after the Sunday of the
 * change.
 */

intern	int	dysize(int);
intern	void	ct_numb(byte*, int);

int	zonelookuptinfo(Tinfo*, int);
int	zonetinfo(Tinfo*, int);
void	zonedump(int fd);

byte*
ctime(int t)
{
	return asctime(localtime(t));
}


Tm*
localtime(int tim)
{
	Tinfo ti;
	Tm * ct;

	if (zonelookuptinfo(&ti, tim) != -1) {
		ct = gmtime(tim + ti.tzoff);
		strncpy(ct->zone, ti.zone, sizeof ct->zone - 1);
		ct->zone[sizeof ct->zone-1] = 0;
		ct->tzoff = ti.tzoff;
		return ct;
	}
	return gmtime(tim);
}


intern Tm xtime;

Tm*
gmtime(int tim)
{
	int	d0, d1;
	int	hms, day;

	/*
	 * break initial number into days
	 */
	hms = tim % 86400;
	day = tim / 86400;
	if (hms < 0) {
		hms += 86400;
		day -= 1;
	}

	/*
	 * generate hours:minutes:seconds
	 */
	xtime.sec = hms % 60;
	d1 = hms / 60;
	xtime.min = d1 % 60;
	d1 /= 60;
	xtime.hour = d1;

	/*
	 * day is the day number.
	 * generate day of the week.
	 * The addend is 4 mod 7 (1/1/1970 was Thursday)
	 */

	xtime.wday = (day + 7340036) % 7;

	/*
	 * year number
	 */
	if (day >= 0)
		for (d1 = 70; day >= dysize(d1); d1++)
			day -= dysize(d1);
	else
		for (d1 = 70; day < 0; d1--)
			day += dysize(d1 - 1);
	xtime.year = d1;
	xtime.yday = d0 = day;

	/*
	 * generate month
	 */

	if (dysize(d1) == 366)
		dmsize[1] = 29;
	for (d1 = 0; d0 >= dmsize[d1]; d1++)
		d0 -= dmsize[d1];
	dmsize[1] = 28;
	xtime.mday = d0 + 1;
	xtime.mon = d1;
	strcpy(xtime.zone, "GMT");
	return & xtime;
}


intern byte cbuf[30];

byte*
asctime(Tm *t)
{
	byte * ncp;

	strcpy(cbuf, "Thu Jan 01 00:00:00 GMT 1970\n");
	ncp = &"SunMonTueWedThuFriSat"[t->wday*3];
	cbuf[0] = *ncp++;
	cbuf[1] = *ncp++;
	cbuf[2] = *ncp;
	ncp = &"JanFebMarAprMayJunJulAugSepOctNovDec"[t->mon*3];
	cbuf[4] = *ncp++;
	cbuf[5] = *ncp++;
	cbuf[6] = *ncp;
	ct_numb(cbuf + 8, t->mday);
	ct_numb(cbuf + 11, t->hour + 100);
	ct_numb(cbuf + 14, t->min + 100);
	ct_numb(cbuf + 17, t->sec + 100);
	ncp = t->zone;
	cbuf[20] = *ncp++;
	cbuf[21] = *ncp++;
	cbuf[22] = *ncp;
	if (t->year >= 100) {
		cbuf[24] = '2';
		cbuf[25] = '0';
	}
	ct_numb(cbuf + 26, t->year + 100);
	return cbuf;
}


intern
int
dysize(int y)
{

	if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
		return 366;
	return 365;
}


intern
void
ct_numb(byte *cp, int n)
{

	cp[0] = ' ';
	if (n >= 10)
		cp[0] = (n / 10) % 10 + '0';
	cp[1] = n % 10 + '0';
}


aggr Zoneinfo {
	int	timecnt;		/* # of transition times */
	int	typecnt;		/* # of local time types */
	int	bytecnt;		/* # of byteacters of time zone abbreviation strings */

	byte * ptime;
	byte * ptype;
	byte * ptt;
	byte * pzone;
};


intern Zoneinfo z;
intern byte *tzdata;

intern
byte*
readtzfile(byte *file)
{
	byte * p;
	int	fd;
	Dir * d;

	fd = open(file, OREAD);
	if (fd < 0)
		return nil;
	d = dirfstat(fd);
	if (d == nil)
		return nil;
	check d->length[1] == 0, "cannot allocate more than INT_MAX bytes";
	p = malloc(d->length[0]);
	if (p != nil)
		readn(fd, p, d->length[0]);
	free(d);
	close(fd);
	return p;
}


intern byte	*zonefile;
void
tzfile(byte *f)
{
	if (tzdata != nil) {
		free(tzdata);
		tzdata = nil;
	}
	z.timecnt = 0;
	zonefile = f;
}


intern
int
get4(byte *p)
{
	return (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
}


enum {
	TTinfosz	 = 4 + 1 + 1,
};

intern
int
parsehead(void)
{
	byte * p;
	int	ver;

	ver = tzdata[4];
	if (ver != 0)
		if (ver != '2')
			return - 1;

	p = tzdata + 4 + 1 + 15;

	z.timecnt = get4(p + 3 * 4);
	z.typecnt = get4(p + 4 * 4);
	if (z.typecnt == 0)
		return - 1;
	z.bytecnt = get4(p + 5 * 4);
	z.ptime = p + 6 * 4;
	z.ptype = z.ptime + z.timecnt * 4;
	z.ptt = z.ptype + z.timecnt;
	z.pzone = z.ptt + z.typecnt * TTinfosz;
	return 0;
}


intern
void
ttinfo(Tinfo *ti, int tti)
{
	byte * p;
	int	i;

	i = z.ptype[tti];
	check i < z.typecnt;

	p = z.ptt + i * TTinfosz;
	ti->tzoff = get4(p);
	ti->dlflag = p[4];
	check p[5] < z.bytecnt;

	ti->zone = (byte * )z.pzone + p[5];
}


intern
void
readtimezone(void)
{
	byte	 * tmp;

	z.timecnt = 0;
	if (zonefile == nil) {
		if ((tmp = getenv("timezone")) != nil) {
			tzdata = readtzfile(tmp);
			free(tmp);
			goto havedata;
		}
		zonefile = "/etc/localtime";
	}
	tzdata = readtzfile(zonefile);
	if (tzdata == nil)
		return;

havedata:
	if (strncmp("TZif", (byte * )tzdata, 4) != 0)
		goto errfree;

	if (parsehead() == -1) {
errfree:
		free(tzdata);
		tzdata = nil;
		z.timecnt = 0;
		return;
	}
}


intern
int
gett4(byte *p)
{
	int	l;

	l = get4(p);
	if (l < 0)
		return 0;
	return l;
}


int
zonetinfo(Tinfo *ti, int i)
{
	if (tzdata == nil)
		readtimezone();
	if (i < 0 || i >= z.timecnt)
		return - 1;
	ti->t = gett4(z.ptime + 4 * i);
	ttinfo(ti, i);
	return i;
}


int
zonelookuptinfo(Tinfo *ti, int t)
{
	byte * p;
	int	i;
	int	oldtt, tt;

	if (tzdata == nil)
		readtimezone();
	oldtt = 0;
	p = z.ptime;
	for (i = 0; i < z.timecnt; i++) {
		tt = gett4(p);
		if (t < tt)
			break;
		oldtt = tt;
		p += 4;
	}
	if (i > 0) {
		ttinfo(ti, i - 1);
		ti->t = oldtt;
		return i - 1;
	}
	return - 1;
}


void
zonedump(int fd)
{
	int	i;
	byte * p;
	int	t;
	Tinfo ti;

	if (tzdata == nil)
		readtimezone();
	p = z.ptime;
	for (i = 0; i < z.timecnt; i++) {
		t = gett4(p);
		ttinfo(&ti, i);
		fprint(fd, "%ld\t%d\t%d\t%s\n", (int)t, ti.tzoff, ti.dlflag, ti.zone);
		p += 4;
	}
}


