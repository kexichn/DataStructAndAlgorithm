#pragma once
#include <iostream>

using std::istream;
using std::ostream;

struct ColumnNode {
	int column = 0;
	int value = 0;
	ColumnNode* nextColumn = nullptr;
};

struct HeadNode {
    int row = -1;
	HeadNode* nextRow = nullptr;
	ColumnNode* columnNode = nullptr;

};


// define the linked matrix class
template <typename T>
class LinkedMatrix {
	friend istream& operator>><>(istream& in, LinkedMatrix<T>& m);
	friend ostream& operator<<<>(ostream& out, LinkedMatrix<T>& m);	
public:
	LinkedMatrix(int rows = 0, int columns = 0);
	~LinkedMatrix();
	void transpose(LinkedMatrix<T>& b);
	void add(LinkedMatrix<T>& b, LinkedMatrix<T>& c);

private:
	int m_rows = 0;
	int m_columns = 0;
	HeadNode* m_head = nullptr;
};

template<typename T>
inline LinkedMatrix<T>::LinkedMatrix(int rows, int columns)
{
	m_rows = rows;
	m_columns = columns;
	m_head = new HeadNode{ -1, nullptr, nullptr };
}

template<typename T>
inline LinkedMatrix<T>::~LinkedMatrix()
{
	HeadNode* p = m_head;
	ColumnNode* q = nullptr;
	while (p->nextRow) {
		q = p->nextRow->columnNode;
		while (q->nextColumn) {
			ColumnNode* tmp = q->nextColumn;
			delete q;
			q = tmp;
		}

		HeadNode* tmp = p->nextRow;	
		delete p;
		p = tmp;
	}
}

template<typename T>
inline void LinkedMatrix<T>::transpose(LinkedMatrix<T>& b)
{
	
}

template <typename T> 
istream& operator>>(istream& in, LinkedMatrix<T>& m) {
	std::cout << "Enter number of rows, columns, and number of terms" << std::endl;
	int rows, columns, terms;
	in >> rows >> columns >> terms;
	m.m_rows = rows;
	m.m_columns = columns;

	HeadNode* p = m.m_head;
	ColumnNode* q = nullptr;
	int i = 0; 
	while (i++ < terms) {
		std::cout << "Enter row, column, and value:";
		int row, column, value;
		in >> row >> column >> value;

		while (p->nextRow != nullptr && p->nextRow->row < row) {
			p = p->nextRow;
		}

		if (p->nextRow == nullptr) {
			p->nextRow = new HeadNode{ row, nullptr, nullptr };
		} else if (p->nextRow->row > row) {
			HeadNode* tmp = p->nextRow;
			p->nextRow = new HeadNode{ row, tmp, nullptr };
		} 

		q = p->nextRow->columnNode;
		ColumnNode* last = nullptr;
		while (q != nullptr && q->column < column) {
			last = q;
			q = q->nextColumn;
		}

		if (q == nullptr) {
			q = new ColumnNode{ column, value, nullptr };
			if (last == nullptr) {
				p->nextRow->columnNode = q;
			} else {
				last->nextColumn = q;
			}
		} else if (q->column > column) {
			if (last == nullptr) {
				p->nextRow->columnNode = new ColumnNode{ column, value, q };
			} else {
				last->nextColumn = new ColumnNode{ column, value, q };
			}
		} else {
			q->value = value;
		}
	}

	return in;
}

template <typename T>
inline ostream& operator<<(ostream& out, LinkedMatrix<T>& m)
{
	out << m.m_rows << " " << m.m_columns << std::endl;
	HeadNode* p = m.m_head;
	ColumnNode* q = nullptr;
	int i = 1;
	for (; i <= m.m_rows; ++i) {
		p = p->nextRow;

		if (p == nullptr) {
			break;
		} 
		
		while (p->row != i) {
			for (int j = 1; j <= m.m_columns; ++j) {
				out << "0 ";
			}
			out << std::endl;
			++i;
		}

		q = p->columnNode;
		for (int j = 1; j <= m.m_columns; ++j) {
			if (q && q->column == j) {
				out << q->value << " ";
				q = q->nextColumn;
			} else {
				out << "0 ";
			}
		}
		out << std::endl;
	}

	for (; i <= m.m_rows; ++i) {
		for (int j = 1; j <= m.m_columns; ++j) {
			out << "0 ";
		}
		out << std::endl;
	}

	return out;
}
