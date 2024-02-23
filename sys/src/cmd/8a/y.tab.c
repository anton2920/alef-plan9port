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

#line 2 "a.y"
#include "a.h"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 4 "a.y"
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
#line 43 "y.tab.c"

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
    0,    0,   32,   31,   33,   31,   31,   31,   31,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   17,   17,   21,   22,   20,
   20,   19,   19,   18,   18,   23,   24,   24,   25,   25,
   26,   26,   27,   27,   28,   28,   29,   29,   29,   30,
   30,   12,   12,   14,   14,   14,   14,   14,   14,   14,
   13,   13,   11,   11,   11,    9,    9,    9,    9,    9,
    7,    7,    7,    7,    7,    7,    8,    5,    5,    5,
    5,    6,    6,   15,   15,   15,   15,   15,   15,   15,
   15,   15,   15,   16,   16,   10,   10,    4,    4,    4,
    3,    3,    3,    1,    1,    1,    1,    1,    1,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
};
static const YYINT yylen[] = {                            2,
    0,    2,    0,    4,    0,    4,    1,    2,    2,    3,
    3,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    0,    1,    3,    3,    2,
    1,    2,    1,    2,    1,    5,    3,    5,    2,    1,
    1,    1,    3,    5,    3,    5,    2,    1,    3,    3,
    5,    1,    1,    1,    1,    2,    2,    1,    1,    1,
    1,    1,    4,    2,    2,    1,    1,    1,    1,    1,
    2,    2,    2,    2,    4,    3,    2,    1,    2,    3,
    4,    1,    1,    1,    4,    4,    6,    9,    3,    3,
    4,    5,    8,    1,    6,    5,    7,    0,    2,    2,
    1,    1,    1,    1,    1,    2,    2,    2,    3,    1,
    3,    3,    3,    3,    3,    4,    4,    3,    3,    3,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
    2,    0,    9,   27,   12,    0,    0,  104,   66,   68,
   70,   67,   69,    0,  105,    0,    0,    0,    0,   53,
   52,    0,   33,   82,   83,   13,    0,   62,   61,    0,
   14,    0,   15,    0,   16,    0,    0,    0,    0,    0,
   60,   58,   54,   40,   59,   55,   20,    0,   18,    0,
   41,   42,   21,    0,    0,    0,    0,   35,   17,    0,
   19,    0,   22,    0,   23,    0,   24,    0,   25,    5,
    0,    3,    0,    8,  107,  106,    0,    0,    0,    0,
   32,    0,    0,  110,    0,  108,    0,    0,    0,   74,
   73,    0,   71,   72,   30,    0,    0,   56,   57,    0,
   65,   39,    0,    0,   64,   34,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   99,  100,    0,
    0,    0,   90,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  109,    0,    0,    0,    0,   76,    0,
   28,   29,    0,    0,    0,   37,    0,    0,   49,    0,
   50,    6,    4,    0,  103,  101,  102,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  113,  114,  115,
    0,    0,   91,   86,    0,   75,   63,    0,    0,    0,
    0,    0,    0,   96,   92,    0,    0,    0,    0,    0,
    0,   36,   38,   44,   46,   51,    0,    0,   87,    0,
   95,   97,    0,    0,   93,    0,   88,
};
static const YYINT yydgoto[] = {                          1,
   39,  105,  178,  100,    0,   40,   48,    0,   41,   42,
   63,   49,   50,   64,   44,   45,   25,   79,   46,   51,
   53,   55,   69,   81,   67,   73,   83,   85,   87,   89,
   21,  135,  133,   22,
};
static const YYINT yysindex[] = {                         0,
  120,  -57,  -27,    4,   -8,   -8,   28,  -36, -255,   16,
   48,   77,   -8,   -8,   -8,   77,  -15,  -13,   21,    0,
    0,   -1,    0,    0,    0,   12,   12,    0,    0,    0,
    0,    0,    0,   27,    0,   28,   66,   12,   13,    0,
    0,   49,    0,    0,    0,    0,   54,    0,    0,   51,
    0,   56,    0,   59,    0,   40,   27,   20,  -22,   68,
    0,    0,    0,    0,    0,    0,    0,   65,    0,   28,
    0,    0,    0,   20,   70,   12,   83,    0,    0,   88,
    0,   89,    0,  106,    0,  112,    0,  116,    0,    0,
   12,    0,   12,    0,    0,    0,   81,   12,   12,  125,
    0,   -2,  134,    0,  110,    0, -132, -109,   84,    0,
    0,   91,    0,    0,    0,   28,   -8,    0,    0,  125,
    0,    0,  124,   12,    0,    0,  -95,   -7,   28,   28,
   28,   -7,  120,  126,  120,  126,   20,    0,    0, -195,
   12,  144,    0,   12,   12,   12,  131,  123,   12,   12,
   12,   12,   12,    0,  141,  157,  167,  174,    0,  177,
    0,    0,  178,  180,  181,    0,  168,  173,    0,  188,
    0,    0,    0,  193,    0,    0,    0,  195,  196,  -38,
  423,  152,  456,   12,   12,   79,   79,    0,    0,    0,
   12,  203,    0,    0,   12,    0,    0,  208,  208,  -25,
  -20,  208,  -16,    0,    0,  210,  370,  370,  224,  -10,
  230,    0,    0,    0,    0,    0,  231,   12,    0,  236,
    0,    0,  243,   12,    0,  248,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,  242,    0,    0,    0,    0,    0,    0,  242,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  250,    0,    0,    0,    0,  118,    0,
    0,  163,    0,    0,    0,    0,    0,    0,    0,  249,
    0,    0,    0,    0,    0,    0,  -18,  254,    0,  255,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  261,
    0,    0,    0,  254,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  263,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  264,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  267,    0,    0,  268,    0,  269,  250,    0,    0,    0,
    0,  169,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  270,  276,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -28,  -40,   87,    0,    0,  373,  381,    0,    0,    0,
    0,  171,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   99,  305,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  383,  302,    0,  -32,    0,   18,    7,    0,    8,   15,
   -6,   71,   -3,  280,   42,   43,  285,    0,  292,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -59,    0,    0,    0,
};
#define YYTABLESIZE 607
static const YYINT yytable[] = {                         47,
  119,   23,   52,   37,   78,   56,   26,   59,   27,   82,
   84,   86,  120,   47,   61,   62,   24,   37,  119,   56,
   26,   98,   27,   68,  120,  121,   34,   47,   47,   80,
  120,   37,   76,   88,   26,   26,   27,   27,  142,  141,
   98,  125,   90,   37,   92,   91,   26,   36,   27,   65,
   66,   76,  107,  119,   26,   37,   27,   94,   26,   70,
   27,  114,   98,  118,   99,   61,   62,   37,  126,   98,
   26,   99,   27,  172,   43,  173,  175,   54,  176,   37,
   43,   93,   26,  119,   27,  177,   97,   76,  108,   38,
   26,   75,   27,  112,  115,  120,   26,  119,  109,  116,
   65,   66,  117,   38,  174,   76,  101,  123,   26,   76,
   27,  124,   26,  162,   27,  153,   37,   38,   38,   26,
  151,   27,  127,   76,  118,  152,   26,  118,   27,   38,
   76,  128,  129,   26,  166,   27,  116,   38,  171,  116,
  101,   38,  137,  155,  156,  118,  153,  146,  157,  130,
  154,  151,  149,   38,  150,  131,  152,  116,  116,  132,
  116,   84,  153,  146,  140,   38,  158,  151,  149,  147,
  150,  148,  152,   38,  143,   84,   84,  163,   20,   38,
  118,  192,  191,  180,  185,  147,  161,  148,  153,  146,
  184,   38,  116,  151,  149,   38,  150,  193,  152,  167,
  168,  169,   38,  145,  212,  213,   94,  194,  216,   38,
  118,  147,   89,  148,   85,  195,   38,  196,  197,  145,
   94,   94,  116,  198,  199,  200,   89,   89,   85,   85,
  201,  202,  203,  144,   28,  204,  205,  206,   29,   30,
   31,   32,  210,   47,   33,   57,   58,   35,   28,  144,
  214,  218,   29,   30,   31,   32,  215,  217,   33,   57,
   58,   35,   28,   28,  219,  220,   29,   30,   31,   32,
  221,  222,   33,   34,   28,   35,   35,  224,   29,   30,
   31,   32,   28,  225,   33,   34,   28,   35,  227,   98,
   29,   30,   31,   32,   71,   35,   33,   34,   28,   35,
   26,   72,   29,   30,   31,   32,    0,   31,   33,   34,
   28,   35,   98,   84,   29,   30,   31,   32,   28,   27,
   33,   48,   64,   35,   28,   47,   10,   11,   43,   74,
   58,   35,  110,  111,   45,   34,   28,   35,  122,    0,
   28,  102,  117,    0,    0,  117,  103,   28,    0,   35,
    0,   74,   58,   35,   28,    0,    0,    0,   34,    0,
   35,   28,  159,  117,  117,    0,  117,   35,    0,  160,
    0,    0,    0,    0,   35,    2,    3,    4,    5,    6,
    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
   60,    0,  134,   77,  136,    0,  163,    0,  117,  155,
  156,   17,   18,   19,  157,    0,  153,    0,   95,   96,
  111,  151,  149,  111,  150,  111,  152,  111,  112,  104,
  106,  112,    0,  112,    0,  112,    0,    0,  117,  113,
    0,  111,  111,    0,  111,    0,    0,    0,    0,  112,
  112,   60,  112,    0,    0,  181,  182,  183,    0,    0,
  186,  187,  188,  189,  190,    0,    0,   77,  104,  153,
  146,    0,    0,    0,  151,  149,  111,  150,    0,  152,
    0,    0,    0,  104,  112,  104,    0,    0,    0,    0,
  138,  139,  147,    0,  148,  207,  208,    0,    0,    0,
    0,   96,  153,    0,  104,    0,  111,  151,  149,    0,
  150,    0,  152,    0,  112,    0,  164,    0,    0,    0,
  165,    0,    0,    0,  170,  147,  145,  148,    0,    0,
    0,    0,    0,  179,    0,    0,  104,  104,  104,    0,
    0,  104,  104,  104,  104,  104,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  104,  104,    0,    0,
    0,    0,    0,  209,    0,    0,    0,  211,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  223,    0,    0,    0,    0,    0,  226,
};
static const YYINT yycheck[] = {                         36,
   41,   59,    6,   40,   11,   42,   43,   44,   45,   13,
   14,   15,   41,   36,    8,    8,   44,   40,   59,   42,
   43,   40,   45,    9,   57,   58,  282,   36,   36,   12,
   59,   40,   40,   16,   43,   43,   45,   45,   41,   42,
   59,   74,   58,   40,   58,   61,   43,   44,   45,    8,
    8,   40,   40,   94,   43,   40,   45,   59,   43,   44,
   45,   47,   43,   56,   45,   59,   59,   40,   75,   43,
   43,   45,   45,  133,    4,  135,  272,    7,  274,   40,
   10,   61,   43,  124,   45,  281,   60,   40,   40,  126,
   43,   44,   45,   40,   44,  124,   43,   56,   45,   44,
   59,   59,   44,  126,  137,   40,   36,   40,   43,   40,
   45,   47,   43,  117,   45,   37,   40,  126,  126,   43,
   42,   45,   40,   40,   38,   47,   43,   41,   45,  126,
   40,   44,   44,   43,  128,   45,   38,  126,  132,   41,
   70,  126,   62,  276,  277,   59,   37,   38,  281,   44,
   41,   42,   43,  126,   45,   44,   47,   59,   60,   44,
   62,   44,   37,   38,   40,  126,  276,   42,   43,   60,
   45,   62,   47,  126,   41,   58,   59,  273,   59,  126,
   94,   41,   42,   40,   62,   60,  116,   62,   37,   38,
   60,  126,   94,   42,   43,  126,   45,   41,   47,  129,
  130,  131,  126,   94,  198,  199,   44,   41,  202,  126,
  124,   60,   44,   62,   44,   42,  126,   41,   41,   94,
   58,   59,  124,   44,   44,   58,   58,   59,   58,   59,
   58,   44,   40,  124,  271,   41,   41,  276,  275,  276,
  277,  278,   40,   36,  281,  282,  283,  284,  271,  124,
  276,   42,  275,  276,  277,  278,  277,  274,  281,  282,
  283,  284,  271,  271,   41,  276,  275,  276,  277,  278,
   41,   41,  281,  282,  271,  284,  284,   42,  275,  276,
  277,  278,  271,   41,  281,  282,  271,  284,   41,   40,
  275,  276,  277,  278,   10,  284,  281,  282,  271,  284,
   59,   10,  275,  276,  277,  278,   -1,   59,  281,  282,
  271,  284,   59,   59,  275,  276,  277,  278,  271,   59,
  281,   59,   59,  284,  271,   59,   59,   59,   59,  282,
  283,  284,  279,  280,   59,  282,  271,  284,   59,   -1,
  271,  276,   38,   -1,   -1,   41,  281,  271,   -1,  284,
   -1,  282,  283,  284,  271,   -1,   -1,   -1,  282,   -1,
  284,  271,  279,   59,   60,   -1,   62,  284,   -1,  279,
   -1,   -1,   -1,   -1,  284,  256,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
    8,   -1,   91,   11,   93,   -1,  273,   -1,   94,  276,
  277,  282,  283,  284,  281,   -1,   37,   -1,   26,   27,
   38,   42,   43,   41,   45,   43,   47,   45,   38,   37,
   38,   41,   -1,   43,   -1,   45,   -1,   -1,  124,   47,
   -1,   59,   60,   -1,   62,   -1,   -1,   -1,   -1,   59,
   60,   59,   62,   -1,   -1,  144,  145,  146,   -1,   -1,
  149,  150,  151,  152,  153,   -1,   -1,   75,   76,   37,
   38,   -1,   -1,   -1,   42,   43,   94,   45,   -1,   47,
   -1,   -1,   -1,   91,   94,   93,   -1,   -1,   -1,   -1,
   98,   99,   60,   -1,   62,  184,  185,   -1,   -1,   -1,
   -1,  109,   37,   -1,  112,   -1,  124,   42,   43,   -1,
   45,   -1,   47,   -1,  124,   -1,  124,   -1,   -1,   -1,
  128,   -1,   -1,   -1,  132,   60,   94,   62,   -1,   -1,
   -1,   -1,   -1,  141,   -1,   -1,  144,  145,  146,   -1,
   -1,  149,  150,  151,  152,  153,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  184,  185,   -1,   -1,
   -1,   -1,   -1,  191,   -1,   -1,   -1,  195,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  218,   -1,   -1,   -1,   -1,   -1,  224,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 321
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
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : prog",
"prog :",
"prog : prog line",
"$$1 :",
"line : LLAB ':' $$1 line",
"$$2 :",
"line : LNAME ':' $$2 line",
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
"spec2 : mem ',' imm",
"spec2 : mem ',' con ',' imm",
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
case 3:
#line 40 "a.y"
	{
		if(yystack.l_mark[-1].sym->value != pc)
			yyerror("redeclaration of %s", yystack.l_mark[-1].sym->name);
		yystack.l_mark[-1].sym->value = pc;
	}
break;
case 5:
#line 47 "a.y"
	{
		yystack.l_mark[-1].sym->type = LLAB;
		yystack.l_mark[-1].sym->value = pc;
	}
break;
case 10:
#line 58 "a.y"
	{
		yystack.l_mark[-2].sym->type = LVAR;
		yystack.l_mark[-2].sym->value = yystack.l_mark[0].lval;
	}
break;
case 11:
#line 63 "a.y"
	{
		if(yystack.l_mark[-2].sym->value != yystack.l_mark[0].lval)
			yyerror("redeclaration of %s", yystack.l_mark[-2].sym->name);
		yystack.l_mark[-2].sym->value = yystack.l_mark[0].lval;
	}
break;
case 12:
#line 68 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 13:
#line 69 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 14:
#line 70 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 15:
#line 71 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 16:
#line 72 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 17:
#line 73 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 18:
#line 74 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 19:
#line 75 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 20:
#line 76 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 21:
#line 77 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 22:
#line 78 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 23:
#line 79 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 24:
#line 80 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 25:
#line 81 "a.y"
	{ outcode(yystack.l_mark[-1].lval, &yystack.l_mark[0].gen2); }
break;
case 26:
#line 84 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	}
break;
case 27:
#line 89 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	}
break;
case 28:
#line 96 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 29:
#line 103 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 30:
#line 110 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-1].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 31:
#line 115 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[0].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 32:
#line 122 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 33:
#line 127 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 34:
#line 134 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 35:
#line 139 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 36:
#line 146 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 37:
#line 154 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 38:
#line 159 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 39:
#line 167 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 40:
#line 172 "a.y"
	{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 43:
#line 183 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 44:
#line 188 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.to = yystack.l_mark[-2].gen;
		if(yyval.gen2.from.index != D_NONE)
			yyerror("dp shift with lhs index");
		yyval.gen2.from.index = yystack.l_mark[0].lval;
	}
break;
case 45:
#line 198 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 46:
#line 203 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.to = yystack.l_mark[-2].gen;
		if(yyval.gen2.to.index != D_NONE)
			yyerror("dp move with lhs index");
		yyval.gen2.to.index = yystack.l_mark[0].lval;
	}
