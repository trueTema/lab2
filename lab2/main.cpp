#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <stdlib.h>
#include <string>
#include <exception>
#include "enum.h"
#include <initializer_list>
#include "Person.h"
#include "sortStation.h"
#include "complex.h"
#include "queue.h"
#include "stack.h"
using namespace std;

int x(int a, int b) {
	return a*b;
}

bool cmp(int a) {
	return a > 2;
}

bool cmp2(int a) {
	return a > 3;
}

bool cmp3(int a) {
	return a > 4;
}

int main() {
	setlocale(LC_CTYPE, "rus");
	complex c(1, 5);
	cout << c << '\n';
	queue<complex> q1({ c, complex(1,4) }, ArrayType);
	cout << q1 << '\n';
	queue<my_pair> q2({ my_pair("asd",1), my_pair("vtb",2) }, ListType);
	cout << q2 << '\n';
	return 0;
}

