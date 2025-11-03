#include <iostream>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <sstream>
#include "Student.h"
#include "VariantBase.h"
#include "memory_usage.h"
using namespace std;
namespace fs = filesystem;

#include "V2_1.cpp"
#include "V2_2.cpp"
#include "V2_3.cpp"
#include "reader_csv.cpp"

vector<int> runExperiment(VariantBase& impl, const vector<Student>& data, int seconds) {
    impl.init(data);
    auto start = chrono::steady_clock::now();
    int op1=0,op2=0,op3=0;
    while (chrono::duration<double>(chrono::steady_clock::now() - start).count() < seconds) {
        int r = rand() % 155;
        if (r < 5){
            impl.find_by_birthday(rand()%12+1, rand()%28+1);
            op1++;
        }
        else if (r < 105){
            impl.change_group_by_email(data[rand()%data.size()].m_email, "TMP");
            op2++;
        }
        else{
            impl.find_group_with_most_same_birthdays();
            op3++;
        }
    }
    cout << "op1="<<op1<<" op2="<<op2<<" op3="<<op3<<endl;
    vector<int> op = {op1, op2, op3};
    return op;
}

void logResult(const string& variant, int size, double memMB, vector<int> op) {
    ofstream out("../task2/results.csv", ios::app);
    if (!out.is_open()) return;
    out << variant << "," << size << "," << memMB << ","
        << op[0] << "," << op[1] << "," << op[2] << ","
        << (op[0] + op[1] + op[2]) << "\n";
}

int main() {
    const string path = (fs::path(PROJECT_SOURCE_DIR) / "students.csv").string();

    ofstream clear("../task2/results.csv", ios::trunc);
    clear << "variant,size,mem_MB,op1,op2,op3,total_ops\n";
    clear.close();

    vector<int> sizes = {100, 1000, 10000, 100000};
    for (int n : sizes) {
        auto data = readCSV(path, n);
        double memBefore = getMemoryMB();
        Variant1 impl;
        impl.init(data);
        double memAfter = getMemoryMB();
        double deltaB = (memAfter - memBefore);
        cout << "\nVariant1\n=== Test for " << n << " students ===\ndeltaMB " << deltaB << '\n';
        logResult("V1", n, deltaB, runExperiment(impl, data, 10));
    }
    for (int n : sizes) {
        auto data = readCSV(path, n);
        double memBefore = getMemoryMB();
        Variant2 impl;
        impl.init(data);
        double memAfter = getMemoryMB();
        double deltaB = (memAfter - memBefore);
        cout << "\nVariant2\n=== Test for " << n << " students ===\ndeltaMB " << deltaB << '\n';
        logResult("V2", n, deltaB, runExperiment(impl, data, 10));
    }
    for (int n : sizes) {
        auto data = readCSV(path, n);
        double memBefore = getMemoryMB();
        Variant3 impl;
        impl.init(data);
        double memAfter = getMemoryMB();
        double deltaB = (memAfter - memBefore);
        cout << "\nVariant3\n=== Test for " << n << " students ===\ndeltaMB " << deltaB << '\n';
        logResult("V3", n, deltaB, runExperiment(impl, data, 10));
    }
}
