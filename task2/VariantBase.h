#pragma once
#include "Student.h"
#include <vector>
#include <string>
using namespace std;

class VariantBase {
public:
    virtual void init(const vector<Student>& students) = 0;
    virtual vector<Student> find_by_birthday(int month, int day) = 0;
    virtual bool change_group_by_email(const string& email, const string& new_group) = 0;
    virtual string find_group_with_most_same_birthdays() = 0;
    virtual ~VariantBase() = default;
};
