#ifndef calculatorMain_H
#define calculatorMain_H
#include "calculatorTree.h"
#include "calculatorStack.h"
#include "Common.h"
#include <ctype.h> // untuk memeriksa apakah sebuah karakter termasuk angka atau bukan pada 'isdigit()'

void InputError();
void CheckAndGetChar(char math_opr);
double term();
double sum();
double factor();

#endif
