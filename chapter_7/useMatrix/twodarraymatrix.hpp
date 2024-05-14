#pragma once
// define the matrix as 2d array

#include <ostream>
#include "exceptions.h"

using std::ostream;

template <typename T>
class TwoDArrayMatrix {
public:
	TwoDArrayMatrix(int row, int column);
    ~TwoDArrayMatrix();

	T& operator()(int i, int j);
	TwoDArrayMatrix& operator=(const TwoDArrayMatrix& other);
	TwoDArrayMatrix operator+(const TwoDArrayMatrix& other);
	TwoDArrayMatrix operator*(const TwoDArrayMatrix& other);

	void output(ostream& out) const;

private:
	int m_row;
	int m_column;
	T** m_element;
};

template <typename T>
TwoDArrayMatrix<T>::TwoDArrayMatrix(int row, int column) {
	m_row = row;
	m_column = column;

	m_element = new T * [m_row];

	for (int i = 0; i < m_row; ++i) {
		m_element[i] = new T[m_column];
		for (int j = 0; j < m_column; ++j) {
			m_element[i][j] = T();
		}
	}
	std::cout << "7777" << std::endl;
}

template <typename T>
TwoDArrayMatrix<T>::~TwoDArrayMatrix() {
	for (int i = 0; i < m_row; ++i) {
		delete[] m_element[i];
	}

	delete[] m_element;

}

template <typename T>
T& TwoDArrayMatrix<T>::operator()(int i, int j) {

	if (i < 1 || i > m_row || j < 1 || j > m_column) {
		throw illegalIndex(" i or j is illegal");
	}

	return m_element[i-1][j-1];

}

template <typename T>
TwoDArrayMatrix<T>& TwoDArrayMatrix<T>::operator=(const TwoDArrayMatrix<T>& other) {

	for (int i = 1; i <= m_row; ++i) {
		for (int j = 1; j <= m_column; ++j) {
			m_element[i-1][j-1] = other.m_element[i-1][j-1];
		}
	}
	std::cout << "8888" << std::endl;
	return *this;
}

template <typename T>
TwoDArrayMatrix<T> TwoDArrayMatrix<T>::operator+(const TwoDArrayMatrix<T>& other) {
	
	TwoDArrayMatrix<T> result(m_row, m_column);
	
	for (int i = 1; i <= m_row; ++i) {
		for (int j = 1; j <= m_column; ++j) {
			result(i, j) = m_element[i-1][j-1] + other.m_element[i-1][j-1];
		}
	}

	return result;
}

template <typename T>
TwoDArrayMatrix<T> TwoDArrayMatrix<T>::operator*(const TwoDArrayMatrix<T>& other) {
	if (m_column != other.m_row) {
		throw matrixSizeMismatch();
	}

	TwoDArrayMatrix<T> result(m_row, other.m_column);

	for (int i = 1; i <= m_row; ++i) {
		for (int j = 1; j <= other.m_column; ++j) {
			for (int k = 1; k <= m_column; ++k) {
				result.m_element[i-1][j-1] += m_element[i-1][k-1] * other.m_element[k-1][j-1];
			}
		}
	}

	return result;
}

template <typename T>
void TwoDArrayMatrix<T>::output(ostream& out) const {
	for (int i = 0; i < m_row; ++i) {
		for (int j = 0; j < m_column; ++j) {
			out << m_element[i][j] << " ";
		}
		out << "\n";
	}
}

template <typename T>
ostream& operator<<(ostream& out, const TwoDArrayMatrix<T>& matrix) {
	matrix.output(out);
	return out;
}
