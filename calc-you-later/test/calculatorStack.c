#include "calculatorStack.h"

int isEmpty(Stack *stack){ // cek stack kosong
	if(!stack){
		printf("Stack tidak tersedia!");
		return TRUE;
	}
	return stack->top == NULL;
}

address createNode(){ // buat node pada stack
	StackNode *node = (StackNode*)calloc(sizeof(StackNode), 1);
	if(!node){
		printf("memory penuh!");
		exit(1);
	}
	return node;
}

address createStack(){ // buat stack
	Stack *stack = (Stack*)calloc(sizeof(Stack), 1);
	if(!stack) {
		printf("memory penuh!");
		exit(1);
	}
	return stack;
}

void printNode(address tNode){
	if(!tNode){
		return;
	}
	if(tNode->isChar){
		printf("%c", tNode->math.num_operator);
	}
	else{
		printf("%g", tNode->math.number);
	}
}

void push(Stack *stack, Operation math, int isChar){
	address P = createNode(P);
	if(!P){
		printf("memory penuh!");
		exit(1);
	}
	P->math = math;
	P->isChar = isChar;
	P->pNode = stack->top;
	stack->top = P;
}

StackNode pop(Stack *stack){
	StackNode Node;
	Node.isChar = FALSE;
	if(!stack || isEmpty(stack)){
		return Node;
	}	
	Node = *(stack->top);
	address P = stack->top;
	stack->top = P->pNode;
	free(P);
	return Node;
}

void removeStack(Stack *stack)
{
	StackNode Node;
	while(!isEmpty(stack)) {
		Node = pop(stack);
		printNode(&Node);
	}
}
