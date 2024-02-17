/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20200330

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 32 "a.y"
#include <stdio.h>	/* if we don't, bison will, and a.h re-#defines getc */
#include "a.h"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 35 "a.y"
typedef union	{
	Sym	*sym;
	int32	lval;
	struct {
		int32 v1;
		int32 v2;
	} con2;
	double	dval;
	char	sval[8];
	Gen	gen;
	Gen2	gen2;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 44 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

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
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,   32,    0,   33,   31,   34,   31,   31,   31,   31,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   17,   17,   21,   22,
   20,   20,   19,   19,   18,   18,   23,   24,   24,   25,
   25,   26,   26,   27,   27,   28,   28,   29,   29,   29,
   30,   30,   12,   12,   14,   14,   14,   14,   14,   14,
   14,   13,   13,   11,   11,   11,    9,    9,    9,    9,
    9,    7,    7,    7,    7,    7,    7,    8,    5,    5,
    5,    5,    6,    6,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   16,   16,   10,   10,    4,    4,
    4,    3,    3,    3,    1,    1,    1,    1,    1,    1,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,
};
static const YYINT yylen[] = {                            2,
    0,    0,    3,    0,    4,    0,    4,    1,    2,    2,
    3,    3,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    0,    1,    3,    3,
    2,    1,    2,    1,    2,    1,    5,    3,    5,    2,
    1,    1,    1,    3,    5,    3,    5,    2,    1,    3,
    3,    5,    1,    1,    1,    1,    2,    2,    1,    1,
    1,    1,    1,    4,    2,    2,    1,    1,    1,    1,
    1,    2,    2,    2,    2,    4,    3,    2,    1,    2,
    3,    4,    1,    1,    1,    4,    4,    6,    9,    3,
    3,    4,    5,    8,    1,    6,    5,    7,    0,    2,
    2,    1,    1,    1,    1,    1,    2,    2,    2,    3,
    1,    3,    3,    3,    3,    3,    4,    4,    3,    3,
    3,
};
static const YYINT yydefred[] = {                         1,
    2,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    8,    3,    0,   10,   28,   13,    0,    0,  105,   67,
   69,   71,   68,   70,    0,  106,    0,    0,    0,    0,
   54,   53,    0,   34,   83,   84,   14,    0,   63,   62,
    0,   15,    0,   16,    0,   17,    0,    0,    0,    0,
    0,   61,   59,   55,   41,   60,   56,   21,    0,   19,
    0,   42,   43,   22,    0,    0,    0,    0,   36,   18,
    0,   20,    0,   23,    0,   24,    0,   25,    0,   26,
    6,    0,    4,    0,    9,  108,  107,    0,    0,    0,
    0,   33,    0,    0,  111,    0,  109,    0,    0,    0,
   75,   74,    0,   72,   73,   31,    0,    0,   57,   58,
    0,   66,   40,    0,    0,   65,   35,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  100,  101,
    0,    0,    0,   91,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  110,    0,    0,    0,    0,   77,
    0,   29,   30,    0,    0,    0,    0,   38,    0,    0,
   50,    0,   51,    7,    5,    0,  104,  102,  103,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  114,
  115,  116,    0,    0,   92,   87,    0,   76,   64,    0,
    0,    0,   78,    0,    0,    0,    0,    0,   97,   93,
    0,    0,    0,    0,    0,    0,   37,    0,    0,   39,
   45,   47,   52,    0,    0,   88,    0,   96,    0,   81,
   98,    0,    0,   82,   94,    0,   89,
};
static const YYINT yydgoto[] = {                          1,
   40,  106,  180,  101,  203,   41,   49,  168,   42,   43,
   64,   50,   51,   65,   45,   46,   26,   80,   47,   52,
   54,   56,   70,   82,   68,   74,   84,   86,   88,   90,
   22,    2,  136,  134,   23,
};
static const YYINT yysindex[] = {                         0,
    0,  115,  -49,   47,    8,   -8,   -8,   32,  -36, -241,
   20,   52,   80,   -8,   -8,   -8,   80,   -3,  -12,    6,
    0,    0,   29,    0,    0,    0,   16,   16,    0,    0,
    0,    0,    0,    0,   23,    0,   32,   68,   16,   54,
    0,    0,   60,    0,    0,    0,    0,   58,    0,    0,
   65,    0,   77,    0,   83,    0,   44,   23,   31,  -22,
   66,    0,    0,    0,    0,    0,    0,    0,   85,    0,
   32,    0,    0,    0,   31,   72,   16,   84,    0,    0,
   94,    0,   97,    0,  104,    0,  106,    0,  109,    0,
    0,   16,    0,   16,    0,    0,    0,   99,   16,   16,
  116,    0,  118,  128,    0,  102,    0,   82, -100,   62,
    0,    0,   86,    0,    0,    0,   32,   -8,    0,    0,
  116,    0,    0,  -94,   16,    0,    0,  -78,   -7,   32,
   32,   32,    4,  115,  364,  115,  364,   31,    0,    0,
  -81,   16,  157,    0,   16,   16,   16,  139,  145,   16,
   16,   16,   16,   16,    0,  162,  160,  172,  187,    0,
  189,    0,    0,  190,  170,  -44,  188,    0,  185,  186,
    0,  206,    0,    0,    0,  211,    0,    0,    0,  224,
  225,  -24,  418,  130,  449,   16,   16,  173,  173,    0,
    0,    0,   16,  232,    0,    0,   16,    0,    0,  242,
    9,  236,    0,  246,   17,   22,  242,   38,    0,    0,
  252,  191,  191,  264,   30,  270,    0,  273,   53,    0,
    0,    0,    0,  285,   16,    0,  303,    0,   56,    0,
    0,  306,   16,    0,    0,  307,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,  291,    0,    0,    0,    0,    0,    0,
  291,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  313,    0,    0,    0,    0,   27,
    0,    0,   93,    0,    0,    0,    0,    0,    0,    0,
  301,    0,    0,    0,    0,    0,    0,  -28,  302,    0,
  308,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  309,    0,    0,    0,  302,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  332,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  333,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  334,    0,    0,  335,    0,  336,  313,    0,    0,
    0,    0,  122,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  337,  341,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -2,  -14,  -25,    0,    0,  376,  389,    0,
    0,    0,    0,  127,    0,    0,    0,    0,    0,    0,
    0,  344,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   95,  328,    0,    0,    0,    0,  349,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  377,   71,    0,  -56,    0,   37,    2,  208,   13,   -5,
    3,  200,   10,  350,   21,   33,  402,    0,  407,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -20,    0,    0,    0,    0,
};
#define YYTABLESIZE 610
static const YYINT yytable[] = {                         48,
  201,  121,  122,   38,   69,   57,   27,   60,   28,   24,
   62,   99,  119,   48,   79,  119,   53,   38,  126,   57,
   27,   63,   28,   83,   85,   87,  120,   48,  166,   66,
   99,   38,   77,  119,   27,   27,   28,   28,  121,   48,
   35,   67,  115,   77,  120,   93,   27,   38,   28,   81,
   27,   37,   28,   89,   91,   77,  121,   92,   27,   38,
   28,   62,   27,   71,   28,   99,   94,  100,  119,  119,
   85,   38,   63,   99,   27,  100,   28,  120,  127,  120,
   66,  176,   98,   38,   85,   85,   27,   95,   28,   39,
   25,   77,   67,  108,   27,   76,   28,  113,  119,  109,
   27,   77,  110,   39,   27,  124,   28,   77,  116,  120,
   27,   77,   28,  174,   27,  175,   28,   39,   39,   38,
  117,  121,   27,  128,   28,   77,  118,  163,   27,   39,
   28,  125,  117,   39,  173,  117,   95,  129,  154,  147,
  130,   39,  155,  152,  150,   39,  151,  131,  153,  132,
   95,   95,  133,  117,  117,  141,  117,   39,  143,  142,
  138,  148,  135,  149,  137,   90,  154,  147,  144,   39,
   86,  152,  150,   21,  151,  159,  153,   39,  164,   90,
   90,  156,  157,   39,   86,   86,  158,   39,  117,  148,
  177,  149,  178,   39,  164,  146,  182,   39,  186,  179,
  195,  217,  194,  193,   44,   39,  187,   55,  223,  154,
   44,   39,  196,  200,  152,  183,  184,  185,  117,  153,
  188,  189,  190,  191,  192,  145,  202,  154,  197,  198,
  199,  204,  152,  150,   29,  151,  102,  153,   30,   31,
   32,   33,  205,  206,   34,   58,   59,   36,   29,  207,
  208,  211,   30,   31,   32,   33,  212,  213,   34,   58,
   59,   36,   29,   29,  209,  210,   30,   31,   32,   33,
  102,  215,   34,   35,   29,   36,   36,   48,   29,  218,
  219,  166,   30,   31,   32,   33,   29,   36,   34,   35,
   29,   36,  221,  225,   30,   31,   32,   33,  222,   36,
   34,   35,   29,   36,  226,  227,   30,   31,   32,   33,
  228,  224,   34,   35,   29,   36,  162,  229,   30,   31,
   32,   33,   29,  230,   34,  231,  234,   36,   29,  169,
  170,  171,   29,   75,   59,   36,  111,  112,   29,   35,
  160,   36,   29,  103,  233,   36,  235,  237,  104,   27,
   29,   36,   99,   75,   59,   36,   29,  156,  157,   32,
   99,   35,  158,   36,  161,  118,   85,   28,  118,   36,
    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
   13,   14,   15,   16,   17,   61,  118,  118,   78,  118,
   49,   65,   48,   11,   12,   44,   18,   19,   20,   46,
  154,  147,   79,   96,   97,  152,  150,   80,  151,  123,
  153,  220,   72,  112,  105,  107,  112,   73,  112,    0,
  112,  118,    0,  148,  114,  149,  113,    0,    0,  113,
    0,  113,    0,  113,  112,  112,   61,  112,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  113,  113,    0,
  113,  118,   78,  105,  154,  147,    0,  146,    0,  152,
  150,    0,  151,    0,  153,    0,    0,    0,  105,  112,
  105,    0,    0,    0,    0,  139,  140,  148,    0,  149,
    0,    0,  113,    0,    0,  154,   97,  145,    0,  105,
  152,  150,    0,  151,    0,  153,    0,    0,    0,  112,
    0,  165,    0,    0,    0,  167,    0,    0,  148,  172,
  149,  146,  113,    0,    0,    0,    0,    0,  181,    0,
    0,  105,  105,  105,    0,    0,  105,  105,  105,  105,
  105,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  105,  105,    0,    0,    0,    0,    0,  214,
    0,    0,    0,  216,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  232,    0,    0,    0,    0,    0,    0,    0,  236,
};
static const YYINT yycheck[] = {                         36,
   45,   58,   59,   40,   10,   42,   43,   44,   45,   59,
    9,   40,   38,   36,   12,   41,    7,   40,   75,   42,
   43,    9,   45,   14,   15,   16,   41,   36,   36,    9,
   59,   40,   40,   59,   43,   43,   45,   45,   41,   36,
  282,    9,   48,   40,   59,   58,   43,   40,   45,   13,
   43,   44,   45,   17,   58,   40,   59,   61,   43,   40,
   45,   60,   43,   44,   45,   43,   61,   45,   94,   57,
   44,   40,   60,   43,   43,   45,   45,   57,   76,   94,
   60,  138,   60,   40,   58,   59,   43,   59,   45,  126,
   44,   40,   60,   40,   43,   44,   45,   40,  124,   40,
   43,   40,   45,  126,   43,   40,   45,   40,   44,  124,
   43,   40,   45,  134,   43,  136,   45,  126,  126,   40,
   44,  124,   43,   40,   45,   40,   44,  118,   43,  126,
   45,   47,   38,  126,  133,   41,   44,   44,   37,   38,
   44,  126,   41,   42,   43,  126,   45,   44,   47,   44,
   58,   59,   44,   59,   60,   40,   62,  126,   41,   42,
   62,   60,   92,   62,   94,   44,   37,   38,   41,  126,
   44,   42,   43,   59,   45,  276,   47,  126,  273,   58,
   59,  276,  277,  126,   58,   59,  281,  126,   94,   60,
  272,   62,  274,  126,  273,   94,   40,  126,   60,  281,
   41,  200,   41,   42,    5,  126,   62,    8,  207,   37,
   11,  126,   41,   44,   42,  145,  146,  147,  124,   47,
  150,  151,  152,  153,  154,  124,  271,   37,   42,   41,
   41,   44,   42,   43,  271,   45,   37,   47,  275,  276,
  277,  278,   58,   58,  281,  282,  283,  284,  271,   44,
   40,  276,  275,  276,  277,  278,  186,  187,  281,  282,
  283,  284,  271,  271,   41,   41,  275,  276,  277,  278,
   71,   40,  281,  282,  271,  284,  284,   36,  271,  271,
   45,   36,  275,  276,  277,  278,  271,  284,  281,  282,
  271,  284,  276,   42,  275,  276,  277,  278,  277,  284,
  281,  282,  271,  284,   41,  276,  275,  276,  277,  278,
   41,  274,  281,  282,  271,  284,  117,   45,  275,  276,
  277,  278,  271,  271,  281,   41,  271,  284,  271,  130,
  131,  132,  271,  282,  283,  284,  279,  280,  271,  282,
  279,  284,  271,  276,   42,  284,   41,   41,  281,   59,
  271,  284,   40,  282,  283,  284,  271,  276,  277,   59,
   59,  282,  281,  284,  279,   38,   59,   59,   41,  284,
  256,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,    9,   59,   60,   12,   62,
   59,   59,   59,   59,   59,   59,  282,  283,  284,   59,
   37,   38,   59,   27,   28,   42,   43,   59,   45,   60,
   47,  204,   11,   38,   38,   39,   41,   11,   43,   -1,
   45,   94,   -1,   60,   48,   62,   38,   -1,   -1,   41,
   -1,   43,   -1,   45,   59,   60,   60,   62,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,   -1,
   62,  124,   76,   77,   37,   38,   -1,   94,   -1,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   92,   94,
   94,   -1,   -1,   -1,   -1,   99,  100,   60,   -1,   62,
   -1,   -1,   94,   -1,   -1,   37,  110,  124,   -1,  113,
   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,  124,
   -1,  125,   -1,   -1,   -1,  129,   -1,   -1,   60,  133,
   62,   94,  124,   -1,   -1,   -1,   -1,   -1,  142,   -1,
   -1,  145,  146,  147,   -1,   -1,  150,  151,  152,  153,
  154,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  186,  187,   -1,   -1,   -1,   -1,   -1,  193,
   -1,   -1,   -1,  197,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  225,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  233,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 322
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'$'","'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,
0,0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'|'",0,"'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"LTYPE0","LTYPE1","LTYPE2","LTYPE3",
"LTYPE4","LTYPEC","LTYPED","LTYPEN","LTYPER","LTYPET","LTYPES","LTYPEM",
"LTYPEI","LTYPEG","LCONST","LFP","LPC","LSB","LBREG","LLREG","LSREG","LFREG",
"LFCONST","LSCONST","LSP","LNAME","LLAB","LVAR",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : prog",
"prog :",
"$$1 :",
"prog : prog $$1 line",
"$$2 :",
"line : LLAB ':' $$2 line",
"$$3 :",
"line : LNAME ':' $$3 line",
"line : ';'",
"line : inst ';'",
"line : error ';'",
"inst : LNAME '=' expr",
"inst : LVAR '=' expr",
"inst : LTYPE0 nonnon",
"inst : LTYPE1 nonrem",
"inst : LTYPE2 rimnon",
"inst : LTYPE3 rimrem",
"inst : LTYPE4 remrim",
"inst : LTYPER nonrel",
"inst : LTYPED spec1",
"inst : LTYPET spec2",
"inst : LTYPEC spec3",
"inst : LTYPEN spec4",
"inst : LTYPES spec5",
"inst : LTYPEM spec6",
"inst : LTYPEI spec7",
"inst : LTYPEG spec8",
"nonnon :",
"nonnon : ','",
"rimrem : rim ',' rem",
"remrim : rem ',' rim",
"rimnon : rim ','",
"rimnon : rim",
"nonrem : ',' rem",
"nonrem : rem",
"nonrel : ',' rel",
"nonrel : rel",
"spec1 : nam '/' con ',' imm",
"spec2 : mem ',' imm2",
"spec2 : mem ',' con ',' imm2",
"spec3 : ',' rom",
"spec3 : rom",
"spec4 : nonnon",
"spec4 : nonrem",
"spec5 : rim ',' rem",
"spec5 : rim ',' rem ':' LLREG",
"spec6 : rim ',' rem",
"spec6 : rim ',' rem ':' LSREG",
"spec7 : rim ','",
"spec7 : rim",
"spec7 : rim ',' rem",
"spec8 : mem ',' imm",
"spec8 : mem ',' con ',' imm",
"rem : reg",
"rem : mem",
"rom : rel",
"rom : nmem",
"rom : '*' reg",
"rom : '*' omem",
"rom : reg",
"rom : omem",
"rom : imm",
"rim : rem",
"rim : imm",
"rel : con '(' LPC ')'",
"rel : LNAME offset",
"rel : LLAB offset",
"reg : LBREG",
"reg : LFREG",
"reg : LLREG",
"reg : LSP",
"reg : LSREG",
"imm : '$' con",
"imm : '$' nam",
"imm : '$' LSCONST",
"imm : '$' LFCONST",
"imm : '$' '(' LFCONST ')'",
"imm : '$' '-' LFCONST",
"imm2 : '$' con2",
"con2 : LCONST",
"con2 : '-' LCONST",
"con2 : LCONST '-' LCONST",
"con2 : '-' LCONST '-' LCONST",
"mem : omem",
"mem : nmem",
"omem : con",
"omem : con '(' LLREG ')'",
"omem : con '(' LSP ')'",
"omem : con '(' LLREG '*' con ')'",
"omem : con '(' LLREG ')' '(' LLREG '*' con ')'",
"omem : '(' LLREG ')'",
"omem : '(' LSP ')'",
"omem : con '(' LSREG ')'",
"omem : '(' LLREG '*' con ')'",
"omem : '(' LLREG ')' '(' LLREG '*' con ')'",
"nmem : nam",
"nmem : nam '(' LLREG '*' con ')'",
"nam : LNAME offset '(' pointer ')'",
"nam : LNAME '<' '>' offset '(' LSB ')'",
"offset :",
"offset : '+' con",
"offset : '-' con",
"pointer : LSB",
"pointer : LSP",
"pointer : LFP",
"con : LCONST",
"con : LVAR",
"con : '-' con",
"con : '+' con",
"con : '~' con",
"con : '(' expr ')'",
"expr : con",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' '<' expr",
"expr : expr '>' '>' expr",
"expr : expr '&' expr",
"expr : expr '^' expr",
"expr : expr '|' expr",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 2:
#line 68 "a.y"
	{
		stmtline = lineno;
	}
break;
case 4:
#line 75 "a.y"
	{
		if(yystack.l_mark[-1].sym->value != pc)
			yyerror("redeclaration of %s", yystack.l_mark[-1].sym->name);
		yystack.l_mark[-1].sym->value = pc;
	}
break;
case 6:
#line 82 "a.y"
	{
		yystack.l_mark[-1].sym->type = LLAB;
		yystack.l_mark[-1].sym->value = pc;
	}
break;
case 11:
#line 93 "a.y"
	{
		yystack.l_mark[-2].sym->type = LVAR;
		yystack.l_mark[-2].sym->value = yystack.l_mark[0].lval;
	}
break;
case 12:
#line 98 "a.y"
	{
		if(yystack.l_mark[-2].sym->value != yystack.l_mark[0].lval)
			yyerror("redeclaration of %s", yystack.l_mark[-2].sym->name);
		yystack.l_mark[-2].sym->value = yystack.l_mark[0].lval;
	}
break;
case 13:
#line 103 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 14:
#line 104 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 15:
#line 105 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 16:
#line 106 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 17:
#line 107 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 18:
#line 108 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 19:
#line 109 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 20:
#line 110 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 21:
#line 111 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 22:
#line 112 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 23:
#line 113 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 24:
#line 114 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 25:
#line 115 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 26:
#line 116 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 27:
#line 119 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	}
break;
case 28:
#line 124 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	}
break;
case 29:
#line 131 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 30:
#line 138 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 31:
#line 145 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-1].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 32:
#line 150 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[0].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 33:
#line 157 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 34:
#line 162 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 35:
#line 169 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 36:
#line 174 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 37:
#line 181 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 38:
#line 189 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 39:
#line 194 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 40:
#line 202 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 41:
#line 207 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 44:
#line 218 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 45:
#line 223 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.to = yystack.l_mark[-2].gen;
		if(yyval.gen2.from.index != D_NONE)
			yyerror("dp shift with lhs index");
		yyval.gen2.from.index = yystack.l_mark[0].lval;
	}
