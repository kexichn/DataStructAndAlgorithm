#ifndef LINEARLIST_H
#define LINEARLIST_H

// linearlist.h  -- declare the class linearList

#include <ostream>

using std::ostream;

template<typename T>
class linearList
{
public:
	virtual ~linearList() { };
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int index) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int index) = 0;
	virtual void insert(int index, const T& theElement) = 0;
	virtual void output(ostream& out) const = 0; 
};

#endif
