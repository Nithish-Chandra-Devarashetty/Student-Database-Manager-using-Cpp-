#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
public:
    string name;
    int rollNo;
    string section;
    string department;

    void inputStudent() {
        cout << "Enter Name: "; cin >> ws; getline(cin, name);
        cout << "Enter Roll Number: "; cin >> rollNo;
        cout << "Enter Section: "; cin >> section;
        cout << "Enter Department: "; cin >> department;
    }

    void displayStudent() const {
        cout << "Name: " << name << ", Roll No: " << rollNo << ", Section: " << section << ", Department: " << department << endl;
    }
};

class StudentDatabase {
private:
    vector<Student> students;
    string filename = "students.dat";

    void saveToFile() {
        ofstream file(filename, ios::binary | ios::trunc);
        for (const auto& student : students) {
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        }
        file.close();
    }

    void loadFromFile() {
        students.clear();
        ifstream file(filename, ios::binary);
        if (!file) return;
        Student s;
        while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
            students.push_back(s);
        }
        file.close();
        sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
            return a.rollNo < b.rollNo;
        });
    }

public:
    StudentDatabase() {
        loadFromFile();
    }

    void addStudent() {
        Student s;
        s.inputStudent();
        students.push_back(s);
        sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
            return a.rollNo < b.rollNo;
        });
        saveToFile();
        cout << "Student added successfully.\n";
    }

    void displayAllStudents() {
        for (const auto& s : students) {
            s.displayStudent();
        }
    }

    void searchByRollNo(int roll) {
        int left = 0, right = students.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (students[mid].rollNo == roll) {
                students[mid].displayStudent();
                return;
            } else if (students[mid].rollNo < roll) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        cout << "Student not found!\n";
    }
};

int main() {
    StudentDatabase db;
    int choice, rollNo;

    while (true) {
        cout << "\n1. Add Student\n2. Display All Students\n3. Search by Roll Number\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: db.addStudent(); break;
            case 2: db.displayAllStudents(); break;
            case 3: 
                cout << "Enter Roll Number to search: ";
                cin >> rollNo;
                db.searchByRollNo(rollNo);
                break;
            case 4: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
