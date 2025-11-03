#include "VariantBase.h"
#include <unordered_map>
using namespace std;

class Variant2 : public VariantBase {
    unordered_map<string, Student> studentsByEmail;
public:
    void init(const vector<Student>& students) override {
        for (auto& s : students) studentsByEmail[s.m_email] = s;
    }

    vector<Student> find_by_birthday(int month, int day) override {
        vector<Student> result;
        for (const auto& [email, st] : studentsByEmail) {
            if (st.m_birth_month == month && st.m_birth_day == day) {
                result.push_back(st);
            }
        }
        return result;
    }

    bool change_group_by_email(const string& email, const string& new_group) override {
        auto it = studentsByEmail.find(email);
        if (it == studentsByEmail.end()) return false;
        it->second.m_group = new_group;
        return true;
    }

    string find_group_with_most_same_birthdays() override {
        unordered_map<string, unordered_map<string, int>> birthday_count;
        string best_group;
        int best_count = 0;

        for (const auto& [email, st] : studentsByEmail) {
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
