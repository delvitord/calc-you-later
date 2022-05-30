#include <ctype.h> // untuk memeriksa apakah sebuah karakter termasuk angka atau bukan pada 'isdigit()'
#include "calculatorTree.h"
#include "calculatorStack.h"
#include "calculatorMain.h"
#include "stackChar.h"
#include "stackInt.h"

char read_operator; // variable for reading a charactor
Root *root;
Stack *stack;
address P;

void InputError();
void CheckAndGetChar(char math_opr);

void chooseMenu(){ 
	int pilihan, desimal;
	do {
		printf("==== Calc-You-Later ===="); 
		printf("\n1. Calculator"); 
		printf("\n2. Biner to Decimal"); 
		printf("\n3. Decimal to Biner"); 
		printf("\n4. Quit"); 
		printf("\nMasukkan Pilihan anda : "); 
		scanf("%d", &pilihan);
		printf("\n");
		switch (pilihan){
			case 1:
				mainCalculator();
				break;
			case 2:
				binToDec();
				break;
			case 3:
				printf("\nMasukkan desimal yang akan dikonversi : "); 
				scanf("%d", &desimal);
				decToBin(desimal);
				break;
		}
	} while(pilihan < 4);

} 

int main(){
	/* Menampilkan Menu pada saat program dijalankan */ 
	chooseMenu(); 
}

void mainCalculator(){
	double value; //akan diisi oleh nilai akhir dari operasi hitung
	StackNode Snode;
	TreeNode *Tnode = NULL;
	printf("Masukan operasi matematika : \n");
	
	//buat root dan stack kosong
	root = createRoot(); //buat tree kosong
	stack = createStack(); //buat stack kosong

	/// process
	char dump = getchar();
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
    printf("Hasil Operasi : %g\n\n", value);
    
    printf("Ingin merubahnya ke dalam bentuk biner? (Y untuk lanjutkan): ", value);
    dump = getchar();
    char isToBiner = getchar();
    if (isToBiner = 'Y'){
    	int toBiner = value;
    	decToBin(toBiner);
	}
    
    
    
	
	/// delete
    deleteAll(P);
    return 0;
}

void binToDec(){
	stackChar s; 
	createstackChar(&s); 
	int pilihan, hasil_desimal = 0, nilai_pop2;
	char nilai_stack, nilai_pop1; 
	printf("Masukkan bilangan biner: ");
	char dump; 
	scanf("%c", &dump);
    do {
    	scanf("%c", &nilai_stack);
    	if (nilai_stack != 10){
    		pushChar(&s, nilai_stack);
		}
	} while (nilai_stack != 10);	//10 adalah ASCII untuk enter
	
	stackInt biner; 
	createstackInt(&biner); 
	int i = s.jumlahTumpukan;
	int value;
	
	for (i; i >= 0; i--){
		value = pow(2,i);
		pushInt(&biner, value);
		
	}

	while (s.jumlahTumpukan > 0){
		popChar(&s, &nilai_pop1);
		popInt(&biner, &nilai_pop2);
		if (nilai_pop1 == '1'){
			hasil_desimal += nilai_pop2;
		}
	}
	printf("\nHasil desimalnya adalah:");
	printf("%d\n\n", hasil_desimal);
}

void decToBin(int desimal){
	int hasil_modulus;
	stackInt toBin; 
	createstackInt(&toBin); 
	while(desimal > 0){
		hasil_modulus = desimal % 2;
		pushInt(&toBin, hasil_modulus);
		desimal /= 2;
	}
	printf("\nBilangan binernya adalah: \n");
	cetakstackBiner(toBin);
	printf("\n\n");
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
