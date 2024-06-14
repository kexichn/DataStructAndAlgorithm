#pragma once

#include <exception>

using std::exception;

template <typename T>
struct LinkNode {
	T value;
	LinkNode* next;

	LinkNode(const T& v, LinkNode* n = nullptr) { value = v; next = n; }
};

template <typename T>
class LinkQueue {
public:
	LinkQueue() = default;
	~LinkQueue();

	T& front();
	T& back();
	void push(const T& e);
	void pop();
	bool empty() { return !m_size; }
	int size() { return m_size; }

private:
	LinkNode<T>* m_frontNode = nullptr;
	LinkNode<T>* m_backNode = nullptr;
	int m_size = 0;
};

template <typename T>
LinkQueue<T>::~LinkQueue() {
	LinkNode<T>* tmp = m_frontNode;
	LinkNode<T>* next = nullptr;
	while (tmp) {
		next = tmp->next;
		delete tmp;
		tmp = next;
	}

	m_frontNode = nullptr;
	m_backNode = nullptr;
	m_size = 0;
}

template <typename T>
T& LinkQueue<T>::front() {
	if (m_frontNode) {
		return m_frontNode->value;
	}
	else {
		throw exception("queue is empty!");
	}
}

template <typename T>
T& LinkQueue<T>::back() {
	if (m_backNode) {
		return m_backNode->value;
	}
	else {
		throw exception("queue is empty!");
	}
}

template <typename T>
void LinkQueue<T>::pop() {
	if (!m_frontNode) {
		throw exception("queue is empty");
	}

	auto node = m_frontNode->next;
	delete m_frontNode;
	m_frontNode = node;
	m_size--;
}

template <typename T>
void LinkQueue<T>::push(const T& e) {
	if (!m_frontNode) {
		m_frontNode = new LinkNode<T>(e);
		m_backNode = m_frontNode;
	}
	else {
		m_backNode->next = new LinkNode<T>(e);
		m_backNode = m_backNode->next;
	}

	m_size++;
}