break;
case 47:
#line 213 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-1].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 48:
#line 218 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[0].gen;
		yyval.gen2.to = nullgen;
	}
break;
case 49:
#line 223 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 50:
#line 230 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-2].gen;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 51:
#line 235 "a.y"
	{
		yyval.gen2.from = yystack.l_mark[-4].gen;
		yyval.gen2.from.scale = yystack.l_mark[-2].lval;
		yyval.gen2.to = yystack.l_mark[0].gen;
	}
break;
case 56:
#line 249 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 57:
#line 253 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 63:
#line 266 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yystack.l_mark[-3].lval + pc;
	}
break;
case 64:
#line 272 "a.y"
	{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yystack.l_mark[-1].sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yystack.l_mark[-1].sym;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 65:
#line 281 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yystack.l_mark[-1].sym;
		yyval.gen.offset = yystack.l_mark[-1].sym->value + yystack.l_mark[0].lval;
	}
break;
case 66:
#line 290 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 67:
#line 295 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 68:
#line 300 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 69:
#line 305 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_SP;
	}
break;
case 70:
#line 310 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[0].lval;
	}
break;
case 71:
#line 317 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 72:
#line 323 "a.y"
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
case 73:
#line 334 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yystack.l_mark[0].sval, sizeof(yyval.gen.sval));
	}
