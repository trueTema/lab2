#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "exception.h"
using namespace std;
template <class T>
class DynamicArray
{

private:
	T* items = nullptr;
	int size = 0;
public:
	//конструкторы
	DynamicArray();
	DynamicArray(int );
	DynamicArray(int , T );
	DynamicArray(T* , int );
	DynamicArray(DynamicArray<T>*);
	DynamicArray(initializer_list<T>);

	//деконструктор
	~DynamicArray();

	//геттеры
	T& Get(int );
	int GetSize();

	//операции
	void Set(int, T);
	void Resize(int );
	void Append(T );
	void Prepend(T );
	void InsertAt(T , int );
	DynamicArray<T>* GetSubArray(int , int);
	DynamicArray<T>* Concat(DynamicArray<T>* );
	void del_item(int );
	int find(int , int , T );
	DynamicArray<T>* SplitArray(bool (T));
	bool Equals(DynamicArray<T>* );
	bool IsSubArr(DynamicArray<T>* );

	//операторы
	T& operator[] (int index);
	bool operator==(DynamicArray<T>& seq);
	bool operator!=(DynamicArray<T>& seq);
};
//конструкторы
template <class T>
DynamicArray<T>::DynamicArray() {
	items = nullptr;
}
template <class T>
DynamicArray<T>::DynamicArray(int count) {
	if (count < 0) throw SetException(SizeBelowZero);
	try {
		items = new T[count];
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
	size = count;
}
template <class T>
DynamicArray<T>::DynamicArray(int count, T fill) {
	if (count < 0) throw SetException(SizeBelowZero);
	try {
		items = new T[count];
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
	size = count;
	for (int i = 0; i < size; i++) items[i] = fill;
}
template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
	if (count < 0) throw SetException(SizeBelowZero);
	try {
		this->items = new T[count];
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
	size = count;
	for (int i = 0; i < size; i++) {
		this->items[i] = items[i];
	}
}
template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T>* dynamic_array) {
	try {
		items = new T[dynamic_array->GetSize()];
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
	size = dynamic_array -> size;
	for (int i = 0; i < size; i++) {
		this->items[i] = dynamic_array -> items[i];
	}
}

template<class T>
DynamicArray<T>::DynamicArray(initializer_list<T> list) :DynamicArray(int(list.size())) {
	int j = 0;
	for (auto i : list) {
		this->items[j] = i;
		j++;
	}
}

//деконструктор
template <class T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->items;
}


//геттеры
template <class T>
T& DynamicArray<T>::Get(int index) {
	if (index >= size || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	return items[index];
}


//операции


template <class T>
void DynamicArray<T>::Resize(int NewSize) {
	if (NewSize < 0) {
		throw SetException(SizeBelowZero);
	}
	try {
		T* items_cur = new T[NewSize];
		int cpy_num = (NewSize > size ? size : NewSize);
		memcpy(items_cur, items, cpy_num * sizeof(T));
		delete[] items;
		items = items_cur;
		size = NewSize;
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
}

template <class T>
void DynamicArray<T>::Append(T item) {
	this->Resize(size + 1);
	this->Set(size - 1, item);
}

template <class T>
void DynamicArray<T>::Prepend(T item) {
	this->Resize(size + 1);
	memmove(this->items + 1, this->items, (size - 1) * sizeof(T));
	this->Set(0, item);
}

template <class T>
void DynamicArray<T>::InsertAt(T item, int index) {
	if (index >= this->size || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	this->Resize(size + 1);
	memmove(this->items + (index + 1), this->items + (index), (size - 1 - index) * sizeof(T));
	this->Set(index, item);
}

template <class T>
DynamicArray<T>* DynamicArray<T>::GetSubArray(int startIndex, int endIndex) {
	if (startIndex >= this->size || startIndex < 0 || endIndex >= this->size || endIndex < 0) {
		throw SetException(IndexOutOfRange);
	}
	if (endIndex < startIndex) {
		throw SetException(NegativeRange);
	}
	DynamicArray<T>* res = new DynamicArray<T>;
	for (int i = startIndex; i <= endIndex; i++) {
		res->Append(this->Get(i));
	}
	return res;
}

template <class T>
DynamicArray<T>* DynamicArray<T>::Concat(DynamicArray<T>* arr) {
	DynamicArray<T>* res = new DynamicArray<T>;
	for (int i = 0; i < size; i++) {
		res->Append(this->Get(i));
	}
	for (int i = 0; i < arr->GetSize(); i++) {
		res->Append(arr->Get(i));
	}
	return res;
}

template <class T>
void DynamicArray<T>::del_item(int index) {
	if (index >= this->size || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	memmove(items + ((index)), items + ((index + 1)), (size - 1 - index) * sizeof(T));
	this->Resize(this->size - 1);
}


template <class T>
int DynamicArray<T>::find(int startIndex, int endIndex, T item) {
	if (startIndex >= this->size || startIndex < 0 || endIndex >= this->size || endIndex < 0) {
		throw SetException(IndexOutOfRange);
	}
	if (endIndex < startIndex) {
		throw SetException(NegativeRange);
	}
	for (int i = startIndex; i <= endIndex; i++) {
		//прописать исключения
		if (this->Get(i) == item) return i;
	}
	return -1;
}

template <class T>
void DynamicArray<T>::Set(int index, T value) {
	if (index >= this->size || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	items[index] = value;
}

template <class T>
DynamicArray<T>* DynamicArray<T>::SplitArray(bool cmp(T)) {
	DynamicArray<T>* res = new DynamicArray<T>;
	for (int i = 0; i < this->size; i++) {
		if (cmp(this->Get(i))) {
			res->Append(this->Get(i));
			this->del_item(i);
			i--;
		}
	}
	return res;
}

template <class T>
bool DynamicArray<T>::Equals(DynamicArray<T>* seq) {
	if (this->GetSize() != seq->GetSize()) return false;
	for (int i = 0; i < seq->GetSize(); i++) {
		if (this->Get(i) != seq->Get(i)) return false;
	}
	return true;
}

template <class T>
bool DynamicArray<T>::IsSubArr(DynamicArray<T>* seq) {
	int pos = 0;
	for (int i = 0; i < seq->GetSize() && pos != -1; i++) {
		pos = this->find(pos, this->GetSize() - 1, seq->Get(i));
	}
	return pos != -1;
}

//операторы
template <class T>
T& DynamicArray<T>:: operator[] (int index) {
	return this -> Get(index);
}

template <class T>
bool DynamicArray<T>:: operator==(DynamicArray<T>& seq) {
	return this->Equals(&seq);
}

template <class T>
bool DynamicArray<T>::operator!=(DynamicArray<T>& seq) {
	return !this->Equals(&seq);
}

template<class T>
int DynamicArray<T>::GetSize() {
	return size;
}

