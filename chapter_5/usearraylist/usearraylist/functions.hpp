#pragma once
// functions.hpp  -- some common functions
#include "exceptions.h"

template <typename T>
void changeLength1D(T*& a, int oldLength, int newLength) {
	if (newLength < 0) {
		throw illegalParameterValue("new length must be >= 0!");
	}

	T* temp = new T[newLength];
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template <typename T>
void changeLength2Dtest(T**& a, int oldLength1, int oldLength2, int newLength1, int newLength2) {
	if (newLength1 < 0 || newLength2 < 0) {
		throw illegalParameterValue("new length must be >= 0!");
	}

	T* temp = new T[newLength1 + newLength2];
	int number1 = std::min(oldLength1, newLength1);
	int number2 = std::min(oldLength2, newLength2);
	std::copy(a, a + number1, temp);
	std::copy(a + oldLength1, a + oldLength1 + number2, a + newLength1);
	delete[] a;
	a = temp;
}


template<class T>
void changeLength2D(T**& a, int oldRows, int copyRows,
	int copyColumns, int newRows, int newColumns)
{
	if (copyRows > newRows || copyColumns > newColumns)
		throw illegalParameterValue("new dimensions are too small");

	T** temp = new T * [newRows];              
	for (int i = 0; i < newRows; i++)
		temp[i] = new T[newColumns];

	for (int i = 0; i < copyRows; i++)
	{
		std::copy(a[i], a[i] + copyColumns, temp[i]);
		delete[] a[i];                      
	}

	for (int i = copyRows; i < oldRows; i++)
		delete[] a[i];

	delete[] a;
	a = temp;
}