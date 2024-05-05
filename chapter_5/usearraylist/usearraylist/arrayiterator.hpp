#pragma once
#include <cstddef>
#include <iterator>

template <typename T>
class iterator
{
public:
	//typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(T* thePosition = 0) { m_position = thePosition; }
	T& operator*() const { return *m_position; }
	T* operator->() const { return &*m_position; }
	T& operator[](int i) const { return *(m_position + i); }
	iterator& operator+=(int i)  { m_position += i; return *this; }
	iterator& operator-=(int i)  { m_position -= i; return *this; }

	iterator operator+(int i) const { return iterator(m_position + i); }
	iterator operator-(int i) const { return iterator(m_position - i); }
	difference_type operator-(const iterator& other) const { return m_position - other.m_position; }
	iterator& operator++() { ++m_position; return *this; }
	iterator operator++(int) { iterator old = *this; ++m_position; return old; }

	iterator& operator--() { --m_position; return *this; }
	iterator operator--(int) { iterator old = *this; --m_position; return old; }

	bool operator!=(const iterator right) const { return m_position != right.m_position; }
	bool operator==(const iterator right) const { return m_position == right.m_position; }
	bool operator<(const iterator& other) const { return (m_position - other.m_position) < 0; }
	//bool operator<=(const iterator& other) const { return (m_position - other.m_position) <= 0; }


protected:
	T* m_position;
};
