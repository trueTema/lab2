#pragma once
template<typename T>
class Sequence
{
public:
	virtual T& GetFirst() = 0;
	virtual T& GetLast() = 0;
	virtual T& Get(int index) = 0;
	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0;
	virtual int GetLength() = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void Set(int index, T item) = 0;
	virtual int find(int startIndex, int endIndex, T item) = 0;
	virtual void del_item(int index) = 0;
	virtual void InsertAt(T item, int index) = 0;
	virtual bool IsSubSeq(Sequence<T>* seq) = 0;
	virtual bool Equals(Sequence<T>* seq) = 0;
	virtual Sequence<T>* SplitSeq(bool (T)) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* seq) = 0;
};

