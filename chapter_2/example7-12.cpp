// example7-12.cpp

#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

// ex7  ex8 ex9 skip

// ex10 
void sort_by_count(int list[], int order[],  int tmp[], int size) {
	//int* order = new int [size];
	for (int i = 1; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			if (list[j] <= list[i]) {
				++order[i];
			} else {
				++order[j];
			}
		}
	}
	
	//int* tmp = new int [size];
	for (int k = 0; k < size; ++k) {
		tmp[order[k]] = list[k];
	}
	
	// copy(tmp, tmp+size, list);
	for (int s = 0; s < size; ++s) {
			list[s] = tmp[s];
	}	
}
// ex11
int index_of_max(int list[], int size) {
	int max_index = 0;
	for (int i = 0; i < size; ++i) {
		if (list[max_index] < list[i]) {
			max_index = i;
		}
	}
	
	return max_index;
}

void sort_by_select(int list[], int size) {
	for (int n = size; n > 1; --n) {
		int j = index_of_max(list, n);
		swap(list[j], list[n-1]);
	}
}

// ex12
void bubble(int list[], int size) {
	for(int i = 1; i < size; ++i) {
		if (list[i] < list[i-1]) {
			swap(list[i], list[i - 1]);
		}
	}
}

void sort_by_bubble(int list[], int size) {
	for (int i = size; i > 1; --i) {
		bubble(list, i);
	}
}

// the main function
int main() {
	
	// ex10
	cout << "example 10£º" << endl;
	int a[5] = { 4, 6, 3, 2, 7 };
	cout << "before sort:";
	copy(a, a+5, ostream_iterator<int>(cout, " "));
	
	cout << "\nafter sort:";
	int order[5] = { 0 };
	int tmp[5] = { 0 };
	sort_by_count(a, order, tmp, 5);
	copy(a, a+5, ostream_iterator<int>(cout, " "));
	
	// ex11
	cout << "\nexample 11:" << endl;
	int b[5] = { 14, 8, 9, 12, 5 };
	cout << "before sort:";
	copy(b, b+5, ostream_iterator<int>(cout, " "));
		
	cout << "\nafter sort:";
	sort_by_select(b, 5);
	copy(b, b+5, ostream_iterator<int>(cout, " "));
	
	// ex12
	cout << "\nexample 12:" << endl;
	int c[5] = { 6, 2, 1, 4, 5 };
	cout << "before sort:";
	copy(c, c+5, ostream_iterator<int>(cout, " "));
		
	cout << "\nafter sort:";
	sort_by_bubble(c, 5);
	copy(c, c+5, ostream_iterator<int>(cout, " "));
	
	return 0;
	
}
