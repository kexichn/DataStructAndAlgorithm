// practice10-11.cpp
#include <iostream>
#include <cstddef>

// p10
int abc(int a, int b, int c) {
	if (a < 0 && b < 0 && c < 0) {
		throw 1;
	} else if (a == 0 && b == 0 && c == 0) {
		throw 2;
	}
	
	return a + b * c;
}

// p11 skip

int main() {
	
	using std::cout;
	using std::endl;
	
	// p10
	int a = -1, b = -2, c = -3;
	try {
		int res = abc(a, b, c);
		cout << res << endl;
	} catch (int e) {
		cout << "error code : " << e << endl;
	}
	
	a = 0, b = 0, c = 0;
	try {
		int res = abc(a, b, c);
		cout << res << endl;
	} catch (int e) {
		cout << "error code : " << e << endl;
	}
	
	a = 1, b = 2, c = 3;
	try {
		int res = abc(a, b, c);
		cout << res << endl;
	} catch (int e) {
		cout << "error code : " << e << endl;
	}
	
	return 0;
	
}

 
