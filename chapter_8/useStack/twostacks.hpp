#pragma once

#include "stack.hpp"

template <typename T>
class TwoStacks : public Stack<T> {
public:
	TwoStacks(int initialCapacity = 10);
	~TwoStacks() { delete[] m_element; }

	void push(const T& item, int stackNumber);
	void pop(int stackNumber);
	T& top(int stackNumber) const;

	bool isEmpty(int stackNumber) const;
	int size(int stackNumber) const;

private:
	int m_stackTop1;
	int m_stackTop2;
	int m_stackSize;
	T* m_element;
	void resizeStack(int size);
};

template <typename T>
TwoStacks<T>::TwoStacks(int initialCapacity) {
	if (initialCapacity <= 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	m_stackTop1 = -1;
	m_stackTop2 = initialCapacity;
	m_stackSize = initialCapacity;
	m_element = new T[m_stackSize];
}

template <typename T>
void TwoStacks<T>::push(const T& item, int stackNumber) {
	if (m_stackTop1 + 1 == m_stackTop2) {
		resizeStack(m_stackSize * 2);
	}
	if (stackNumber == 1) {
		m_element[++m_stackTop1] = item;
	}
	else {
		m_element[--m_stackTop2] = item;
	}
}

template <typename T>
void TwoStacks<T>::pop(int stackNumber) {
	if (stackNumber == 1) {
		if (m_stackTop1 == -1) {
			throw std::out_of_range("Stack 1 is empty");
		}
		m_element[m_stackTop1--].~T();
	}
	else {
		if (m_stackTop2 == m_stackSize) {
			throw std::out_of_range("Stack 2 is empty");
		}
		m_element[m_stackTop2++].~T();
	}
}

template <typename T>
T& TwoStacks<T>::top(int stackNumber) const {
	if (stackNumber == 1) {
		if (m_stackTop1 == -1) {
			throw std::out_of_range("Stack 1 is empty");
		}
		return m_element[m_stackTop1];
	}
	else {
		if (m_stackTop2 == m_stackSize) {
			throw std::out_of_range("Stack 2 is empty");
		}
		return m_element[m_stackTop2];
	}
}

template <typename T>
bool TwoStacks<T>::isEmpty(int stackNumber) const {
	if (stackNumber == 1) {
		return m_stackTop1 == -1;
	}
	else {
		return m_stackTop2 == m_stackSize;
	}
}

template <typename T>
int TwoStacks<T>::size(int stackNumber) const {
	if (stackNumber == 1) {
		return m_stackTop1 + 1;
	}
	else {
		return m_stackSize - m_stackTop2;
	}
}

template <typename T>
void TwoStacks<T>::resizeStack(int size) {
	T* newElement = new T[size];
	copy(m_element, m_element + m_stackTop1 + 1, newElement);
	copy(m_element + m_stackTop2, m_element + m_stackSize, newElement + size - m_stackTop2);
	delete[] m_element;
	m_element = newElement;
	m_stackSize = size;
	m_stackTop2 = size - (m_stackSize - m_stackTop2);
}