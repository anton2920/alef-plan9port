#include <u.h>
#include <libc.h>
#include <bio.h>
#include <ctype.h>
#define Extern extern
#include "parl.h"
#include "globl.h"

extern int regmap[D_CS];

void
zeroregm(Node *n)
{
	instruction(AMOVL, con(0), n);
}

/* do we need to load the address of a lint? */
int
laddr(Node *n, int a)
{
	switch(n->type) {
	case ONAME:
		if(a)
			return 1;
		return !(n->t->class == External || n->t->class == Global || n->t->class == Internal);

	case OCONST:
	case OREGISTER:
	case OINDREG:
		return 1;
	}
	return 0;
}

long
hi64v(Node *n)
{
	/* TODO(anton2920): result will be incorrect on big-endian machine. */
	return (long)((uvlong)n->lival>>32) & ~0L;
}

long
lo64v(Node *n)
{
	/* TODO(anton2920): result will be incorrect on big-endian machine. */
	return (long)(n->lival) & ~0L;
}

Node *
hi64(Node *n)
{
	return con(hi64v(n));
}

Node *
lo64(Node *n)
{
	return con(lo64v(n));
}

static Node *
anonreg(void)
{
	Node *n;

	n = an(OREGISTER, ZeroN, ZeroN);
	n->reg = D_NONE;
	n->t = builtype[TINT];
	return n;
}

static Node *
regpair(Node *n, Node *t)
{
	Node *r;

	if(n != ZeroN && n->type == OREGPAIR)
		return n;
	r = an(OREGPAIR, anonreg(), anonreg());
	if(n != ZeroN)
		r->t = n->t;
	else
		r->t = t->t;
	return r;
}

static void
evacaxdx(Node *r)
{
	Node nod1, nod2;

	if(r->reg == D_AX || r->reg == D_DX) {
		regmap[D_AX]++;
		regmap[D_DX]++;
		/*
		 * this is just an optim that should
		 * check for spill
		 */
		r->t = builtype[TUINT];
		reg(&nod1, r, ZeroN);
		// nodreg(&nod2, ZeroN, r->reg);
		instruction(AMOVL, &nod2, &nod1);
		regfree(r);
		r->reg = nod1.reg;
		regmap[D_AX]--;
		regmap[D_DX]--;
	}
}

/* lazy instantiation of register pair */
static int
instpair(Node *n, Node *l)
{
	int r;

	r = 0;
	if(n->left->reg == D_NONE) {
		if(l != ZeroN) {
			n->left->reg = l->reg;
			r = 1;
		}
		else
			reg(n->left, n->left, ZeroN);
	}
	if(n->right->reg == D_NONE)
		reg(n->right, n->right, ZeroN);
	return r;
}

static void
zapreg(Node *n)
{
	if(n->reg != D_NONE) {
		//prtree(n, "zapreg");
		regfree(n);
		n->reg = D_NONE;
	}
}

static void
freepair(Node *n)
{
	regfree(n->left);
	regfree(n->right);
}

/* n is not OREGPAIR, nn is */
void
loadpair(Node *n, Node *nn)
{
	Node nod;

	instpair(nn, ZeroN);
	if(n->type == OCONST) {
		instruction(AMOVL, lo64(n), nn->left);
		n->ival += Machint;
		instruction(AMOVL, hi64(n), nn->right);
		n->ival -= Machint;
		return;
	}
	if(!laddr(n, 0)) {
		/* steal the right register for the laddr */
		nod = regnode;
		nod.reg = nn->right->reg;
		lcgen(n, &nod);
		n = &nod;
		regind(n, n);
		n->ival = 0;
	}
	instruction(AMOVL, n, nn->left);
	n->ival += Machint;
	instruction(AMOVL, n, nn->right);
	n->ival -= Machint;
}

/* n is OREGPAIR, nn is not */
static void
storepair(Node *n, Node *nn, int f)
{
	Node nod;

	if(!laddr(nn, 0)) {
		reglcgen(&nod, nn, ZeroN);
		nn = &nod;
	}
	instruction(AMOVL, n->left, nn);
	nn->ival += Machint;
	instruction(AMOVL, n->right, nn);
	nn->ival -= Machint;
	if(nn == &nod)
		regfree(&nod);
	if(f)
		freepair(n);
}

enum
{
/* 4 only, see WW */
	WNONEQ	= 0,
	WCONST,
	WADDR,
	WHARD,
};

static int
whatof(Node *n, int a)
{
	if(n->type == OCONST)
		return WCONST;
	return !laddr(n, a) ? WHARD : WADDR;
}

/* can upgrade an extern to addr for AND */
static int
reduxv(Node *n)
{
	return lo64v(n) == 0 || hi64v(n) == 0;
}

int
cond(int op)
{
	switch(op) {
	case OCAND:
	case OCOR:
	case ONOT:
		return 1;

	case OEQ:
	case ONEQ:
	case OLEQ:
	case OLT:
	case OGEQ:
	case OGT:
	case OHI:
	case OHS:
	case OLO:
	case OLS:
		return 1;
	}
	return 0;
}

/*
 * for a func operand call it and then return
 * the safe node
 */
static Node *
vfunc(Node *n, Node *nn)
{
	Node *t;

	if(n->type != OFUNC)
		return n;
	t = an(0, ZeroN, ZeroN);
	if(nn == ZeroN || nn == nodret)
		nn = n;
	regsalloc(t, nn);
	sugen(n, t, 8);
	return t;
}

/* try to steal a reg */
static int
getreg(Node **np, Node *t, int r)
{
	Node *n, *p;

	n = *np;
	if(n->reg == r) {
		p = an(0, ZeroN, ZeroN);
		reg(p, n, ZeroN);
		instruction(AMOVL, n, p);
		*t = *n;
		*np = p;
		return 1;
	}
	return 0;
}

