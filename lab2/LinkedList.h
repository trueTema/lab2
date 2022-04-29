#pragma once
#include "exception.h"
using namespace std;
template <class T>
class LinkedList
{
private:
	struct Item {
		Item* next = nullptr;
		Item* prev = nullptr;
		T data;
	};

	struct List {
		Item* head = nullptr;
		Item* tail = nullptr;
	};

	int size = 0;
	List* items;
	List* CreateList() {
		List* list;
		try {
			list = new List;
		}
		catch (std::bad_alloc) {
			throw SetException(MemoryAllocateError);
		}
		list->head = nullptr;
		list->tail = nullptr;
		return list;
	}

	void clear() {
		Item* cur = items->head;
		while (cur != nullptr) {
			Item* cur2 = cur->next;
			delete cur;
			cur = cur2;
		}
		if (items) {
			delete items;
		}
	}

	void push_back(T data) {
		Item* cur;
		try {
			cur = new Item;
		}
		catch (std::bad_alloc) {
			throw SetException(MemoryAllocateError);
		}
		int len = size;
		cur->prev = items->tail;
		cur->next = nullptr;
		cur->data = data;
		if (len != 0) {
			items->tail->next = cur;
		}
		items->tail = cur;
		if (len == 0) items->head = cur;
		size++;
	}

	void push(T data, int index) {
		Item* cur = items->head;
		if (index < 0) {
			throw SetException(IndexOutOfRange);
		}
		for (int i = 0; cur != nullptr && i < index; i++) {
			cur = cur->next;
		}
		if (cur == nullptr) {
			throw SetException(IndexOutOfRange);
		}
		Item* newitem;
		try {
			newitem = new Item;
		}
		catch (std::bad_alloc) {
			throw SetException(MemoryAllocateError);
		}
		newitem->next = cur;
		newitem->prev = cur->prev;
		newitem->data = data;
		cur->prev->next = newitem;
		cur->prev = newitem;
		size++;
	}

	void delete_item(int index) {
		if (index >= this->size || index < 0) {
			throw SetException(IndexOutOfRange);
		}
		Item* cur = items->head;

		for (int i = 0; i < index; i++) {
			cur = cur->next;
		}
		if (cur->prev != nullptr && cur->next != nullptr) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
		}
		else if (cur->next == nullptr && cur->prev != nullptr) {
			items->tail = cur->prev;
			items->tail->next = nullptr;
		}
		else if (cur->prev == nullptr && cur->next != nullptr) {
			items->head = cur->next;
			items->head->prev = nullptr;
		}
		else {
			items->head = nullptr;
			items->tail = nullptr;
		}

		delete cur;
		size--;
	}

	void SetItem(int index, T item) {
		Item* cur = items->head;
		if (index < 0) {
			throw SetException(IndexOutOfRange);
		}
		for (int i = 0; cur != nullptr && i < index; i++) {
			cur = cur->next;
		}
		if (cur == nullptr) {
			throw SetException(IndexOutOfRange);
		}
		cur -> data = item;
	}

	T& GetItem(int index) {
		Item* cur = items->head;
		if (index < 0) {
			throw SetException(IndexOutOfRange);
		}
		for (int i = 0; cur != nullptr && i < index; i++) {
			cur = cur->next;
		}
		if (cur == nullptr) {
			throw SetException(IndexOutOfRange);
		}
		return cur->data;
	}

	void push_tobegin(T data) {
		Item* cur = nullptr;
		try {
			cur = new Item;
		}
		catch (std::bad_alloc) {
			throw SetException(MemoryAllocateError);
		}
		int len = size;
		cur->next = items->head;
		cur->prev = nullptr;
		cur->data = data;
		size++;
		items->head = cur;
		if (len == 0) items->tail = cur;
	}
