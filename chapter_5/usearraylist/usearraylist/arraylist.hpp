#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP
// arraylist.hpp
// arraylist.h  -- declare the arrayList class

#include "arrayiterator.hpp"
#include <initializer_list>
#include <sstream>
#include <ostream>
#include <iterator>
#include <cmath>
#include "linearlist.h"
#include "exceptions.h"
#include "functions.hpp"


template <typename T>
class arrayList : public linearList<T>
{
public:
	// public variables
	const static int INIT_CAPACITY = 10;
	arrayList(const arrayList<T>&);
	arrayList(std::initializer_list<T> list);
	arrayList(int initialCapacity = INIT_CAPACITY, int increaseLength = 10);
	~arrayList() { delete [] element; element = nullptr; }
	
	// member functions inherited from the base class

	bool empty() const override { return listSize == 0; } 
	int size() const override { return listSize; }
	T& get(int index) const override;
	int indexOf(const T& theElement) const override;
	void erase(int index) override;
	void insert(int index, const T& theElement) override;
	void output(ostream& out) const override;
	

	// Operator overloading
	T& operator [](const int index) const;
	bool operator ==(const arrayList<T>& other) const;
	bool operator !=(const arrayList<T>& other) const { return !(*this == other); }
	bool operator <(const arrayList<T>& other) const;

	// public functions
	int capacity() const { return arrayLength; }
	void trimToSize();
	void setSize(int size);

	void push_back(const T& theElement);  // 11
	void pop_back();
	void swap(arrayList<T>& other);
	void reserve(int theCapacity);
	T& set(int index, T& theElement);
	void clear();
	void removeRange(int start, int end);
	int lastIndexOf(const T& theElement);
	void reverse(int start, int end);
	void reverse() { reverse(0, listSize); }
	void leftShift(int i);  // 23
	void circularShift(int i);

	void half();

	void meld(const arrayList<T>& a, const arrayList<T>& b);
	arrayList<T>& merge(const arrayList<T>& a, const arrayList<T>& b);
	void split(arrayList<T>& a, arrayList<T>& b);

	typedef iterator<T> iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }
	
private:
	T* element = nullptr;
	int listSize = 0;
	int arrayLength = 0;

	int m_increaseLength = -1;

	
	void checkIndex(int theIndex) const;
}; 

