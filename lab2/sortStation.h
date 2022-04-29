#pragma once
#include "stack.h"
#include "queue.h"
#include <ostream>
using namespace std;

class my_pair {
private:
	string type_name;
	size_t num_name;
public:
	my_pair(string a, int b);
	my_pair();
	string type();
	size_t num();
	bool operator==(my_pair);
	bool operator!=(my_pair);
	friend std::ostream& operator << (std:: ostream& os, my_pair& mp);
};



void sort(queue<my_pair>&);
void getSourceQueue(queue<my_pair>&);