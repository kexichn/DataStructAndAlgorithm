#pragma once
#include <string>
#include <ostream>
struct studentRecord
{
    int score;
    std::string* name;
    studentRecord() { score = 0; name = nullptr; }
    studentRecord(int s, std::string* n) { score = s, name = n; }

    int operator!=(const studentRecord& x) const { return (score != x.score); }
    operator int() const { return score; }
};

std::ostream& operator<<(std::ostream& out, const studentRecord& x) {
    out << *x.name << ":" << x.score << " ";
    return out;
}
