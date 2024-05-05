// main.cpp

#include <iostream>
#include "arraylist.hpp" 
#include <algorithm>

static bool cmp(int a, int b) { return a < b;  }

int main() {

	using std::cout;
	using std::endl;
	
	
	try {
		arrayList<int> test2 = { };

		cout << test2 << endl;
	}
	catch (BaseException& e) {
		cout << e.what() << endl;
	}
	catch (...) {
		cout << "some errors!" << endl;
	}

	return 0;
}