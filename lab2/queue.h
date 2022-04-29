#pragma once
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include <initializer_list>
#include <iostream>
#include <string>
#include "enum.h"
using namespace std;

template<class T>
class queue
{
	template<class Y>
	friend std::ostream& operator<<(std::ostream& os, queue<Y>& q);
private:
	type param;
protected:
	Sequence<T>* seq;
public:
	queue(type);
	queue(queue<T>&);
	queue(initializer_list<T>, type);
	~queue();

	bool find(T);
	void push(T);
	void pop();
	T& front();
	int GetLength();
	queue<T>* Concat(queue<T>*);
	bool Equals(queue<T>*);
	bool IsSubQueue(queue<T>*);
	queue<T>* GetSubQueue(int startIndex, int endIndex);
	queue<T>* SplitQueue(bool (T));


	queue<T>* where(bool (T));
	void map(T (T));
	T reduce(T (T, T), T);

	bool operator ==(queue<T>&);
	//template<class Y>
	bool operator !=(queue<T>&);
};

template<class T>
queue<T>::queue(type param) {
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
queue<T>::queue(queue<T>& q) {
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
queue<T>::queue(initializer_list<T> list, type param) {
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
queue<T>::~queue() {
	delete seq;
}

template<class T>
bool queue<T>::find(T item) {
	return (this->seq->find(0, this->seq->GetLength() - 1, item)) != -1;
}

template<class T>
void queue<T>::push(T item) {
	seq->Append(item);
}

template<class T>
void queue<T>::pop() {
	seq->del_item(0);
}

template<class T>
T& queue<T>::front() {
	return seq->GetFirst();
}

template<class T>
int queue<T>::GetLength()  {
	return this->seq->GetLength();
}

template<class T>
queue<T>* queue<T>::Concat(queue<T>* st) {
	queue<T>* res = new queue<T>(param);
	res->seq = this->seq->Concat(st->seq);
	return res;
}

template<class T>
bool queue<T>::Equals(queue<T>* st) {
	return (st->seq)->Equals(this->seq);
}

template<class T>
bool queue<T>::IsSubQueue(queue<T>* st) {
	return this->seq->IsSubSeq(st->seq);
}

template<class T>
queue<T>* queue<T>::GetSubQueue(int startIndex, int endIndex) {
	queue<T>* res = new queue<T>( this -> param);
	res->seq = this->seq->GetSubSequence(startIndex, endIndex);
	return res;
}

template<class T>
queue<T>* queue<T>::SplitQueue(bool cmp(T)) {
	queue<T>* res = new queue<T>(this -> param);
	res->seq = this->seq->SplitSeq(cmp);
	if (res->GetLength() == 0) {
		delete res;
		return nullptr;
	}
	return res;
}

template<class T>
queue<T>* queue<T>::where(bool cmp(T)) {
	queue<T>* res = new queue<T>(param);
	for (int i = 0; i < this->GetLength(); i++) {
		if (cmp(this->seq->Get(i))) {
			res->seq->Append(this->seq->Get(i));
		}
	}
	return res;
}

template<class T>
void queue<T>::map(T change(T)) {

	for (int i = 0; i < this->GetLength(); i++) {
		this->seq->Set(i,change(this -> seq -> Get(i)));
	}
}

template<class T>
T queue<T>::reduce(T change(T, T), T startConst) {
	T res = change(this->seq->Get(0), startConst);
	for (int i = 1; i < this->GetLength(); i++) {
		res = change(res, this->seq->Get(i));
	}
	return res;
}

template<class T>
bool queue<T>::operator ==(queue<T> &q) {
	return this->Equals(&q);
}

template<class T>
bool queue<T>::operator !=(queue<T>& q) {
	return !this -> Equals(&q);
}

template<class T>
std::ostream& operator << (std::ostream& os, queue<T>& q) {
	os <<  "{ ";
	for (int i = 0; i < q.GetLength(); i++) {
		if (i < q.GetLength() - 1) {
			os << q.seq -> Get(i) << ", ";
		}
		else {
			os << q.seq->Get(i);
		}
	}
	os << " }";
	return os;
}