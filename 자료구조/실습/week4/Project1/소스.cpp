#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "eval_postfix.h"
void main()
{
	char exp[100]; // postfix expression
	int result;
	while (1) {
		printf("\n Input postfix expression: ");
		scanf("%s", exp);
		result = eval_postfix(exp);
		printf(" Result = %d \n\n", result);
	}
}

boolean is_number(char c)
{
	if (('0' <= c) && (c <= '9'))
		return true;
	else
		return false;
}

void push(int e)
{
	if (top >= MAX_SIZE - 1)
	{
		printf("Stack is full !!!");
		return;
	}

	stack[++top] = e;
}
int pop()
{
	if (top == -1)
	{
		printf("Stack is empty!");
		return 0;
	}
	else
	{
		return stack[top--];
	}
}

boolean is_op(char c)
{
	if (!(is_number(c)))
		return true;
	else
		return false;
}
int eval_postfix(char *exp)
{
	int i = 0;
	char token = exp[0];
	int op, op1, op2;
	while ( token != NULL)
	{
		if (is_number(token))
		{
			op = token - '0';
			push(op);
		}

		if(is_op(token))
		{
			op2 = pop();
			op1 = pop();

			switch (token)
			{
			case '+':
				push(op1 + op2);
				break;
			case '-':
				push(op1 - op2);
				break;
			case '*':
				push(op1 * op2);
				break;
			case '/':
				push(op1 / op2);
				break;
			}
		}

		token = exp[++i];
	}

	return pop();
}
