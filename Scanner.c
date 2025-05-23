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
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "    @@                             @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLL                     @@    �
# ECHO "    @@     LLLLLLLLL  PPPPPPP      @@    �
# ECHO "    @@     LLLLLLLLL  PPP   PPP    @@    �
# ECHO "    @@                PP      PP   @@    �
# ECHO "    @@                PPP   PPP    @@    �
# ECHO "    @@                PPPPPPP      @@    �
# ECHO "    @@                PPP          @@    �
# ECHO "    @@                PPP          @@    �
# ECHO "    @@                PPP          @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@           LAZY PY           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/


/*
************************************************************
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#define NDEBUG
#include <assert.h>  /* assert() prototype */


/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

int numScannerErrors = 0;
ScannerData scData;

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
lp_intg line;								/* Current line number of the source code */
extern lp_intg errorNumber;				/* Defined in platy_st.c - run-time error number */

extern lp_intg stateType[NUM_STATES];
extern lp_string keywordTable[KWT_SIZE];

extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern lp_intg transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

lp_intg startScanner(BufferPointer psc_buf) {
	/* TO_DO: Start histogram */
	for (lp_intg i = 0; i < NUM_TOKENS;i++) {
		scData.scanHistogram[i] = 0;
	}
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(lp_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	lp_char c;			/* input symbol */
	lp_intg state = 0;	/* initial state of the FSM */
	lp_intg lexStart;	/* start offset of a lexeme in the input char buffer (array) */
	lp_intg lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	lp_intg lexLength;	/* token length */
	lp_intg i;			/* counter */
	///lp_char newc;		// new char

	/* Starting lexeme */
	lp_string lexeme;	/* lexeme (to check the function) */
	lexeme = (lp_string)malloc(VID_LEN * sizeof(lp_char));
	if (!lexeme)
		return currentToken;
    // check rn
	lexeme[0] = EOS_CHR;

	while (1) { /* endless loop broken by token returns it will generate a warning */
        int size = 0;
		c = readerGetChar(sourceBuffer);

		// TO_DO: Defensive programming
		if (c < 0 || c >= NCHAR) {
            if (c == EOF_CHR) {
                currentToken.code = SEOF_T;
                scData.scanHistogram[currentToken.code]++;
                currentToken.attribute.seofType = SEOF_255;
                return currentToken;
            }
            return currentToken;
        }

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case SPC_CHR:
            printf("SPC_CHR\n");
            numOfSpaces++;
            break;
		case TAB_CHR:
            printf("TAB_CHR\n");
			break;
		case NWL_CHR:
            numOfSpaces = 0;
			line++;
			break;

		/* Cases for symbols */
		case SCL_CHR:
			currentToken.code = EOS_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
        case EQL_CHR:
            // we have a "=" character
            // check if its a assignment operator or a comparison operator
            // if the next character is a "=" character then its a comparison operator
            // otherwise its a assignment operator
            c = readerGetChar(sourceBuffer);
            if (c == EQL_CHR) {
                currentToken.code = CMP_T;
                scData.scanHistogram[currentToken.code]++;
                return currentToken;
            } else {
                currentToken.code = ASG_T;
                scData.scanHistogram[currentToken.code]++;
                // we have an assignment operator now we check what exactly is being assigned

                // loop until we reach a new line character
                lp_intg innerSize = 0;
                while ((c = readerGetChar(sourceBuffer)) != NWL_CHR) {
                    // if we reach a new line character then we have reached the end of the assignment
                    if (c == NWL_CHR) {
                        readerRetract(sourceBuffer);
                        break;
                    }
                    innerSize++;
                }
                // go back to original position before the assignment
                for (int y = 0; y < innerSize + 1; y++) {
                    readerRetract(sourceBuffer);
                }
                lexemeBuffer = readerCreate(innerSize + 1, 0, MODE_FIXED);
                // Process the assignment until the end of the assignment or file
                while ((c = readerGetChar(sourceBuffer)) != NWL_CHR) {
                    // add the character to the lexeme buffer
                    readerAddChar(lexemeBuffer, c);
                }
                // allocate space for the lexeme string
                lexeme = (lp_string)malloc(innerSize * sizeof(lp_char));
                // move the contents of the lexeme buffer to the lexeme string to save token contents
                strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
                // free the lexeme buffer
                readerFree(lexemeBuffer);
                // Set the assignment in the token's attribute
                strncpy(currentToken.attribute.idLexeme, lexeme, innerSize + 1);
                currentToken.attribute.idLexeme[innerSize + 1] = EOS_CHR;

                return currentToken;
            }

        case UND_CHR:
            // we have an "_" character
            // most case it will be __main__
            // special identifiers like these require 2 underscores then the name
            // proceed with caution
            currentToken.code = SPL_VAR_T;
            scData.scanHistogram[currentToken.code]++;
            size = 0;

            // dynamically allocate a buffer to store the identifier
            // traverses the buffer until the next space character
            while ((c = readerGetChar(sourceBuffer)) != SPC_CHR) {
                size++;
            }

            // go back to original position before the identifier
            for (int y = 0; y < size + 2; y++) {
                readerRetract(sourceBuffer);
            }
            lexemeBuffer = readerCreate(size + 1, 0, MODE_FIXED);
            // Process the identifier until the end of the identifier or file
            while ((c = readerGetChar(sourceBuffer)) != SPC_CHR) {
                // add the character to the lexeme buffer
                readerAddChar(lexemeBuffer, c);
            }
            // allocate space for the lexeme string
            lexeme = (lp_string)malloc(size * sizeof(lp_char));
            // move the contents of the lexeme buffer to the lexeme string to save token contents
            strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
            // free the lexeme buffer
            readerFree(lexemeBuffer);
            // Set the identifier in the token's attribute
            strncpy(currentToken.attribute.idLexeme, lexeme, size + 1);
            currentToken.attribute.idLexeme[size + 1] = EOS_CHR;

            return currentToken;
        case AQT_CHR:
            // we have a '"' character
            currentToken.code = STR_T;
            size = 0;
            scData.scanHistogram[currentToken.code]++;
            // dynamically allocate a buffer to store the string literal
            // traverses the buffer until the next quote character
            while ((c = readerGetChar(sourceBuffer)) != AQT_CHR) {
                if (c == NWL_CHR) {
                    line++;
                }
                size++;
            }
            // go back to original position before the string literal
            for (int y = 0; y < size + 1; y++) {
                readerRetract(sourceBuffer);
            }
            lexemeBuffer = readerCreate(size + 1, 0, MODE_FIXED);
            // Process the string literal until the end of the string or file
            while ((c = readerGetChar(sourceBuffer)) != AQT_CHR) {
                // add the character to the lexeme buffer
                readerAddChar(lexemeBuffer, c);
                if (c == NWL_CHR) {
                    line++;
                }
            }
            // allocate space for the lexeme string
            lexeme = (lp_string)malloc(size * sizeof(lp_char));
            // move the contents of the lexeme buffer to the lexeme string to save token contents
            strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
            // free the lexeme buffer
            readerFree(lexemeBuffer);
            // Set the string literal in the token's attribute
            strncpy(currentToken.attribute.idLexeme, lexeme, size + 1);
            currentToken.attribute.idLexeme[size + 1] = EOS_CHR;
            return currentToken;
        case QUT_CHR:
            currentToken.code = STR_T;
            size = 0;
            scData.scanHistogram[currentToken.code]++;
            // dynamically allocate a buffer to store the string literal
            // traverses the buffer until the next quote character
            while ((c = readerGetChar(sourceBuffer)) != QUT_CHR) {
                if (c == NWL_CHR) {
                    line++;
                }
                size++;
            }

            // go back to original position before the string literal
            for (int y = 0; y < size + 1; y++) {
                readerRetract(sourceBuffer);
            }
            lexemeBuffer = readerCreate(size + 1, 0, MODE_FIXED);
            // Process the string literal until the end of the string or file
            while ((c = readerGetChar(sourceBuffer)) != QUT_CHR) {
                // add the character to the lexeme buffer
                readerAddChar(lexemeBuffer, c);
                if (c == NWL_CHR) {
                    line++;
                }
            }
            // allocate space for the lexeme string
            lexeme = (lp_string)malloc(size * sizeof(lp_char));
            // move the contents of the lexeme buffer to the lexeme string to save token contents
            strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
            // free the lexeme buffer
            readerFree(lexemeBuffer);
            // Set the string literal in the token's attribute
            strncpy(currentToken.attribute.idLexeme, lexeme, size + 1);
            currentToken.attribute.idLexeme[size + 1] = EOS_CHR;

            return currentToken;
		case LPR_CHR:
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case RPR_CHR:
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case LBR_CHR:
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case RBR_CHR:
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		/* Cases for END OF FILE */
		case EOS_CHR:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;

        case SCP_CHR:
            // we have a ":" character
            currentToken.code = SMC_T;
            scData.scanHistogram[currentToken.code]++;
            return currentToken;

        case LTH_CHR:
            // we have a "<" character
            currentToken.code = CMP_T;
            scData.scanHistogram[currentToken.code]++;

            // we check what the next character is to determine what type of comparison operator it is
            c = readerGetChar(sourceBuffer);
            if (c == EQL_CHR) {
                // we have a "<=" character
                currentToken.code = CMP_T;
                currentToken.attribute.relationalOperator = OP_LTE;
                scData.scanHistogram[currentToken.code]++;

                // retract the buffer to the original position
                readerRetract(sourceBuffer);

                // keep reading to see what's getting compared
                // loop until we reach a new line character or until a semicolon ":"

                int innerSize = 0;
                while ((c = readerGetChar(sourceBuffer)) != SCP_CHR) {
                    // if we reach a new line character then we have reached the end of the comparison
                    if (c == NWL_CHR) {
                        readerRetract(sourceBuffer);
                        break;
                    }
                    innerSize++;
                }

                // go back to original position before the comparison
                for (int y = 0; y < innerSize + 2; y++) {
                    readerRetract(sourceBuffer);
                }
                lexemeBuffer = readerCreate(innerSize + 1, 0, MODE_FIXED);
                // Process the comparison until the end of the comparison or file
                while ((c = readerGetChar(sourceBuffer)) != SCP_CHR) {
                    // add the character to the lexeme buffer
                    readerAddChar(lexemeBuffer, c);
                }
                // allocate space for the lexeme string
                lexeme = (lp_string)malloc((innerSize + 1) * sizeof(lp_char));
                strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
                strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
                currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;
                currentToken.attribute.relationalOperator = OP_LTE;

                free (lexeme);
                return currentToken;
            }


            return currentToken;

        case HST_CHR: // Handle comment character
            currentToken.code = CMT_T;
            scData.scanHistogram[currentToken.code]++;
            size = 0;
            // dynamically allocate a buffer to store the comment text
            // keep incrementing the length until we reach # or EOF

            while ((c = readerGetChar(sourceBuffer)) != '#' && c != EOF_CHR) {
                size++;
                if (c == NWL_CHR) {
                    line++;
                }
            }

            // go back to original position before the comment
            for (int y = 0; y < size; y++) {
                readerRetract(sourceBuffer);
            }
            lexemeBuffer = readerCreate(size + 1, 0, MODE_FIXED);

            // Process the comment until the end of the comment or file
            while ((c = readerGetChar(sourceBuffer)) != '#' && c != EOF_CHR) {
                // add the character to the lexeme buffer
                readerAddChar(lexemeBuffer, c);
                if (c == NWL_CHR) {
                    line++;
                }
            }
            // allocate space for the lexeme string
            lexeme = (lp_string)malloc(size * sizeof(lp_char));

            // move the contents of the lexeme buffer to the lexeme string to save token contents
            strcpy(lexeme, readerGetContent(lexemeBuffer, 0));
            // free the lexeme buffer
            readerFree(lexemeBuffer);

            // Set the comment text in the token's attribute
            strncpy(currentToken.attribute.idLexeme, lexeme, size + 1);
            currentToken.attribute.idLexeme[size + 1] = EOS_CHR;

            return currentToken;
		case EOF_CHR:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			state = nextState(state, c);
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((lp_intg)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}

			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));

			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			lexeme = readerGetContent(lexemeBuffer, 0);
			// TO_DO: Defensive programming
			if (!lexeme)
				return currentToken;
			currentToken = (*finalStateTable[state])(lexeme);
			readerRestore(lexemeBuffer);
			return currentToken;
		} // switch

	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