static Node *
snarfreg(Node *n, Node *t, int r, Node *d, Node *c)
{
	if(n == ZeroN || n->t != OREGPAIR || (!getreg(&n->left, t, r) && !getreg(&n->right, t, r))) {
		/*
		if(nodreg(t, ZeroN, r)) {
			reg(c, d, ZeroN);
			instruction(AMOVL, t, c);
			regmap[r]++;
			return c;
		}
		*/
		regmap[r]++;
	}
	return ZeroN;
}

enum
{
	Vstart	= Nrops,

	Vgo,
	Vamv,
	Vmv,
	Vzero,
	Vop,
	Vopx,
	Vins,
	Vins0,
	Vinsl,
	Vinsr,
	Vinsla,
	Vinsra,
	Vinsx,
	Vmul,
	Vshll,
	VT,
	VF,
	V_l_lo_f,
	V_l_hi_f,
	V_l_lo_t,
	V_l_hi_t,
	V_l_lo_u,
	V_l_hi_u,
	V_r_lo_f,
	V_r_hi_f,
	V_r_lo_t,
	V_r_hi_t,
	V_r_lo_u,
	V_r_hi_u,
	Vspazz,
	Vend,

	V_T0,
	V_T1,
	V_F0,
	V_F1,

	V_a0,
	V_a1,
	V_f0,
	V_f1,

	V_p0,
	V_p1,
	V_p2,
	V_p3,
	V_p4,

	V_s0,
	V_s1,
	V_s2,
	V_s3,
	V_s4,

	C00,
	C01,
	C31,
	C32,

	O_l_lo,
	O_l_hi,
	O_r_lo,
	O_r_hi,
	O_t_lo,
	O_t_hi,
	O_l,
	O_r,
	O_l_rp,
	O_r_rp,
	O_t_rp,
	O_r0,
	O_r1,
	O_ZeroNop,

	O_a0,
	O_a1,

	V_C0,
	V_C1,

	V_S0,
	V_S1,

	VOPS	= 5,
	VLEN	= 5,
	VARGS	= 2,

	S00	= 0,
	Sc0,
	Sc1,
	Sc2,
	Sac3,
	Sac4,
	S10,

	SAgen	= 0,
	SAclo,
	SAc32,
	SAchi,
	SAdgen,
	SAdclo,
	SAdc32,
	SAdchi,

	B0c	= 0,
	Bca,
	Bac,

	T0i	= 0,
	Tii,

	Bop0	= 0,
	Bop1,
};

/*
 * _testv:
 * 	CMPL	lo,$0
 * 	JNE	true
 * 	CMPL	hi,$0
 * 	JNE	true
 * 	GOTO	false
 * false:
 * 	GOTO	code
 * true:
 * 	GOTO	patchme
 * code:
 */

static uchar	testi[][VLEN] =
{
	{Vop, ONEQ, O_l_lo, C00},
	{V_s0, Vop, ONEQ, O_l_hi, C00},
	{V_s1, Vgo, V_s2, Vgo, V_s3},
	{VF, V_p0, V_p1, VT, V_p2},
	{Vgo, V_p3},
	{VT, V_p0, V_p1, VF, V_p2},
	{Vend},
};

/* shift left general case */
static uchar	shll00[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vinsl, ASHLL, O_r, O_l_rp},
	{Vins, ASHLL, O_r, O_l_lo, Vgo},
	{V_p0, V_s0},
	{Vins, ASHLL, O_r, O_l_lo},
	{Vins, AMOVL, O_l_lo, O_l_hi},
	{Vzero, O_l_lo, V_p0, Vend},
};

/* shift left rp, const < 32 */
static uchar	shllc0[][VLEN] =
{
	{Vinsl, ASHLL, O_r, O_l_rp},
	{Vshll, O_r, O_l_lo, Vend},
};

/* shift left rp, const == 32 */
static uchar	shllc1[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_l_hi},
	{Vzero, O_l_lo, Vend},
};

/* shift left rp, const > 32 */
static uchar	shllc2[][VLEN] =
{
	{Vshll, O_r, O_l_lo},
	{Vins, AMOVL, O_l_lo, O_l_hi},
	{Vzero, O_l_lo, Vend},
};

/* shift left addr, const == 32 */
static uchar	shllac3[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{Vzero, O_t_lo, Vend},
};

/* shift left addr, const > 32 */
static uchar	shllac4[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{Vshll, O_r, O_t_hi},
	{Vzero, O_t_lo, Vend},
};

/* shift left of constant */
static uchar	shll10[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsl, ASHLL, O_r, O_t_rp},
	{Vins, ASHLL, O_r, O_t_lo, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{V_l_lo_t, Vins, ASHLL, O_r, O_t_hi},
	{Vzero, O_t_lo, V_p0, Vend},
};

static uchar	(*shlltab[])[VLEN] =
{
	shll00,
	shllc0,
	shllc1,
	shllc2,
	shllac3,
	shllac4,
	shll10,
};

/* shift right general case */
static uchar	shrl00[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vinsr, ASHRL, O_r, O_l_rp},
	{Vins, O_a0, O_r, O_l_hi, Vgo},
	{V_p0, V_s0},
	{Vins, O_a0, O_r, O_l_hi},
	{Vins, AMOVL, O_l_hi, O_l_lo},
	{V_T1, Vzero, O_l_hi},
	{V_F1, Vins, ASARL, C31, O_l_hi},
	{V_p0, Vend},
};

/* shift right rp, const < 32 */
static uchar	shrlc0[][VLEN] =
{
	{Vinsr, ASHRL, O_r, O_l_rp},
	{Vins, O_a0, O_r, O_l_hi, Vend},
};

/* shift right rp, const == 32 */
static uchar	shrlc1[][VLEN] =
{
	{Vins, AMOVL, O_l_hi, O_l_lo},
	{V_T1, Vzero, O_l_hi},
	{V_F1, Vins, ASARL, C31, O_l_hi},
	{Vend},
};

