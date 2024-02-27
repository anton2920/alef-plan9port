/* From <sys/syscall.h>. */
#define	SYS_rfork	251

#define	UNLOCKED	0x0
#define	LOCKED	0xdeadead

#define	PAUSE	BYTE $0xF3; BYTE $0x90

	TEXT rfork(SB), 1, $16
	MOVL	$LOCKED, spin+12(SP)

	MOVL	flags+0(FP), AX
	MOVL	AX, 4(SP)
	MOVL	$SYS_rfork, AX
	INT	$0x80
	JAE	ok
	CALL	abort(SB)
	MOVL	$0, 0
ok:
	CMPL	AX, $0
	JNE	parent
child:
	PAUSE
	PAUSE
	PAUSE
	PAUSE
	MOVL	$LOCKED, AX
	XCHGL	AX, spin+12(SP)
	CMPL	AX, $0
	JNE	child
	RET
parent:
	MOVL	AX, (SP)
	MOVL	tdb+4(FP), AX
	MOVL	AX, 4(SP)
	MOVL	syserrstr+8(FP), AX
	MOVL	AX, 8(SP)
	CALL	ALEF_setproc(SB)
	MOVL	$UNLOCKED, spin+12(SP)

	/* NOTE(anton2920): caller doesn't care about pid, so return anything that is 'true'. */
	MOVL	$1, AX
	RET
