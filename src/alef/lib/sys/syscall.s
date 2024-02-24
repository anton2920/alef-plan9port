// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/* TODO(anton2920): return multiple values. */
TEXT Syscall(SB), $0
	MOVL	trap+0(FP), AX	// syscall entry
	// slide args down on top of system call number
	LEAL		a1+4(FP), SI
	LEAL		trap+0(FP), DI
	CLD
	MOVSL
	MOVSL
	MOVSL
	INT	$0x80
	JAE	ok1
	MOVL	$-1, AX
	RET
ok1:
	RET

TEXT	Syscall6(SB), $0
	MOVL	trap+0(FP), AX	// syscall entry
	// slide args down on top of system call number
	LEAL		a1+4(FP), SI
	LEAL		trap+0(FP), DI
	CLD
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	MOVSL
	INT	$0x80
	JAE	ok2
	MOVL	$-1, AX
	RET
ok2:
	RET
