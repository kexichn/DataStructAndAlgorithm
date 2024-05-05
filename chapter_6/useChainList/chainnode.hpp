#pragma once

template <typename T>
class Chain;

template <typename T>
class CircularChain;

template <typename T>
class iterator;

template <typename T>
class ChainNode {
	friend class Chain<T>;
	friend class iterator<T>;
	friend class CircularChain<T>;
public:
	ChainNode() { }
	ChainNode(const T& element) { this->element = element; }
	ChainNode(const T& e, ChainNode<T>* n) { element = e;  next = n; }

	T& operator*() { return element; }
	bool operator<(const ChainNode<T>& other) { return element < other.element; }
	bool operator>(const ChainNode<T>& other) { return element > other.element; }

private:
	T element = T();
	ChainNode<T>* next = nullptr;
};
