/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# "=---------------------------------------="
# "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# "=---------------------------------------="
# "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# "    @@                             @@    ”
# "    @@           %&@@@@@@@@@@@     @@    ”
# "    @@       @%% (@@@@@@@@@  @     @@    ”
# "    @@      @& @   @ @       @     @@    ”
# "    @@     @ @ %  / /   @@@@@@     @@    ”
# "    @@      & @ @  @@              @@    ”
# "    @@       @/ @*@ @ @   @        @@    ”
# "    @@           @@@@  @@ @ @      @@    ”
# "    @@            /@@    @@@ @     @@    ”
# "    @@     @      / /     @@ @     @@    ”
# "    @@     @ @@   /@/   @@@ @      @@    ”
# "    @@     @@@@@@@@@@@@@@@         @@    ”
# "    @@                             @@    ”
# "    @@         S O F I A           @@    ”
# "    @@                             @@    ”
# "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# "                                         "
# "[READER SCRIPT .........................]"
# "                                         "
*/


/*
************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */
lp_intg numOfSpaces = 0;

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

lp_void startParser() {
	/* TO_DO: Initialize Parser data */
	lp_intg i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
    // debug
    /*
    switch(lookahead.code) {
        case CMT_T:
            printf("CMT_T\n");
            break;
        case SEOF_T:
            printf("SEOF_T\n");
            break;
        case ERR_T:
            printf("ERR_T\n");
            break;
        case MNID_T:
            printf("MNID_T\n");
            break;
        case STR_T:
            printf("STR_T\n");
            break;
        case KW_T:
            printf("KW_T\n");
            break;
        case LPR_T:
            printf("LPR_T\n");
            break;
        case RPR_T:
            printf("RPR_T\n");
            break;
        case LBR_T:
            printf("LBR_T\n");
            break;
        case RBR_T:
            printf("RBR_T\n");
            break;
        case EOS_T:
            printf("EOS_T\n");
            break;
        default:
            printf("Unknown\n");
    }
    */
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}

