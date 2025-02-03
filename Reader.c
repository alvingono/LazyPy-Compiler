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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

BufferPointer readerCreate(lp_intg size, lp_intg increment, lp_char mode) {
	BufferPointer readerPointer;
	lp_intg count = 0;
	/* TO_DO: Defensive programming */
	if (size < 0)
		size = READER_DEFAULT_SIZE;
	if (increment < 0)
		increment = READER_DEFAULT_INCREMENT;
	if (mode!='f' && mode != 'a' && mode != 'm')
		return LP_INVALID;

	if (!size)
		size = READER_DEFAULT_SIZE;
	if (!increment)
		increment = READER_DEFAULT_INCREMENT;
	if (!mode)
		mode = MODE_FIXED;
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return LP_INVALID;
	readerPointer->content = (lp_string)malloc(size);
	if (!readerPointer->content)
		return LP_INVALID;

	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < 128; i++) {
		readerPointer->histogram[i] = 0;
	}
	
	/* TO_DO: Initialize errors */
	readerPointer->numReaderErrors = 0;
	readerPointer->mode = mode;
	readerPointer->size = size;
	readerPointer->increment = increment;


	readerPointer->mode = mode;
	readerPointer->size = size;
	readerPointer->increment = increment;

	/* TO_DO: Initialize flags */
	readerPointer->flags.isEmpty = LP_FALSE;
	readerPointer->flags.isFull = LP_FALSE;
	readerPointer->flags.isMoved = LP_FALSE;
	readerPointer->flags.isRead = LP_FALSE;

	/* TO_DO: Default checksum */
	readerPointer->checksum = 0;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer readerPointer, lp_char ch) {
	lp_string tempReader = LP_INVALID;
	lp_intg newSize = 0;
	lp_char tempChar = ' ';
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Reset Realocation */
	readerPointer->flags.isMoved = LP_FALSE;
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->positions.wrte * (lp_intg)sizeof(lp_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags.isFull = LP_FALSE;

	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags.isFull = LP_TRUE;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* TO_DO: Update the last position with Terminator */
			readerPointer->content[readerPointer->positions.wrte++] = READER_TERMINATOR;
			
			return LP_ERROR;
			break;
		case MODE_ADDIT:
			/* TO_DO: Update size for Additive mode */
			newSize = readerPointer->size + readerPointer->increment;

			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size) {
				readerPointer->flags.isFull = LP_TRUE;
				return LP_ERROR;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Update size for Additive mode */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize < readerPointer->size) {
				readerPointer->flags.isFull = LP_TRUE;
				return LP_ERROR;
			}
			break;
		default:
			return LP_ERROR;
		}
		/* TO_DO: Reallocate */
		tempReader = realloc(readerPointer->content, newSize);

		/* TO_DO: Defensive programming */
		if (!tempReader) {
			return LP_ERROR;
		}
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		readerPointer->flags.isFull = LP_FALSE;
		return readerPointer;
	}
	/* TO_DO: Update the flags */
	readerPointer->flags.isFull = LP_FALSE;
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	/* TO_DO: Updates histogram */
	if ((lp_intg)ch >= 0 && (lp_intg)ch < 128) {
		readerPointer->histogram[(lp_intg)ch] = readerPointer->histogram[(lp_intg)ch] + 1;
	}
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the write, mark and read to zero */
	/* TO_DO: Adjust flags */
	if (!readerPointer) {
		return LP_FALSE;
	}
	readerPointer->flags.isEmpty = LP_FALSE;
	readerPointer->flags.isFull = LP_FALSE;
	readerPointer->flags.isMoved = LP_FALSE;
	readerPointer->flags.isRead = LP_FALSE;

	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;
	return LP_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Free pointers */
	if (!readerPointer) {
		return LP_FALSE;
	}
	free(readerPointer);
	return LP_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	if (!readerPointer) {
		return LP_FALSE;
	}

	if (readerPointer->flags.isFull) {
		return LP_TRUE;
	}
	return LP_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	if (!readerPointer) {
		return LP_FALSE;
	}

	if (readerPointer->flags.isEmpty) {
		return LP_TRUE;
	}
	return LP_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerSetMark(BufferPointer const readerPointer, lp_intg mark) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust mark */
	if (!readerPointer) {
		return LP_FALSE;
	}

	if (mark >=0 && mark <= readerPointer->positions.wrte) {
		readerPointer->positions.mark = mark;
		return LP_TRUE;
	}
	return LP_FALSE;
	
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerPrint(BufferPointer const readerPointer) {
	lp_intg cont = 0;
	lp_char c;

	/* Defensive */
	if (!readerPointer || !readerPointer->content) {
		return LP_ERROR;
	}

	if (readerPointer->positions.wrte == 0) {
		return 0;
	}

	c = readerGetChar(readerPointer);
	while (cont < readerPointer->positions.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}

	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerLoad(BufferPointer readerPointer, FILE* const fileDescriptor) {
	lp_intg size = 0;
	lp_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return LP_ERROR;
	}
	while (!feof(fileDescriptor)) {
		c = (lp_char)fgetc(fileDescriptor);
		if (!(readerPointer = readerAddChar(readerPointer, c))) {
			ungetc(c, fileDescriptor);
		}
		
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return LP_FALSE;
	}
	/* TO_DO: Recover positions: read and mark must be zero */

	/* TO_DO: Update flags */
	
	readerPointer->flags.isRead = LP_FALSE;

	
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;

	return LP_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || readerPointer->positions.read == 0)
		return LP_FALSE;
	/* TO_DO: Retract (return 1 pos read) */
	readerPointer->positions.read--;

	return LP_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_FALSE;
	/* TO_DO: Restore positions (read to mark) */
	readerPointer->positions.read = readerPointer->positions.mark;

	return LP_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Defensive programming */
	if (!readerPointer || readerPointer->positions.read >= readerPointer->positions.wrte)
		return READER_TERMINATOR;
	return readerPointer->content[readerPointer->positions.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_string readerGetContent(BufferPointer const readerPointer, lp_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || pos < 0 || pos >= readerPointer->positions.wrte)
		return LP_INVALID;

	return readerPointer->content + pos;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Return read */
	return readerPointer->positions.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Return wrte */

	return readerPointer->positions.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Return mark */
	return readerPointer->positions.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_char readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_INVALID;

	/* TO_DO: Return mode */
	return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_void readerPrintStat(BufferPointer const readerPointer) {
	lp_intg i;
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return;
	/* TO_DO: Updates the histogram */
	printf("Character Frequency Histogram:\n");
	for (i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0) {
			printf("'%c' : %d || ", (lp_char)i, readerPointer->histogram[i]);
		}
	}
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
lp_intg readerGetNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_ERROR;
	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}

/*
***********************************************************
* Function name: readerCalcChecksum
* Purpose: Calculates the checksum of the reader (8 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

lp_void readerCalcChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return;
	/* TO_DO: Calculate checksum */
	lp_byte checksum = 0;
	for (lp_intg i = 0; i < readerPointer->positions.wrte; i++) {
		checksum ^= readerPointer->content[i];
	}
	readerPointer->checksum = checksum;
}

/*
***********************************************************
* Function name: readerPrintFlags
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

lp_boln readerPrintFlags(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return LP_FALSE;
	/* TO_DO: Shows flags */
	printf("Flags: Empty=%d, Full=%d, Read=%d, Moved=%d\n",
		readerPointer->flags.isEmpty,
		readerPointer->flags.isFull,
		readerPointer->flags.isRead,
		readerPointer->flags.isMoved);

	return LP_TRUE;
}
