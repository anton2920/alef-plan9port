#define LTYPE0 257
#define LTYPE1 258
#define LTYPE2 259
#define LTYPE3 260
#define LTYPE4 261
#define LTYPEC 262
#define LTYPED 263
#define LTYPEN 264
#define LTYPER 265
#define LTYPET 266
#define LTYPES 267
#define LTYPEM 268
#define LTYPEI 269
#define LTYPEG 270
#define LCONST 271
#define LFP 272
#define LPC 273
#define LSB 274
#define LBREG 275
#define LLREG 276
#define LSREG 277
#define LFREG 278
#define LFCONST 279
#define LSCONST 280
#define LSP 281
#define LNAME 282
#define LLAB 283
#define LVAR 284
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union	{
	Sym	*sym;
	long	lval;
	struct {
		long v1;
		long v2;
	} con2;
	double	dval;
	char	sval[8];
	Gen	gen;
	Gen2	gen2;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
