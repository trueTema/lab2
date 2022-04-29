#pragma once
#include "DynamicArray.h"
#include "Sequence.h"
using namespace std;
template<typename T>
class ArraySequence : public Sequence<T>
{
protected:
	DynamicArray<T>* arr;
public:
	ArraySequence();
	ArraySequence(T*, int);
	ArraySequence(Sequence<T>*);
	ArraySequence(initializer_list<T>);
	~ArraySequence();

	T& GetFirst() override;
	T& GetLast() override;
	T& Get(int) override;
	
	
	Sequence<T>* GetSubSequence(int, int) override;
	int GetLength() override;
	void Append(T) override;
	void Prepend(T) override;
	void Set(int, T) override;
	void InsertAt(T, int) override;
	void del_item(int) override;
	Sequence<T>* SplitSeq(bool (T)) override;
	Sequence<T>* Concat(Sequence<T>*) override;
	int find(int, int, T) override;
	bool IsSubSeq(Sequence<T>*) override;
	bool Equals(Sequence<T>*) override;
	
	
	bool operator==(Sequence<T>*);
	bool operator!=(Sequence<T>*);
};

template<typename T>
ArraySequence<T>::ArraySequence() {
	arr = new DynamicArray<T>;
}

template<typename T>
ArraySequence<T>::ArraySequence(T* items, int count) {
	arr = new DynamicArray<T>(items, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(Sequence<T>* arr) {
	this->arr = new DynamicArray<T>(((ArraySequence<T>*)arr)->arr);
}

template<typename T>
ArraySequence<T>::ArraySequence(initializer_list<T> list) {
	this->arr = new DynamicArray<T>(list);
}


template<typename T>
ArraySequence<T>::~ArraySequence() {
	delete arr;
}

template<typename T>
T& ArraySequence<T>::GetFirst() {
	return this->arr->Get(0);
}


template<typename T>
T& ArraySequence<T>::GetLast()  {
	return this->arr->Get(this->arr->GetSize() - 1);
}

template<typename T>
T& ArraySequence<T>::Get(int index)  {
	return this->arr->Get(index);
}

template<typename T>
Sequence<T>* ArraySequence<T>::GetSubSequence(int startIndex, int endIndex)  {
	DynamicArray<T>* x = this->arr->GetSubArray(startIndex, endIndex);
	ArraySequence<T>* resseq = new ArraySequence<T>;
	delete resseq->arr;
	resseq->arr = x;
	return resseq;
}

template<typename T>
int ArraySequence<T>::GetLength() {
	return this->arr->GetSize();
}
template<typename T>
void ArraySequence<T>::Append(T item)  {
	this->arr->Append(item);
}
template<typename T>
void ArraySequence<T>::Prepend(T item)  {
	this->arr->Prepend(item);
}

template<typename T>
void ArraySequence<T>::Set(int index, T item)  {
	this->arr->Set(index, item);
}

template<typename T>
void ArraySequence<T>::InsertAt(T item, int index)  {
	this->arr->InsertAt(item, index);
}

template<typename T>
void ArraySequence<T>::del_item(int index)  {
	this->arr->del_item(index);
}

template<typename T>
Sequence<T>* ArraySequence<T>::SplitSeq(bool cmp(T))  {
	DynamicArray<T>* x = this->arr->SplitArray(cmp);
	ArraySequence<T>* resseq = new ArraySequence<T>;
	delete resseq->arr;
	resseq->arr = x;
	return resseq;
}

template<typename T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* seq)  {
	DynamicArray<T>* x = this->arr->Concat(((ArraySequence<T>*)seq)->arr);
	ArraySequence<T>* resseq = new ArraySequence<T>;
	delete resseq->arr;
	resseq->arr = x;
	return resseq;
}

template<typename T>
int ArraySequence<T>::find(int startIndex, int endIndex, T item)  {
	return this->arr->find(startIndex, endIndex, item);
}

template<typename T>
bool ArraySequence<T>::IsSubSeq(Sequence<T>* seq)  {
	return this->arr->IsSubArr(((ArraySequence<T>*)seq)->arr);
}

template<typename T>
bool ArraySequence<T>::Equals(Sequence<T>* seq) {
	return this->arr->Equals(((ArraySequence<T>*)seq)->arr);
}

template<typename T>
bool ArraySequence<T>:: operator==(Sequence<T>* seq) {
	return this->Equals(seq);
}

template<typename T>
bool ArraySequence<T>:: operator!=(Sequence<T>* seq) {
	return !this->Equals(seq);
}