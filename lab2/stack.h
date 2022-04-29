#pragma once
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include <iostream>
#include <initializer_list>
#include "enum.h"

template<class T>
class stack
{
	
	template<class Y>
	friend std::ostream& operator<<(std::ostream& os, stack<Y>& q);
private:
	type param;
protected:
	Sequence<T>* seq;
public:
	stack(type);
	stack(stack<T>&);
	stack(initializer_list<T>, type);
	~stack();

	bool find(T);
	void push(T);
	void pop();
	T& top();
	int GetLength();
	stack<T>* Concat(stack<T>*);
	bool Equals(stack<T>*);
	bool IsSubStack(stack<T>*);
	stack<T>* GetSubStack(int startIndex, int endIndex);
	stack<T>* where(bool(T));
	void map(T(T));
	T reduce(T(T, T), T);

	bool operator ==(stack<T>&);
	bool operator !=(stack<T>&);
};

template<class T>
stack<T>::stack(type param) {
	this->param = param;
	switch (param) {
	case ArrayType:
		seq = new ArraySequence<T>;
		break;
	case ListType:
		seq = new ListSequence<T>;
		break;
	default:
		break;
	}

}

template<class T>
stack<T>::stack(stack<T>& q) {
	this->param = q.param;
	switch (param) {
	case ArrayType:
		seq = new ArraySequence<T>(q.seq);
		break;
	case ListType:
		seq = new ListSequence<T>(q.seq);
		break;
	default:
		break;
	}
}

template<class T>
stack<T>::stack(initializer_list<T> list, type param) {
	this->param = param;
	switch (param) {
	case ArrayType:
		seq = new ArraySequence<T>(list);
		break;
	case ListType:
		seq = new ListSequence<T>(list);
		break;
	default:
		break;
	}
}

template<class T>
stack<T>::~stack() {
	delete seq;
}

template<class T>
bool stack<T>::find(T item) {
	return (this->seq->find(0, this->seq->GetLength() - 1, item)) != -1;
}

template<class T>
void stack<T>::push(T item) {
	seq->Prepend(item);
}

template<class T>
T& stack<T>::top() {
	return this->seq->GetFirst();
}

template<class T>
void stack<T>::pop() {
	seq->del_item(0);
}

template<class T>
int stack<T>::GetLength() {
	return this->seq->GetLength();
}

template<class T>
stack<T>* stack<T>::Concat(stack<T>* st) {
	stack<T>* res = new stack<T>(param);
	res -> seq = this->seq->Concat(st -> seq);
	return res;
}

template<class T>
bool stack<T>::Equals(stack<T>* st) {
	return st ->seq->Equals(this->seq);
}

template<class T>
bool stack<T>::IsSubStack(stack<T>* st) {
	return this->seq->IsSubSeq(st -> seq);
}

template<class T> 
stack<T>* stack<T>::GetSubStack(int startIndex, int endIndex) {
	stack<T>* res = new stack<T>(this -> param);
	res->seq = this->seq->GetSubSequence(startIndex, endIndex);
	return res;
}


template<class T>
stack<T>* stack<T>::where(bool cmp(T)) {
	stack<T>* res = new stack<T>(param);
	for (int i = 0; i < this->GetLength(); i++) {
		if (cmp(this->seq->Get(i))) {
			res->seq->Append(this->seq->Get(i));
		}
	}
	return res;
}

template<class T>
void stack<T>::map(T change(T)) {

	for (int i = 0; i < this->GetLength(); i++) {
		this->seq->Set(i, change(this->seq->Get(i)));
	}
}

template<class T>
T stack<T>::reduce(T change(T, T), T startConst) {
	T res = change(this->seq->Get(0), startConst);
	for (int i = 1; i < this->GetLength(); i++) {
		res = change(res, this->seq->Get(i));
	}
	return res;
}


template<class T>
std::ostream& operator << (std::ostream& os, stack<T>& st) {
	os << "{ ";
	for (int i = 0; i < st.GetLength(); i++) {
		if (i < st.GetLength() - 1) {
			os << st.seq->Get(i) << ", ";
		}
		else {
			os << st.seq->Get(i);
		}
	}
	os << " }";
	return os;
}

template<class T>
bool stack<T>::operator ==(stack<T>& q) {
	return this->Equals(&q);
}

template<class T>
bool stack<T>::operator !=(stack<T>& q) {
	return !this->Equals(&q);
}