break;
case 74:
#line 340 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yystack.l_mark[0].dval;
	}
break;
case 75:
#line 346 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yystack.l_mark[-1].dval;
	}
break;
case 76:
#line 352 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yystack.l_mark[0].dval;
	}
break;
case 77:
#line 360 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST2;
		yyval.gen.offset = yystack.l_mark[0].con2.v1;
		yyval.gen.offset2 = yystack.l_mark[0].con2.v2;
	}
break;
case 78:
#line 369 "a.y"
	{
		yyval.con2.v1 = yystack.l_mark[0].lval;
		yyval.con2.v2 = 0;
	}
break;
case 79:
#line 374 "a.y"
	{
		yyval.con2.v1 = -yystack.l_mark[0].lval;
		yyval.con2.v2 = 0;
	}
break;
case 80:
#line 379 "a.y"
	{
		yyval.con2.v1 = yystack.l_mark[-2].lval;
		yyval.con2.v2 = yystack.l_mark[0].lval;
	}
break;
case 81:
#line 384 "a.y"
	{
		yyval.con2.v1 = -yystack.l_mark[-2].lval;
		yyval.con2.v2 = yystack.l_mark[0].lval;
	}
break;
case 84:
#line 395 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yystack.l_mark[0].lval;
	}
break;
case 85:
#line 401 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 86:
#line 407 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 87:
#line 413 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yystack.l_mark[-5].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 88:
#line 422 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-6].lval;
		yyval.gen.offset = yystack.l_mark[-8].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 89:
