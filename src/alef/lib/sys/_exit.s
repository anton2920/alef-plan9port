#define SYS_exit        1

TEXT _exit(SB), $0
	MOVL	$SYS_exit, AX
	MOVL	ret+0(FP), DI
	INT	$0x80
	MOVL	$0x0, 0x0