// definition for the class construtor
template <typename T>
arrayList<T>::arrayList(std::initializer_list<T> list) {
	if (list.size() > 0) {
		arrayLength = static_cast<int>(list.size());
		element = new T[arrayLength];
		std::copy(list.begin(), list.end(), element);
		listSize = arrayLength;
	}
	else {
		arrayLength = INIT_CAPACITY;
		element = new T[arrayLength];
		listSize = arrayLength;
	}
}
template <typename T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template <typename T>
arrayList<T>::arrayList(int initialCapacity, int increaseLength) {
	if (initialCapacity < 1 || increaseLength < 1) {
		std::ostringstream s;
		s << "Intial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}

	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
	m_increaseLength = increaseLength;
}

// definition for public functions of the class
template <typename T>
void arrayList<T>::trimToSize() {
	int newSize = listSize < 1 ? 1 : listSize;
	T* temp = new T[listSize];
	std::copy(element, element + listSize, temp);
	arrayLength = newSize;

	delete[] element;
	element = temp;
}

template <typename T>
void arrayList<T>::setSize(int size) {
	if (size > arrayLength) {
		std::ostringstream s;
		s << "Intial capacity = " << arrayLength << " size is greater than capacity!";
		throw illegalParameterValue(s.str());
	}

	listSize = size;
}

template <typename T>
void arrayList<T>::checkIndex(int theIndex) const {
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template <typename T>
T& arrayList<T>::get(int theIndex) const {
	checkIndex(theIndex);
	return element[theIndex];
}

template <typename T>
int arrayList<T>::indexOf(const T& theElement) const {
	int result = (int) (std::find(element, element + listSize, theElement) - element);
	if (result == listSize) {
		result = -1;
	}
	return result;
}

template <typename T>
void arrayList<T>::erase(int index) {
	checkIndex(index);
	std::copy(element + index + 1, element + listSize, element + index);
	element[--listSize].~T();
	
	if (listSize < (arrayLength / 4)) {
		arrayLength = std::max(arrayLength / 2, INIT_CAPACITY);
		T* temp = new T[arrayLength];
		std::copy(element, element + listSize, temp);
		delete[] element;
		element = temp;
	}
}

template <typename T>
void arrayList<T>::insert(int index, const T& theElement) {
	if (index < 0 || index > listSize) {
		std::ostringstream s;
		s << "index = " << index << " size = " << listSize;
		throw illegalIndex(s.str());
	}
	
	if (listSize == arrayLength) {
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	
	std::copy_backward(element + index, element + listSize, element + listSize + 1);
	element[index] = theElement;
	++listSize;
}

template <typename T>
void arrayList<T>::output(ostream& out) const {
	copy(element, element +listSize, std::ostream_iterator<T>(out, " "));
}

// the definetions for operator overloading
template <typename T>
T& arrayList<T>::operator[](const int index) const { 
	if (index >= listSize) {	
		std::ostringstream s;
		s << "index = " << index << " listSize = " << listSize;
		throw illegalIndex(s.str());
	}

	return element[index];
}

template <typename T>
bool arrayList<T>::operator ==(const arrayList<T>& other) const {
	bool result = true;
	if (listSize == other.listSize &&
		arrayLength == other.arrayLength) {
		for (int i = 0; i < listSize; ++i) {
			if (element[i] != other.element[i]) {
				result = false;
				break;
			}
		}
	} else {
		result = false;
	}

	return result;
}

template <typename T>
bool arrayList<T>::operator <(const arrayList<T>& other) const {
	bool result = true;
	if (listSize == other.listSize &&
		arrayLength == other.arrayLength) {
		for (int i = 0; i < listSize; ++i) {
			if (element[i] >= other.element[i]) {
				result = false;
				break;
			}
		}
	} else {
		result = false;
	}

	return result;
}

template <typename T>
void arrayList<T>::push_back(const T& theElement) {
	if (listSize == arrayLength) {
		int newLength = 2 * arrayLength;
		if (m_increaseLength > 0) {
			newLength = arrayLength + m_increaseLength;
		}
		changeLength1D(element, arrayLength, newLength);
		arrayLength = newLength;
	}

	element[listSize] = theElement;
	++listSize;
}

template <typename T>
void arrayList<T>::pop_back() {
	if (listSize > 0) {
		element[listSize - 1].~T();
		--listSize;
	}  // 如果没有元素，实际上也就没有删除的必要
}

template <typename T>
void arrayList<T>::swap(arrayList<T>& other) {
	std::swap(element, other.element);
	std::swap(arrayLength, other.arrayLength);
	std::swap(listSize, other.listSize);
}

template <typename T>
void arrayList<T>::reserve(int theCapacity) {
	if (theCapacity > arrayLength) {
		T* temp = new T[theCapacity];
		std::copy(element, element + listSize, temp);
		delete[] element;
		element = temp;
		arrayLength = theCapacity;
	}
}

template <typename T>
T& arrayList<T>::set(int index, T& theElement) {
	if (index >= listSize) {
		std::ostringstream s;
		s << "index = " << index << " listSize = " << listSize;
		throw illegalIndex(s.str());
	}

	T result = element[index];
	element[index] = theElement;
	return std::move(result);
}

template <typename T>
void arrayList<T>::clear() {
	for (int i = 0; i < listSize; ++i) {
		element[i].~T();
	}
	listSize = 0;
}

template <typename T>
void arrayList<T>::removeRange(int start, int end) {
	checkIndex(start);
	if (end < start) {
		std::ostringstream s;
		s << "start = " << start << " end = " << end;
		throw illegalIndex(s.str());
	}
	int endIndex = std::min(listSize, end);
	for (int i = start; i < endIndex; ++i) {
		element[i].~T();
	}
	if (end < listSize) {
		std::copy(element + end, element + listSize, element + start);
	}
	listSize -= endIndex - start;
}
template <typename T>
int arrayList<T>::lastIndexOf(const T& theElement) {
	int result = -1;
	for (int i = listSize - 1; i != -1; --i) {
		if (element[i] == theElement) {
			result = i;
			break;
		}
	}

	return result;
}

template <typename T>
void arrayList<T>::reverse(int start, int end) {
	int left = start;
	int right = end - 1;
	while (left < right) {
		std::swap(element[left], element[right]);
		++left;
		--right;
	}
}

template <typename T>
void arrayList<T>::leftShift(int i) {
	checkIndex(i);
	std::copy(element + i, element + listSize, element);
	removeRange(listSize - i, listSize);
}

template <typename T>
void arrayList<T>::circularShift(int i) {
	checkIndex(i);
	reverse(0, listSize);
	reverse(0, listSize - i);
	reverse(listSize - i, listSize);
}

template <typename T>
void arrayList<T>::half() {
	int fast = 2, slow = 1;
	for (; fast < listSize; fast += 2) {
		element[slow].~T();
		element[slow] = element[fast];
		++slow;
	}
	int curSize = (listSize + 1) / 2;
	for (int i = curSize; i < listSize; ++i) {
		element[i].~T();
	}

	listSize = curSize;
}
template <typename T>
void arrayList<T>::meld(const arrayList<T>& a, const arrayList<T>& b) {

	delete[] element;
	arrayLength = listSize = a.size() + b.size();
	element = new T[listSize];

	int first = 0, second = 0;
	int i = 0;
	for (; i < listSize; ++i) {
		if (first < a.size() || 
			second < b.size()) {
			break;
		} 

		if (i % 2) {
			element[i] = b[second++];
		}
		else {
			element[i] = a[first++];
		}
	}

	if (first == a.size()) {
		std::copy(b.element + second, b.element + b.size(), element + i);
	}
	else {
		std::copy(a.element + first, a.element + a.size(), element + i);
	}
}

template <typename T>
arrayList<T>& arrayList<T>::merge(const arrayList<T>& a, 
	                              const arrayList<T>& b) {
	delete[] element;
	listSize = a.size() + b.size();
	element = new T[listSize];
	arrayLength = listSize;

	int first = 0, second = 0;
	int i = 0;
	for ( ; i < listSize; ++i) {
		if (first >= a.size() || 
			second >= b.size()) {
			break;	
		}

		if (a[first] < b[second]) {
			element[i] = a[first++];
		}
		else {
			element[i] = b[second++];
		}
	}

	if (first == a.size()) {
		std::copy(b.element + second, b.element + b.size(), element + i);
	}
	else {
		std::copy(a.element + first, a.element + a.size(), element + i);
	}

	return *this;
}

template <typename T>
void arrayList<T>::split(arrayList<T>& a, arrayList<T>& b) {
	for (int i = 0; i < listSize; ++i) {
		if (i % 2) {
			b.push_back(element[i]);
		}
		else {
			a.push_back(element[i]);
		}
	}
}

template <typename T>
ostream& operator<<(ostream& out, const arrayList<T>& x) {
	x.output(out);
	return out;
}

#endif