#line 431 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
	}
break;
case 90:
#line 436 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
	}
break;
case 91:
#line 441 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-1].lval;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 92:
#line 447 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 93:
#line 455 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yystack.l_mark[-6].lval;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 94:
#line 465 "a.y"
	{
		yyval.gen = yystack.l_mark[0].gen;
	}
break;
case 95:
#line 469 "a.y"
	{
		yyval.gen = yystack.l_mark[-5].gen;
		yyval.gen.index = yystack.l_mark[-3].lval;
		yyval.gen.scale = yystack.l_mark[-1].lval;
		checkscale(yyval.gen.scale);
	}
break;
case 96:
#line 478 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = yystack.l_mark[-1].lval;
		yyval.gen.sym = yystack.l_mark[-4].sym;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 97:
#line 485 "a.y"
	{
		yyval.gen = nullgen;
		yyval.gen.type = D_STATIC;
		yyval.gen.sym = yystack.l_mark[-6].sym;
		yyval.gen.offset = yystack.l_mark[-3].lval;
	}
break;
case 98:
#line 493 "a.y"
	{
		yyval.lval = 0;
	}
break;
case 99:
#line 497 "a.y"
	{
		yyval.lval = yystack.l_mark[0].lval;
	}
break;
case 100:
#line 501 "a.y"
	{
		yyval.lval = -yystack.l_mark[0].lval;
	}
