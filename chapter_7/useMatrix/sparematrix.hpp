#pragma once
#include <vector>
#include <iostream>

using std::istream;
using std::ostream;

template <typename T>
struct MatrixItem {
	int row;
	int column;
	T value;
};


template <typename T>
class SpareMatrix {
	template <typename S>
	friend ostream& operator<<(ostream&, SpareMatrix<S>&);
	template <typename V>
	friend  istream& operator>>(istream&, SpareMatrix<V>&);

public:
	void transpose(SpareMatrix<T>& b);
	void add(SpareMatrix<T>& b, SpareMatrix<T>& c);

private:
	int m_rows = 0;
	int m_columns = 0;
	std::vector<MatrixItem<T>> m_termsVec;
};

template <typename T>
void SpareMatrix<T>::transpose(SpareMatrix<T>& matrix) {
	matrix.m_rows = m_rows;
	matrix.m_columns = m_columns;
	matrix.m_termsVec.resize(m_termsVec.size());

	int* colsize = new int[m_columns + 1];
	int* rowNext = new int[m_columns + 1];

	if (m_termsVec.size() > 0) {
		for (int i = 1; i <= m_columns; ++i) {
			colsize[i] = 0;
		}

		for (int i = 0; i < m_termsVec.size(); ++i) {
			colsize[m_termsVec[i].column]++;
		}

		rowNext[1] = 0;
		for (int i = 2; i <= m_columns; ++i) {
			rowNext[i] = rowNext[i - 1] + colsize[i - 1];
		}

		for (int i = 0; i < m_termsVec.size(); ++i) {
			int j = rowNext[m_termsVec[i].column];
			matrix.m_termsVec[j].row = m_termsVec[i].column;
			matrix.m_termsVec[j].column = m_termsVec[i].row;
			matrix.m_termsVec[j].value = m_termsVec[i].value;
			rowNext[m_termsVec[i].column]++;
		}
	}
}

template <typename T>
void SpareMatrix<T>::add(SpareMatrix<T>& b, SpareMatrix<T>& c) {
	if (m_rows != b.m_rows || m_columns != b.m_columns) {
		throw exception("Incompatible matrices");
	}

	c.m_rows = m_rows;
	c.m_columns = m_columns;
	c.m_termsVec.clear();
	int cSize = 0;

	int aPos = 0, bPos = 0;
	
	while (aPos < m_termsVec.size() && bPos < b.m_termsVec.size()) {
		int tIndex = m_termsVec[aPos].row * m_columns + m_termsVec[aPos].column;
		int bIndex = b.m_termsVec[bPos].row * b.m_columns + b.m_termsVec[bPos].column;

		if (tIndex < bIndex) {
			c.m_termsVec.push_back(m_termsVec[aPos]);
			aPos++;
		}
		else if (tIndex == bIndex) {
			MatrixItem<T> item;
			item.row = m_termsVec[aPos].row;
			item.column = m_termsVec[aPos].column;
			item.value = m_termsVec[aPos].value + b.m_termsVec[bPos].value;
			if (item.value != 0) {
				c.m_termsVec.push_back(item);
				cSize++;
			}
			aPos++;
			bPos++;
		}
		else {
			c.m_termsVec.push_back(b.m_termsVec[bPos]);
			bPos++;
		}
	}

	for (; aPos < m_termsVec.size(); ++aPos) {
		c.m_termsVec.push_back(m_termsVec[aPos]);
	}

	for (; bPos < b.m_termsVec.size(); ++bPos) {
		c.m_termsVec.push_back(b.m_termsVec[bPos]);
	}
}

template <typename T>
ostream& operator<<(ostream& out, SpareMatrix<T>& matrix) {
	out << "rows = " << matrix.m_rows << "columns = " << matrix.m_columns << std::endl;
	out << "terms = " << matrix.m_termsVec.size() << std::endl;

	auto it = matrix.m_termsVec.begin();
	for (; it != matrix.m_termsVec.end(); ++it) {
		out << "m(" << it->row << ", " << it->column << ") = " << it->value << std::endl;
	}
	return out;
}

template <typename T>
istream& operator>>(istream& in, SpareMatrix<T>& matrix) {
	std::cout << "enter number of rows, columns and terms:";
	int nums = 0;
	in >> matrix.m_rows >> matrix.m_columns >> nums;
	// to check the inputs
	matrix.m_termsVec.resize(nums);
	MatrixItem<T> item;
	for (int i = 0; i < nums; ++i) {
		std::cout << "enter the row, column and value:" << i + 1 << std::endl;
		in >> item.row >> item.column >> item.value;
		// to check the inputs
		matrix.m_termsVec[i] = item;
	}

	return in;
}