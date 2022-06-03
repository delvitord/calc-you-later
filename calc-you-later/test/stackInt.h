/* 
* File : stackInt.h 
* Deskripsi : Header file dari ADT Stack [Linked List] */ 

#ifndef _stackInt_H 
#define _stackInt_H 
#include "boolean.h" 
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#define nil NULL 
#define info(p) (p)->info 
#define prev(p) p->prev 
#define top(s) (s).top 

/* Definisi Type Bentukan ADT Stack [Linked List] */ 
typedef struct telmstackInt *addressInt; 
typedef struct telmstackInt{ 
	int info; 
	addressInt prev; 
}tabstackInt; 
typedef struct{ 
	addressInt top; 
	int jumlahTumpukan;
}stackInt; 

void createstackInt (stackInt *s);  
addressInt alokasiInt (int x); 
void dealokasiInt (addressInt p); 
void pushInt (stackInt *s, int x); 
void popInt(stackInt *s, int *x); 
void cetakstackInt(stackInt s); 
void cetakstackBiner(stackInt s);
boolean isstackInt_empty(stackInt s); 

#endif


