#pragma once
#include <cstddef>
#include <iterator>

template <typename T>
class ArrayIterator
{
public:
	//typedef std::bidirectional_ArrayIterator_tag ArrayIterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	ArrayIterator(T* thePosition = 0) { m_position = thePosition; }
	T& operator*() const { return *m_position; }
	T* operator->() const { return &*m_position; }
	T& operator[](int i) const { return *(m_position + i); }
	ArrayIterator& operator+=(int i)  { m_position += i; return *this; }
	ArrayIterator& operator-=(int i)  { m_position -= i; return *this; }

	ArrayIterator operator+(int i) const { return ArrayIterator(m_position + i); }
	ArrayIterator operator-(int i) const { return ArrayIterator(m_position - i); }
	difference_type operator-(const ArrayIterator& other) const { return m_position - other.m_position; }
	ArrayIterator& operator++() { ++m_position; return *this; }
	ArrayIterator operator++(int) { ArrayIterator old = *this; ++m_position; return old; }

	ArrayIterator& operator--() { --m_position; return *this; }
	ArrayIterator operator--(int) { ArrayIterator old = *this; --m_position; return old; }

	bool operator!=(const ArrayIterator right) const { return m_position != right.m_position; }
	bool operator==(const ArrayIterator right) const { return m_position == right.m_position; }
	bool operator<(const ArrayIterator& other) const { return (m_position - other.m_position) < 0; }
	//bool operator<=(const ArrayIterator& other) const { return (m_position - other.m_position) <= 0; }


protected:
	T* m_position;
};