/* shift right rp, const > 32 */
static uchar	shrlc2[][VLEN] =
{
	{Vins, O_a0, O_r, O_l_hi},
	{Vins, AMOVL, O_l_hi, O_l_lo},
	{V_T1, Vzero, O_l_hi},
	{V_F1, Vins, ASARL, C31, O_l_hi},
	{Vend},
};

/* shift right addr, const == 32 */
static uchar	shrlac3[][VLEN] =
{
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{V_T1, Vzero, O_t_hi},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{Vend},
};

/* shift right addr, const > 32 */
static uchar	shrlac4[][VLEN] =
{
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{Vins, O_a0, O_r, O_t_lo},
	{V_T1, Vzero, O_t_hi},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{Vend},
};

/* shift right of constant */
static uchar	shrl10[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsr, ASHRL, O_r, O_t_rp},
	{Vins, O_a0, O_r, O_t_hi, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{V_l_hi_t, Vins, O_a0, O_r, O_t_lo},
	{V_l_hi_u, V_S1},
	{V_T1, Vzero, O_t_hi, V_p0},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{Vend},
};

static uchar	(*shrltab[])[VLEN] =
{
	shrl00,
	shrlc0,
	shrlc1,
	shrlc2,
	shrlac3,
	shrlac4,
	shrl10,
};

/* shift asop left general case */
static uchar	asshllgen[][VLEN] =
{
	{V_a0, V_a1},
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_r0},
	{Vins, AMOVL, O_l_hi, O_r1},
	{Vinsla, ASHLL, O_r, O_r0},
	{Vins, ASHLL, O_r, O_r0},
	{Vins, AMOVL, O_r1, O_l_hi},
	{Vins, AMOVL, O_r0, O_l_lo, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vzero, O_l_lo},
	{Vins, ASHLL, O_r, O_r0},
	{Vins, AMOVL, O_r0, O_l_hi, V_p0},
	{V_f0, V_f1, Vend},
};

/* shift asop left, const < 32 */
static uchar	asshllclo[][VLEN] =
{
	{V_a0, V_a1},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vins, AMOVL, O_l_hi, O_r1},
	{Vinsla, ASHLL, O_r, O_r0},
	{Vshll, O_r, O_r0},
	{Vins, AMOVL, O_r1, O_l_hi},
	{Vins, AMOVL, O_r0, O_l_lo},
	{V_f0, V_f1, Vend},
};

/* shift asop left, const == 32 */
static uchar	asshllc32[][VLEN] =
{
	{V_a0},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vzero, O_l_lo},
	{Vins, AMOVL, O_r0, O_l_hi},
	{V_f0, Vend},
};

/* shift asop left, const > 32 */
static uchar	asshllchi[][VLEN] =
{
	{V_a0},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vzero, O_l_lo},
	{Vshll, O_r, O_r0},
	{Vins, AMOVL, O_r0, O_l_hi},
	{V_f0, Vend},
};

/* shift asop dest left general case */
static uchar	asdshllgen[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsl, ASHLL, O_r, O_t_rp},
	{Vins, ASHLL, O_r, O_t_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{Vzero, O_l_lo},
	{Vins, ASHLL, O_r, O_t_hi},
	{Vzero, O_t_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi, V_p0},
	{Vend},
};

/* shift asop dest left, const < 32 */
static uchar	asdshllclo[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsl, ASHLL, O_r, O_t_rp},
	{Vshll, O_r, O_t_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vend},
};

/* shift asop dest left, const == 32 */
static uchar	asdshllc32[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{Vzero, O_t_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vend},
};

/* shift asop dest, const > 32 */
static uchar	asdshllchi[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_hi},
	{Vzero, O_t_lo},
	{Vshll, O_r, O_t_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vend},
};

static uchar	(*asshlltab[])[VLEN] =
{
	asshllgen,
	asshllclo,
	asshllc32,
	asshllchi,
	asdshllgen,
	asdshllclo,
	asdshllc32,
	asdshllchi,
};

/* shift asop right general case */
static uchar	asshrlgen[][VLEN] =
{
	{V_a0, V_a1},
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_r0},
	{Vins, AMOVL, O_l_hi, O_r1},
	{Vinsra, ASHRL, O_r, O_r0},
	{Vinsx, Bop0, O_r, O_r1},
	{Vins, AMOVL, O_r0, O_l_lo},
	{Vins, AMOVL, O_r1, O_l_hi, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_hi, O_r0},
	{Vinsx, Bop0, O_r, O_r0},
	{V_T1, Vzero, O_l_hi},
	{Vins, AMOVL, O_r0, O_l_lo},
	{V_F1, Vins, ASARL, C31, O_r0},
	{V_F1, Vins, AMOVL, O_r0, O_l_hi},
	{V_p0, V_f0, V_f1, Vend},
};

/* shift asop right, const < 32 */
static uchar	asshrlclo[][VLEN] =
{
	{V_a0, V_a1},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vins, AMOVL, O_l_hi, O_r1},
	{Vinsra, ASHRL, O_r, O_r0},
	{Vinsx, Bop0, O_r, O_r1},
	{Vins, AMOVL, O_r0, O_l_lo},
	{Vins, AMOVL, O_r1, O_l_hi},
	{V_f0, V_f1, Vend},
};

/* shift asop right, const == 32 */
static uchar	asshrlc32[][VLEN] =
{
	{V_a0},
	{Vins, AMOVL, O_l_hi, O_r0},
	{V_T1, Vzero, O_l_hi},
	{Vins, AMOVL, O_r0, O_l_lo},
	{V_F1, Vins, ASARL, C31, O_r0},
	{V_F1, Vins, AMOVL, O_r0, O_l_hi},
	{V_f0, Vend},
};

/* shift asop right, const > 32 */
static uchar	asshrlchi[][VLEN] =
{
	{V_a0},
	{Vins, AMOVL, O_l_hi, O_r0},
	{V_T1, Vzero, O_l_hi},
	{Vinsx, Bop0, O_r, O_r0},
	{Vins, AMOVL, O_r0, O_l_lo},
	{V_F1, Vins, ASARL, C31, O_r0},
	{V_F1, Vins, AMOVL, O_r0, O_l_hi},
	{V_f0, Vend},
};

