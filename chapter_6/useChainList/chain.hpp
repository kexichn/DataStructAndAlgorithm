#pragma once
// define the class chainNode
#include <sstream>
#include <ostream>
#include <utility>
#include <initializer_list>
#include "linearlist.h"
#include "exceptions.h"
#include "chainiterator.hpp"
#include "arraylist.hpp"
#include "chainnode.hpp"

template <typename T>
class Chain : public linearList<T> {
public:
	Chain(int initialCapacity = 10);
	Chain(const Chain<T>& other);
	Chain(const std::initializer_list<T>& list);
	~Chain();

	// the functions of ADT
	bool empty() const { return listSize == 0; }
	int size() const { return listSize;  }
	T& get(int index) const;
	int indexOf(const T& theElement) const;
	void erase(int index);
	void insert(int index, const T& theElement);
	void output(ostream& out) const;
	void clear();
	int lastIndexOf(const T& theElement) const;
	void push_back(const T& theElement);

	// practice 1-27
	void setSize(int theSize);
	void set(int theIndex, const T& theElement);
	void removeRange(int start, int end);

	// overload operator
	T& operator[](int index) const;
	bool operator==(const Chain<T>& other) const;
	bool operator!=(const Chain<T>& other) const;
	bool operator<(const Chain<T>& other) const;
	
	void swap(Chain<T>& other);
	void fromList(const arrayList<T>& list);
	void toList(arrayList<T>& list);
	void leftShift(int i);
	void reverse();
	void meld(Chain<T>& a, Chain<T>& b);
	void merge(Chain<T>& a, Chain<T>& b);
	void split(Chain<T>& a, Chain<T>& b);
	void circularShift(int i);

	void insertSort();
	void bubbleSort();
	void selectSort();
	void countSort();
	void binSort(int range);
	void baseSort(int range, int base);

	typedef iterator<T> iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(); }

protected:
	void checkIndex(int index) const;
	ChainNode<T>* firstNode = nullptr;
	ChainNode<T>* lastNode = nullptr;
	int listSize = 0;
};

template <typename T>
Chain<T>::Chain(int initialCapacity) {
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Intial capacity = " << initialCapacity << "must be > 0";
		throw illegalParameterValue(s.str());
	}
	
	firstNode = nullptr;
	listSize = 0;
}

template <typename T>
Chain<T>::Chain(const Chain<T>& theList) {
	listSize = theList.listSize;

	if (listSize == 0) {
		firstNode = nullptr;
		return;
	}

	ChainNode<T>* sourceNode = theList.firstNode;
	firstNode = new ChainNode<T>(sourceNode->element);

	sourceNode = sourceNode->next;
	ChainNode<T>* targetNode = firstNode;

	while (sourceNode) {
		targetNode->next = new ChainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		targetNode = targetNode->next;
	}

	targetNode->next = nullptr;
}

template <typename T>
Chain<T>::Chain(const std::initializer_list<T>& list) {
	ChainNode<T>* node = nullptr;
	for (auto it = list.begin(); it != list.end(); ++it) {
		node = new ChainNode(*it);
		if (!firstNode) {
			firstNode = lastNode = node;
		}
		else {
			lastNode->next = node;
			lastNode = lastNode->next;
		}
	}

	listSize = list.size();
}

