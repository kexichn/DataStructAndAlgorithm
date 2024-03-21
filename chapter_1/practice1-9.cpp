// practice1-9.cpp  -- the functions which are the answers for the practice 1 - 9

#include <iostream>
#include <cstddef>

// p1
void swap(int& x, int& y) {
	int temp = x;
	x = y;
	y = temp;
} 

// p2
template <typename T>
size_t count(T array[], size_t n, T value) {
	size_t result = 0; 
	for (size_t idx = 0; idx < n; ++idx) {
		if (array[idx] == value) {
			++result;
		}
	}
	return result;
}

// p3
template <typename T>
void fill(T array[], size_t start, size_t end, T value) {
	for (int i = start; i < end; ++i) {
		array[i] = value;
	}
}

// p4  p5 skip

// p6
template <typename T>
bool is_sorted(T array[], size_t size) {
	bool result = true;
	for (int i = 1; i < size; ++i) {
		if (array[i] < array[i-1]) {
			result = false;
			break;
		}
	}
	
	return result;
}


// p7 p8 p9 skip 

// the main funtion for testing the answers above;
int main() {
	using std::cout;
	using std::endl;
	
	// p1
	int a = 2, b = 5;
	swap(a, b);
	cout << a << "  " << b << endl;
	
	// p2
	int arr[5] = { 2, 4, 5, 2, 3 };
	cout << count(arr, 5, 2) << endl;
	
	// p3
	int a3[5];
	fill(a3, 2, 3, 10);
	for (int i = 0; i < 5; ++i) {
		cout << a3[i] << endl;
	}
	
	// p4
	
}
