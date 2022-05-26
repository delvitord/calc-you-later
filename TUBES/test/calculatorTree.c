#include "calculatorTree.h"

address createRoot(){
	address P = (Root*)calloc(sizeof(Root), 1);
	if(!P) {
		printf("memory penuh!");
		exit(1);
	}
	return P;
}

address createTree(){
	address P = (TreeNode*)calloc(sizeof(TreeNode), 1);
	if(!P){
		printf("memory penuh!");
		exit(1);
	}
	return P;
}

// Node : parent node
// math : input data1
// isChar : input data2
// return self node or new child node

address createChild(TreeNode *Node,Operation math,int isChar){
	if(!Node){
		Node = createTree();
		Node->math = math;
		Node->isChar = isChar;
		return Node;
	}
	if(Node->left && Node->right){
		Node = Node->parent;
		if(!Node){
			return NULL;
		}
		return createChild(Node,math,isChar);
	}

	if(!isChar){ // number, from right. return self node pointer.
		if(Node->right){
			left(Node,math,isChar);
		}
		else{
			right(Node,math,isChar);
		}
		return Node;
	}
	else{ // operator, from left. return its child node pointer.
		if(Node->left){
			right(Node,math,isChar);
			return Node->right;
		}
		else{
			left(Node,math,isChar);
			return Node->left;
		}
	}
}

void left(TreeNode *Node,Operation math,int isChar){
	address P = createTree();
	if(!P){
		return;
	}
	P->math = math;
	P->isChar = isChar;
	Node->left = P;
	P->parent = Node;
}

void right(TreeNode *Node,Operation math,int isChar)
{
address P = createTree();
	if(!P){
		return;
	}
	P->math = math;
	P->isChar = isChar;
	Node->right = P;
	P->parent = Node;
}

void print(Operation math,int isChar)
{
	if(isChar){
		printf("%c", math.num_operator);
	}
	else{
		printf("%g", math.number);
	}
}

void traversal(Root *root,int mode){
	address P = root->root;
	switch(mode){
		case PREORDER:
			preorder(P);
			break;
		case INORDER:
			inorder(P);
			break;
		case POSTORDER:
			postorder(P);
			break;
	}
}

void preorder(TreeNode *tNode){
	if(!tNode){
		return;
	}
	print(tNode->math, tNode->isChar);
	preorder(tNode->left);
	preorder(tNode->right);
}

void inorder(TreeNode *tNode){
	if(!tNode)	return;
	inorder(tNode->left);
	print(tNode->math, tNode->isChar);
	inorder(tNode->right);
}

void postorder(TreeNode *tNode){
	if(!tNode)	return;
	postorder(tNode->left);
	postorder(tNode->right);
	print(tNode->math, tNode->isChar);
}

//melakukan delete pada element tertentu
address minValueNode(address P){
	address current = P;
	while (current && current->left != NULL){ //loop hingga mencapai leaf paling kiri
        current = current->left;
	}
    return current;
}

address deleteNode(address P, int isChar){
	if (P == NULL){ //jika address NULL
        return P;
    }
    if (isChar < P->isChar){ //jika node yang akan di delete memiliki nilai yang lebih kecil dari parent
        P->left = deleteNode(P->left, isChar);
    }
    else if (isChar > P->isChar){ //jika node yang akan di delete memiliki nilai yang lebih besar dari parent
        P->right = deleteNode(P->right, isChar);
    }
    else{
        // node dengan hanya satu child atau tanpa child samasekali
        if (P->left == NULL){ // node dengan child lebih kecil dari parent
            address temp = P->right;
            free(P);
            return temp;
        }
        else if (P->right == NULL){ // node dengan child lebih besar dari parent
            address temp = P->left;
            free(P);
            return temp;
        }
        address temp = minValueNode(P->right);
        P->isChar = temp->isChar;
        P->right = deleteNode(P->right, temp->isChar);
    }
    return P;
}

void deleteAll(address treeNode){
	if (treeNode == NULL) return;
	deleteAll(treeNode->left);
    deleteAll(treeNode->right);
    printf("\n Deleting node : %d\n", treeNode->isChar);
    free(treeNode);
}
