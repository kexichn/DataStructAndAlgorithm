#pragma once
#include <cstddef>
#include <iterator>

template <typename T>
class ChainNode;

template <typename T>
class iterator
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(ChainNode<T>* theNode = nullptr) { m_node = theNode; }
	T& operator*() { return m_node->element; }
	T* operator->() const { return &m_node->element; }
	
	iterator& operator++() { m_node = m_node->next; return *this; }
	iterator operator++(int) { iterator old = *this;  m_node = m_node->next; return old; }

	bool operator!=(const iterator right) const { return m_node != right.m_node; }
	bool operator==(const iterator right) const { return m_node == right.m_node; }

protected:
	ChainNode<T>* m_node = nullptr;
};
