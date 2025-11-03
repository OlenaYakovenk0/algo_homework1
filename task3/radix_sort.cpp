#include <vector>
#include <string>
using namespace std;

#include "Student.h"

void radix_sort(vector<Student>& students) {
    if (students.empty()) return;

    const int ASCII = 256;
    size_t len = students[0].m_group.size();

    vector<Student> temp(students.size());

    for (int pos = int(len) - 1; pos >= 0; --pos) {

        int count[ASCII] = {0};
        for (auto& s : students) {
            unsigned char c = s.m_group[pos];
            count[c]++;
        }

        for (int i = 1; i < ASCII; i++)
            count[i] += count[i - 1];

        for (int i = int(students.size()) - 1; i >= 0; --i) {
            unsigned char c = students[i].m_group[pos];
            temp[--count[c]] = students[i];
        }

        students = temp;
    }
}
