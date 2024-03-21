// program4_1.cpp

#include <iostream>
#include <ctime> 

using std::cout;
using std::endl;

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

void test_run_time_1(int a[], int step, double clocksPerMillis) {
	cout << "The worse case time in molliseconds are " << endl;
		cout << "n \t time" << endl;
		
		for (int n = 0; n < 1000; n += step) {
			for (int i = 0; i < n; ++i) {
				a[i] = n - i;
			}
			
			clock_t start_time = clock();
			sort_by_insert(a, n);
			double elapse_millis = (clock() - start_time) / clocksPerMillis;
			
			cout << n << "\t" << elapse_millis << endl;
			
			if (n == 100) step = 100;
			
		}
}

void test_run_time_2(int a[], int step, double clocksPerMillis) {
	cout << "The worse case time in molliseconds are " << endl;
		cout << "n \tRepetitions \t Total Ticks \tTime per Sort" << endl;
		
		for (int n = 0; n < 1000; n += step) {
			
			
			
			long numer_of_repetitons = 0;
			clock_t start_time = clock();
			do {
				++numer_of_repetitons;
				
				for (int i = 0; i < n; ++i) {
					a[i] = n - i;
				}
				
				sort_by_insert(a, n);
			} while (clock() - start_time < 1000);
			
			double elapse_millis = (clock() - start_time) / clocksPerMillis;
			
			cout << n << "\t" << numer_of_repetitons << "\t" << elapse_millis 
			<< "\t" << elapse_millis / numer_of_repetitons << endl;
			
			if (n == 100) step = 100;
			
		}
}


int main() {
	
	
	int a[1000];
	int step = 10;
	
	double clocksPerMillis = double(CLOCKS_PER_SEC);
	cout << "test 1:" << endl;
	test_run_time_1(a, step, clocksPerMillis);
	
	cout << "test_2:" << endl;
	test_run_time_2(a, step, clocksPerMillis);
	
	return 0;
	
}
