/*
(int, int, int)
syscall(int, int, int, int);
*/
TEXT syscall(SB), $20
	/* NOTE(anton2920): saving return tuple address. */
	MOVL	AX, 16(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	MOVSL
	MOVSL
	MOVSL
	INT	$0x80
	JAE	ok1
	MOVL	AX, CX
	MOVL	16(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok1:
	MOVL	AX, CX
	MOVL	16(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET


/*
(int, int, int)
syscall6(int, int, int, int, int, int, int);
*/
TEXT	syscall6(SB), $32
	/* NOTE(anton2920): saving return tuple address. */
	MOVL	AX, 28(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	INT	$0x80
	JAE	ok2
	MOVL	AX, CX
	MOVL	28(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok2:
	MOVL	AX, CX
	MOVL	28(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET


/*
(int, int, int)
syscall9(int, int, int, int, int, int, int, int, int, int);
*/
TEXT	syscall9(SB), $44
	/* NOTE(anton2920): saving return tuple address. */
	MOVL	AX, 40(SP)

	/* NOTE(anton2920): using MOVSL as mem-mem MOVs aren't supported otherwise. */
	MOVL	trap+0(FP), AX
	LEAL	a1+4(FP), SI
	LEAL	4(SP), DI
	CLD
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	INT	$0x80
	JAE	ok3
	MOVL	AX, CX
	MOVL	40(SP), AX
	MOVL	CX, 8(AX)
	MOVL	$-1, 4(AX)
	MOVL	$-1, (AX)
	RET
ok3:
	MOVL	AX, CX
	MOVL	40(SP), AX
	MOVL	$0, 8(AX)
	MOVL	DX, 4(AX)
	MOVL	CX, (AX)
	RET
