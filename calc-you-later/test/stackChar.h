/* 
* File : stackChar.h 
* Deskripsi : Header file dari ADT Stack [Linked List] */ 

#ifndef _stackChar_H 
#define _stackChar_H 
#include "boolean.h" 
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#define nil NULL 
#define info(p) (p)->info 
#define prev(p) p->prev 
#define top(s) (s).top 

/* Definisi Type Bentukan ADT Stack [Linked List] */ 
typedef struct telmstackChar *addressChar; 
typedef struct telmstackChar{ 
	char info; 
	addressChar prev; 
}tabstackChar; 
typedef struct{ 
	addressChar top; 
	int jumlahTumpukan;
}stackChar; 

void createstackChar(stackChar *s); 
addressChar alokasiChar(char x); 
void dealokasiChar(addressChar p); 
void pushChar(stackChar *s, char x); 
void popChar(stackChar *s, char *x); 
void cetakstackChar(stackChar s); 
boolean isstackChar_empty(stackChar s); 

#endif


