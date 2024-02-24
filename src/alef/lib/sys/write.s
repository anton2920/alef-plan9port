#define SYS_write       4

TEXT write(SB), $0
	MOVL	$SYS_write, AX
	MOVL	fd+0(FP), DI
	MOVL	buf+4(FP), SI
	MOVL	len+8(FP), DX
	INT	$0x80
	MOVL	AX, ret+12(FP)
	RET
