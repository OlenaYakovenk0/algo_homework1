#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <string>
#include "Student.h"
using namespace std;


vector<Student> readCSV(const string& filename, int limit = -1) {
    ifstream file(filename);
    vector<Student> res;
    if (!file.is_open()) return res;

    string line; getline(file, line);
    int count = 0;
    while (getline(file, line)) {
        if (limit != -1 && count >= limit) break;
        Student st; stringstream ss(line); string temp;
        getline(ss, st.m_name, ',');
        getline(ss, st.m_surname, ',');
        getline(ss, st.m_email, ',');
        getline(ss, temp, ','); st.m_birth_year = stoi(temp);
        getline(ss, temp, ','); st.m_birth_month = stoi(temp);
        getline(ss, temp, ','); st.m_birth_day = stoi(temp);
        getline(ss, st.m_group, ',');
        getline(ss, temp, ','); st.m_rating = stof(temp);
        getline(ss, st.m_phone_number, ',');
        res.push_back(st);
        count++;
    }
    return res;
}
