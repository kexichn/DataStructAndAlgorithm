
#include <iostream>
#include "appofstack.hpp"

int main()
{
    vector<int> tmp = { 3, 1, 6, 7, 2, 8, 5, 4 };
    

    auto res = rerangeTrain(tmp, 3);
    for (auto i : res) {
		cout << i << " ";
	}

}
