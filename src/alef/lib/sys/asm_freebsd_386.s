/* From <sys/syscall.h>. */
#define	SYS_rfork	251

#define	UNLOCKED	0x0
#define	LOCKED	0xdeadead

#define	PAUSE	BYTE $0xF3; BYTE $0x90


/* int	ProcNew(int, Tdb*, byte*) */
	TEXT ProcNew(SB), 1, $16
	MOVL	$LOCKED, spin+-4(SP)

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
	XCHGL	AX, spin+-4(SP)
	CMPL	AX, $UNLOCKED
	JNE	child
	MOVL	$0, AX
	RET
parent:
	MOVL	AX, (SP)
	MOVL	tdb+4(FP), AX
	MOVL	AX, 4(SP)
	MOVL	syserrstr+8(FP), AX
	MOVL	AX, 8(SP)
	CALL	ALEF_setproc(SB)
	MOVL	$UNLOCKED, spin+-4(SP)

	/* NOTE(anton2920): caller doesn't care about pid, so return anything that is 'true'. */
	MOVL	$1, AX
	RET


/* (int, int, int)	RawSyscall(int, int, int, int); */
	TEXT RawSyscall(SB), 1, $20
	/* Saving return tuple address. */
	MOVL	AX, ret+-4(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	MOVL	$3, CX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	REP; MOVSL
	INT	$0x80
	JAE	ok1
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok1:
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET


/* (int, int, int)	RawSyscall6(int, int, int, int, int, int, int); */
	TEXT	RawSyscall6(SB), 1, $32
	/* Saving return tuple address. */
	MOVL	AX, ret+-4(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	MOVL	$6, CX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	REP; MOVSL
	INT	$0x80
	JAE	ok2
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok2:
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET


/* (int, int, int)	RawSyscall9(int, int, int, int, int, int, int, int, int, int); */
	TEXT	RawSyscall9(SB), 1, $44
	/* Saving return tuple address. */
	MOVL	AX, ret+-4(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	MOVL	$9, CX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	REP; MOVSL
	INT	$0x80
	JAE	ok3
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok3:
	MOVL	AX, CX
	MOVL	ret+-4(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET
