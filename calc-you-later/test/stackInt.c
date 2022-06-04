/* 
* File : stackInt.c 
* Deskripsi : Body file dari ADT Stack [Linked List] */ 

#include "stackInt.h"
#include <stdio.h> 
#include <conio.h> 


/* {Konstruktor pembentuk Stack} */ 
void createstackInt(stackInt *s){ 

	top(*s) = nil; 
	(*s).jumlahTumpukan = 0;
} 

/* {Opeasi terhadap komponen : selektor Get dan Set} */ 
//Destruktor or Dealokator 
addressInt alokasiInt(int x){ 

	tabstackInt *p; 

	p = (tabstackInt*)malloc(sizeof(tabstackInt)); 
	if(p != nil){ 
		info(p) = x; 
		p->prev = nil; 
		return p; 
	} else { 
		return nil; 
	} 
} 

void dealokasiInt(addressInt p){ 
	free(p); 
} 

void pushInt(stackInt *s, int x){ 
	addressInt p,q; 
	p = alokasiInt(x); 
	if (isstackInt_empty(*s)) { // Stack Kosong 
		top(*s) = p; 
	} else { // Stack tidak kosong 
		prev(p) = top(*s); 
		top(*s) = p; 
	
	} 
	(*s).jumlahTumpukan += 1;
} 
int popInt(stackInt *s){ 
	addressInt pTOP; 
	pTOP = top(*s); 
	int x = info(pTOP); 
	if(prev(pTOP) == nil){ // hanya ada 1 elemen 
		top(*s) = nil; 
	} else { // lebih dari satu elemen 
		top(*s) = prev(pTOP); 
		prev(pTOP) = nil; 
	} 
	(*s).jumlahTumpukan -= 1;
	return x;
} 
void cetakstackInt(stackInt s){ 
	tabstackInt *p, *q; 
	printf("isi stack dari mulai TOP s.d. BUTTOM : \n"); 
	if(!isstackInt_empty(s)){
		p = top(s); 
		printf("[ %d ]", info(p)); 
		p = prev(p); 
		while (p != nil){ 
			printf(" - [ %d ]", info(p)); 
			p = prev(p); 
		} 
	} else { 
		printf("[ Empty ]"); 
	} 
} 

void cetakstackBiner(stackInt s){ 
	tabstackInt *p, *q; 

	if(!isstackInt_empty(s)){
		p = top(s); 
		while (p != nil){ 
			printf("%d", info(p)); 
			p = prev(p); 
		} 
	} else { 
		printf("[ Empty ]"); 
	} 
} 

boolean isstackInt_empty(stackInt s){ 
	if(top(s) == nil){ 
		return true; 
	} else { 
		return false; 
	} 
} 

