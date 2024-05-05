#pragma once
#include <sstream>
#include <initializer_list>
#include "linearlist.h"
#include "chainnode.hpp"
#include "exceptions.h"

template <typename T>
class CircularChain : public linearList<T> {
public:
	CircularChain();
	CircularChain(const std::initializer_list<T>& list);
	~CircularChain();

	// override functions of the base class 
	bool empty() const override { return m_list_size == 0; }
	int size() const override { return m_list_size; };
	T& get(int index) const override;
	int indexOf(const T& theElement) const override;
	void erase(int index) override;
	void insert(int index, const T& theElement) override;
	void output(ostream& out) const override;

	void clear();

	// practice 28-42
	void reverse();
	void meld(CircularChain<T>& a, CircularChain<T>& b);
	void merge(CircularChain<T>& a, CircularChain<T>& b);
	void split(CircularChain<T>& a, CircularChain<T>& b);


private:
	using Node = ChainNode<T>;
	Node* m_head_node = nullptr;
	int m_list_size = 0;

	void checkIndex(int index, bool isextend = false) const;
};

template <typename T>
CircularChain<T>::CircularChain() {
	m_head_node = new Node();
	m_head_node->next = m_head_node;
}

template <typename T>
CircularChain<T>::CircularChain(const std::initializer_list<T>& list) : CircularChain() {
	Node* p = m_head_node;
	for (auto it = list.begin(); it != list.end(); ++it) {
		p->next = new Node(*it, p->next);
		p = p->next;
	}

	m_list_size = list.size();
}

template <typename T>
CircularChain<T>::~CircularChain() {
	while (m_head_node->next != m_head_node) {
		auto p = m_head_node->next;
		m_head_node->next = p->next;
		delete p;
	}

	delete m_head_node;
}

template <typename T>
void CircularChain<T>::checkIndex(int index, bool isextend) const {
	int fix_index = isextend ? m_list_size: m_list_size - 1;

	if (index < 0 || index > fix_index) {
		std::ostringstream s;
		s << "index = " << index << " size = " << m_list_size;
		throw illegalIndex(s.str());
	}
}

template <typename T>
T& CircularChain<T>::get(int index) const {
	checkIndex(index);

	auto p = m_head_node->next;
	for (int i = 0; i < index; ++i) {
		p = p->next;
	}

	return p->element;
}

template <typename T>
int CircularChain<T>::indexOf(const T& theElement) const {
	m_head_node->element = theElement;

	int result = -1, idx = 0;
	Node* p = m_head_node->next;
	for ( ; p->element != theElement; ++idx) { 
		p = p->next;
	}

	if (p != m_head_node) result = idx;

	return result;
}

template <typename T>
void CircularChain<T>::erase(int index) {
	checkIndex(index);

	Node* p = m_head_node;
	for (int i = 0; i < index; ++i) {
		p = p->next;
	}

	Node* t = p->next;
	p->next = t->next;
	delete t;

	--m_list_size;
}

template <typename T>
void CircularChain<T>::insert(int index, const T& theElement) {
	checkIndex(index, true);

	Node* p = m_head_node;
	for (int i = 0; i < index; ++i) {
		p = p->next;
	}

	Node* t = p->next;
	p->next = new Node(theElement, t);

	++m_list_size;
}

template <typename T>
void CircularChain<T>::output(ostream& out) const {
	Node* p = m_head_node->next;
	for (; p != m_head_node; p = p->next) {
		out << p->element << " ";
	}
}

template <typename T>
void CircularChain<T>::clear() {
	Node* p = m_head_node->next;
	Node* p_after = p->next;
	while (p != m_head_node) {
		p_after = p->next;	
		m_head_node->next = p_after;

		delete p;
		p = p_after;
		p_after = p->next;
	}

	m_list_size = 0;
}

template <typename T>
void CircularChain<T>::reverse() {
	Node* p = m_head_node->next;
	Node* p_front = m_head_node;
	Node* p_after = p->next;
	while (p_front != p_after) {
		p->next = p_front;	

		p_front = p;
		p = p_after;
		p_after = p->next;
	}
}

template <typename T>
void CircularChain<T>::meld(CircularChain<T>& a, CircularChain<T>& b) {
	clear();
	Node* p = a.m_head_node->next;
	Node* q = b.m_head_node->next;

	Node* cur = m_head_node;
	bool isp = true;
	while (p != a.m_head_node  && q != b.m_head_node) {
		if (isp) {
			cur->next = p;
			p = p->next;
		}
		else {
			cur->next = q;
			q = q->next;
		}

		cur = cur->next;
		isp = !isp;
	}

	while (p != a.m_head_node) {
		cur->next = p;
		p = p->next;
		cur = cur->next;
	}

	while (q != b.m_head_node) {
		cur->next = q;
		q = q->next;
		cur = cur->next;
	}

	cur->next = m_head_node;
	m_list_size = a.m_list_size + b.m_list_size;

	a.m_head_node->next = a.m_head_node;
	b.m_head_node->next = b.m_head_node;
	a.m_list_size = 0;
	b.m_list_size = 0;
}

template <typename T>
void CircularChain<T>::merge(CircularChain<T>& a, CircularChain<T>& b) {
	clear();
	Node* p = a.m_head_node->next;
	Node* q = b.m_head_node->next;

	Node* cur = m_head_node;
	while (p != a.m_head_node && q != b.m_head_node) {
		if (*p < *q) {
			cur->next = p;
			p = p->next;
		}
		else {
			cur->next = q;
			q = q->next;
		}
		cur = cur->next;
	}

	while (p != a.m_head_node) {
		cur->next = p;
		p = p->next;
		cur = cur->next;
	}

	while (q != b.m_head_node) {
		cur->next = q;
		q = q->next;
		cur = cur->next;
	}

	cur->next = m_head_node;
	m_list_size = a.m_list_size + b.m_list_size;

	a.m_head_node->next = a.m_head_node;
	b.m_head_node->next = b.m_head_node;
	a.m_list_size = 0;
	b.m_list_size = 0;
}

template <typename T>
void CircularChain<T>::split(CircularChain<T>& a, CircularChain<T>& b) {
	
	a.clear();
	b.clear();

	Node* p = a.m_head_node;
	Node* q = b.m_head_node;
	Node* cur = m_head_node->next;

	bool isp = true;

	while (cur != m_head_node) {
		if (isp) {
			p->next = cur;
			p = p->next;
		}
		else {
			q->next = cur;
			q = q->next;
		}

		cur = cur->next;
		isp = !isp;
	}

	int c = m_list_size & 1 ? 1 : 0;
	a.m_list_size = m_list_size / 2 + c;
	b.m_list_size = m_list_size / 2;

	m_list_size = 0;

	m_head_node->next = m_head_node;
	p->next = a.m_head_node;
	q->next = b.m_head_node;
}

template <typename T>
ostream& operator<<(ostream& out, const CircularChain<T>& x) {
	x.output(out);
	return out;
}