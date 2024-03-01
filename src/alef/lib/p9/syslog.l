#include <alef.h>

intern byte	syslogname[NAMELEN];
intern byte	sysname[NAMELEN];
intern int		logfd = -1;
intern int		consfd = -1;
intern QLock	sysloglock;

/*
 * Print
 *  sysname: time: mesg
 * on /sys/log/logname.
 * If cons or log file can't be opened, print on the system console, too.
 */
void
syslog(int, byte *, byte *, ...)
{
	werrstr("not implemented");
	return;
}


