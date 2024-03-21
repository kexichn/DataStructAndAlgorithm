// example1-3.cpp 

#include <iostream>
#include <iterator>

using namespace std;

// ex1
int factorial(int n) {
	if (n == 0) throw "error of n!";
	if (n == 1) return 1;
	else return n * factorial(n-1);
}

// ex2
template <typename T>
T rSum(T a[], int n) {
	if (n <= 0) return 0;
	return rSum(a, n - 1) + a[n-1];
}

// ex3
template <typename T>
void permutations(T list[], int k, int m) {
	if (k == m) {
		copy(list, list+m+1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} else {
		for (int i = k; i <= m; ++i) {
			swap(list[k], list[i]);
			permutations(list, k + 1, m);
			swap(list[k], list[i]);
		}
	}
}


int main() {
	
	// ex1
	cout << "example 1:" << endl;
	int n = 0, res = 0;
	
	try {
		cout << "Please input a number:";
		cin >> n;
		res  = factorial(n);
		cout << "the factorial result of " << n << " is :" << res << endl;
	} catch (char* e) {
		cout << e << endl;
	}
	
	// ex2
	cout << "example 2:" << endl;
	int a[5] = { 4, 6, 2, 3, 8};
	
	cout << "the sum of array is " << rSum(a, 5) << endl;
	
	// ex3
	cout << "example 3:" << endl;
	int c[3] = { 1, 2, 3 };
	permutations(c, 0, 2);
	
	return 0;
}