/* shift asop dest right general case */
static uchar	asdshrlgen[][VLEN] =
{
	{Vop, OGEQ, O_r, C32},
	{V_s0, Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsr, ASHRL, O_r, O_t_rp},
	{Vinsx, Bop0, O_r, O_t_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi, Vgo},
	{V_p0, V_s0},
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{V_T1, Vzero, O_t_hi},
	{Vinsx, Bop0, O_r, O_t_lo},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{Vins, AMOVL, O_t_hi, O_l_hi, V_p0},
	{Vend},
};

/* shift asop dest right, const < 32 */
static uchar	asdshrlclo[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsr, ASHRL, O_r, O_t_rp},
	{Vinsx, Bop0, O_r, O_t_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vend},
};

/* shift asop dest right, const == 32 */
static uchar	asdshrlc32[][VLEN] =
{
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{V_T1, Vzero, O_t_hi},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi},
	{Vend},
};

/* shift asop dest, const > 32 */
static uchar	asdshrlchi[][VLEN] =
{
	{Vins, AMOVL, O_l_hi, O_t_lo},
	{V_T1, Vzero, O_t_hi},
	{Vinsx, Bop0, O_r, O_t_lo},
	{V_T1, Vins, AMOVL, O_t_hi, O_l_hi},
	{V_T1, Vins, AMOVL, O_t_lo, O_l_lo},
	{V_F1, Vins, AMOVL, O_t_lo, O_t_hi},
	{V_F1, Vins, ASARL, C31, O_t_hi},
	{V_F1, Vins, AMOVL, O_t_lo, O_l_lo},
	{V_F1, Vins, AMOVL, O_t_hi, O_l_hi},
	{Vend},
};

static uchar	(*asshrltab[])[VLEN] =
{
	asshrlgen,
	asshrlclo,
	asshrlc32,
	asshrlchi,
	asdshrlgen,
	asdshrlclo,
	asdshrlc32,
	asdshrlchi,
};

static uchar	shrlargs[]	= { ASHRL, 1 };
static uchar	sarlargs[]	= { ASARL, 0 };

/* ++ -- */
static uchar	incdec[][VLEN] =
{
	{Vinsx, Bop0, C01, O_l_lo},
	{Vinsx, Bop1, C00, O_l_hi, Vend},
};

/* ++ -- *p */
static uchar	incdecpre[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsx, Bop0, C01, O_t_lo},
	{Vinsx, Bop1, C00, O_t_hi},
	{Vins, AMOVL, O_t_lo, O_l_lo},
	{Vins, AMOVL, O_t_hi, O_l_hi, Vend},
};

/* *p ++ -- */
static uchar	incdecpost[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsx, Bop0, C01, O_l_lo},
	{Vinsx, Bop1, C00, O_l_hi, Vend},
};

/* binop rp, rp */
static uchar	binop00[][VLEN] =
{
	{Vinsx, Bop0, O_r_lo, O_l_lo},
	{Vinsx, Bop1, O_r_hi, O_l_hi, Vend},
	{Vend},
};

/* binop rp, addr */
static uchar	binoptmp[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_r_lo, O_r0},
	{Vinsx, Bop0, O_r0, O_l_lo},
	{Vins, AMOVL, O_r_hi, O_r0},
	{Vinsx, Bop1, O_r0, O_l_hi},
	{V_f0, Vend},
};

/* binop t = *a op *b */
static uchar	binop11[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vinsx, Bop0, O_r_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsx, Bop1, O_r_hi, O_t_hi, Vend},
};

/* binop t = rp +- c */
static uchar	add0c[][VLEN] =
{
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_l_lo},
	{V_r_lo_f, Vamv, Bop0, Bop1},
	{Vinsx, Bop1, O_r_hi, O_l_hi},
	{Vend},
};

/* binop t = rp & c */
static uchar	and0c[][VLEN] =
{
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_l_lo},
	{V_r_lo_f, Vins, AMOVL, C00, O_l_lo},
	{V_r_hi_t, Vinsx, Bop1, O_r_hi, O_l_hi},
	{V_r_hi_f, Vins, AMOVL, C00, O_l_hi},
	{Vend},
};

/* binop t = rp | c */
static uchar	or0c[][VLEN] =
{
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_l_lo},
	{V_r_hi_t, Vinsx, Bop1, O_r_hi, O_l_hi},
	{Vend},
};

/* binop t = c - rp */
static uchar	sub10[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_l_lo, O_r0},
	{Vinsx, Bop0, O_r_lo, O_r0},
	{Vins, AMOVL, O_l_hi, O_r_lo},
	{Vinsx, Bop1, O_r_hi, O_r_lo},
	{Vspazz, V_f0, Vend},
};

/* binop t = c + *b */
static uchar	addca[][VLEN] =
{
	{Vins, AMOVL, O_r_lo, O_t_lo},
	{V_l_lo_t, Vinsx, Bop0, O_l_lo, O_t_lo},
	{V_l_lo_f, Vamv, Bop0, Bop1},
	{Vins, AMOVL, O_r_hi, O_t_hi},
	{Vinsx, Bop1, O_l_hi, O_t_hi},
	{Vend},
};

/* binop t = c & *b */
static uchar	andca[][VLEN] =
{
	{V_l_lo_t, Vins, AMOVL, O_r_lo, O_t_lo},
	{V_l_lo_t, Vinsx, Bop0, O_l_lo, O_t_lo},
	{V_l_lo_f, Vzero, O_t_lo},
	{V_l_hi_t, Vins, AMOVL, O_r_hi, O_t_hi},
	{V_l_hi_t, Vinsx, Bop1, O_l_hi, O_t_hi},
	{V_l_hi_f, Vzero, O_t_hi},
	{Vend},
};

