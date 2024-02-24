#define SYS_brk        17

TEXT brk_(SB), $0
	MOVL	$SYS_brk, AX
	MOVL	break+0(FP), DI
	INT	$0x80
	MOVL	AX, ret+4(FP)
