#include <ctype.h> // untuk memeriksa apakah sebuah karakter termasuk angka atau bukan pada 'isdigit()'
#include "calculatorTree.h"
#include "calculatorStack.h"

char read_operator; // variable for reading a charactor
Root *root;
Stack *stack;
address P;

void InputError(){
	printf("warning!\nplease insert the correct input.");
	exit(1);
}

void CheckAndGetChar(char math_opr){
	if(math_opr != read_operator){
		InputError();
	}
	read_operator = getchar();
}

double term();
double sum();
double factor();

int main(){
	double value;
	StackNode Snode;
	TreeNode *Tnode = NULL;
	printf("Masukan operasi matematika : \n");
	
	/// make data structures for each cases
	root = createRoot();
	stack = createStack();

	/// process
    read_operator = getchar();
    value = sum();
	// now, stack is already built

	/// construct tree
	while(!isEmpty(stack)){
		// As the stack is being removed, constructs tree
		Snode = pop(stack);
		while(Snode.isChar)
		{
			// operator
			Tnode = createChild(Tnode, Snode.math, Snode.isChar);
			if(root->root == NULL)	root->root = Tnode;
			Snode = pop(stack);
		}
		// number
		Tnode = createChild(Tnode, Snode.math, Snode.isChar);
		if(root->root == NULL)	root->root = Tnode;
	}
    // lakukan print secara transversal
    printf("prefix : ");
    traversal(root,PREORDER);
    puts("");
    printf("infix : ");
    traversal(root,INORDER);
    puts("");
    printf("postfix : ");
    traversal(root,POSTORDER);
    puts("");
    printf("Hasil Operasi : %g\n", value);

    /// delete
    deleteAll(P);
    return 0;
}

/* push data in the stack with the method of post-fix
   calculate addition and subtraction */
double sum(){
	double temp = term();
	Operation math;
	while(read_operator == '+' || read_operator == '-'){
		if(read_operator == '+'){
			math.num_operator = '+';
			CheckAndGetChar('+');
			temp += term();
			push(stack, math, TRUE);
		}
		else if(read_operator == '-'){
			math.num_operator = '-';
			CheckAndGetChar('-');
			temp -= term();
			push(stack, math, TRUE);
		}
	}
	return temp;
}

/** \brief
 * push data in the stack with the method of post-fix
 * calculate multiple and devision
 */
double term(){
	double temp = factor();
	Operation math;
	while(read_operator == '*' || read_operator == '/'){
		if(read_operator == '*'){
			math.num_operator = '*';
			CheckAndGetChar('*');
			temp *= factor();
			push(stack, math, TRUE);
		}
		else if(read_operator == '/'){
			math.num_operator = '/';
			CheckAndGetChar('/');
			temp /= factor();
			push(stack, math, TRUE);
		}
	}
	return temp;
}

/** \brief
 * push data in the stack with the method of post-fix
 * regards factor as a number
 */
double factor(){
	double temp = 0.0;
	Operation math;
	if(read_operator == '('){
		// start with new sum again
		CheckAndGetChar('(');
		temp = sum();
		CheckAndGetChar(')');
	}
	else if(read_operator == '-'){
		// negation
		CheckAndGetChar('-');
		math.num_operator = '-';
		temp = -factor();
		push(stack, math, TRUE);
		return temp;
	}
	else if(read_operator == '+'){
		// there is no meaning, but just exception dealing
		CheckAndGetChar('+');
		return factor();
	}
	else if(isdigit(read_operator)){
		ungetc(read_operator, stdin);
		scanf("%lf", &temp);
		math.number = temp;
		push(stack, math, FALSE);
		read_operator = getchar();
	}
	else InputError();
	return temp;
}