/* binop t = c | *b */
static uchar	orca[][VLEN] =
{
	{Vins, AMOVL, O_r_lo, O_t_lo},
	{V_l_lo_t, Vinsx, Bop0, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_r_hi, O_t_hi},
	{V_l_hi_t, Vinsx, Bop1, O_l_hi, O_t_hi},
	{Vend},
};

/* binop t = c - *b */
static uchar	subca[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsx, Bop0, O_r_lo, O_t_lo},
	{Vinsx, Bop1, O_r_hi, O_t_hi},
	{Vend},
};

/* binop t = *a +- c */
static uchar	addac[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_t_lo},
	{V_r_lo_f, Vamv, Bop0, Bop1},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{Vinsx, Bop1, O_r_hi, O_t_hi},
	{Vend},
};

/* binop t = *a | c */
static uchar	orac[][VLEN] =
{
	{Vins, AMOVL, O_l_lo, O_t_lo},
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_t_lo},
	{Vins, AMOVL, O_l_hi, O_t_hi},
	{V_r_hi_t, Vinsx, Bop1, O_r_hi, O_t_hi},
	{Vend},
};

/* binop t = *a & c */
static uchar	andac[][VLEN] =
{
	{V_r_lo_t, Vins, AMOVL, O_l_lo, O_t_lo},
	{V_r_lo_t, Vinsx, Bop0, O_r_lo, O_t_lo},
	{V_r_lo_f, Vzero, O_t_lo},
	{V_r_hi_t, Vins, AMOVL, O_l_hi, O_t_hi},
	{V_r_hi_t, Vinsx, Bop0, O_r_hi, O_t_hi},
	{V_r_hi_f, Vzero, O_t_hi},
	{Vend},
};

static uchar	ADDargs[]	= { AADDL, AADCL };
static uchar	ANDargs[]	= { AANDL, AANDL };
static uchar	ORargs[]	= { AORL, AORL };
static uchar	SUBargs[]	= { ASUBL, ASBBL };
static uchar	XORargs[]	= { AXORL, AXORL };

static uchar	(*ADDtab[])[VLEN] =
{
	add0c, addca, addac,
};

static uchar	(*ANDtab[])[VLEN] =
{
	and0c, andca, andac,
};

static uchar	(*ORtab[])[VLEN] =
{
	or0c, orca, orac,
};

static uchar	(*SUBtab[])[VLEN] =
{
	add0c, subca, addac,
};

/* mul of const32 */
static uchar	mulc32[][VLEN] =
{
	{V_a0, Vop, ONEQ, O_l_hi, C00},
	{V_s0, Vins, AMOVL, O_r_lo, O_r0},
	{Vins, AMULL, O_r0, O_ZeroNop},
	{Vgo, V_p0, V_s0},
	{Vins, AMOVL, O_l_hi, O_r0},
	{Vmul, O_r_lo, O_r0},
	{Vins, AMOVL, O_r_lo, O_l_hi},
	{Vins, AMULL, O_l_hi, O_ZeroNop},
	{Vins, AADDL, O_r0, O_l_hi},
	{V_f0, V_p0, Vend},
};

/* mul of const64 */
static uchar	mulc64[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_r_hi, O_r0},
	{Vop, OLOR, O_l_hi, O_r0},
	{Vop, ONEQ, O_r0, C00},
	{V_s0, Vins, AMOVL, O_r_lo, O_r0},
	{Vins, AMULL, O_r0, O_ZeroNop},
	{Vgo, V_p0, V_s0},
	{Vmul, O_r_lo, O_l_hi},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vmul, O_r_hi, O_r0},
	{Vins, AADDL, O_l_hi, O_r0},
	{Vins, AMOVL, O_r_lo, O_l_hi},
	{Vins, AMULL, O_l_hi, O_ZeroNop},
	{Vins, AADDL, O_r0, O_l_hi},
	{V_f0, V_p0, Vend},
};

/* mul general */
static uchar	mull[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_r_hi, O_r0},
	{Vop, OLOR, O_l_hi, O_r0},
	{Vop, ONEQ, O_r0, C00},
	{V_s0, Vins, AMOVL, O_r_lo, O_r0},
	{Vins, AMULL, O_r0, O_ZeroNop},
	{Vgo, V_p0, V_s0},
	{Vins, AIMULL, O_r_lo, O_l_hi},
	{Vins, AMOVL, O_l_lo, O_r0},
	{Vins, AIMULL, O_r_hi, O_r0},
	{Vins, AADDL, O_l_hi, O_r0},
	{Vins, AMOVL, O_r_lo, O_l_hi},
	{Vins, AMULL, O_l_hi, O_ZeroNop},
	{Vins, AADDL, O_r0, O_l_hi},
	{V_f0, V_p0, Vend},
};

/* cast rp l to rp t */
static uchar	castrp[][VLEN] =
{
	{Vmv, O_l, O_t_lo},
	{VT, Vins, AMOVL, O_t_lo, O_t_hi},
	{VT, Vins, ASARL, C31, O_t_hi},
	{VF, Vzero, O_t_hi},
	{Vend},
};

/* cast rp l to addr t */
static uchar	castrpa[][VLEN] =
{
	{VT, V_a0, Vmv, O_l, O_r0},
	{VT, Vins, AMOVL, O_r0, O_t_lo},
	{VT, Vins, ASARL, C31, O_r0},
	{VT, Vins, AMOVL, O_r0, O_t_hi},
	{VT, V_f0},
	{VF, Vmv, O_l, O_t_lo},
	{VF, Vzero, O_t_hi},
	{Vend},
};

static uchar	netab0i[][VLEN] =
{
	{Vop, ONEQ, O_l_lo, O_r_lo},
	{V_s0, Vop, ONEQ, O_l_hi, O_r_hi},
	{V_s1, Vgo, V_s2, Vgo, V_s3},
	{VF, V_p0, V_p1, VT, V_p2},
	{Vgo, V_p3},
	{VT, V_p0, V_p1, VF, V_p2},
	{Vend},
};

