/* 
* File : stackChar.c 
* Deskripsi : Body file dari ADT Stack Dinamis yang infotypenya bertipe Char */ 

#include "stackChar.h"
#include <stdio.h> 
#include <conio.h> 

void createstackChar(stackChar *s){ 
	top(*s) = nil; 
	(*s).jumlahTumpukan = 0;
} 

addressChar alokasiChar(char x){ 
	tabstackChar *p; 
	p = (tabstackChar*)malloc(sizeof(tabstackChar)); 
	if(p != nil){ 
		info(p) = x; 
		p->prev = nil; 
		return p; 
	} else { 
		return nil; 
	} 
} 

void dealokasiChar(addressChar p){ 
	free(p); 
} 

void pushChar(stackChar *s, char x){ 
	addressChar p,q; 
	p = alokasiChar(x); 
	if (isstackChar_empty(*s)) {
		top(*s) = p; 
	} else { 
		prev(p) = top(*s); 
		top(*s) = p; 
	
	} 
	(*s).jumlahTumpukan += 1;
} 
char popChar(stackChar *s){  
	addressChar pTOP; 
	pTOP = top(*s); 
	char x = info(pTOP); 
	if(prev(pTOP) == nil){ // hanya ada 1 elemen 
		top(*s) = nil; 
	} else { // lebih dari satu elemen 
		top(*s) = prev(pTOP); 
		prev(pTOP) = nil; 
	} 
	(*s).jumlahTumpukan -= 1;
	return x;
} 
void cetakstackChar(stackChar s){ 
	tabstackChar *p, *q; 
	printf("isi stack dari mulai TOP s.d. BUTTOM : \n"); 
	if(!isstackChar_empty(s)){
		p = top(s); 
		printf("[ %c ]", info(p)); 
		p = prev(p); 
		while (p != nil){ 
			printf(" - [ %c ]", info(p)); 
			p = prev(p); 
		} 
	} else { 
		printf("[ Empty ]"); 
	} 
} 

boolean isstackChar_empty(stackChar s){ 
	if(top(s) == nil){ 
		return true; 
	} else { 
		return false; 
	} 
} 




