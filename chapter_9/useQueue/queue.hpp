#pragma once

#include <exception>
#include <iostream>
#include <algorithm>

using std::istream;
using std::ostream;
using std::cout;

template <typename T>
class Queue {
	template <typename S>
	friend istream& operator>>(istream& is, Queue<S>& q);
	template <typename S>
	friend ostream& operator<<(ostream& os, const Queue<S>& q);
public:
	Queue();
	~Queue();
	void push(const T& data);
	void pop();
	T& front();
	T& back();
	bool empty() { return m_head == m_tail; }
	int size() { return m_size; }

private:
	T* m_data;
	int m_size;
	int m_head;
	int m_tail;
};

template <typename T>
Queue<T>::Queue() {
	m_data = new T[3];
	m_size = 3;
	m_head = 0;
	m_tail = 0;
}

template <typename T>
Queue<T>::~Queue() {
	delete[] m_data;
}

template <typename T>
void Queue<T>::push(const T& data) {
	if ((m_tail + 1) % m_size == m_head) {
		int newsize = m_size * 2;
		T* tmp = new T[newsize];
		if (m_head < m_tail) {
		    std::copy(m_data + m_head + 1, m_data + m_tail + 1, tmp + 1);
		}
		else {
			std::copy(m_data + m_head + 1, m_data + m_size, tmp + 1);
			std::copy(m_data, m_data + m_tail + 1, tmp + 1 + m_size - m_head);
		}
		m_head = 0;
		m_tail = m_size - 1;
		m_size = m_size * 2;

		delete[] m_data;
		m_data = tmp;
	}
	
	m_tail = (m_tail + 1) % m_size;
	m_data[m_tail] = data;
}

template <typename T>
void Queue<T>::pop() {
	if (empty()) {
		throw std::exception("Queue is empty");
	}

	m_head = (m_head + 1) % m_size;
	m_data[m_head].~T();
}

template <typename T>
T& Queue<T>::front() {
	if (empty()) {
		throw std::exception("Queue is empty");
	}

	return m_data[(m_head + 1) % m_size];
}

template <typename T>
T& Queue<T>::back() {
	if (empty()) {
		throw std::exception("Queue is empty");
	}

	return m_data[m_tail];
}

template <typename T>
istream& operator>>(istream& is, Queue<T>& q) {
	T data;
	int n;
	cout << "Enter element num: ";
	is >> n;
	for (int i = 0; i < n; i++) {
		cout << "Enter element: ";
		is >> data;
		q.push(data);
	}
	return is;

}
template <typename T>
ostream& operator<<(ostream& os, const Queue<T>& q) {
    
	int start = (q.m_head + 1) % q.m_size;
	int end = (q.m_tail + 1) % q.m_size;
	for (int i = start; i != end; i = (++i) % q.m_size) {
		os << q.m_data[i] << " ";
	}
	return os;
}