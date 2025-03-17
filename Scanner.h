/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: Alvin Gono AND Igor Wambyakaley
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLL                     @@    ”
# ECHO "    @@     LLLLLLLLL  PPPPPPP      @@    ”
# ECHO "    @@     LLLLLLLLL  PPP   PPP    @@    ”
# ECHO "    @@                PP      PP   @@    ”
# ECHO "    @@                PPP   PPP    @@    ”
# ECHO "    @@                PPPPPPP      @@    ”
# ECHO "    @@                PPP          @@    ”
# ECHO "    @@                PPP          @@    ”
# ECHO "    @@                PPP          @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@           LAZY PY           @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/


/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 15

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	FLT_T,		/* 13: FLOAT literal token */
	VID_T		/* 13: FLOAT literal token */
};

/* TO_DO: Define the list of keywords */
static lp_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"FLT_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV , OP_MOD} AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	lp_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	lp_intg intValue;				/* integer literal attribute (value) */
	lp_intg keywordIndex;			/* keyword index in the keyword table */
	lp_intg contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	lp_real floatValue;				/* floating-point literal attribute (value) */
	lp_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	lp_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	lp_byte flags;			/* Flags information */
	union {
		lp_intg intValue;				/* Integer value */
		lp_real floatValue;			/* Float value */
		lp_string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	lp_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	lp_intg scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* TO_DO: Define lexeme FIXED classes */
/* EOF definitions */
#define EOS_CHR '\0'	// CH00
#define EOF_CHR 0xFF	// CH01
#define UND_CHR '_'		// CH02
#define AMP_CHR '&'		// CH03
#define QUT_CHR '\''	// CH04
#define HST_CHR '#'		// CH05
#define TAB_CHR '\t'	// CH06
#define SPC_CHR ' '		// CH07
#define NWL_CHR '\n'	// CH08
#define SCL_CHR ';'		// CH09
#define LPR_CHR '('		// CH10
#define RPR_CHR ')'		// CH11
#define LBR_CHR '{'		// CH12
#define RBR_CHR '}'		// CH13
#define SCP_CHR ':'		// CH14
#define OAB_CHR '['		// CH15
#define CAB_CHR ']'		// CH16
#define PRD_CHR '.'		// CH17
#define AQT_CHR '"'		// CH18




/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */


/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */


 /* TO_DO: State transition table definition */
#define NUM_STATES		19
#define CHAR_CLASSES	10

/* TO_DO: Transition table - type of states defined in separate table */
static lp_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    ",   #,    ',     ,        . ,   (,    other
	   L(0), D(1), U(2), K(3), H(4), Q(5), [a-z](7) , F(8), Bo(9), O(10) */
	{  ESNR,   13, ESNR,   11,	 18,	4,         1, ESNR  ,ESNR,	ESNR},	// S0: NOAS
	{     1,    1,    1,   2,	 2,		2,	       1,	 2 ,	3,	ESNR},	// S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},	// S2: ASNR (VARID|KEY)
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},	// S3: ASWR (FUNCID)
	{     4,    4,    4,    4,    4,    5,         4,     4,     4,    4},	// S4: NOAS
	{  ESNR, ESNR, ESNR, ESNR, ESNR,    6, 	    ESNR,  ESNR,  ESNR,	ESNR},	// S5: NOAR 
	{     6,    6,    6,    6,    6,    7,         6,     6,     6,    6},	// S6: NOAS
	{  ESNR, ESNR, ESNR, ESNR, ESNR,    8,      ESNR,  ESNR,  ESNR,	ESNR},	// S7: NOAR
	{  ESNR, ESNR, ESNR, ESNR, ESNR,    9,      ESNR,  ESNR,  ESNR,	ESNR},	// S8: NOAR
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},  // S9: ASWR (COM)
	//{  FSNR, FSNR, FSNR, FSNR, FSNR, FSNR,      FSNR,  FSNR,  FSNR,	FSNR},  // S10: ASWR (SCOM)
	{    11,   11,   11,  12,	 11,   11,	  	  11,	 11,	11,	  11},	// S11: NOAS
	{   FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},	// S12: ASNR (SL)
	{    17,   13,   17,   17,	 17,   17,	  	  17,	 14,	17,	ESNR},	// S13: NOAR 
	{  ESNR,   15, ESNR, ESNR, ESNR, ESNR,      ESNR,  ESNR,  ESNR,	ESNR},	// S14: NOAS
	{    16,   15,   16,   16,	 16,   16,	  	  16,	 16,	16,	ESNR},	// S15: NOAR
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},	// S16: ASNR (FLOAT)
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS},	// S17: ASNR (INT)
	{    18,   18,   18,   18,	 19,   18,	 	  18,	 18,	18,	ESNR},	// S18: NOAR 
	{    FS,   FS,   FS,   FS,   FS,   FS,        FS,    FS,    FS,	  FS}  // S19: ASWR (SCOM)
};


/* TO_DO: Define list of acceptable states */
static lp_intg stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY/VAR) - Methods */
	FSWR, /* 03 (MID) */
	NOFS, /* 04 */
	NOFS, /* 05  */
	NOFS, /* 06 */
	NOFS, /* 07 (*/
	NOFS, /* 08  */
	FSNR, /* 09 (COM)*/
	
	NOFS, /* 11 */
	FSNR, /* 12 (SL)  */
	NOFS, /* 13  */
	NOFS, /* 14 */
	NOFS, /* 15  */
	FSWR, /* 16 (FLOAT)*/
	FSWR, /* 17 (INT) */
	NOFS, /* 18 */
	FSNR /* 19 (SCOM) */

};
/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
lp_intg			startScanner(BufferPointer psc_buf);
static lp_intg	nextClass(lp_char c);					/* character class function */
static lp_intg	nextState(lp_intg, lp_char);		/* state machine function */
lp_void			printScannerData(ScannerData scData);
Token				tokenizer(lp_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(lp_string lexeme);

/* Declare accepting states functions */
Token funcSL	(lp_string lexeme);
Token funcIL	(lp_string lexeme);
Token funcID	(lp_string lexeme);
Token funcCMT   (lp_string lexeme);
Token funcKEY	(lp_string lexeme);
Token funcErr	(lp_string lexeme);
Token funcFL   (lp_string lexeme);




/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcKEY,		/* MNID	[02] */
	funcID ,	/* KEY  [03] */
	NULL,		/* -    [04] */
	NULL,		/* SL   [05] */
	NULL,		/* -    [06] */
	NULL,	/* COM  [07] */
	NULL,	/* ERR1 [08] */
	funcCMT,		/* -    [09] */
	NULL,		/* MNID	[11] */
	funcSL,	/* KEY  [12] */
	NULL,		/* -    [13] */
	NULL,		/* -    [14] */
	NULL,		/* SL   [15] */
	funcFL,		/* -    [16] */
	funcIL,	/* COM  [17] */
	NULL,   /* ERR1 [18] */
	funcCMT 	/* ERR2 [19] */
	
	
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 20

/* TO_DO: Define the list of keywords */
static lp_string keywordTable[KWT_SIZE] = {
	"data",		/* KW00 */
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do",		/* KW09 */
	"return",	/* KW10 */
	"def",	    /* KW11 */
	"for",	   /* KW12 */
	"true",	/* KW13 */
	"false",	/* KW14 */
	"break",	/* KW15 */
	"elif",	/* KW16 */
    "continue",	/* KW17 */
	"finaly",	/* KW18 */
	"print"	/* KW19 */

	
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT TAB_CHR  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	lp_char indentationCharType;
	lp_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
lp_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
