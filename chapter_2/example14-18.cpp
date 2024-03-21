// example14-18.cpp

#include <algorithm>

using namespace std;

// ex14
void insert(int list[], int size, int x) {
	int i = size - 1;
	for ( ; i > 0 && list[i] > x; --i) {
		list[i+1] = list[i];
	}
	
	list[i+1] = x; 
}

// ex15
void sort_by_count(int list[], int size, int order[]) {
	for (int i = 0; i < size; ++i) {
		while (order[i] != i) {
			swap(list[i], list[order[i]]);
			swap(order[i], order[order[i]]);
		}
	}	
}

// ex16
void sort_by_select(int list[], int size) {
	bool is_sort = false;
	for (int i = size; !is_sort && i > 0; --i) {
		int index_of_max = 0;
		is_sort = true;
		for (int j = 0; j < i; ++j) {
			if (list[index_of_max] <= list[i]) {
				index_of_max = i;
			} else {
				is_sort = false;
			}
		}
		
		swap(list[index_of_max], list[i - 1]);
	}
}

// ex17
bool bubble(int list[], int size) {
	bool swapped = false;
	for (int i = 1; i < size; ++i) {
		if (list[i] < list[i-1]) {
			swap(list[i], list[i-1]);
			swapped = true;
		}
	}
	
	return swapped;
} 

void sort_by_bubble(int list[], int size) {
	for (int i = size; i > 1 && bubble(list, i); --i);
}

// ex18
void sort_by_insert(int list[], int size) {
	for (int i = 1; i < size; ++i) {
		int t = list[i];
		int j = i - 1;
		for ( ; j >= 0 && t < list[j]; --j) {
			list[j+1] = list[j];
		}
		list[j+1] = t;
	}
}
