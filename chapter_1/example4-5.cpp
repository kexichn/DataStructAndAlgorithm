// example4-5.cpp

#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

// ex4
// accumulate(start, end, initValue, operator);
template <typename T>
T sum(T a[], size_t n) {
	T res = 0;
	return accumulate(a, a+n, res);
}

template <typename T>
T product(T a[], size_t n) {
	T res = 1;
	return accumulate(a, a+n, res, multiplies<T>());
}

// ex5
template <typename T>
void permutations(T list[], int /*k*/, int m) {
	do {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} while (next_permutation(list, list + m + 1));
} 


// the main function
int main() {
	// ex1
	cout << "\nexample 1:" << endl;
	int a[5] { 1, 2, 3, 4 ,5 };
	cout << "the sum of a is " << sum(a, 5) << endl;
	
	// ex2
	cout << "\nexample 2:" << endl;
	int b[3] = { 1, 2, 3 };
	cout << "the permutations of a is :" << endl;
	permutations(b, 0, 2);
}
