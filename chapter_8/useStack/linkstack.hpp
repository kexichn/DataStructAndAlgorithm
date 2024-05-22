#pragma once

#include "stack.hpp"

template <typename T>
class LinkStack : public Stack<T> {
public:
	LinkStack();
	~LinkStack();

	void push(const T& item);
	void pop();
	T& top() const;

	bool isEmpty() const;
	int size() const;

private:
		struct Node {
			T data;
			Node* next;
		}
		* m_top;
		int m_size;
};

template <typename T>
LinkStack<T>::LinkStack() {
	m_top = nullptr;
	m_size = 0;
}

template <typename T>
LinkStack<T>::~LinkStack() {
	while (!isEmpty()) {
		pop();
	}
}

template <typename T>
void LinkStack<T>::push(const T& item) {
	Node* newNode = new Node{ item, m_top };
	m_top = newNode;
	++m_size;
}

template <typename T>
void LinkStack<T>::pop() {
	if (isEmpty()) {
		throw std::out_of_range("Stack is empty");
	}
	Node* temp = m_top;
	m_top = m_top->next;
	delete temp;
	--m_size;
}

template <typename T>
T& LinkStack<T>::top() const {
	if (isEmpty()) {
		throw std::out_of_range("Stack is empty");
	}
	return m_top->data;
}

template <typename T>
bool LinkStack<T>::isEmpty() const {
	return m_top == nullptr;
}

template <typename T>
int LinkStack<T>::size() const {
	return m_size;
}