static uchar	netabii[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_l_lo, O_r0},
	{Vop, ONEQ, O_r0, O_r_lo},
	{V_s0, Vins, AMOVL, O_l_hi, O_r0},
	{Vop, ONEQ, O_r0, O_r_hi},
	{V_s1, Vgo, V_s2, Vgo, V_s3},
	{VF, V_p0, V_p1, VT, V_p2},
	{Vgo, V_p3},
	{VT, V_p0, V_p1, VF, V_p2},
	{V_f0, Vend},
};

static uchar	cmptab0i[][VLEN] =
{
	{Vopx, Bop0, O_l_hi, O_r_hi},
	{V_s0, Vins0, AJNE},
	{V_s1, Vopx, Bop1, O_l_lo, O_r_lo},
	{V_s2, Vgo, V_s3, Vgo, V_s4},
	{VT, V_p1, V_p3},
	{VF, V_p0, V_p2},
	{Vgo, V_p4},
	{VT, V_p0, V_p2},
	{VF, V_p1, V_p3},
	{Vend},
};

static uchar	cmptabii[][VLEN] =
{
	{V_a0, Vins, AMOVL, O_l_hi, O_r0},
	{Vopx, Bop0, O_r0, O_r_hi},
	{V_s0, Vins0, AJNE},
	{V_s1, Vins, AMOVL, O_l_lo, O_r0},
	{Vopx, Bop1, O_r0, O_r_lo},
	{V_s2, Vgo, V_s3, Vgo, V_s4},
	{VT, V_p1, V_p3},
	{VF, V_p0, V_p2},
	{Vgo, V_p4},
	{VT, V_p0, V_p2},
	{VF, V_p1, V_p3},
	{V_f0, Vend},
};

static uchar	(*NEtab[])[VLEN] =
{
	netab0i, netabii,
};

static uchar	(*cmptab[])[VLEN] =
{
	cmptab0i, cmptabii,
};

static uchar	GEargs[]	= { OGT, OHS };
static uchar	GTargs[]	= { OGT, OHI };
static uchar	HIargs[]	= { OHI, OHI };
static uchar	HSargs[]	= { OHI, OHS };