template <typename T>
Chain<T>::~Chain() {
	while (firstNode) {
		ChainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <typename T>
void Chain<T>::checkIndex(int index) const {
	if (index < 0 || index >= listSize) {
		std::ostringstream s;
		s << "index = " << index << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template <typename T>
T& Chain<T>::get(int index) const {
	checkIndex(index);
	ChainNode<T>* curNode = firstNode;
	for (int i = 0; i < index; ++i) {
		curNode = curNode->next;
	}
	return curNode->element;
}

template <typename T>
int Chain<T>::indexOf(const T& theElement) const {
	ChainNode<T>* curNode = firstNode;
	int index = 0;
	while (curNode && curNode->element != theElement) {
		curNode = curNode->next;
		++index;
	}

	if (!curNode) {
		index = -1;
	}

	return index;
}

template <typename T>
void Chain<T>::erase(int index) {
	checkIndex(index);

	ChainNode<T>* delNode = nullptr;
	if (index == 0) {
		delNode = firstNode;
		firstNode = firstNode->next;
	}
	else {
		ChainNode<T>* p = firstNode;
		for (int i = 0; i < index - 1; ++i) {
			p = p->next;
		}

		delNode = p->next;
		p->next = delNode->next;

		if (index == listSize - 1) lastNode = p;
	}
	delete delNode;
	--listSize;
}

template <typename T>
void Chain<T>::insert(int index, const T& theElement) {
	if (index < 0 || index > listSize) {
		std::ostringstream s;
		s << "index = " << index << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (index == 0) {
		firstNode = new ChainNode<T>(theElement, firstNode);
	}
	else {
		ChainNode<T>* p = firstNode;
		for (int i = 0; i < index - 1; ++i) {
			p = p->next;
		}

		ChainNode<T>* newNode = new ChainNode<T>(theElement, p->next);
		p->next = newNode;

		if (index == listSize) lastNode = newNode;
	}
	
	++listSize;
}

template <typename T>
void Chain<T>::clear() {
	while (firstNode) {
		auto node = firstNode->next;
		delete firstNode;
		firstNode = lastNode = node;
	}

	listSize = 0;
}

template <typename T>
void Chain<T>::push_back(const T& theElement) {
	auto node = new ChainNode<T>(theElement, nullptr);
	if (!firstNode) {
		firstNode = lastNode = node;
	}
	else {
		lastNode->next = node;
		lastNode = node;
	}

	++listSize;
}

template <typename T>
void Chain<T>::setSize(int theSize) {
	while (listSize > theSize) {
		erase(listSize - 1);
	}
}

template <typename T>
void Chain<T>::set(int theIndex, const T& theElement) {
	checkIndex(theIndex);

	auto p = firstNode;
	int i = 0;
	while (i < theIndex) {
		p = p->next;
		++i;
	}
	p->element = theElement;
}

template <typename T>
void Chain<T>::removeRange(int start, int end) {
	checkIndex(start);
	int last = std::min(listSize, end);
	if (last <= start) return;

	auto p = firstNode;
	ChainNode<T>* tmpLast = nullptr;
	for (int i = 0; i < start; ++i) {
		tmpLast = p;
		p = p->next;
	}

	ChainNode<T>* q = nullptr;
	int i = start;
	while (i++ < last) {
		q = p->next;
		delete p;
		p = q;
	}

	tmpLast->next = q;

	if (listSize <= end) lastNode = tmpLast;

	listSize -= last - start;
}

template <typename T>
int Chain<T>::lastIndexOf(const T& theElement) const {

	ChainNode<T>* p = firstNode;
	int result = -1;

	for (int i = 0; i < listSize; ++i) {
		if (p->element == theElement) {
			result = i;
		}
		p = p->next;
	}

	return result;
}

// overload operator
template <typename T>
T& Chain<T>::operator[](int index) const {
	checkIndex(index);

	ChainNode<T>* p = firstNode;
	for (int i = 0; i < listSize; ++i) {
		if (i == index) {
			return p->element;
		}

		p = p->next;
	}
}

template <typename T>
bool Chain<T>::operator==(const Chain<T>& other) const {
	bool result = false;
	auto p = firstNode;
	auto q = other.firstNode;

	if (listSize != other.listSize) {
		goto last;
	 }

	result = true;
	while (p != lastNode) {
		if (p->element != q->element) {
			result = false;
			break;
		}

		p = p->next;
		q = q->next;
	}

last:
	return result;
}

template <typename T>
bool Chain<T>::operator!=(const Chain<T>& other) const {
	return !(*this == other);
}

template <typename T>
bool Chain<T>::operator<(const Chain<T>& other) const {
	bool result = false;
	auto p = firstNode;
	auto q = other.firstNode;

	if (listSize != other.listSize) {
		goto last;
	}

	result = true;
	while (p != lastNode) {
		if (p->element >= q->element) {
			result = false;
			break;
		}

		p = p->next;
		q = q->next;
	}

last:
	return result;
}

template <typename T>
void Chain<T>::swap(Chain<T>& other) {
	std::swap(firstNode, other.firstNode);
	std::swap(lastNode, other.lastNode);
	std::swap(listSize, other.listSize);
}

template <typename T>
void Chain<T>::fromList(const arrayList<T>& list) {
	clear();
	for (int i = 0; i < list.size(); ++i) {
		push_back(list[i]);
	}
}

template <typename T>
void Chain<T>::toList(arrayList<T>& list) {
	list.clear();
	auto curNode = firstNode;
	while (curNode) {
		list.push_back(curNode->element);
		curNode = curNode->next;
	}
}

template <typename T>
void Chain<T>::leftShift(int i) {
	int j = 0;
	while (j++ < i && firstNode) {
		auto node = firstNode->next;
		delete firstNode;
		firstNode = node;
	}

	if (firstNode) {
		listSize -= i;
	}
	else {
		listSize = 0;
		lastNode = nullptr;
	}
}

template <typename T>
void Chain<T>::reverse() {
	int i = -1, j = listSize;
	while (++i < --j) {
		std::swap(get(i), get(j));
	}
}

template <typename T>
void Chain<T>::meld(Chain<T>& a, Chain<T>& b) {
	clear();
	firstNode = a.firstNode;
	if (!firstNode) return;

	ChainNode<T> *p = a.firstNode, *q = b.firstNode;
	ChainNode<T> *r = nullptr, * s = nullptr, * last = nullptr;
	while (p && q) {
		s = p->next;
		r = q->next;
		p->next = q;
		q->next = s;
		q = r;
		last = p;
		p = s;
	}

	auto get_last = [](ChainNode<T>* t)->ChainNode<T>*{
			ChainNode<T>* last = nullptr;
			while (t) { last = t; t = t->next; }
			return last;
		};

	if (p) {
		lastNode = get_last(p);
	} else {
		last->next->next = q;
		auto x = get_last(q);
		lastNode = x ? x : last->next;
	}

	listSize = a.listSize + b.listSize;
	a.listSize = 0;
	b.listSize = 0;
	a.firstNode = a.lastNode = nullptr;
	b.firstNode = b.lastNode = nullptr;
}

template <typename T>
void Chain<T>::merge(Chain<T>& a, Chain<T>& b) {
	clear();

	using Node = ChainNode<T>*;
	auto get_small = [](Node& n1, Node& n2)->Node {
		    Node result = nullptr;
			if (*n1 < *n2) { result = n1; n1 = n1->next; } 
			else { result = n2; n2 = n2->next; }
			return result;
		};

	Node p = a.firstNode;
	Node q = b.firstNode;

	firstNode = get_small(p, q);

	Node r = firstNode;
	while (p && q) {
		r->next = get_small(p, q);
		r = r->next;
	}

	if (p) {
		r->next = p;
		lastNode = a.lastNode;
	}
	else {
		r->next = q;
		lastNode = b.lastNode;
	}

	listSize = a.listSize + b.listSize;
	a.firstNode = a.lastNode = nullptr;
	b.firstNode = b.lastNode = nullptr;
}

template <typename T>
void Chain<T>::split(Chain<T>& a, Chain<T>& b) {
	a.clear();
	b.clear();

	using Node = ChainNode<T>*;
	Node p = nullptr;
	Node q = nullptr;
	bool isFirst = true;
	while (firstNode) {
		if (!b.firstNode) {
			b.firstNode = firstNode;
			p = b.firstNode;
			b.listSize = 1;
		}
		else if (!a.firstNode) {
			a.firstNode = firstNode;
			q = a.firstNode;
			a.listSize = 1;
		}
		else {
			if (isFirst) {
				p->next = firstNode;
				p = p->next;
				++b.listSize;
			}
			else {
				q->next = firstNode;
				q = q->next;
				++a.listSize;
			}

			isFirst = !isFirst;
		}

		firstNode = firstNode->next;
	}

	q->next = nullptr;
	p->next = nullptr;
	a.lastNode = q;
	b.lastNode = p;
	lastNode = nullptr;
	listSize = 0;
	
}

template <typename T>
void Chain<T>::circularShift(int i) {
	
	if (i < 0 || !firstNode || !firstNode->next) return;

	i %= listSize;

	int j = -1;
	while (++j < i) {
		auto p = firstNode->next;
		firstNode->next = nullptr;
		lastNode->next = firstNode;
		lastNode = lastNode->next;
		firstNode = p;
	}
}

template <typename T>
void Chain<T>::insertSort() {
	if (!firstNode) {
		return;
	}

	using Node = ChainNode<T>*;
	Node head = new ChainNode<T>(0, firstNode);

	Node q = firstNode->next;
	Node p = firstNode;
	firstNode->next = nullptr;
	while (q) {
		Node r = q->next;
		q->next = nullptr;
		p = head;
		while (p->next) {
			if (*q < *(p->next)) {
				q->next = p->next;
				p->next = q;
				if (p == head) {
					firstNode = p->next;
				}
				break;	
			} 
			p = p->next;
		}

		if (!q->next) { p->next = q; }
		q = r;
	}

	delete head;
	while (p->next) p = p->next;
	lastNode = p;
}

// 这里应该是可以避免使用下标的
template <typename T>
void Chain<T>::bubbleSort() {
	if (!firstNode) return;
	
	using Node = ChainNode<T>;	
	Node* p = nullptr, * q = nullptr;
	for (int i = 0; i < listSize; ++i) {
		p = firstNode;
		q = firstNode->next;
		for (int j = 0; j < listSize - i - 1; ++j) {
			if (*p > *q) {
				std::swap(p->element, q->element);
			}
			p = p->next;
			q = q->next;
		}
	}
}

template <typename T>
void Chain<T>::selectSort() {
	if (!firstNode) return;

	using Node = ChainNode<T>;

	Node* head = new Node(T(), firstNode);
	Node* curNode, * maxNode, * bkNode1, * bkNode2;
	for (int size = listSize; size > 0; --size) {
		maxNode = head;
		curNode = head->next;
		for (int i = 1; i < size; ++i) {
			if (*(curNode->next) > *(maxNode->next)) 
				maxNode = curNode;
			curNode = curNode->next;
		}

		bkNode1 = maxNode->next;
		bkNode2 = curNode->next;
		curNode->next = bkNode1;
		maxNode->next = bkNode1->next;
		bkNode1->next = bkNode2;

		if (!(bkNode1->next)) lastNode = bkNode1;
	}

	firstNode = head->next;
	delete head;
}

template <typename T>
void Chain<T>::countSort() {
	const int size = listSize;
	int* count = new int[size];

	memset(count, 0, sizeof(int) * size);

	using Node = ChainNode<T>;
	// 获得排序数组
	Node* left = firstNode, * right = nullptr;
	for (int i = 0; i < size - 1; ++i) {
		right = left->next;
		for (int j = i + 1; j < size; ++j) {
			*right < *left ? ++count[i] : ++count[j];
			right = right->next;
		}

		left = left->next;
	}

	Node* p = firstNode, * q = nullptr;
	for (int i = 0; i < size; ++i) {
		q = p;
		for (int j = i; j < size; ++j) {
			if (count[j] == i) {
				std::swap(p->element, q->element);
				std::swap(count[i], count[j]);
			}
			q = q->next;	
		}
		p = p->next;
	}
}

template <typename T>
void Chain<T>::binSort(int range) {
	int base = range + 1;
	baseSort(range, base);
}

template <typename T>
void Chain<T>::baseSort(int range, int base) {
	ChainNode<T>** bottom, ** top;
	bottom = new ChainNode<T>*[base];
	top = new ChainNode<T>*[base];

	int q = range, i = 1;
	ChainNode<T>* y = nullptr;
	do {		
		y = nullptr;
		for (int b = 0; b < base; ++b) {
			bottom[b] = nullptr;
		}

		for (; firstNode; firstNode = firstNode->next) {
			int score = int(firstNode->element) % int(pow(base, i)) / pow(base, i-1);
			if (bottom[score]) {
				top[score]->next = firstNode;
				top[score] = firstNode;
			}
			else {
				bottom[score] = top[score] = firstNode;
			}
		}

		for (int score = 0; score < base; ++score) {
			if (bottom[score]) {
				y ? y->next = bottom[score] : firstNode = bottom[score];
				y = top[score];
			}
		}
		lastNode = y;
		if (y) y->next = nullptr;
		q /= base;
		++i;
	} while (q);


	delete[] bottom;
	delete[] top;
}


template <typename T>
void list2array(Chain<T>& chain, arrayList<T>& array) {
	array.clear();
	for (int i = 0; i < chain.size(); ++i) {
		array.insert(i, chain.get(i));
	}
};

template <typename T>
void list2array2(Chain<T>& chain, arrayList<T>& array) {
	array.clear();
	auto itt = chain.begin();
	for (; itt != chain.end(); ++itt) {
		array.push_back(*itt);
	}
};

template <typename T>
void reverse(Chain<T>& chain) {
	int i = 0, j = chain.size() - 1;
	for (; i < j; ++i, --j) {
		std::swap(chain[i], chain[j]);
	}
}

template <typename T>
void Chain<T>::output(ostream& out) const {
	auto curNode = firstNode;
	for (; curNode != nullptr; curNode = curNode->next) {
		out << curNode->element << " ";
	}
}

template <typename T>
ostream& operator<<(ostream& out, const Chain<T>& x) {
	x.output(out);
	return out;
}