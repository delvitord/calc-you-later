#ifndef common_H
#define common_H

#include <stdlib.h>
#include <stdio.h>

#define PREORDER	0
#define INORDER		1
#define POSTORDER	2

#define TRUE		1
#define FALSE	 	0

typedef struct addNode *address;
typedef union{ //struct untuk assign operasi matematika
	double number;
	char num_operator;
} Operation;

#endif
