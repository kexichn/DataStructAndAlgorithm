#pragma once

template <typename T>
class Stack {
public:
	virtual ~Stack() { }
	virtual void push(const T& item) = 0;
	virtual void pop() = 0;
	virtual T& top() const = 0;
	virtual bool isEmpty() const = 0;
	virtual int size() const = 0;
};
