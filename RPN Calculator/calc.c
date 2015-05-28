#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{

	assert(sizeDynArr(stack) >= 2 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the top of Stack
	TYPE valOne = topDynArr(stack);

	//Pop that value
	popDynArr(stack);

	//Get the new value at top
	TYPE valTwo = topDynArr(stack);

	//Pop second value
	popDynArr(stack);

	//Add the elements
	TYPE valSum = valTwo + valOne;

	//Push the sum back onto the stack
	pushDynArr(stack, valSum);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{

	assert(sizeDynArr(stack) >= 2 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the top of Stack
	TYPE valOne = topDynArr(stack);

	//Pop that value
	popDynArr(stack);

	//Get the new value at top
	TYPE valTwo = topDynArr(stack);

	//Pop second value
	popDynArr(stack);

	//Subtract the elements
	//valTwo is first num on command line
	TYPE valDiff = valTwo - valOne;

	//Push the difference back on the stack
	pushDynArr(stack, valDiff);

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	assert(sizeDynArr(stack) >= 2 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the top of Stack
	TYPE valOne = topDynArr(stack);

	//Pop that value
	popDynArr(stack);

	//Get the new value at top
	TYPE valTwo = topDynArr(stack);

	//Pop second value
	popDynArr(stack);

	//Divide the two elements
	//valTwo first num on command line
	TYPE valQuo = valTwo / valOne;

	pushDynArr(stack, valQuo);

}

/*  param: the stack being manipulated
    pre: the stack contains at least 2 elements
    post: top two elements are popped and their
    product is pushed onto stack
*/
void multiply (struct DynArr *stack)
{
 	assert(sizeDynArr(stack) >= 2 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the top of Stack
	TYPE valOne = topDynArr(stack);

	//Pop that value
	popDynArr(stack);

	//Get the new value at top
	TYPE valTwo = topDynArr(stack);

	//Pop second value
	popDynArr(stack);

	//Multiply the two values
	TYPE valMul = valOne * valTwo;

	//Put the product on the stack
	pushDynArr(stack, valMul);
}

/*  param: the stack being manipulated
    pre: the stack contains at least 2 elements
    post: the value of the second number on the
    stack raised to the first number on top
    of the stack is pushed onto the stack
*/
void power (struct DynArr *stack)
{
	assert(sizeDynArr(stack) >= 2 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the top of Stack
	TYPE valOne = topDynArr(stack);

	//Pop that value
	popDynArr(stack);

	//Get the new value at top
	TYPE valTwo = topDynArr(stack);

	//Pop second value
	popDynArr(stack);

	//Use power function
	TYPE raised = pow(valTwo, valOne);

	//Push the returned value on stack
	pushDynArr(stack, raised);

}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: element on stack is squared and
    result pushed back on top of stack
*/
void square (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

    //Get the value at top
    TYPE valTop = topDynArr(stack);

    //Pop the value
    popDynArr(stack);

    //Square the value
    TYPE valSquared = valTop * valTop;

    //Push the result back on the stack
    pushDynArr(stack, valSquared);

}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: element on top of stack is cubed
    and result pushed back on stack
*/
void cubed (struct DynArr *stack)
{
     //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at top
	TYPE valTop = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Cube the value
	TYPE valCubed = valTop * valTop * valTop;

	//Push the result back on the stack
	pushDynArr(stack, valCubed);
}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: absolute value of the value on
    top of the stack is pushed back onto
    stack
*/
void absolute (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at top
	TYPE valTop = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Use fabs function
	TYPE valAbs = fabs(valTop);

	//Push the result back on stack
	pushDynArr(stack, valAbs);
}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: square root of value at the top of
    the stack is pushed back onto stack
*/
void sqRoot (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at the top
	TYPE valTop = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Use sqrt fucntion
	TYPE valRoot = sqrt(valTop);

	//Push the result back on stack
	pushDynArr(stack, valRoot);
}

/*
    param: the stack being manipulated
    pre: stack contains at least one element
    post: exp value of the number that was
    on top of the stack placed onto stack
*/
void exponent (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at the top
	TYPE valTop = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Use exp function
	TYPE valExp = exp (valTop);

	//Push the result back on stack
	pushDynArr(stack, valExp);
}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: natural log of top number on the stack
    is pushed back onto stack
*/
void logNatural (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at the top
	TYPE topVal = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Use log function
	TYPE valLn = log(topVal);

	//Push value back onto stack
	pushDynArr(stack, valLn);
}

/*  param: the stack being manipulated
    pre: stack contains at least one element
    post: log base 10 of number on the top of the
    stack pushed back onto stack
*/
void logTen (struct DynArr *stack)
{
    //Only need one operand in this case
	assert(sizeDynArr(stack) >= 1 && "You didn't enter enough numbers or didn't follow RPN notation!");

	//Get the value at the top
	TYPE topVal = topDynArr(stack);

	//Pop the value
	popDynArr(stack);

	//Use the log function
	TYPE valLog = log10(topVal);

	//Push the value back onto stack
	pushDynArr(stack, valLog);
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//In a complete Polish notation , there must be one more operand than operator (Wikipedia)
	//ints below hold num of (binary) operators and operands.
	int numOperands = 0;
	int numOperators = 0;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i = 1; i < numInputTokens; i++)
	{
		s = inputString[i];
		//If s is a number, will be parsed to numToAdd
		double numToAdd;

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			{
                add(stack);
                numOperators++;
			}
		else if(strcmp(s,"-") == 0)
			{
			    subtract(stack);
                numOperators++;
			}
		else if(strcmp(s, "/") == 0)
			{
			    divide(stack);
                numOperators++;
			}
		else if(strcmp(s, "x") == 0)
			{
			    multiply(stack);
                numOperators++;
			}
		else if(strcmp(s, "^") == 0)
			{
			    power(stack);
                numOperators++;
			}
        //rest are unary operators
		else if(strcmp(s, "^2") == 0)
            {
                square(stack);
            }
		else if(strcmp(s, "^3") == 0)
			{
			    cubed(stack);
			}
		else if(strcmp(s, "abs") == 0)
			{
			    absolute(stack);
			}
		else if(strcmp(s, "sqrt") == 0)
            {
                sqRoot(stack);
            }
		else if(strcmp(s, "exp") == 0)
            {
                exponent(stack);
            }
		else if(strcmp(s, "ln") == 0)
			{
			    logNatural(stack);
			}
		else if(strcmp(s, "log") == 0)
			{
			    logTen(stack);
			}
		else if(strcmp(s, "pi") == 0)
            {
                double piVal = 3.14159265;
                //Push value of pi onto stack
                pushDynArr(stack, piVal);
                numOperands++;
            }
        else if (strcmp(s, "e") ==0)
            {
                double eVal = 2.7182818;
                //Push value of e onto stack
                pushDynArr(stack, eVal);
                numOperands++;
            }
        //If this next function returns 1, it's a number
        //Push the number onto the stack
        else if(isNumber(s, &numToAdd) == 1)
            {
                pushDynArr(stack, numToAdd);
                numOperands++;
            }
		//If we get to this point, they have entered an invalid
		//character, operator, and operand
		else
            {
                printf("%s is not a valid input.\n", s);
                printf("Please rerun the program with supported operands, operators, and spaces.\n");
                exit(1);
            }

	}	//end for

	/* FIXME: You will write this part of the function (2 steps below)
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	 //Stack should have one value in it: the final result.
	 //Less means user did not provide enough numbers for amount of operators
	 int difference = numOperands - numOperators;
	 if (difference <= 0)
     {
         printf("You didn't enter enough numbers (too many operators) for the calculator to work.\n");
         printf("Please rerun the program, supplying the correct number.\n");
         //Exit with error
         exit(1);
     }
     else if(difference > 1)
     {
         printf("You entered too many numbers for the number of entered operators.\n");
         printf("Please rerun the program, supplying the correct number.\n");
         //Exit with error
         exit(1);
     }
     else
     {
         result = topDynArr(stack);
     }


	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	printf("Result of calculation is: %lf\n", calculate(argc,argv));
	return 0;
}