break;
case 46:
#line 233 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 47:
#line 238 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.to = yystack.l_mark[-2].gen;
		if(yyval.gen2.to.index != D_NONE)
			yyerror("dp move with lhs index");
		yyval.gen2.to.index = yystack.l_mark[0].lval;
	}
break;
case 48:
#line 248 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-1].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 49:
#line 253 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[0].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 50:
#line 258 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 51:
#line 265 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 52:
#line 270 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 57:
#line 284 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 58:
#line 288 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 64:
#line 301 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yystack.l_mark[-3].lval + pc;
	}
break;
case 65:
#line 307 "a.y"
	{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yystack.l_mark[-1].sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yystack.l_mark[-1].sym;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 66:
#line 316 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yystack.l_mark[-1].sym;
		yyval.gen.offset = yystack.l_mark[-1].sym->value + yystack.l_mark[0].lval;
	}
break;
case 67:
#line 325 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 68:
#line 330 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 69:
#line 335 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 70:
#line 340 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_SP;
	}
break;
case 71:
#line 345 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 72:
#line 352 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 73:
#line 358 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
		yyval.gen.index = yystack.l_mark[0].gen.type;
		yyval.gen.type = D_ADDR;
		/*
		if($2.type == D_AUTO || $2.type == D_PARAM)
			yyerror("constant cannot be automatic: %s",
				$2.sym->name);
		 */
	}
