#include "Sequence.h"
#include "LinkedList.h"
using namespace std;
#pragma once
template<typename T>
class ListSequence : public Sequence<T>
{
protected:
	LinkedList<T>* list;
public:
	ListSequence();
	ListSequence(T*, int);
	ListSequence(Sequence<T>*);
	ListSequence(initializer_list<T>);
	
	~ListSequence();

	T& GetFirst() override;
	T& GetLast() override;
	T& Get(int) override;
	Sequence<T>* GetSubSequence(int, int) override;
	int GetLength() override;
	void Set(int, T) override;
	void Append(T) override;
	void Prepend(T) override;
	void InsertAt(T, int) override;
	void del_item(int) override;
	int find(int, int, T) override;
	Sequence<T>* SplitSeq(bool (T)) override;
	bool IsSubSeq(Sequence<T>*) override;
	bool Equals(Sequence<T>*) override;
	Sequence<T>* Concat(Sequence<T>*) override;

	bool operator==(Sequence<T>*);
	bool operator!=(Sequence<T>*);
};
template<typename T>
ListSequence<T>::ListSequence() {
	list = new LinkedList<T>;
}

template<typename T>
ListSequence<T>::ListSequence(T* items, int count) {
	list = new LinkedList<T>(items, count);
}

template<typename T>
ListSequence<T>::ListSequence(Sequence<T>* list) {
	this->list = new LinkedList<T>(((ListSequence<T>*)list)->list);
}

template<typename T>
ListSequence<T>::ListSequence(initializer_list<T> list) {
	this->list = new LinkedList<T>(list);
}


template<typename T>
ListSequence<T>::~ListSequence() {
	delete list;
}

template<typename T>
T& ListSequence<T>::GetFirst() {
	return this->list->GetFirst();
}
template<typename T>
T& ListSequence<T>::GetLast() {
	return this->list->GetLast();
}
template<typename T>
T& ListSequence<T>::Get(int index)  {
	return this->list->Get(index);
}
template<typename T>
Sequence<T>* ListSequence<T>::GetSubSequence(int startIndex, int endIndex) {
	LinkedList<T>* x = this->list->GetSubList(startIndex, endIndex);
	ListSequence<T>* resseq = new ListSequence<T>;
	delete resseq->list;
	resseq->list = x;
	return resseq;
}
template<typename T>
int ListSequence<T>::GetLength() {
	return this->list->GetLength();
}

template<typename T>
void ListSequence<T>::Set(int index, T item) {
	this->list->Set(index, item);
}

template<typename T>
void ListSequence<T>::Append(T item) {
	this->list->Append(item);
}
template<typename T>
void ListSequence<T>::Prepend(T item) {
	this->list->Prepend(item);
}
template<typename T>
void ListSequence<T>::InsertAt(T item, int index) {
	this->list->InsertAt(item, index);
}

template<typename T>
void ListSequence<T>::del_item(int index) {
	this->list->del_item(index);
}

template<typename T>
int ListSequence<T>::find(int startIndex, int endIndex, T item) {
	return this->list->find(startIndex, endIndex, item);
}

template<typename T>
Sequence<T>* ListSequence<T>::SplitSeq(bool (*cmp)(T)) {
	LinkedList<T>* x = this->list->SplitList(cmp);
	ListSequence<T>* resseq = new ListSequence<T>;
	delete resseq->list;
	resseq->list = x;
	return resseq;
}

template<typename T>
bool ListSequence<T>::IsSubSeq(Sequence<T>* seq) {
	return this->list->IsSubList(((ListSequence<T>*)seq)->list);
}

template<typename T>
bool ListSequence<T>::Equals(Sequence<T>* seq) {
	return this->list->Equals(((ListSequence<T>*)seq)->list);
}

template<typename T>
Sequence<T>* ListSequence<T>::Concat(Sequence<T>* seq) {
	LinkedList<T>* x = this->list->Concat(((ListSequence<T>*)seq)->list);
	ListSequence<T>* resseq = new ListSequence<T>;
	delete resseq->list;
	resseq->list = x;
	return resseq;
}

template<typename T>
bool ListSequence<T>::operator==(Sequence<T>* seq) {
	return this->Equals(seq);
}
template<typename T>
bool ListSequence<T>::operator!=(Sequence<T>* seq) {
	return !this->Equals(seq);
}