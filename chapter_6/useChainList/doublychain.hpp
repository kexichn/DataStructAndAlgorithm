#pragma once
#include <sstream>
#include "linearlist.h"
#include "exceptions.h"

template <typename T>
class DoublyChain;

template <typename T>
class DoublyChainNode {
	friend class DoublyChain<T>;
public:
	DoublyChainNode() = default;
	DoublyChainNode(const T& element) { this->element = element; }
	DoublyChainNode(const T& e, DoublyChainNode<T>* n) { element = e;  next = n; }
	DoublyChainNode(const T& e, DoublyChainNode<T>* n, DoublyChainNode<T>* p) 
	{ element = e;  next = n; prev = p; }

	T& operator*() { return element; }
	bool operator<(const DoublyChainNode<T>& other) { return element < other.element; }
	bool operator>(const DoublyChainNode<T>& other) { return element > other.element; }

private:
	T element = T();
	DoublyChainNode<T>* prev = nullptr;
	DoublyChainNode<T>* next = nullptr;
};

template <typename T>
class DoublyChain : public linearList<T> {
public:
	DoublyChain();
	DoublyChain(const std::initializer_list<T>& list);
	~DoublyChain();

	// override functions of the base class 
	bool empty() const override { return m_list_size == 0; }
	int size() const override { return m_list_size; };
	T& get(int index) const override;
	int indexOf(const T& theElement) const override;
	void erase(int index) override;
	void insert(int index, const T& theElement) override;
	void output(ostream& out) const override;

	void clear();

private:
	using Node = DoublyChainNode<T>;
	Node* m_head_node = nullptr;
	int m_list_size = 0;

	void checkIndex(int index) const;
	Node* findNode(int index) const;
};

template <typename T>
DoublyChain<T>::DoublyChain() {
	m_head_node = new Node();
	m_head_node->next = m_head_node;
	m_head_node->prev = m_head_node;
}

template <typename T>
DoublyChain<T>::DoublyChain(const std::initializer_list<T>& list) : DoublyChain() {
	Node* p = m_head_node;
	Node* tmp = nullptr;
	for (auto it = list.begin(); it != list.end(); ++it) {
		tmp = new Node(*it, m_head_node, p);
		p->next = tmp;
		m_head_node->prev = tmp;
		p = p->next;
	}

	m_list_size = list.size();
}

template <typename T>
DoublyChain<T>::~DoublyChain() {
	clear();
	delete m_head_node;
}

template <typename T>
void DoublyChain<T>::checkIndex(int index) const {
	if (index < 0 || index >= m_list_size) {
		std::ostringstream s;
		s << "index = " << index << " size = " << m_list_size;
		throw illegalIndex(s.str());
	}
}

template <typename T>
DoublyChainNode<T>* DoublyChain<T>::findNode(int index) const {
	checkIndex(index);

	Node* p = m_head_node->next;
	if (index < m_list_size / 2) {
		for (int i = 0; i < index; ++i) {
			p = p->next;
		}
	}
	else {
		for (int i = 0; i < m_list_size - index + 1; ++i) {
			p = p->prev;
		}
	}

	return p;
}

template <typename T>
T& DoublyChain<T>::get(int index) const {
	Node* p = findNode(index);
	return p->element;
}

template <typename T>
int DoublyChain<T>::indexOf(const T& theElement) const {
	
	int result = -1;

	m_head_node->element = theElement;
	Node* p = m_head_node->next;
	int i = 0;
	while (p->element != theElement) {
		p = p->next;
		++i;
	}

	if (p != m_head_node) result = i;
	return result;

}

template <typename T>
void DoublyChain<T>::erase(int index) {
	Node* p = findNode(index);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--m_list_size;
}

template <typename T>
void DoublyChain<T>::insert(int index, const T& theElement) {
	Node* p = findNode(index);

	Node* tmp = new Node(theElement, p, p->prev);
	p->prev->next = tmp;
	p->next->prev = tmp;
	++m_list_size;
}

template <typename T>
void DoublyChain<T>::output(ostream& out) const {
	Node* p = m_head_node->next;
	while (p != m_head_node) {
		out << p->element << " ";
		p = p->next;
	}
}

template <typename T>
void DoublyChain<T>::clear() {
	Node* p = m_head_node->next;
	Node* tmp = nullptr;
	while (p != m_head_node) {
		tmp = p;
		p = p->next;
		delete tmp;
	}

	m_list_size = 0;
}

template <typename T>
ostream& operator<<(ostream& out, const DoublyChain<T>& chain) {
	chain.output(out);
	return out;
}