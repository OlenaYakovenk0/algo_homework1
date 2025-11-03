#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>

#include "radix_sort.cpp"
#include "reader_csv.cpp"
using namespace std;
using namespace chrono;
namespace fs = filesystem;


void write_students(const string& filename, const vector<Student>& students) {
    ofstream fout(filename);

    fout << "m_name,m_surname,m_email,m_birth_year,m_birth_month,m_birth_day,m_group,m_rating,m_phone_number\n";

    for (const auto& s : students) {
        fout << s.m_name << ','
             << s.m_surname << ','
             << s.m_email << ','
             << s.m_birth_year << ','
             << s.m_birth_month << ','
             << s.m_birth_day << ','
             << s.m_group << ','
             << s.m_rating << ','
             << s.m_phone_number << '\n';
    }

    fout.close();
}

void sort_std(vector<Student>& students) {
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {return a.m_group < b.m_group;});
}

template <typename Func>
double measure_time(Func f, vector<Student>& students) {
    auto start = high_resolution_clock::now();
    f(students);
    auto end = high_resolution_clock::now();
    duration<double, milli> dur = end - start;
    return dur.count();
}

int main() {
    const string path = (fs::path(PROJECT_SOURCE_DIR) / "students.csv").string();
    vector<Student> students = readCSV(path);
    cout << "Read " << students.size() << " students\n";
    auto students1 = students;
    auto students2 = students;

    double t_std = measure_time(radix_sort, students1);
    double t_radix = measure_time(sort_std, students2);

    cout << "sort: " << t_std << " ms\n";
    cout << "Radix sort: " << t_radix << " ms\n";

    write_students("../task3/sorted_csv/sorted_std.csv", students1);
    write_students("../task3/sorted_csv/sorted_radix.csv", students2);
}