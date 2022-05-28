#include <ctype.h> // untuk memeriksa apakah sebuah karakter termasuk angka atau bukan pada 'isdigit()'
#include "calculatorTree.h"
#include "calculatorStack.h"
#include "calculatorMain.h"

char read_operator; // variable for reading a charactor
Root *root;
Stack *stack;
address P;

void InputError();
void CheckAndGetChar(char math_opr);

int main(){
	double value; //akan diisi oleh nilai akhir dari operasi hitung
	StackNode Snode;
	TreeNode *Tnode = NULL;
	printf("Masukan operasi matematika : \n");
	
	//buat root dan stack kosong
	root = createRoot(); //buat tree kosong
	stack = createStack(); //buat stack kosong

	/// process
    read_operator = getchar(); //read operator agar operasi bilangan dapat dilakukan pada sum(), term(), dan factor() sehingga proses perhitungan dapat dilakukan
    value = sum(); // value diisi sum() karena sum() merupakan proses terakhir dalam operasi matematika sehingga keluaran dari sum() merupakan hasil akhir (value)
    
	//Stack telah terbentuk dengan telah berhasilnya dibaca operasi hitung dan angka yang diinputkan

	// construct tree dari Stack yang sudah terbentuk
	while(!isEmpty(stack)){ //selama stack masih terisi maka construct tree
		// As the stack is being removed, constructs tree
		Snode = pop(stack); // pop dari stack (pop dulu baru create)
		while(Snode.isChar) //selama dalam stack node masih terdapat ischar (id) yang harus di cek
		{
		// operator (math.num_operator)
		Tnode = createChild(Tnode, Snode.math, Snode.isChar); //pada tree node buat child baru
		if(root->root == NULL){ // jika root kosong
			root->root = Tnode; // isi root
		}
			Snode = pop(stack); // pop dari stack (create dulu baru pop)
		}
		// number (math.number)
		Tnode = createChild(Tnode, Snode.math, Snode.isChar); //pada tree node buat child baru
		if(root->root == NULL){ // jika root kosong
			root->root = Tnode; // isi root
		}	
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

// urutan program : faktor (cek kondisi) >> square (pangkat) >> term (kali dan bagi) >> sum (tambah dan kurang)

/* push data in the stack with the method of post-fix
   calculate addition and subtraction */
double sum(); // fungsi (+) dan (-)

/** \brief
 * push data in the stack with the method of post-fix
 * calculate multiple and devision
 */
double term(); // fungsi (+) dan (-)

/** \brief
 * push data in the stack with the method of post-fix
 * regards factor as a number
 */
double factor(); // fungsi untuk operasi lainnya
