/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: TO_DO
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
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: Sep 01 2024
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* TO_DO: Adjust your language (cannot be "Sofia") */

/* TO_DO: Language name */
#define STR_LANGNAME	"LazyPy"

/* TO_DO: Logical constants - adapt for your language */
#define LP_TRUE		1
#define LP_FALSE		0
#define LP_ERROR		(-1)	/* General error message */

#define LP_INVALID	NULL

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/


/* TO_DO: Define your typedefs */
typedef char			lp_char;
typedef char*			lp_string;
typedef int				lp_intg;
typedef float			lp_real;
typedef void			lp_void;

typedef char			lp_boln;
typedef unsigned char	lp_byte;

typedef long			lp_long;
typedef double			lp_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER  = '1',
	PGM_SCANNER = '2',
	PGM_PARSER  = '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
lp_intg mainReader(lp_intg argc, lp_string* argv);
lp_intg mainScanner(lp_intg argc, lp_string* argv);
lp_intg mainParser(lp_intg argc, lp_string* argv);

lp_void printLogo();

#endif
