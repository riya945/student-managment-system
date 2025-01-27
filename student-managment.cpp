#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    string course;
    float gpa;

public:
    void input();
    void display() const;
    int getId() const;
    static void addStudent();
    static void viewStudents();
    static void searchStudent();
    static void deleteStudent();

    friend ofstream& operator<<(ofstream& out, const Student& s);
    friend ifstream& operator>>(ifstream& in, Student& s);
};

void Student::input() {
    cout << "Enter student ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, name);
    cout << "Enter course: ";
    getline(cin, course);
    cout << "Enter GPA: ";
    cin >> gpa;
}

void Student::display() const {
    cout << "ID: " << id << "\tName: " << name << "\tCourse: " << course << "\tGPA: " << gpa << endl;
}

int Student::getId() const {
    return id;
}

ofstream& operator<<(ofstream& out, const Student& s) {
    out << s.id << " " << s.name << " " << s.course << " " << s.gpa << endl;
    return out;
}

ifstream& operator>>(ifstream& in, Student& s) {
    in >> s.id >> ws;
    getline(in, s.name, ' ');
    getline(in, s.course, ' ');
    in >> s.gpa;
    return in;
}

const string filename = "students.txt";

void Student::addStudent() {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    Student student;
    student.input();
    file << student;
    file.close();
    cout << "Student added successfully!" << endl;
}

void Student::viewStudents() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Student student;
    cout << "\nID\tName\tCourse\tGPA" << endl;
    while (file >> student) {
        student.display();
    }
    file.close();
}

void Student::searchStudent() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    int id;
    cout << "Enter student ID to search: ";
    cin >> id;

    Student student;
    bool found = false;
    while (file >> student) {
        if (student.getId() == id) {
            cout << "\nStudent found:\n";
            student.display();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
    file.close();
}

void Student::deleteStudent() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "Error creating temporary file." << endl;
        file.close();
        return;
    }

    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    Student student;
    bool deleted = false;
    while (file >> student) {
        if (student.getId() != id) {
            tempFile << student;
        } else {
            deleted = true;
        }
    }

    file.close();
    tempFile.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    if (deleted) {
        cout << "Student record deleted successfully!" << endl;
    } else {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Student::addStudent();
                break;
            case 2:
                Student::viewStudents();
                break;
            case 3:
                Student::searchStudent();
                break;
            case 4:
                Student::deleteStudent();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}

