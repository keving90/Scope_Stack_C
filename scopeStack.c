/*****************************************************************************************
Prologue

UCSC Extension: Advanced C Programming

Instructor: Rajainder A. Yeldandi

Author: Kevin Geiszler

Assignment Number: 8, Stacks

Topics: Stacks

File Name: assignment8_KevinGeiszler.c

Date: 2/21/2017

Objective: This program scans an input file, and places the opening scope characters, (,
		   [, and {, into a stack. When the equivalent closing scope characters are found,
		   the characters in the stack are removed.
		   
Comments:  This program checks for proper scoping. If improper scoping occurs, an error
		   message is displayed when the program is finished.

*****************************************************************************************/

//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 50
#define EMPTYSTACK -1
#define TRUE 1
#define FALSE 0

typedef struct stack {
	int top;
	char stackelement[MAXSTACK];
} CHSTACK;

/****************************************************************************************/

//Function prototypes
int empty(struct stack *);
char pop(struct stack *);
void push(struct stack *, char);
int checkStack(FILE *, FILE *, CHSTACK *);

/****************************************************************************************/

//The main function
int main(int argc, char *argv[])
{
	CHSTACK chStack, *pChst;
	chStack.top = EMPTYSTACK;
	pChst = &chStack;
	int isValid;
	FILE *pInFile, *pOutFile;
	
	if (argc != 3)
	{
		printf("Error, need the following file usage: %s inputFile outputFile\n", argv[0]);
		exit(1);
	}
	
	if ((pInFile = fopen(argv[1], "r")) == NULL)
	{
		printf("Error opening input file: %s\n", argv[1]);
		exit(1);
	}
	
	if ((pOutFile = fopen(argv[2], "w")) == NULL)
	{
		printf("Error opening output file: %s\n", argv[2]);
		exit(1);
	}
	
	rewind(pInFile);
	
	isValid = checkStack(pInFile, pOutFile, pChst);
	
	if (isValid == TRUE)
	{
		printf("This expression is valid!\n\n");
		fprintf(pOutFile, "This expression is valid!\n\n");
	}
	else
	{
		printf("This expression is not valid due to incorrect scoping!\n\n");
		fprintf(pOutFile, "This expression is not valid due to incorrect scoping!");
	}
	
	fclose(pInFile);
	fclose(pOutFile);
	
	return 0;
} //end main

/****************************************************************************************/

//Verifies if the stack is empty.

int empty(CHSTACK *ps)
{
	if (ps->top == EMPTYSTACK)
		return(TRUE);
	else
		return(FALSE);
}

/****************************************************************************************/

//Removes an the item that is at the top of the stack and returns it.

char pop(CHSTACK *ps)
{
	if (empty(ps))
	{
		printf("%s", "stack underflow");
		exit(1);
	} //end if
	
	return (ps->stackelement[ps->top--]);
}

/****************************************************************************************/

//Places an item at the top of the stack.

void push(CHSTACK *ps, char x)
{
	if (ps->top == MAXSTACK - 1)
	{
		printf("%s", "stack overflow");
		exit(1);
	} //end if
	else
		ps->stackelement[++(ps->top)] = x;
}

/****************************************************************************************/

//Scans the input file, places any open scope characters into the stack, removes closing
//scope characters from the stack, and checks for proper scoping.

int checkStack(FILE *pInFile, FILE *pOutFile, CHSTACK *pChst)
{
	
	char ch, popChar;
	int isValid = TRUE;

	while ((ch = getc(pInFile)) != EOF)
	{
		if (ch == '(' || ch == '{' || ch == '[')
		{
			push(pChst, ch);
			printf("Character input '%c' has been pushed into the scope stack.\n\n", ch);
			fprintf(pOutFile, "Character input '%c' has been pushed into the scope stack.\n\n", ch);
		} //end if opening scope
		else if (ch == ')' || ch == '}' || ch == ']')
		{
			if (pChst->top == EMPTYSTACK)
			{
				isValid = FALSE;
			} //end if stack is empty
			else
			{
				popChar = pop(pChst);
			
				if (ch == ')')
				{
					printf("Input character is '%c'. Expecting '(' to pop, popped character '%c'.\n\n", ch, popChar);
					fprintf(pOutFile, "Input character is '%c'. Expecting '(' to pop, popped character '%c'.\n\n", ch, popChar);
					
					//if incorrect closing scope is used, then the expression is invalid
					if (popChar != '(')
						isValid = FALSE;
				} //end if (
				else if (ch == '}')
				{
					printf("Input character is '%c'. Expecting '{' to pop, popped character '%c'.\n\n", ch, popChar);
					fprintf(pOutFile, "Input character is '%c'. Expecting '{' to pop, popped character '%c'.\n\n", ch, popChar);
					
					//if incorrect closing scope is used, then the expression is invalid
					if (popChar != '{')
						isValid = FALSE;
				} //end if {
				else if (ch == ']')
				{
					printf("Input character is '%c'. Expecting '[' to pop, popped character '%c'.\n\n", ch, popChar);
					fprintf(pOutFile, "Input character is '%c'. Expecting '[' to pop, popped character '%c'.\n\n", ch, popChar);
					
					//if incorrect closing scope is used, then the expression is invalid
					if (popChar != '[')
						isValid = FALSE;
				} //end if [
			}
		} //end if closing scope
		//ignore non-scoping characters
		else if (ch != '(' && ch != ')' && ch != '{' && ch != '}' && ch != '[' && ch != ']')
		{
			printf("Input character '%c' is being ignored for now.\n\n", ch);
			fprintf(pOutFile, "Input character '%c' is being ignored for now.\n\n", ch);
		} //end if not scope
	
	} //end while loop
	
	//if the scoping stack isn't empty at the end of the expression, then it's invalid
	if (pChst->top != EMPTYSTACK)
			isValid = FALSE;
	
	//if there are no scoping errors, then isValid == TRUE throughout the function		
	return isValid;
}

/****************************************************************************************/


