lp_void printTokenType() {
    switch (lookahead.code) {
        case CMT_T:
            printf("CMT_T\n");
            break;
        case SEOF_T:
            printf("SEOF_T\n");
            break;
        case ERR_T:
            printf("ERR_T\n");
            break;
        case MNID_T:
            printf("MNID_T\n");
            break;
        case STR_T:
            printf("STR_T\n");
            break;
        case KW_T:
            printf("KW_T\n");
            break;
        case LPR_T:
            printf("LPR_T\n");
            break;
        case RPR_T:
            printf("RPR_T\n");
            break;
        case LBR_T:
            printf("LBR_T\n");
            break;
        case RBR_T:
            printf("RBR_T\n");
            break;
        case EOS_T:
            printf("EOS_T\n");
            break;
        case VID_T:
            printf("VID_T\n");
            break;
        case INL_T:
            printf("INL_T\n");
            break;
        case FLT_T:
            printf("FLT_T\n");
            break;
        case SMC_T:
            printf("SMC_T\n");
            break;
        case ASG_T:
            printf("ASG_T\n");
            break;
        case CMP_T:
            printf("CMP_T\n");
            break;
        case SPL_VAR_T:
            printf("SPL_VAR_T\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    printf("%s\n", lookahead.attribute.idLexeme);
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
lp_void matchToken(lp_intg tokenCode, lp_intg tokenAttribute) {
    // debug
    /* switch(tokenCode) {
        case CMT_T:
            printf("CMT_T\n");
            break;
        case SEOF_T:
            printf("SEOF_T\n");
            break;
        case ERR_T:
            printf("ERR_T\n");
            break;
        case MNID_T:
            printf("MNID_T\n");
            break;
        case STR_T:
            printf("STR_T\n");
            break;
        case KW_T:
            printf("KW_T\n");
            break;
        case LPR_T:
            printf("LPR_T\n");
            break;
        case RPR_T:
            printf("RPR_T\n");
            break;
        case LBR_T:
            printf("LBR_T\n");
            break;
        case RBR_T:
            printf("RBR_T\n");
            break;
        case EOS_T:
            printf("EOS_T\n");
            break;
    } */
    numOfSpaces = 0;
    /* switch(lookahead.code) {
        case CMT_T:
            printf("CMT_T\n");
            break;
        case SEOF_T:
            printf("SEOF_T\n");
            break;
        case ERR_T:
            printf("ERR_T\n");
            break;
        case MNID_T:
            printf("MNID_T\n");
            break;
        case STR_T:
            printf("STR_T\n");
            break;
        case KW_T:
            printf("KW_T\n");
            break;
        case LPR_T:
            printf("LPR_T\n");
            break;
        case RPR_T:
            printf("RPR_T\n");
            break;
        case LBR_T:
            printf("LBR_T\n");
            break;
        case RBR_T:
            printf("RBR_T\n");
            break;
        case EOS_T:
            printf("EOS_T\n");
            break;
        case VID_T:
            printf("VID_T\n");
            break;
        case INL_T:
            printf("INL_T\n");
            break;
        case FLT_T:
            printf("FLT_T\n");
            break;
        case SMC_T:
            printf("SMC_T\n");
            break;
        case ASG_T:
            printf("ASG_T\n");
            break;
        case CMP_T:
            printf("CMP_T\n");
            break;
        case SPL_VAR_T:
            printf("SPL_VAR_T\n");
            break;
        default:
            printf("Unknown\n");
    } */

	lp_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if ((lookahead.attribute.codeType != tokenAttribute) && (tokenAttribute != NO_ATTR))
			matchFlag = 0;
        break;

    case VID_T:
    case LPR_T:
        if (tokenAttribute != NO_ATTR)
            matchFlag = 1;
        break;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
        break;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
lp_void syncErrorHandler(lp_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
lp_void printError() {
	int extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {CMT_T, MNID_T (main&), SEOF_T}.
 ***********************************************************
 */
lp_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
    while (lookahead.code != SEOF_T) {
        switch (lookahead.code) {
            case CMT_T:
                comment();

                break;
                /*
                case KW_T:
                    // handle case for def FUNC_NAME(POSSIBLE VALUES)
                    if (lookahead.attribute.codeType == KW_T && strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
                        matchToken(KW_T, KW_main);
                        matchToken(LPR_T, NO_ATTR);
                        matchToken(RPR_T, NO_ATTR);
                        matchToken(LBR_T, NO_ATTR);
                        optionalStatements();
                        matchToken(RBR_T, NO_ATTR);
                        break;
                    }
                    else {
                        printError();
                }
                */
            case KW_T:
                // we have a keyword, could be def, int.
                // check for def
                // printf("%s\n", lookahead.attribute.idLexeme);
                if (strncmp(lookahead.attribute.idLexeme, "def", 3) == 0) {
                    matchToken(KW_T, KW_def);
                    matchToken(VID_T, NO_ATTR);
                    matchToken(LPR_T, NO_ATTR);
                    matchToken(RPR_T, NO_ATTR);
                    matchToken(SMC_T, NO_ATTR);
                    optionalStatements();
                }
                break;

            case MNID_T:
                // we have a method name
                break;
            case SEOF_T:
                ; // Empty
                break;
            case VID_T:
                // we have a method name or a variable.
                // check to see if its valid.
                matchToken(VID_T, NO_ATTR);
                matchToken(LPR_T, NO_ATTR);
                matchToken(RPR_T, NO_ATTR);
                break;
            default:
                // print token type
                // printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", (enum TOKENS) lookahead.code);
                // printTokenType();
                printError();
        }
    }
    printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
lp_void comment() {
	psData.parsHistogram[BNF_comment]++;

    // consume entire comment token

	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
lp_void dataSession() {
	psData.parsHistogram[BNF_dataSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		// matchToken(KW_T, KW_data);
		matchToken(LBR_T, NO_ATTR);
		optVarListDeclarations();
		matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
	}
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
lp_void optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
lp_void codeSession() {
	psData.parsHistogram[BNF_codeSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		// matchToken(KW_T, KW_code);
		matchToken(LBR_T, NO_ATTR);
		optionalStatements();
		matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
lp_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
    if (numOfSpaces % 4 != 0) {
        printf("ERROR: Indentation error\n");
        return;
    }
    lp_intg currentIndent = (lp_intg) numOfSpaces / 4;
    printf("CURRENT INDENT: %d\n", currentIndent);
    while (currentIndent == numOfSpaces / 4) {
        switch (lookahead.code) {
            case CMT_T:
                comment();
                break;
            case MNID_T:
                if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
                    (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
                    statements();
                    break;
                }
            case KW_T:
                // we have a keyword, could be def, int.
                // check for def
                // printf("%s\n", lookahead.attribute.idLexeme);
                if (strncmp(lookahead.attribute.idLexeme, "def", 3) == 0) {
                    matchToken(KW_T, KW_def);
                    matchToken(VID_T, NO_ATTR);
                    matchToken(LPR_T, NO_ATTR);
                    matchToken(RPR_T, NO_ATTR);
                    matchToken(SMC_T, NO_ATTR);
                    optionalStatements();
                } else if (strncmp(lookahead.attribute.idLexeme, "print", 4) == 0) {
                    matchToken(KW_T, KW_print);
                    matchToken(LPR_T, NO_ATTR);
                    printTokenType();
                    if (lookahead.code == STR_T) {
                        matchToken(STR_T, NO_ATTR);
                    } else if (lookahead.code == VID_T) {
                        matchToken(VID_T, NO_ATTR);
                    }
                    matchToken(RPR_T, NO_ATTR);
                } else if (strncmp(lookahead.attribute.idLexeme, "input", 5) == 0) {

                } else if (strncmp(lookahead.attribute.idLexeme, "int", 3) == 0) {
                    matchToken(KW_T, KW_int);
                    printTokenType();
                } else if (strncmp(lookahead.attribute.idLexeme, "while", 5) == 0) {
                    matchToken(KW_T, KW_while);
                    matchToken(VID_T, NO_ATTR);
                    matchToken(CMP_T, NO_ATTR);
                    optionalStatements();
                    printTokenType();
                } else if (strncmp(lookahead.attribute.idLexeme, "return", 6) == 0) {
                    matchToken(KW_T, KW_return);
                    printTokenType();
                    matchToken(VID_T, NO_ATTR);
                }
                else {
                    printf("%s\n", lookahead.attribute.idLexeme);
                    printTokenType();
                }
                break;
            case VID_T:
                // we have a method name or a variable.
                // check to see if its valid.
                // printf("%s\n", lookahead.attribute.idLexeme);
                matchToken(VID_T, NO_ATTR);

                if (lookahead.code == LPR_T) {
                    matchToken(LPR_T, NO_ATTR);
                    matchToken(RPR_T, NO_ATTR);
                } else if (lookahead.code == ASG_T) {
                    matchToken(ASG_T, NO_ATTR);
                }

                break;
            default:
                // printTokenType();
                break;
        }
    }
    printf("FINAL INDENT: %d\n", numOfSpaces / 4);
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
lp_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
lp_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
lp_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
lp_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
lp_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
lp_void printBNFData(ParserData psData) {
}
*/
lp_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}
