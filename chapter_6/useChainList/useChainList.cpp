
#include <iostream>
#include "chain.hpp"
#include "studentrecord.h"

void binSort(Chain<studentRecord>& theChain, int range);

int main()
{
    using std::cout;
    using std::endl;

    std::string name1 = "kerr", name2 = "sundy", name3 = "lucy", 
        name4 = "biny", name5 = "gore", name6 = "gut", name7 = "arc", 
        name8 = "qwe", name9 = "trc", name10 = "gvy", name11 = "ghu",
        name12 = "pou";
    studentRecord s1 = { 5, &name1 },
        s2 = { 4, &name2 },
        s3 = { 11, &name3 },
        s4 = { 9, &name4 },
        s5 = { 7, &name5 },
        s6 = { 19, &name6 },
        s7 = { 14, &name7 },
        s8 = { 6, &name8 },
        s9 = { 8, &name9 },
        s10 = { 17, &name10 },
        s11 = { 5, &name11 },
        s12 = { 3, &name12 };

    Chain<studentRecord> chain = { s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12 };

    cout << chain << endl;
    chain.binSort(20);
    cout << chain << endl;

    /*double s = CLOCKS_PER_SEC / 1000;
    clock_t st = clock();

    double els = (clock() - st) / s;
    cout << els << "ms" << endl;*/
}


void binSort(Chain<studentRecord>& theChain, int range) {
    using stu = studentRecord;
    using stuChain = Chain<studentRecord>;
    stuChain* bin = new stuChain[range + 1];

    int num = theChain.size();
    for (int i = 1; i <= num; ++i) {
        stu x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0, x);
    }

    for (int j = range; j >= 0; --j) {
        while (!bin[j].empty()) {
            stu x = bin[j].get(0);
            bin[j].erase(0);
            theChain.insert(0, x);
        }
    }

    delete [] bin;
}