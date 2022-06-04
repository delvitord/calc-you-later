#include "calculatorMain.h"

//Fungsi utama Kalkulator dan fungsi tambahan minor
char read_operator; // variable for reading a charactor
Root *root;
Stack *stack;
address P;

void InputError(){ //sebagai error handling jika terjadi kesalahan input
	printf("warning!\nplease insert the correct input."); 
	exit(1);
	}
	
void CheckAndGetChar(char math_opr){ // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
	if(math_opr != read_operator){ // jika operator yang diinput tidak sama dengan operator yang valid
		InputError(); //lakukan  error handling
		}
		read_operator = getchar(); //read operator agar operasi bilangan dapat dilakukan pada sum(), term(), dan factor() sehingga proses perhitungan dapat dilakukan
	}

// urutan program : faktor (cek kondisi) >> square (pangkat) >> sroot (akar) >> trigonometry >> term (kali dan bagi) >> sum (tambah dan kurang)

/* push data in the stack with the method of post-fix
   calculate addition and subtraction */
double sum(){ // fungsi (+) dan (-)
	double temp = term(); // temp akan diisi nilai dari term ((*) dan (:))
	Operation math; // math (double number dan char num_operator)
	while(read_operator == '+' || read_operator == '-'){ //read_operator yang valid adalah (+) dan (-)
		if(read_operator == '+'){ // jika read_operator (+)
			math.num_operator = '+'; // char num_operator diisi oleh char read_operator (+)
			CheckAndGetChar('+'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp += term(); // agar term (yang berisi * dan :) bisa dieksekusi terlebih dahulu)
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
		else if(read_operator == '-'){ // jika read_operator (-)
			math.num_operator = '-'; // char num_operator diisi oleh char read_operator (-)
			CheckAndGetChar('-'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp -= term(); // agar term (yang berisi * dan :) bisa dieksekusi terlebih dahulu)
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
	}
	return temp; // return nilai temp yang valuenya telah di update dengan sum
}

/** \brief
 * push data in the stack with the method of post-fix
 * calculate multiple and devision
 */
double term(){ // fungsi (*) dan (/)
	double temp = trigonometry(); // temp akan diisi nilai dari trigonometry()
	Operation math; // math (double number dan char num_operator)
	while(read_operator == '*' || read_operator == '/'){ //read_operator yang valid adalah (*) dan (:)
		if(read_operator == '*'){ // jika read_operator (*)
			math.num_operator = '*'; // char num_operator diisi oleh char read_operator (*)
			CheckAndGetChar('*'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp *= trigonometry(); // agar dapat dilakukan trigonometry terlebih dahulu pada trigonometry jika trigonometry akan dieksekusi terlebih dahulu
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
		else if(read_operator == '/'){ // jika read_operator (:)
			math.num_operator = '/'; // char num_operator diisi oleh char read_operator (:)
			CheckAndGetChar('/'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp /= trigonometry(); // agar dapat dilakukan trigonometry terlebih dahulu pada trigonometry jika trigonometry akan dieksekusi terlebih dahulu
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
		
	}
	return temp; // return nilai temp yang valuenya telah di update dengan term
}

/** \brief
 * push data in the stack with the method of post-fix
 * calculate multiple and devision
 */
double square(){ // fungsi untuk operasi perpangkatan
	double temp = factor(); // temp akan diisi nilai factor (cek syarat)
	Operation math; // math (double number dan char num_operator)
	while(read_operator == '^'){ //read_operator yang valid adalah (^), (v) , (!)  
		if(read_operator == '^'){ // jika read_operator (^)
			math.num_operator = '^'; // char num_operator diisi oleh char read_operator (^)
			CheckAndGetChar('^'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = pow(temp,factor()); // agar dapat dilakukan pengecekan terlebih dahulu pada faktor karena faktor akan dieksekusi terlebih dahulu
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
 }
	return temp; // return nilai temp yang valuenya telah di update dengan term
}

/** \brief
 * push data in the stack with the method of post-fix
 * calculate multiple and devision
 */
double sroot(){ // fungsi untuk operasi akar
	double temp = square(); // temp akan diisi nilai square (kuadrat)
	Operation math; // math (double number dan char num_operator)
	while(read_operator == 's'|| read_operator == 'c'){ //read_operator yang valid adalah (s) square, (c) cubic
		if(read_operator == 's'){ // jika read_operator (s)
			math.num_operator = 's'; // char num_operator diisi oleh char read_operator (s)
			CheckAndGetChar('s'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = sqrt(temp); // temp diisi nilai akar kuadrat dari temp yang sebelumnya (square())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
		if(read_operator == 'c'){ // jika read_operator (c)
			math.num_operator = 'c'; // char num_operator diisi oleh char read_operator (c)
			CheckAndGetChar('c'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = cbrt(temp); // temp diisi nilai akar kubik dari temp yang sebelumnya (square())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
		}
 }
	return temp; // return nilai temp yang valuenya telah di update dengan term
}

double trigonometry(){ // fungsi untuk trigonometri
	double temp = sroot(); //// temp akan diisi nilai sroot (akar)
	Operation math; // math (double number dan char num_operator)
	while(read_operator == 'i'|| read_operator == 'o'|| read_operator == 'a'|| read_operator == 'l'){ //read_operator yang valid adalah (i) sin, (o) cos, (a) tan, (l) log 
		if(read_operator == 'i'){ // jika read_operator (i)
			math.num_operator = 'i'; // char num_operator diisi oleh char read_operator (c)
			CheckAndGetChar('i'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = sin(temp); // temp diisi nilai sin dari temp yang sebelumnya (sroot())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
	}
	else if(read_operator == 'o'){ // jika read_operator (o)
			math.num_operator = 'o'; // char num_operator diisi oleh char read_operator (o)
			CheckAndGetChar('o'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = cos(temp); // temp diisi nilai cos dari temp yang sebelumnya (sroot())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
	}
	else if(read_operator == 'a'){ // jika read_operator (a)
			math.num_operator = 'a'; // char num_operator diisi oleh char read_operator (a)
			CheckAndGetChar('a'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = tan(temp); // temp diisi nilai tan dari temp yang sebelumnya (sroot())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
	}
	else if(read_operator == 'l'){ // jika read_operator (l)
			math.num_operator = 'l'; // char num_operator diisi oleh char read_operator (l)
			CheckAndGetChar('l'); // melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
			temp = log10(temp); // temp diisi nilai logaritma dari temp yang sebelumnya (sroot())
			push(stack, math, TRUE); // push (ke top, math (number dan num_operator), TRUE(1) isChar)
	}
 }
	return temp;
}

/** \brief
 * push data in the stack with the method of post-fix
 * regards factor as a number
 */
double factor(){ // fungsi untuk operasi lainnya
	double temp = 0.0; // nilai temp awal dideklarasikan sebagai nol karena faktor (cek kondisi) merupakan fungsi yang pertama dieksekusi pada operasi matematika
	Operation math; //math (double number dan char num_operator)
	if(read_operator == '('){ //read_operator yang valid adalah "("
		// start with new sum again
		CheckAndGetChar('('); //melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
		temp = sum(); // temp akan diisi nilai sum karena yang akan mengerjakan adalah penjumlahan atau pengurangan yang ada di dalam kurung terlebih dahulu
		CheckAndGetChar(')'); //melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
	}
	else if(read_operator == '-'){ // jika ada angka negatif
		// negation
		CheckAndGetChar('-'); //melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
		math.num_operator = '-'; // char num_operator diisi oleh char read_operator (-)
		temp = -factor(); //temp diisi dengan nilai faktor negatif
		push(stack, math, TRUE); //push (ke top, math (number dan num_operator), TRUE(1) isChar)
		return temp; // return value temp yang sudah di update berdasarkan perhitungan diatas
	}
	else if(read_operator == '+'){ //hanya untuk memastikan bahwa fungsi angka negatif bekerja
		// there is no meaning, but just exception dealing
		CheckAndGetChar('+'); //melakukan cek apakah inputan valid dan meminta input berupa char yang diakhiri dengan enter
		return factor(); //mengembalikan value sesuai nilai faktor (apakah positif atau negatif
	}
	else if(isdigit(read_operator)){ //untuk memeriksa apakah sebuah karakter termasuk angka atau bukan
		ungetc(read_operator, stdin); //agar operator yang salah tidak di displaykan dan di save ke file
		scanf("%lf", &temp); //agar akurat 15 angka di belakang koma (double)
		math.number = temp; // double numer pada Operation math diisi nilai temp yang diinput oleh user
		push(stack, math, FALSE); //lakukan push hanya pada number (operator => isChar = False(0))
		read_operator = getchar(); //read operator agar operasi bilangan dapat dilakukan pada sum(), term(), dan factor()
	}
	else InputError(); // jika terjadi kesalahan inputan
	return temp; // mengembalikan nilai temp sesuai yang diisikan user
}

double factorial(){ //catatan: Untuk sementara belum dapat membaca operasi faktorial
	double temp = sroot();
	Operation math;
	while (read_operator == '!'){
		if (read_operator == '!'){
			math.num_operator = '!';
			CheckAndGetChar('!');
			if(temp == 0){
				return 1;
			}
			temp = temp*factorial(temp-1);
			push(stack, math, TRUE);
		}
	}
}