break;
case 74:
#line 369 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yystack.l_mark[0].sval, sizeof(yyval.gen.sval));
	}
break;
case 75:
#line 375 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yystack.l_mark[0].dval;
	}
break;
case 76:
#line 381 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yystack.l_mark[-1].dval;
	}
break;
case 77:
#line 387 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yystack.l_mark[0].dval;
	}
break;
case 78:
#line 395 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST2;
		yyval.gen.offset = yystack.l_mark[0].con2.v1;
		yyval.gen.offset2 = yystack.l_mark[0].con2.v2;
	}
break;
case 79:
#line 404 "a.y"
	{
		yyval.con2.v1 = yystack.l_mark[0].lval;
		yyval.con2.v2 = 0;
	}
break;
case 80:
#line 409 "a.y"
	{
		yyval.con2.v1 = -yystack.l_mark[0].lval;
		yyval.con2.v2 = 0;
	}
break;
case 81:
#line 414 "a.y"
	{
		yyval.con2.v1 = yystack.l_mark[-2].lval;
		yyval.con2.v2 = yystack.l_mark[0].lval;
	}
break;
case 82:
#line 419 "a.y"
	{
		yyval.con2.v1 = -yystack.l_mark[-2].lval;
		yyval.con2.v2 = yystack.l_mark[0].lval;
	}