/* Big Generator */
static void
biggen(Node *l, Node *r, Node *t, int true, uchar code[][VLEN], uchar *a)
{
	int i, j, g, oc, op, lo, ro, to, xo, *xp;
	Type *lt;
	Prog *pr[VOPS];
	Node *ot, *tl, *tr, tmps[2];
	uchar *c, (*cp)[VLEN], args[VARGS];

	if(a != nil)
		memmove(args, a, VARGS);
//print("biggen %d %d %d\n", args[0], args[1], args[2]);
//if(l) prtree(l, "l");
//if(r) prtree(r, "r");
//if(t) prtree(t, "t");
	lo = ro = to = 0;
	cp = code;

	for (;;) {
		c = *cp++;
		g = 1;
		i = 0;
//print("code %d %d %d %d %d\n", c[0], c[1], c[2], c[3], c[4]);
		for(;;) {
			switch(op = c[i]) {
			case Vgo:
				if(g)
					gbranch(OGOTO);
				i++;
				break;

			case Vamv:
				i += 3;
				if(i > VLEN) {
					diag(l, "bad Vop");
					return;
				}
				if(g)
					args[c[i - 1]] = args[c[i - 2]];
				break;

			case Vzero:
				i += 2;
				if(i > VLEN) {
					diag(l, "bad Vop");
					return;
				}
				j = i - 1;
				goto op;

			case Vspazz:	// nasty hack to save a reg in SUB
//print("spazz\n");
				if(g) {
//print("hi %R lo %R t %R\n", r->right->reg, r->left->reg, tmps[0].reg);
					ot = r->right;
					r->right = r->left;
					tl = an(0, ZeroN, ZeroN);
					*tl = tmps[0];
					r->left = tl;
					tmps[0] = *ot;
//print("hi %R lo %R t %R\n", r->right->reg, r->left->reg, tmps[0].reg);
				}
				i++;
				break;

			case Vmv:
			case Vmul:
			case Vshll:
				i += 3;
				if(i > VLEN) {
					diag(l, "bad Vop");
					return;
				}
				j = i - 2;
				goto op;

			case Vins0:
				i += 2;
				if(i > VLEN) {
					diag(l, "bad Vop");
					return;
				}
				instruction(c[i - 1], ZeroN, ZeroN);
				break;

			case Vop:
			case Vopx:
			case Vins:
			case Vinsl:
			case Vinsr:
			case Vinsla:
			case Vinsra:
			case Vinsx:
				i += 4;
				if(i > VLEN) {
					diag(l, "bad Vop");
					return;
				}
				j = i - 2;
				goto op;

			op:
				if(!g)
					break;
				tl = ZeroN;
				tr = ZeroN;
				for(; j < i; j++) {
					switch(c[j]) {
					case C00:
						ot = con(0);
						break;
					case C01:
						ot = con(1);
						break;
					case C31:
						ot = con(31);
						break;
					case C32:
						ot = con(32);
						break;

					case O_l:
					case O_l_lo:
						ot = l; xp = &lo; xo = 0;
						goto op0;
					case O_l_hi:
						ot = l; xp = &lo; xo = Machint;
						goto op0;
					case O_r:
					case O_r_lo:
						ot = r; xp = &ro; xo = 0;
						goto op0;
					case O_r_hi:
						ot = r; xp = &ro; xo = Machint;
						goto op0;
					case O_t_lo:
						ot = t; xp = &to; xo = 0;
						goto op0;
					case O_t_hi:
						ot = t; xp = &to; xo = Machint;
						goto op0;
					case O_l_rp:
						ot = l;
						break;
					case O_r_rp:
						ot = r;
						break;
					case O_t_rp:
						ot = t;
						break;
					case O_r0:
					case O_r1:
						ot = &tmps[c[j] - O_r0];
						break;
					case O_ZeroNop:
						ot = ZeroN;
						break;

					op0:
						switch(ot->op) {
						case OCONST:
							if(xo)
								ot = hi64(ot);
							else
								ot = lo64(ot);
							break;
						case OREGPAIR:
							if(xo)
								ot = ot->right;
							else
								ot = ot->left;
							break;
						case OREGISTER:
							break;
						default:
							if(xo != *xp) {
								ot->ival += xo - *xp;
								*xp = xo;
							}
						}
						break;

					default:
						diag(l, "bad V_lop");
						return;
					}
					if(tl == nil)
						tl = ot;
					else
						tr = ot;
				}
				if(op == Vzero) {
					zeroregm(tl);
					break;
				}
				oc = c[i - 3];
				if(op == Vinsx || op == Vopx) {
//print("%d -> %d\n", oc, args[oc]);
					oc = args[oc];
				}
				else {
					switch(oc) {
					case O_a0:
					case O_a1:
						oc = args[oc - O_a0];
						break;
					}
				}
				switch(op) {
				case Vmul:
					mulgen(tr->t, tl, tr);
					break;
				case Vmv:
					gmove(tl, tr);
					break;
				case Vshll:
					shiftit(tr->t, tl, tr);
					break;
				case Vop:
				case Vopx:
					gopcode(oc, builtype[TUINT], tl, tr);
					break;
				case Vins:
				case Vinsx:
					instruction(oc, tl, tr);
					break;
				case Vinsl:
					instruction(oc, tl, tr->right);
					p->from.index = tr->left->reg;
					break;
				case Vinsr:
					instruction(oc, tl, tr->left);
					p->from.index = tr->right->reg;
					break;
				case Vinsla:
					instruction(oc, tl, tr + 1);
					p->from.index = tr->reg;
					break;
				case Vinsra:
					instruction(oc, tl, tr);
					p->from.index = (tr + 1)->reg;
					break;
				}
				break;

			case VT:
				g = true;
				i++;
				break;
			case VF:
				g = !true;
				i++;
				break;

			case V_T0: case V_T1:
				g = args[op - V_T0];
				i++;
				break;

			case V_F0: case V_F1:
				g = !args[op - V_F0];
				i++;
				break;

			case V_C0: case V_C1:
				if(g)
					args[op - V_C0] = 0;
				i++;
				break;

			case V_S0: case V_S1:
				if(g)
					args[op - V_S0] = 1;
				i++;
				break;

			case V_l_lo_f:
				g = lo64v(l) == 0;
				i++;
				break;
			case V_l_hi_f:
				g = hi64v(l) == 0;
				i++;
				break;
			case V_l_lo_t:
				g = lo64v(l) != 0;
				i++;
				break;
			case V_l_hi_t:
				g = hi64v(l) != 0;
				i++;
				break;
			case V_l_lo_u:
				g = lo64v(l) >= 0;
				i++;
				break;
			case V_l_hi_u:
				g = hi64v(l) >= 0;
				i++;
				break;
			case V_r_lo_f:
				g = lo64v(r) == 0;
				i++;
				break;
			case V_r_hi_f:
				g = hi64v(r) == 0;
				i++;
				break;
			case V_r_lo_t:
				g = lo64v(r) != 0;
				i++;
				break;
			case V_r_hi_t:
				g = hi64v(r) != 0;
				i++;
				break;
			case V_r_lo_u:
				g = lo64v(r) >= 0;
				i++;
				break;
			case V_r_hi_u:
				g = hi64v(r) >= 0;
				i++;
				break;

			case Vend:
				goto out;

			case V_a0: case V_a1:
				if(g) {
					lt = l->t;
					l->t = builtype[TUINT];
					reg(&tmps[op - V_a0], l, ZeroN);
					l->t = lt;
				}
				i++;
				break;

			case V_f0: case V_f1:
				if(g)
					regfree(&tmps[op - V_f0]);
				i++;
				break;

			case V_p0: case V_p1: case V_p2: case V_p3: case V_p4:
				if(g)
					patch(pr[op - V_p0], pc);
				i++;
				break;

			case V_s0: case V_s1: case V_s2: case V_s3: case V_s4:
				if(g)
					pr[op - V_s0] = p;
				i++;
				break;

			default:
				diag(l, "bad biggen: %d", op);
				return;
			}
			if(i == VLEN || c[i] == 0)
				break;
		}
	}
out:
	if(lo)
		l->ival -= lo;
	if(ro)
		r->ival -= ro;
	if(to)
		t->ival -= to;
}