lp_intg nextState(lp_intg state, lp_char c) {
	lp_intg col;
	lp_intg next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

lp_intg nextClass(lp_char c) {
	lp_intg val = -1;
	switch (c) {
    case SPC_CHR:
        val = 7;
        break;
	case UND_CHR:
		val = 2;
		break;
	case PRD_CHR:
		val = 7;
		break;
	case QUT_CHR:
		val = 5;
		break;
	case HST_CHR:
		val = 4;
		break;
	case AQT_CHR:
		val = 3;
		break;

	case LPR_CHR:
		val = 8;
		break;
	case EOS_CHR:
	
	default:
		if (isalpha(c))
			val = 0;
		else if (isdigit(c))
			val = 1;
		else if (islower(c))
			val = 6;
		else
			val = 9;
	}
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(lp_string lexeme) {
	Token currentToken = { 0 };
	lp_intg i = 0, len = (lp_intg)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NWL_CHR)
			line++;
	}
	currentToken.code = CMT_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(lp_string lexeme) {
	Token currentToken = { 0 };
	lp_long tlong;
	if (lexeme[0] != EOS_CHR && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.intValue = (lp_intg)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(lp_string lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	lp_char lastch = lexeme[length - 1];
	lp_intg isID = LP_FALSE;
	switch (lastch) {
		case LPR_CHR:
			currentToken.code = MNID_T;
			scData.scanHistogram[currentToken.code]++;
			isID = LP_TRUE;
			break;
		default:
			// Test Keyword
			///lexeme[length - 1] = EOS_CHR;
			currentToken = funcKEY(lexeme);
			break;
	}
	if (isID == LP_TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(lp_string lexeme) {
	Token currentToken = { 0 };
	lp_intg i = 0, len = (lp_intg)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == NWL_CHR)
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			scData.scanHistogram[currentToken.code]++;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, EOS_CHR)) {
		currentToken.code = RTE_T;
		scData.scanHistogram[currentToken.code]++;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(lp_string lexeme) {
	Token currentToken = { 0 };
	lp_intg kwindex = -1, j = 0;
	lp_intg len = (lp_intg)strlen(lexeme);
	///lexeme[len - 1] = EOS_CHR;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		scData.scanHistogram[currentToken.code]++;
		currentToken.attribute.codeType = kwindex;
	}
	else {
		currentToken.code = VID_T;
        strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
        currentToken.attribute.idLexeme[VID_LEN] = EOS_CHR;
		scData.scanHistogram[currentToken.code]++;
		
	}
    // transfer the string to the current token
    // copy the string to the current token
    strncpy(currentToken.attribute.idLexeme, lexeme, len);
    currentToken.attribute.idLexeme[len] = EOS_CHR;
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(lp_string lexeme) {
	Token currentToken = { 0 };
	lp_intg i = 0, len = (lp_intg)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = EOS_CHR;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == NWL_CHR)
			line++;
	currentToken.code = ERR_T;
	scData.scanHistogram[currentToken.code]++;
	return currentToken;
}

Token funcFL(lp_string lexeme)
{
	Token currentToken = { 0 };
	lp_real tlong;
	if (lexeme[0] != EOS_CHR && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = FLT_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.floatValue = (lp_real)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

lp_void printToken(Token t) {
	extern lp_string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
    case SMC_T:
        printf("SMC_T\t\t:\n");
        break;
    case ASG_T:
        printf("ASG_T\t\t= VALUES: %s\n", t.attribute.idLexeme);
        break;
    case CMP_T:
        switch (t.attribute.relationalOperator) {
            case OP_LTE:
                printf("CMP_T\t\t%s\n", t.attribute.idLexeme);
                break;
            default:
                printf("CMP_T\t\t==\n");
                break;
        }
        break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case VID_T:
		printf("VID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case FLT_T:
		printf("FLT_T\t\t%f\n", t.attribute.floatValue);
		break;
    case SPL_VAR_T:
        printf("SPL_VAR_T\t%s\n", t.attribute.idLexeme);
        break;
	case INL_T:
		printf("FLT_T\t\t%d\n", t.attribute.intValue);
		break;
	case STR_T:
		printf("STR_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case LPR_T:
		printf("LPR_T\t\t(\n");
		break;
	case RPR_T:
		printf("RPR_T\t\t)\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\t\t'%s'\n", t.attribute.idLexeme);
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
lp_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
