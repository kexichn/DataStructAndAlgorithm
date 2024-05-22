#pragma once

#include <iostream>
#include <algorithm>	
#include "stack.hpp"

using std::istream;
using std::ostream;
using std::copy;

template <typename T>
class ArrayStack : public Stack<T> {
	template <typename S>
	friend istream& operator>>(istream& in, ArrayStack<S>& stack);
	template <typename S>
	friend ostream& operator<<(ostream& out, ArrayStack<S>& stack);
public:
	ArrayStack(int initialCapacity = 10);
	~ArrayStack() { delete[] m_element; }

	void push(const T& item);	

	void pop() {
		if (m_stackTop == -1) {
			throw std::out_of_range("Stack is empty");
		}
		m_element[m_stackTop--].~T();
	}

	T& top() const {
		if (m_stackTop == -1) {
			throw std::out_of_range("Stack is empty");
		}
		return m_element[m_stackTop];
	}

	bool isEmpty() const { return m_stackTop == -1; }
	int size() const { return m_stackTop + 1; }
	void splitStack(ArrayStack<T>& stack1, ArrayStack<T>& stack2);
	void mergeStack(ArrayStack<T>& stack);
	

private:
	int m_stackTop;
	int m_stackSize;
	T* m_element;
	void resizeStack(int size);
};

template <typename T>
ArrayStack<T>::ArrayStack(int initialCapacity) {
	if (initialCapacity <= 0) {
		throw std::invalid_argument("Initial capacity must be greater than 0");
	}
	m_stackTop = -1;
	m_stackSize = initialCapacity;
	m_element = new T[m_stackSize];
}

template <typename T>
void ArrayStack<T>::push(const T& item) {
	if (m_stackTop == m_stackSize - 1) {
		m_stackSize *= 2;
		T* newElement = new T[m_stackSize];
		copy(m_element, m_element + m_stackTop + 1, newElement);
		delete[] m_element;
		m_element = newElement;
		
	}
	m_element[++m_stackTop] = item;
}

template<typename T>
void ArrayStack<T>::splitStack(ArrayStack<T>& stack1, ArrayStack<T>& stack2) {
	int halfSize = m_stackTop / 2 + 1;
	stack1.resizeStack(halfSize+1);
	stack2.resizeStack(halfSize+1);

	copy(m_element, m_element + halfSize, stack1.m_element);
	stack1.m_stackTop = halfSize-1;
	copy(m_element + halfSize, m_element + m_stackTop + 1, stack2.m_element);
	stack2.m_stackTop = m_stackTop - halfSize;
}

template<typename T>
void ArrayStack<T>::mergeStack(ArrayStack<T>& stack)
{
	m_stackSize = m_stackTop + stack.m_stackTop + 2;
	T* newElement = new T[m_stackSize];
	copy(stack.m_element, stack.m_element + m_stackTop + 1, newElement);
	copy(m_element, m_element + m_stackTop + 1, newElement + stack.m_stackTop + 1);
	delete[] m_element;
	m_element = newElement;
	m_stackTop = m_stackSize - 1;
}

template<typename T>
void ArrayStack<T>::resizeStack(int size)
{
	if (size <= m_stackSize) {
		m_stackTop = -1;  // reset the stack top
		return;
	}

	T* newElement = new T[size];
	copy(m_element, m_element + m_stackTop + 1, newElement);
	delete[] m_element;
	m_element = newElement;
	m_stackSize = size;
	m_stackTop = -1;  // reset the stack top
}

template <typename T>
istream& operator>>(istream& in, ArrayStack<T>& stack) {
	int n;
	std::cout << "Enter the number of elements: ";
	in >> n;
	stack.resizeStack(n);
	for (int i = 0; i < n; i++) {
		int item;
		in >> item;
		stack.push(item);
	}
	return in;
}

template <typename T>
ostream& operator<<(ostream& out, ArrayStack<T>& stack) {
	for (int i = 0; i < stack.size(); i++) {
		out << stack.m_element[i] << " ";
	}
	return out;
}