public:
	//конструкторы
	LinkedList();
	LinkedList(T*, int);
	LinkedList(LinkedList<T>*);
	LinkedList(initializer_list<T>);
	
	//деконструктор
	~LinkedList();

	//функции
	T& GetFirst();
	T& GetLast();
	T& Get(int);
	int GetLength();
	void Append(T);
	void Prepend(T);
	void Set(int, T);
	void InsertAt(T, int);
	LinkedList<T>* GetSubList(int, int);
	LinkedList<T>* Concat(LinkedList<T>*);
	void del_item(int);
	int find(int, int, T);
	LinkedList<T>* SplitList(bool (T));
	bool Equals(LinkedList<T>*);
	bool IsSubList(LinkedList<T>*);

	//операторы
	T& operator[](int);
	bool operator==(LinkedList<T>&);
	bool operator!=(LinkedList<T>&);
};

//конструкторы
template<class T>
LinkedList<T>::LinkedList() {
	items = CreateList();
}
template<class T>
LinkedList<T>::LinkedList(T* items, int count) {
	this->items = CreateList();

	for (int i = 0; i < count; i++) {
		push_back(items[i]);
	}
	size = count;
}
template<class T>
LinkedList<T>::LinkedList(LinkedList<T>* LL) {
	items = CreateList();

	for (int i = 0; i < LL->size; i++) {
		push_back(LL->Get(i));
	}
	size = LL ->size;
}

template<class T>
LinkedList<T>::LinkedList(initializer_list<T> list) {
	items = CreateList();
	for (auto i : list) {
		push_back(i);
	}
	size = int(list.size());
}


//деконструктор
template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

//функции
template<class T>
T& LinkedList<T>::GetFirst() {
	return this->GetItem(0);
}

template<class T>
T& LinkedList<T>::GetLast() {
	return this->GetItem(this->size-1);
}

template<class T>
T& LinkedList<T>::Get(int index) {
	return GetItem(index);
}

template<class T>
int LinkedList<T>::GetLength() {
	return size;
}

template<class T>
void LinkedList<T>::Append(T item) {
	push_back(item);
}

template<class T>
void LinkedList<T>::Prepend(T item) {
	push_tobegin(item);
}

template<class T>
void LinkedList<T>::Set(int index, T item) {
	SetItem(index, item);
}

template<class T>
void LinkedList<T>::InsertAt(T item, int index) {
	push(item, index);
}

template<class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) {
	if (endIndex < startIndex) throw SetException(NegativeRange);
	LinkedList<T>* list = new LinkedList;
	for (int i = startIndex; i <= endIndex; i++) {
		list->Append(this->Get(i));
	}
	return list;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList<T>* list_res = new LinkedList;
	for (int i = 0; i < size; i++) {
		list_res->Append(this->Get(i));
	}
	for (int i = 0; i < list->size; i++) {
		list_res->Append(list->Get(i));
	}
	return list_res;
}

template<class T>
void LinkedList<T>::del_item(int index) {
	this->delete_item(index);
}

template<class T>
int LinkedList<T>::find(int startIndex, int endIndex, T item) {
	if (endIndex < startIndex) throw SetException(NegativeRange);
	for (int i = startIndex; i <= endIndex; i++) {
		if (this->Get(i) == item) return i;
	}
	return -1;
}

template<class T>
LinkedList<T>* LinkedList<T>::SplitList(bool cmp(T)) {
	LinkedList<T>* res = new LinkedList<T>;
	for (int i = 0; i < this->size; i++) {
		if (cmp(this->Get(i))) {
			res->Append(this->Get(i));
			this->del_item(i);
			i--;
		}
	}
	return res;
}

template<class T>
bool LinkedList<T>::Equals(LinkedList<T>* seq) {
	if (this->GetLength() != seq->GetLength()) return false;
	for (int i = 0; i < seq->GetLength(); i++) {
		if (this->Get(i) != seq->Get(i)) return false;
	}
	return true;
}

template<class T>
bool LinkedList<T>::IsSubList(LinkedList<T>* seq) {
	int pos = 0;
	for (int i = 0; i < seq->GetLength() && pos != -1; i++) {
		pos = this->find(pos, this->GetLength() - 1, seq->Get(i));
	}
	return pos != -1;
}

//операторы
template<class T>
T& LinkedList<T>:: operator[](int index) {
	return GetItem(index);
}

template<class T>
bool LinkedList<T>:: operator==(LinkedList<T>& seq) {
	return this->Equals(&seq);
}

template<class T>
bool LinkedList<T>:: operator!=(LinkedList<T>& seq) {
	return !this->Equals(&seq);
}