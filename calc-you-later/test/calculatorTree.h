#ifndef calculatorTree_H
#define calculatorTree_H
#include "Common.h"

typedef struct TreeNode{
	int isChar;
	Operation math;
	address parent;
	address left;
	address right;
} TreeNode;

typedef struct Root{
	address root;
} Root;

address createRoot();
address createTree();
address createChild(TreeNode *Node,Operation math,int isChar);
void left(TreeNode *Node,Operation math,int isChar);
void right(TreeNode *Node,Operation math,int isChar);
void print(Operation math,int isChar);
void traversal(Root *root,int mode);
void preorder(TreeNode *tNode);
void inorder(TreeNode *tNode);
void postorder(TreeNode *tNode);
address minValueNode(address P);
address deleteNode(address P, int id);
void deleteAll(address treeNode);

#endif