break;
case 102:
#line 508 "a.y"
	{
		yyval.lval = D_AUTO;
	}
break;
case 105:
#line 516 "a.y"
	{
		yyval.lval = yystack.l_mark[0].sym->value;
	}
break;
case 106:
#line 520 "a.y"
	{
		yyval.lval = -yystack.l_mark[0].lval;
	}
break;
case 107:
#line 524 "a.y"
	{
		yyval.lval = yystack.l_mark[0].lval;
	}
break;
case 108:
#line 528 "a.y"
	{
		yyval.lval = ~yystack.l_mark[0].lval;
	}
break;
case 109:
#line 532 "a.y"
	{
		yyval.lval = yystack.l_mark[-1].lval;
	}
break;
case 111:
#line 539 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval + yystack.l_mark[0].lval;
	}
break;
case 112:
#line 543 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval - yystack.l_mark[0].lval;
	}
break;
case 113:
#line 547 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval * yystack.l_mark[0].lval;
	}
break;
case 114:
#line 551 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval / yystack.l_mark[0].lval;
	}
break;
case 115:
#line 555 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval % yystack.l_mark[0].lval;
	}
break;
case 116:
#line 559 "a.y"
	{
		yyval.lval = yystack.l_mark[-3].lval << yystack.l_mark[0].lval;
	}
break;
case 117:
#line 563 "a.y"
	{
		yyval.lval = yystack.l_mark[-3].lval >> yystack.l_mark[0].lval;
	}
break;
case 118:
#line 567 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval & yystack.l_mark[0].lval;
	}
break;
case 119:
#line 571 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval ^ yystack.l_mark[0].lval;
	}
break;
case 120:
#line 575 "a.y"
	{
		yyval.lval = yystack.l_mark[-2].lval | yystack.l_mark[0].lval;
	}
break;
#line 1397 "y.tab.c"
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