break;
case 85:
#line 430 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 86:
#line 436 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 87:
#line 442 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 88:
#line 448 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yystack.l_mark[-5].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 89:
#line 457 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-6].lval;
		yyval.gen.offset = yystack.l_mark[-8].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 90:
#line 466 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
	}
break;
case 91:
#line 471 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
	}
break;
case 92:
#line 476 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 93:
#line 482 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 94:
#line 490 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-6].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 95:
#line 500 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 96:
#line 504 "a.y"
	{
		yyval.gen = yystack.l_mark[-5].gen;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 97:
#line 513 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[-1].lval;
		yyval.gen.sym = yystack.l_mark[-4].sym;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 98:
#line 520 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_STATIC;
		yyval.gen.sym = yystack.l_mark[-6].sym;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 99:
#line 528 "a.y"
	{
		yyval.lval = 0;
	}
break;
case 100:
#line 532 "a.y"
	{
		yyval.lval = yystack.l_mark[0].lval;
	}
break;
case 101:
#line 536 "a.y"
	{
		yyval.lval = -yystack.l_mark[0].lval;
	}
break;
case 103:
#line 543 "a.y"
	{
		yyval.lval = D_AUTO;
	}
break;
case 106:
#line 551 "a.y"
	{
		yyval.lval = yystack.l_mark[0].sym->value;
	}
break;
case 107:
#line 555 "a.y"
	{
		yyval.lval = -yystack.l_mark[0].lval;
	}
break;
case 108:
#line 559 "a.y"
	{
		yyval.lval = yystack.l_mark[0].lval;
	}
break;
case 109:
#line 563 "a.y"
	{
		yyval.lval = ~yystack.l_mark[0].lval;
	}
break;
case 110:
#line 567 "a.y"
	{
		yyval.lval = yystack.l_mark[-1].lval;
	}
break;
case 112:
#line 574 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval + yystack.l_mark[0].lval;
	}
break;
case 113:
#line 578 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval - yystack.l_mark[0].lval;
	}
break;
case 114:
#line 582 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval * yystack.l_mark[0].lval;
	}
break;
case 115:
#line 586 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval / yystack.l_mark[0].lval;
	}
break;
case 116:
#line 590 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval % yystack.l_mark[0].lval;
	}
break;
case 117:
#line 594 "a.y"
	{
		yyval.lval = yystack.l_mark[-3].lval << yystack.l_mark[0].lval;
	}
break;
case 118:
#line 598 "a.y"
	{
		yyval.lval = yystack.l_mark[-3].lval >> yystack.l_mark[0].lval;
	}
break;
case 119:
#line 602 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval & yystack.l_mark[0].lval;
	}
break;
case 120:
#line 606 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval ^ yystack.l_mark[0].lval;
	}
break;
case 121:
#line 610 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval | yystack.l_mark[0].lval;
	}
break;
#line 1410 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
