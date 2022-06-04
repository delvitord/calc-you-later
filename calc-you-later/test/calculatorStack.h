#ifndef calculatorStack_H
#define calculatorStack_H
#include "Common.h"

/* Definisi Type Bentukan ADT Stack [Linked List] */ 
typedef struct StackNode{
	int isChar;
	Operation math;
	address pNode;
} StackNode;

typedef struct Stack{
	address top;
} Stack;

int isEmpty(Stack *stack);
address createNode();
address createStack();
void printNode(address tNode);
void push(Stack *stack, Operation math, int isChar);
StackNode pop(Stack *stack);
void removeStack(Stack *stack);

#endif
