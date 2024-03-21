// practice19-26.cpp

#include <iostream>
#include <cmath>
#include <iterator>

using namespace std;

// p19
int factorial(int n) {
	int res = 1;
	for (int i = 1; i <= n; ++i) {
		res *= i;
	}
	
	return res;
} 

// p20
int fibonacci(int n) {
	if (n <= 1) return n;
	return fibonacci(n-1) + fibonacci(n-2);
}

// p21
int func(int n) {
	if (n & 1) {
		return func(3 * n - 1);
	} else {
		return n / 2;
	}	
}

int func2(int n) {
	if (n & 1) {
		return (3 * n - 1) / 2;
	} else {
		return n / 2;
	}
}

// p22
int achermann(int i, int j) {
	if (i == 1) {
		return pow(2, j);
	} else if (j == 1) {
		return achermann(i-1, j);
	} else {
		return achermann(i-1, achermann(i, j-1));
	}
}

// p23
int gcd(int x, int y) {
	if (y == 0) {
		return x;
	} else {
		return gcd(y, x % y);
	}
} 

// aditional p23
int lcm(int x, int y) {
	return x * y / gcd(x, y);
}

// p24
bool isIn(int a[], size_t size, int value) {
	if (size == 1) return value == a[0];
	if (a[size-1] == value) return true;
	return isIn(a, size-1, value);
}

// p25
void subSetGeneration(int a[], int size, int start) {
	if (start == size) {
		copy(a, a+size, ostream_iterator<int>(cout, ""));
		cout << endl;
		return;
	}
		
	a[start] = 0;
	subSetGeneration(a, size, start + 1);
	a[start] = 1;
	subSetGeneration(a, size, start + 1);
}

// p26
int grayCode(int n) {
	if (n == 1) return 1;
	
}

// the main funciton
int main() {
	
	
	// p25
	cout << "practice 25:" << endl;
	int a[3] = { };
	subSetGeneration(a, 3, 0);
}
