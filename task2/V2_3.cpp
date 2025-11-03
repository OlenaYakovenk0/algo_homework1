#include "VariantBase.h"
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

class Variant3 : public VariantBase {
    map<pair<int,int>, vector<Student>> studentsByBirthday;
    vector<Student> students;
public:
    void init(const vector<Student>& s) override {
        students = s;
        for (auto st : s)
            studentsByBirthday[{st.m_birth_month, st.m_birth_day}].push_back(st);
    }

    vector<Student> find_by_birthday(int month, int day) override {
        auto it = studentsByBirthday.find({month, day});
        if (it == studentsByBirthday.end()) return {};
        return it->second;
    }

    bool change_group_by_email(const string& email, const string& new_group) override {
        for (auto& st : students){
            if (st.m_email == email){
                st.m_group = new_group;
                return true;
            }
        }
        return false;
    }

    string find_group_with_most_same_birthdays() override {
        unordered_map<string, map<string, int>> birthday_count;
        string bestGroup;
        int bestCount = 0;

        for (const auto& st : students) {
            string key = to_string(st.m_birth_month) + "." + to_string(st.m_birth_day);
            birthday_count[st.m_group][key]++;
            if (birthday_count[st.m_group][key] > bestCount) {
                bestCount = birthday_count[st.m_group][key];
                bestGroup = st.m_group;
            }
        }

        return bestGroup;
    }
};
