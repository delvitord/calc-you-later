#include <ctype.h> // untuk memeriksa apakah sebuah karakter termasuk angka atau bukan pada 'isdigit()'
#include <windows.h>
#include "calculatorTree.h"
#include "calculatorStack.h"
#include "calculatorMain.h"
#include "stackChar.h"
#include "stackInt.h"
#include "boolean.h"

char read_operator; // variable for reading a charactor
Root *root;
Stack *stack;
address P;

void InputError();
void CheckAndGetChar(char math_opr);

void gotoxy(int x, int y){
                COORD coord;
                coord.X = x;
                coord.Y = y;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void chooseMenu(){ 
	int pilihan, desimal;
	do {
		system("cls");
		gotoxy(45,7); printf("============================");
		gotoxy(45,8);printf("==== CALC - YOU - LATER ===="); 
		gotoxy(45,9);printf("============================");
		gotoxy(52,11);printf("1. Calculator"); 
		gotoxy(49,12);printf("2. Biner ke Desimal"); 
		gotoxy(49,13);printf("3. Desimal ke Biner"); 
		gotoxy(54,14);printf("4. Quit"); 
		gotoxy(48,18);printf("------ Main Menu ------");
		gotoxy(47,16);printf("Masukkan Pilihan anda : "); 
		scanf("%d", &pilihan);
		char dump = getchar();
		switch (pilihan){
			case 1:
				menu_calculator();
				break;
			case 2: 
				menu_binToDec();
				break;
			case 3:
				menu_decToBin();
				break;
		}
	} while(pilihan < 4);

} 

int main(){
	/* Menampilkan Menu pada saat program dijalankan */ 
	chooseMenu(); 
}

void menu_calculator(){
	double result; //akan diisi oleh nilai akhir dari operasi hitung
	StackNode Snode;
	TreeNode *Tnode = NULL;
	printUI();
	printf("Masukkan operasi matematika :");
	gotoxy(0,6);
	
	//buat root dan stack kosong
	root = createRoot(); //buat tree kosong
	stack = createStack(); //buat stack kosong

	/// process
    read_operator = getchar(); //read operator agar operasi bilangan dapat dilakukan pada sum(), term(), dan factor() sehingga proses perhitungan dapat dilakukan
    result = sum(); // result diisi sum() karena sum() merupakan proses terakhir dalam operasi matematika sehingga keluaran dari sum() merupakan hasil akhir (result)
    
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
    printf("\nprefix : ");
    traversal(root,PREORDER);
    puts("");
    printf("infix : ");
    traversal(root,INORDER);
    puts("");
    printf("postfix : ");
    traversal(root,POSTORDER);
    puts("");
    printf("\nHasil Operasi : \n%g\n\n", result);
    
    if(result > 0){
	    printf("Ingin merubahnya ke dalam bentuk biner? (Klik Y untuk Ya): ");
	    char isToBiner = getch();
	    if (isToBiner == 'Y' || isToBiner == 'y'){
	    	int toBiner = result;
	    	decToBin(toBiner);
		} else {
			printf("\n\n");
		}
	}
	
	printf("Klik spasi jika ingin memasukkan operasi matematika yang lain: ");
    char isToMenu = getch();
    isToMenu == ' ' ? menu_calculator() : main();
}

void menu_binToDec(){
	system("cls");
	gotoxy(45,1); printf("============================");
	gotoxy(45,2);printf("==== CALC - YOU - LATER ===="); 
	gotoxy(45,3);printf("============================");
	gotoxy(41,4);printf("-Pengubah Bilangan Biner ke Desimal-");
	gotoxy(75,7); printf("Notes:");
	gotoxy(75,8); printf("Program tidak akan memproses inputan salah");
	gotoxy(75,9); printf("(ada karakter selain 1 dan 0)");
	gotoxy(0,7);
	
	stackChar s; 
	createstackChar(&s); 
	char nilai_stack;
	printf("Masukkan bilangan biner: \n");
	boolean inputSalah = false;

    do {
    	scanf("%c", &nilai_stack);
    	if (nilai_stack == '1' || nilai_stack == '0'){	
    		pushChar(&s, nilai_stack);
		} else if (nilai_stack != 10) { //10 adalah ASCII untuk enter
			inputSalah = true;
		}
	} while (nilai_stack != 10);	//10 adalah ASCII untuk enter
	
	
	if (inputSalah == false){
		int hasil = binToDec(s);
		printf("\nHasil desimalnya adalah:\n");
		printf("%d\n\n", hasil);
		printf("Klik spasi jika ingin memasukkan bilangan biner yang lain: ");
	    char isToMenu = getch();
	    isToMenu == ' ' ? menu_binToDec() : main();
	} else {
		printf("\nInput yang anda masukkan salah\n");
		printf("Klik apa saja untuk kembali memasukkan bilangan biner: ");
	    char isToMenu = getch();
	    isToMenu == ' ' ? menu_binToDec() : menu_binToDec();
	}
}

int binToDec(stackChar s){
	int pilihan, hasil_desimal = 0, nilai_pop2;
	char nilai_pop1; 
	
	stackInt biner; 
	createstackInt(&biner); 
	int i = s.jumlahTumpukan;
	int value;
	
	for (i; i >= 0; i--){
		value = pow(2,i);
		pushInt(&biner, value);
	}

	while (s.jumlahTumpukan > 0){
		nilai_pop1 = popChar(&s);
		nilai_pop2 = popInt(&biner);
		if (nilai_pop1 == '1'){
			hasil_desimal += nilai_pop2;
		}
	}
	return hasil_desimal;
}

void menu_decToBin(){
	int desimal;
	system("cls");
	gotoxy(45,1); printf("============================");
	gotoxy(45,2);printf("==== CALC - YOU - LATER ===="); 
	gotoxy(45,3);printf("============================");
	gotoxy(41,4);printf("-Pengubah Bilangan Desimal ke Biner-");
	gotoxy(75,7); printf("Notes:");
	gotoxy(75,8); printf("Program tidak akan memproses inputan salah");
	gotoxy(75,9); printf("(selain dari bilangan bulat positif)");
	gotoxy(0,7);
	printf("\nMasukkan desimal yang akan dikonversi (Bilangan bulat positif): \n"); 
	scanf("%d", &desimal);
	if (desimal > 0){
		decToBin(desimal);
		printf("Klik spasi jika ingin konversi bilangan desimal lain: ");
		char isToMenu = getch();
		isToMenu == ' ' ? menu_decToBin() : main();
	} else {
		printf("\nInput yang anda masukkan salah\n");
		printf("Klik apa saja untuk kembali memasukkan bilangan bulat positif: ");
	    char isToMenu = getch();
	    isToMenu == ' ' ? menu_decToBin() : menu_decToBin();
	}
	
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

void printUI(){
	system("cls");
	gotoxy(45,1); printf("============================");
	gotoxy(45,2);printf("==== CALC - YOU - LATER ===="); 
	gotoxy(45,3);printf("============================");
	gotoxy(75,5); printf("Operator Matematika");
	gotoxy(75,6); printf("'+' untuk tambah");
	gotoxy(75,7); printf("'-' untuk kurang dan bilangan negatif");
	gotoxy(75,8); printf("'*' untuk kali");
 	gotoxy(75,9); printf("'/' untuk bagi");
	gotoxy(75,10); printf("'^' untuk pangkat");
	gotoxy(75,11); printf("'s' untuk akar pangkat dua");
	gotoxy(75,12); printf("'c' untuk akar pangkat tiga");
	gotoxy(75,13); printf("'i' untuk sin");
	gotoxy(75,14); printf("'o' untuk cos");
	gotoxy(75,15); printf("'a' untuk tan");
	gotoxy(75,16); printf("'l' untuk logaritma");
	
	gotoxy(75,18); printf("Operator yang berupa huruf ditulis");
	gotoxy(75,19); printf("setelah bilangan atau kurung yang ");
	gotoxy(75,20); printf("akan dihitung dengan operator tersebut");
	
	gotoxy(75,22); printf("Tingkatan prioritas operasi");
	gotoxy(75,23); printf("1. Bilangan negatif dan kurung'()'");
	gotoxy(75,24); printf("2. Pangkat");
	gotoxy(75,25); printf("3. Akar");
	gotoxy(75,26); printf("4. Trigonometri dan Logaritma");
	gotoxy(75,27); printf("5. Kali dan bagi");
	gotoxy(75,28); printf("6. Tambah dan kurang");

	gotoxy(0,5);
}