int
cgen64(Node *n, Node *nn)
{
	Type *dt;
	uchar *args, (*cp)[VLEN], (**optab)[VLEN];
	int li, ri, lri, dr, si, m, op, sh, cmp, true;
	Node *c, *d, *l, *r, *t, *s, nod1, nod2, nod3, nod4, nod5;

	if(debug['g']) {
		prtree(nn, "cgen64 lhs");
		prtree(n, "cgen64");
		print("AX = %d\n", regmap[D_AX]);
	}
	cmp = 0;
	sh = 0;

	switch(n->t) {
	case ONEG:
		d = regpair(nn, n);
		sugen(n->left, d, 8);
		instruction(ANOTL, ZeroN, d->right);
		instruction(ANEGL, ZeroN, d->left);
		instruction(ASBBL, con(-1), d->right);
		break;

	case OCOM:
		if(!laddr(n->left, 0) || !laddr(nn, 0))
			d = regpair(nn, n);
		else
			return 0;
		sugen(n->left, d, 8);
		instruction(ANOTL, ZeroN, d->left);
		instruction(ANOTL, ZeroN, d->right);
		break;

	case OADD:
		optab = ADDtab;
		args = ADDargs;
		goto twoop;
	case OAND:
		optab = ANDtab;
		args = ANDargs;
		goto twoop;
	case OLOR:
		optab = ORtab;
		args = ORargs;
		goto twoop;
	case OSUB:
		optab = SUBtab;
		args = SUBargs;
		goto twoop;
	case OXOR:
		optab = ORtab;
		args = XORargs;
		goto twoop;
	case OASHL:
		sh = 1;
		args = nil;
		optab = shlltab;
		goto twoop;
	case OLSHR:
		sh = 1;
		args = shrlargs;
		optab = shrltab;
		goto twoop;
	case OASHR:
		sh = 1;
		args = sarlargs;
		optab = shrltab;
		goto twoop;
	case OEQ:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case ONEQ:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OLEQ:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OLT:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OGEQ:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OGT:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OHI:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OHS:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OLO:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;
	case OLS:
		cmp = 1;
		args = nil;
		optab = nil;
		goto twoop;

twoop:
		dr = nn != ZeroN && nn->t == OREGPAIR;
		l = vfunc(n->left, nn);
		if(sh)
			r = n->right;
		else
			r = vfunc(n->right, nn);

		li = l->op == ONAME || l->op == OINDREG || l->op == OCONST;
		ri = r->op == ONAME || r->op == OINDREG || r->op == OCONST;

#define	IMM(l, r)	((l) | ((r) << 1))

		lri = IMM(li, ri);

		/* find out what is so easy about some operands */
		if(li)
			li = whatof(l, sh | cmp);
		if(ri)
			ri = whatof(r, cmp);

		if(sh)
			goto shift;

		if(cmp)
			goto cmp;

		/* evaluate hard subexps, stealing nn if possible. */
		switch(lri) {
		case IMM(0, 0):
		bin00:
			if(l->complex > r->complex) {
				if(dr)
					t = nn;
				else
					t = regpair(ZeroN, n);
				sugen(l, t, 8);
				l = t;
				t = regpair(ZeroN, n);
				sugen(r, t, 8);
				r = t;
			}
			else {
				t = regpair(ZeroN, n);
				sugen(r, t, 8);
				r = t;
				if(dr)
					t = nn;
				else
					t = regpair(ZeroN, n);
				sugen(l, t, 8);
				l = t;
			}
			break;
		case IMM(0, 1):
			if(dr)
				t = nn;
			else
				t = regpair(ZeroN, n);
			sugen(l, t, 8);
			l = t;
			break;
		case IMM(1, 0):
			if(n->t == OSUB && l->op == OCONST && hi64v(l) == 0) {
				lri = IMM(0, 0);
				goto bin00;
			}
			if(dr)
				t = nn;
			else
				t = regpair(ZeroN, n);
			sugen(r, t, 8);
			r = t;
			break;
		case IMM(1, 1):
			break;
		}

#define	WW(l, r)	((l) | ((r) << 2))
		d = ZeroN;
		dt = nn->t;
		nn->t = builtype[TINT];

		switch(lri) {
		case IMM(0, 0):
			biggen(l, r, ZeroN, 0, binop00, args);
			break;
		case IMM(0, 1):
			switch(ri) {
			case WNONEQ:
				diag(r, "bad whatof\n");
				break;
			case WCONST:
				biggen(l, r, ZeroN, 0, optab[B0c], args);
				break;
			case WHARD:
				reglcgen(&nod2, r, ZeroN);
				r = &nod2;
				/* fall thru */
			case WADDR:
				biggen(l, r, ZeroN, 0, binoptmp, args);
				if(ri == WHARD)
					regfree(r);
				break;
			}
			break;
		case IMM(1, 0):
			if(n->t == OSUB) {
				switch(li) {
				case WNONEQ:
					diag(l, "bad whatof\n");
					break;
				case WHARD:
					reglcgen(&nod2, l, ZeroN);
					l = &nod2;
					/* fall thru */
				case WADDR:
				case WCONST:
					biggen(l, r, ZeroN, 0, sub10, args);
					break;
				}
				if(li == WHARD)
					regfree(l);
			}
			else {
				switch(li) {
				case WNONEQ:
					diag(l, "bad whatof\n");
					break;
				case WCONST:
					biggen(r, l, ZeroN, 0, optab[B0c], args);
					break;
				case WHARD:
					reglcgen(&nod2, l, ZeroN);
					l = &nod2;
					/* fall thru */
				case WADDR:
					biggen(r, l, ZeroN, 0, binoptmp, args);
					if(li == WHARD)
						regfree(l);
					break;
				}
			}
			break;
		case IMM(1, 1):
			switch(WW(li, ri)) {
			case WW(WCONST, WHARD):
				if(r->op == ONAME && n->t == OAND && reduxv(l))
					ri = WADDR;
				break;
			case WW(WHARD, WCONST):
				if(l->op == ONAME && n->t == OAND && reduxv(r))
					li = WADDR;
				break;
			}
			if(li == WHARD) {
				reglcgen(&nod3, l, ZeroN);
				l = &nod3;
			}
			if(ri == WHARD) {
				reglcgen(&nod2, r, ZeroN);
				r = &nod2;
			}
			d = regpair(nn, n);
			instpair(d, ZeroN);
			switch(WW(li, ri)) {
			case WW(WCONST, WADDR):
			case WW(WCONST, WHARD):
				biggen(l, r, d, 0, optab[Bca], args);
				break;

			case WW(WADDR, WCONST):
			case WW(WHARD, WCONST):
				biggen(l, r, d, 0, optab[Bac], args);
				break;

			case WW(WADDR, WADDR):
			case WW(WADDR, WHARD):
			case WW(WHARD, WADDR):
			case WW(WHARD, WHARD):
				biggen(l, r, d, 0, binop11, args);
				break;

			default:
				diag(r, "bad whatof pair %d %d\n", li, ri);
				break;
			}
			if(li == WHARD)
				regfree(l);
			if(ri == WHARD)
				regfree(r);
			break;
		}

		nn->t = dt;

		if(d != ZeroN)
			goto finished;

		switch(lri) {
		case IMM(0, 0):
			freepair(r);
			/* fall thru */;
		case IMM(0, 1):
			if(!dr)
				storepair(l, nn, 1);
			break;
		case IMM(1, 0):
			if(!dr)
				storepai