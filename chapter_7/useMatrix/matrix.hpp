#pragma once
// define the matrix class

#include <ostream>

#include "exceptions.h"

using std::ostream;

template <typename T>
class Matrix {
public:
	Matrix(int rows = 0, int columns = 0);
	Matrix(const Matrix<T>& m);
	~Matrix() { delete[] m_element; }

	int rows() const { return m_rows; }
	int columns() const { return columns; }
	T& operator()(int i, int j) const;
	Matrix<T>& operator=(const Matrix<T>&);
	Matrix<T> operator+() const { return *this; }
	Matrix<T> operator+(const Matrix<T>&) const;
	Matrix<T> operator-() const;
	Matrix<T> operator-(const Matrix<T>&) const;
	Matrix<T> operator*(const Matrix<T>&) const;
	Matrix<T>& operator+=(const T&);
	Matrix<T>& operator-=(const T&);
	Matrix<T>& operator*=(const T&);
	Matrix<T>& operator/=(const T&);
	Matrix<T>& tranpose();

	void output(ostream& out) const;

private:
	int m_rows;
	int m_columns;
	T* m_element;
};

template <typename T>
Matrix<T>::Matrix(int rows, int columns) {
	if (rows < 0 || columns < 0) {
		throw illegalParameterValue("rows and colums must be >= 0");
	}

	if ((rows == 0 || columns == 0) && (rows != 0 || columns != 0)) {
		throw illegalParameterValue("either both or neither rows and columns should be zero");
	}

	m_rows = rows;
	m_columns = columns;
	m_element = new T[rows * columns];

	for (int i = 0; i < m_rows * m_columns; ++i) {
		m_element[i] = T();
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) {
	m_rows = m.m_rows;
	m_columns = m.m_columns;
	m_element = new T[m_rows * m_columns];

	std::copy(m.m_element, m.m_element + m.m_rows * m.m_columns, m_element);
}
template <typename T>
T& Matrix<T>::operator()(int i, int j) const {
	if (i < 1 || i > m_rows || j < 1 || j > m_columns) {
		throw matrixIndexOutOfRange();
	}

	return m_element[(i - 1) * m_columns + j - 1];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
	if (this != &m) {
		delete[] m_element;
		m_rows = m.m_rows;
		m_columns = m.m_columns;
		m_element = new T[m_rows * m_columns];

		std::copy(m.m_element, m.m_element + m.m_rows * m.m_columns, m_element);
	}

	return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m) const {
	if (m_rows != m.m_rows || m_columns != m.m_columns) {
		throw matrixSizeMismatch();
	}

	Matrix<T> w(m_rows, m_columns);

	for (int i = 0; i < m_rows * m_columns; ++i) {
		w.m_element[i] = m_element[i] + m.m_element[i];
	}

	return w;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
	Matrix result(m_rows, m_columns);
	for (int i = 0; i < m_rows * m_columns; ++i) {
		result.m_element[i] = -m_element[i];
	}

	return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& m) const {
	if (m_rows != m.m_rows || m_columns != m.m_columns) {
		throw matrixSizeMismatch();
	}

	Matrix<T> w(m_rows, m_columns);

	for (int i = 0; i < m_rows * m_columns; ++i) {
		w.m_element[i] = m_element[i] - m.m_element[i];
	}

	return w;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& m) const {
	if (m_columns != m.m_rows) {
		throw matrixSizeMismatch();
	}

	Matrix<T> w(m_rows, m.m_columns);

	for (int i = 1; i <= m_rows; ++i) {
		for (int j = 1; j <= m.m_columns; ++j) {
			for (int k = 1; k <= m_columns; ++k) {
				w(i, j) += (*this)(i, k) * m(k, j);
			}
		}
	}

	return w;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const T& v) {
	for (int i = 0; i < m_rows * m_columns; ++i) {
		m_element[i] += v;
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const T& v) {
	for (int i = 0; i < m_rows * m_columns; ++i) {
		m_element[i] -= v;
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T& v) {
	for (int i = 0; i < m_rows * m_columns; ++i) {
		m_element[i] *= v;
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T& v) {
	for (int i = 0; i < m_rows * m_columns; ++i) {
		m_element[i] /= v;
	}

	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::tranpose() {
	T* tmp = new T[m_rows * m_columns];

	for (int i = 1; i <= m_rows; ++i) {
		for (int j = 1; j <= m_columns; ++j) {
			tmp[(j - 1) * m_rows + i - 1] = m_element[(i - 1) * m_columns + j - 1];
		}
	}

	std::swap(m_rows, m_columns);
	delete[] m_element;
	m_element = tmp;

	return *this;
}

template <typename T>
void Matrix<T>::output(ostream& out) const {
	for (int i = 0; i < m_rows * m_columns; ++i) {
		if ((i % m_columns) == 0 && i) {
			out << "\n";
		}
		out << m_element[i] << " ";
	}
}

template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m) {
	m.output(out);

	return out;
}