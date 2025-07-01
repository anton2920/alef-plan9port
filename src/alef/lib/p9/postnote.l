#include	<alef.h>
#include	"sys.h"


/*
 * System defined signals.
 */
#define	SIGHUP		1	/* hangup */
#define	SIGINT		2	/* interrupt */
#define	SIGQUIT		3	/* quit */
#define	SIGILL		4	/* illegal instr. (not reset when caught) */
#define	SIGTRAP		5	/* trace trap (not reset when caught) */
#define	SIGABRT		6	/* abort() */
#define	SIGIOT		SIGABRT	/* compatibility */
#define	SIGEMT		7	/* EMT instruction */
#define	SIGFPE		8	/* floating point exception */
#define	SIGKILL		9	/* kill (cannot be caught or ignored) */
#define	SIGBUS		10	/* bus error */
#define	SIGSEGV		11	/* segmentation violation */
#define	SIGSYS		12	/* non-existent system call invoked */
#define	SIGPIPE		13	/* write on a pipe with no one to read it */
#define	SIGALRM		14	/* alarm clock */
#define	SIGTERM		15	/* software termination signal from kill */
#define	SIGURG		16	/* urgent condition on IO channel */
#define	SIGSTOP		17	/* sendable stop signal not from tty */
#define	SIGTSTP		18	/* stop signal from tty */
#define	SIGCONT		19	/* continue a stopped process */
#define	SIGCHLD		20	/* to parent on child stop or exit */
#define	SIGTTIN		21	/* to readers pgrp upon background tty read */
#define	SIGTTOU		22	/* like TTIN if (tp->t_local&LTOSTOP) */
#define	SIGIO		23	/* input/output possible signal */
#define	SIGXCPU		24	/* exceeded CPU time limit */
#define	SIGXFSZ		25	/* exceeded file size limit */
#define	SIGVTALRM	26	/* virtual time alarm */
#define	SIGPROF		27	/* profiling time alarm */
#define	SIGWINCH	28	/* window size changes */
#define	SIGINFO		29	/* information request */
#define	SIGUSR1		30	/* user defined signal 1 */
#define	SIGUSR2		31	/* user defined signal 2 */
#define	SIGTHR		32	/* reserved by thread library. */
#define	SIGLWP		SIGTHR
#define	SIGLIBRT	33	/* reserved by real-time library. */

aggr _tab {
	int	sig;
	byte	 * str;
};


intern _tab tab[] = {
	{ SIGHUP,  		"hangup" },
	{ SIGINT,  		"interrupt" },
	{ SIGQUIT,  		"quit" },
	{ SIGILL,  		"sys: illegal instruction" },
	{ SIGTRAP,  		"sys: breakpoint" },
	{ SIGABRT,  		"sys: abort" },
	{ SIGEMT,  		"sys: emulate instruction executed" },
	{ SIGFPE,  		"sys: fp: trap" },
	{ SIGKILL,  		"sys: kill" },
	{ SIGBUS,  		"sys: bus error" },
	{ SIGSEGV,  		"sys: segmentation violation" },
	{ SIGALRM,  		"alarm" },
	{ SIGTERM,  		"kill" },
	{ SIGURG,  		"sys: urgent condition on socket" },
	{ SIGSTOP,  		"sys: stop" },
	{ SIGTSTP,  		"sys: tstp" },
	{ SIGCONT,  		"sys: cont" },
	{ SIGCHLD,  		"sys: child" },
	{ SIGTTIN,  		"sys: ttin" },
	{ SIGTTOU,  		"sys: ttou" },
	{ SIGIO,  		"sys: i/o possible on fd" },
	{ SIGXCPU,  		"sys: cpu time limit exceeded" },
	{ SIGXFSZ,  		"sys: file size limit exceeded" },
	{ SIGVTALRM,  	"sys: virtual time alarm" },
	{ SIGPROF,  		"sys: profiling timer alarm" },
	{ SIGWINCH,  	"sys: window size change" },
	{ SIGINFO,  		"sys: status request" },
	{ SIGUSR1,  		"sys: usr1" },
	{ SIGUSR2,  		"sys: usr2" },
	{ SIGPIPE,  		"sys: write on closed pipe" },
};


intern int
_p9strsig(byte *s)
{
	int	i;

	for (i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
		if (strcmp(s, tab[i].str) == 0)
			return tab[i].sig;
	return 0;
}


int
postnote(int who, int pid, byte *msg)
{
	int	sig;

	sig = _p9strsig(msg);
	if (sig == 0) {
		werrstr("unknown note");
		return -1;
	}

	if (pid <= 0) {
		werrstr("bad pid in postnote");
		return -1;
	}

	switch (who) {
	default:
		werrstr("bad who in postnote");
		return -1;
	case PNPROC:
		return kill(pid, sig);
	case PNGROUP:
		return kill(-pid, sig);
	}
}


