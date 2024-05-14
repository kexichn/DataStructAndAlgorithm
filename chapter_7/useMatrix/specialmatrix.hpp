#pragma once
#include "exceptions.h"


// define other special matrix

/**********Diagonal Matrix***********/
template <typename T>
class DiagonalMatrix {
public:
	DiagonalMatrix(int n = 10);
	~DiagonalMatrix() { delete[] m_element; }
	T get(int, int) const;
	void set(int, int, const T&);

private:
	int m_matrix_size;
	T* m_element;
};

template <typename T>
DiagonalMatrix<T>::DiagonalMatrix(int n) {
	if (n < 1) {
		throw illegalParameterValue("Matrix size must be > 0!");
	}

	m_matrix_size = n;
	m_element = new T[n];
}


template <typename T>
T DiagonalMatrix<T>::get(int i, int j) const {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	if (i == j) {
		return m_element[i-1];
	}
	else {
		return 0;
	}
}


template <typename T>
void DiagonalMatrix<T>::set(int i, int j, const T& e) {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	if (i == j) {
		m_element[i - 1] = e;
	} else {
		if (e != 0) {
			throw illegalParameterValue("nondiagonal elements must be zero!");
		}
	}
}


/**********Tridiagonal Matrix***********/
template <typename T>
class TridiagonalMatrix {
public:
	TridiagonalMatrix(int n = 10);
	~TridiagonalMatrix() { delete[] m_element; }
	T get(int, int) const;
	void set(int, int, const T&);

private:
	int m_matrix_size;
	T* m_element;
};

template <typename T>
TridiagonalMatrix<T>::TridiagonalMatrix(int n) {
	if (n < 1) {
		throw illegalParameterValue("Matrix size must be > 0!");
	}

	m_matrix_size = n;
	m_element = new T[3 * n -2];
}


template <typename T>
T TridiagonalMatrix<T>::get(int i, int j) const {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	T res;
	switch (i - j) {
	case 1:
		res = m_element[i - 2];
		break;
	case 0:
		res = m_element[i + m_matrix_size - 2];
		break;
	case -1:
		res = m_element[2 * m_matrix_size + i - 2];
		break;
	default:
		res = 0;
		break;
	}

	return res;
}


template <typename T>
void TridiagonalMatrix<T>::set(int i, int j, const T& e) {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	switch (i - j) {
	case 1:
		m_element[i - 2] = e;
		break;
	case 0:
		m_element[i + m_matrix_size - 2] = e;
		break;
	case -1:
		m_element[2 * m_matrix_size + i - 2] = e;
		break;
	default:
		if (e != 0) {
			throw illegalParameterValue("nontridiagonal elements must be zero!");
		}
		// if e is 0, it's unnecessary to store!
		break;
	}
}

/**********upper triangular Matrix***********/
template <typename T>
class UpperTriangularMatrix {
public:
	UpperTriangularMatrix(int n = 10);
	~UpperTriangularMatrix() { delete[] m_element; }
	T get(int, int) const;
	void set(int, int, const T&);

private:
	int m_matrix_size;
	T* m_element;
};

template <typename T>
UpperTriangularMatrix<T>::UpperTriangularMatrix(int n) {
	if (n < 1) {
		throw illegalParameterValue("Matrix size must be > 0!");
	}

	m_matrix_size = n;
	m_element = new T[(n + 1) * n / 2];
}


template <typename T>
T UpperTriangularMatrix<T>::get(int i, int j) const {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	if (i <= j) {
		int idx = (2 * m_matrix_size + 2 - i) * (i - 1) / 2 + j - 1;
		return m_element[idx];
	} else {
		return 0;
	}
}


template <typename T>
void UpperTriangularMatrix<T>::set(int i, int j, const T& e) {
	if (i < 1 || j < 1 || i > m_matrix_size || j > m_matrix_size) {
		throw matrixIndexOutOfRange();
	}

	if (i <= j) {
		int idx = (2 * m_matrix_size + 2 - i) * (i - 1) / 2 + j - 1;
		m_element[idx] = e;
	} else {
		// if e is 0, it's unnecessary to store!
		if (e != 0) {
			throw illegalParameterValue("nontridiagonal elements must be zero!");
		}
	}
}