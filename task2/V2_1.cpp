#include "VariantBase.h"
#include <vector>
#include <unordered_map>
using namespace std;

class Variant1 : public VariantBase {
    vector<Student> students;
public:
    void init(const vector<Student>& s) override { students = s; }

    vector<Student> find_by_birthday(int month, int day) override {
        vector<Student> res;
        for (auto& st : students)
            if (st.m_birth_month == month && st.m_birth_day == day)
                res.push_back(st);
        return res;
    }

    bool change_group_by_email(const string& email, const string& new_group) override {
        for (auto& st : students)
            if (st.m_email == email){
                st.m_group = new_group;
                return true;
            }
        return false;
    }

    string find_group_with_most_same_birthdays() override {
        unordered_map<string, unordered_map<string, int>> birthday_count;
        string best_group;
        int best_count = 0;

        for (const auto& st : students) {
            string key = to_string(st.m_birth_day) + "." + to_string(st.m_birth_month);
            birthday_count[st.m_group][key]++;
            if (birthday_count[st.m_group][key] > best_count) {
                best_count = birthday_count[st.m_group][key];
                best_group = st.m_group;
            }
        }
        return best_group;
    }
};
