#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h> // For color & sleep
#include <conio.h>   // For getch()
#include <sstream>
using namespace std;

// Utility: set console color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Utility: show header
void showHeader() {
    system("cls");
    setColor(11);
    cout << "\n========== SCHOOL / COLLEGE MANAGEMENT SYSTEM ==========\n";
    setColor(15);
}

// ====== CLASS: STUDENT ======
class Student {
private:
    bool studentExists(int rollNo) {
        ifstream file("students.txt");
        if (!file) return false;
        
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                stringstream ss(line.substr(0, pos));
                int existingRoll;
                if (ss >> existingRoll && existingRoll == rollNo) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
        return false;
    }

public:
    int rollNo;
    string name;
    string className;
    float marks[5];
    float total;
    float percentage;

    bool input() {
        cout << "\nEnter Roll No: ";
        if (!(cin >> rollNo)) {
            setColor(12);
            cout << "Invalid Roll No! Please enter numbers only.\n";
            setColor(15);
            cin.clear();
            cin.ignore(10000, '\n');
            return false;
        }
        
        // Check if roll number already exists
        if (studentExists(rollNo)) {
            setColor(12);
            cout << "Student with Roll No " << rollNo << " already exists!\n";
            setColor(15);
            cin.ignore(10000, '\n');
            return false;
        }
        
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        
        cout << "Enter Class Name: ";
        getline(cin, className);
        
        total = 0;
        cout << "Enter marks for 5 subjects:\n";
        for (int i = 0; i < 5; i++) {
            cout << "Subject " << i + 1 << ": ";
            if (!(cin >> marks[i]) || marks[i] < 0 || marks[i] > 100) {
                setColor(12);
                cout << "Invalid marks! Please enter between 0-100.\n";
                setColor(15);
                cin.clear();
                cin.ignore(10000, '\n');
                return false;
            }
            total += marks[i];
        }
        percentage = total / 5.0;
        return true;
    }

    void display() const {
        cout << left << setw(10) << rollNo
             << setw(20) << name
             << setw(15) << className
             << setw(10) << total
             << setw(10) << fixed << setprecision(2) << percentage
             << setw(8) << grade() << endl;
    }

    string grade() const {
        if (percentage >= 80) return "A+";
        else if (percentage >= 70) return "A";
        else if (percentage >= 60) return "B";
        else if (percentage >= 50) return "C";
        else if (percentage >= 40) return "D";
        else return "F";
    }
};

// ====== CLASS: TEACHER ======
class Teacher {
private:
    bool teacherExists(int id) {
        ifstream file("teachers.txt");
        if (!file) return false;
        
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                stringstream ss(line.substr(0, pos));
                int existingId;
                if (ss >> existingId && existingId == id) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
        return false;
    }

public:
    int id;
    string name;
    string subject;
    string qualification;

    bool input() {
        cout << "\nEnter Teacher ID: ";
        if (!(cin >> id)) {
            setColor(12);
            cout << "Invalid Teacher ID! Please enter numbers only.\n";
            setColor(15);
            cin.clear();
            cin.ignore(10000, '\n');
            return false;
        }
        
        // Check if teacher ID already exists
        if (teacherExists(id)) {
            setColor(12);
            cout << "Teacher with ID " << id << " already exists!\n";
            setColor(15);
            cin.ignore(10000, '\n');
            return false;
        }
        
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        
        cout << "Enter Subject: ";
        getline(cin, subject);
        
        cout << "Enter Qualification: ";
        getline(cin, qualification);
        
        return true;
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(20) << subject
             << setw(20) << qualification << endl;
    }
};

// ====== FUNCTION DECLARATIONS ======
void addStudent();
void showStudents();
void searchStudent();
void deleteStudent();
void addTeacher();
void showTeachers();
void searchTeacher();
void deleteTeacher();

int main() {
    int choice;
    
    // Welcome animation
    setColor(11);
    cout << "Loading School Management System";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(500);
    }
    setColor(15);
    
    do {
        showHeader();
        cout << "\n1. Student Management";
        cout << "\n2. Teacher Management"; 
        cout << "\n3. Exit";
        cout << "\n\nEnter your choice: ";
        
        if (!(cin >> choice)) {
            setColor(12);
            cout << "\nInvalid input! Please enter a number (1-3).\n";
            setColor(15);
            cin.clear();
            cin.ignore(10000, '\n');
            Sleep(1000);
            continue;
        }

        switch (choice) {
            case 1: {
                int studentChoice;
                do {
                    showHeader();
                    cout << "\n=== STUDENT MANAGEMENT ===";
                    cout << "\n1. Add Student";
                    cout << "\n2. Show All Students";
                    cout << "\n3. Search Student";
                    cout << "\n4. Delete Student";
                    cout << "\n5. Back to Main Menu";
                    cout << "\n\nEnter your choice: ";
                    
                    if (!(cin >> studentChoice)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }
                    
                    switch (studentChoice) {
                        case 1: addStudent(); break;
                        case 2: showStudents(); break;
                        case 3: searchStudent(); break;
                        case 4: deleteStudent(); break;
                        case 5: break;
                        default: 
                            setColor(12);
                            cout << "\nInvalid Choice!\n";
                            setColor(15);
                            Sleep(1000);
                    }
                } while (studentChoice != 5);
                break;
            }
            case 2: {
                int teacherChoice;
                do {
                    showHeader();
                    cout << "\n=== TEACHER MANAGEMENT ===";
                    cout << "\n1. Add Teacher";
                    cout << "\n2. Show All Teachers";
                    cout << "\n3. Search Teacher";
                    cout << "\n4. Delete Teacher";
                    cout << "\n5. Back to Main Menu";
                    cout << "\n\nEnter your choice: ";
                    
                    if (!(cin >> teacherChoice)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        continue;
                    }
                    
                    switch (teacherChoice) {
                        case 1: addTeacher(); break;
                        case 2: showTeachers(); break;
                        case 3: searchTeacher(); break;
                        case 4: deleteTeacher(); break;
                        case 5: break;
                        default: 
                            setColor(12);
                            cout << "\nInvalid Choice!\n";
                            setColor(15);
                            Sleep(1000);
                    }
                } while (teacherChoice != 5);
                break;
            }
            case 3: 
                setColor(10);
                cout << "\nThank you for using School Management System!\n";
                setColor(15);
                break;
            default:
                setColor(12);
                cout << "\nInvalid Choice! Please choose 1-3.\n";
                setColor(15);
                Sleep(1000);
        }
    } while (choice != 3);

    return 0;
}

// ====== STUDENT FUNCTIONS ======
void addStudent() {
    showHeader();
    cout << "\n[ ADD STUDENT ]\n";
    
    Student s;
    if (s.input()) {
        ofstream file("students.txt", ios::app);
        if (!file) {
            setColor(12);
            cout << "\nError: Could not open file for writing!\n";
            setColor(15);
            getch();
            return;
        }
        file << s.rollNo << "|" << s.name << "|" << s.className << "|" 
             << s.total << "|" << s.percentage << endl;
        file.close();
        
        setColor(10);
        cout << "\nStudent Added Successfully!\n";
        setColor(15);
    } else {
        setColor(12);
        cout << "\nFailed to add student!\n";
        setColor(15);
    }
    getch();
}

void showStudents() {
    showHeader();
    cout << "\n[ ALL STUDENTS ]\n";
    
    ifstream file("students.txt");
    if (!file) {
        setColor(12);
        cout << "No student records found!\n";
        setColor(15);
        getch();
        return;
    }

    cout << left << setw(10) << "RollNo" << setw(20) << "Name" << setw(15)
         << "Class" << setw(10) << "Total" << setw(10) << "Percent" << setw(8) << "Grade" << endl;
    cout << "---------------------------------------------------------------------\n";

    string line;
    bool hasStudents = false;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Student s;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        size_t pos4 = line.find('|', pos3 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos && 
            pos3 != string::npos && pos4 != string::npos) {
            
            stringstream ss(line.substr(0, pos1));
            ss >> s.rollNo;
            s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            s.className = line.substr(pos2 + 1, pos3 - pos2 - 1);
            
            stringstream ss2(line.substr(pos3 + 1, pos4 - pos3 - 1));
            ss2 >> s.total;
            
            stringstream ss3(line.substr(pos4 + 1));
            ss3 >> s.percentage;
            
            setColor(14);
            s.display();
            setColor(15);
            hasStudents = true;
        }
    }
    file.close();
    
    if (!hasStudents) {
        setColor(12);
        cout << "No students found in records!\n";
        setColor(15);
    }
    getch();
}

void searchStudent() {
    showHeader();
    cout << "\n[ SEARCH STUDENT ]\n";
    
    int rollNo;
    cout << "Enter Roll No to search: ";
    if (!(cin >> rollNo)) {
        setColor(12);
        cout << "Invalid Roll No!\n";
        setColor(15);
        cin.clear();
        cin.ignore(10000, '\n');
        getch();
        return;
    }
    
    ifstream file("students.txt");
    if (!file) {
        setColor(12);
        cout << "No student records found!\n";
        setColor(15);
        getch();
        return;
    }

    string line;
    bool found = false;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        size_t pos = line.find('|');
        if (pos != string::npos) {
            stringstream ss(line.substr(0, pos));
            int currentRoll;
            if (ss >> currentRoll && currentRoll == rollNo) {
                found = true;
                
                Student s;
                size_t pos1 = pos;
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);
                size_t pos4 = line.find('|', pos3 + 1);
                
                s.rollNo = currentRoll;
                s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                s.className = line.substr(pos2 + 1, pos3 - pos2 - 1);
                
                stringstream ss2(line.substr(pos3 + 1, pos4 - pos3 - 1));
                ss2 >> s.total;
                
                stringstream ss3(line.substr(pos4 + 1));
                ss3 >> s.percentage;
                
                setColor(10);
                cout << "\nStudent Found!\n";
                cout << "Roll No: " << s.rollNo << endl;
                cout << "Name: " << s.name << endl;
                cout << "Class: " << s.className << endl;
                cout << "Total Marks: " << s.total << endl;
                cout << "Percentage: " << fixed << setprecision(2) << s.percentage << "%" << endl;
                cout << "Grade: " << s.grade() << endl;
                setColor(15);
                break;
            }
        }
    }
    file.close();
    
    if (!found) {
        setColor(12);
        cout << "\nStudent with Roll No " << rollNo << " not found!\n";
        setColor(15);
    }
    getch();
}

void deleteStudent() {
    showHeader();
    cout << "\n[ DELETE STUDENT ]\n";
    
    int rollNo;
    cout << "Enter Roll No to delete: ";
    if (!(cin >> rollNo)) {
        setColor(12);
        cout << "Invalid Roll No!\n";
        setColor(15);
        cin.clear();
        cin.ignore(10000, '\n');
        getch();
        return;
    }
    
    ifstream file("students.txt");
    if (!file) {
        setColor(12);
        cout << "No student records found!\n";
        setColor(15);
        getch();
        return;
    }

    ofstream temp("temp.txt");
    if (!temp) {
        setColor(12);
        cout << "Error creating temporary file!\n";
        setColor(15);
        file.close();
        getch();
        return;
    }

    string line;
    bool found = false;
    
    while (getline(file, line)) {
        if (line.empty()) {
            temp << endl;
            continue;
        }
        
        size_t pos = line.find('|');
        if (pos != string::npos) {
            stringstream ss(line.substr(0, pos));
            int currentRoll;
            if (ss >> currentRoll) {
                if (currentRoll != rollNo) {
                    temp << line << endl;
                } else {
                    found = true;
                }
            } else {
                temp << line << endl;
            }
        } else {
            temp << line << endl;
        }
    }
    
    file.close();
    temp.close();
    
    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        setColor(10);
        cout << "\nStudent deleted successfully!\n";
        setColor(15);
    } else {
        remove("temp.txt");
        setColor(12);
        cout << "\nStudent with Roll No " << rollNo << " not found!\n";
        setColor(15);
    }
    getch();
}

// ====== TEACHER FUNCTIONS ======
void addTeacher() {
    showHeader();
    cout << "\n[ ADD TEACHER ]\n";
    
    Teacher t;
    if (t.input()) {
        ofstream file("teachers.txt", ios::app);
        if (!file) {
            setColor(12);
            cout << "\nError: Could not open file for writing!\n";
            setColor(15);
            getch();
            return;
        }
        file << t.id << "|" << t.name << "|" << t.subject << "|" << t.qualification << endl;
        file.close();
        
        setColor(10);
        cout << "\nTeacher Added Successfully!\n";
        setColor(15);
    } else {
        setColor(12);
        cout << "\nFailed to add teacher!\n";
        setColor(15);
    }
    getch();
}

void showTeachers() {
    showHeader();
    cout << "\n[ ALL TEACHERS ]\n";
    
    ifstream file("teachers.txt");
    if (!file) {
        setColor(12);
        cout << "No teacher records found!\n";
        setColor(15);
        getch();
        return;
    }

    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20)
         << "Subject" << setw(20) << "Qualification" << endl;
    cout << "---------------------------------------------------------------\n";

    string line;
    bool hasTeachers = false;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Teacher t;
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            stringstream ss(line.substr(0, pos1));
            ss >> t.id;
            t.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            t.subject = line.substr(pos2 + 1, pos3 - pos2 - 1);
            t.qualification = line.substr(pos3 + 1);
            
            setColor(14);
            t.display();
            setColor(15);
            hasTeachers = true;
        }
    }
    file.close();
    
    if (!hasTeachers) {
        setColor(12);
        cout << "No teachers found in records!\n";
        setColor(15);
    }
    getch();
}

void searchTeacher() {
    showHeader();
    cout << "\n[ SEARCH TEACHER ]\n";
    
    int id;
    cout << "Enter Teacher ID to search: ";
    if (!(cin >> id)) {
        setColor(12);
        cout << "Invalid Teacher ID!\n";
        setColor(15);
        cin.clear();
        cin.ignore(10000, '\n');
        getch();
        return;
    }
    
    ifstream file("teachers.txt");
    if (!file) {
        setColor(12);
        cout << "No teacher records found!\n";
        setColor(15);
        getch();
        return;
    }

    string line;
    bool found = false;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        size_t pos = line.find('|');
        if (pos != string::npos) {
            stringstream ss(line.substr(0, pos));
            int currentId;
            if (ss >> currentId && currentId == id) {
                found = true;
                
                Teacher t;
                size_t pos1 = pos;
                size_t pos2 = line.find('|', pos1 + 1);
                size_t pos3 = line.find('|', pos2 + 1);
                
                t.id = currentId;
                t.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                t.subject = line.substr(pos2 + 1, pos3 - pos2 - 1);
                t.qualification = line.substr(pos3 + 1);
                
                setColor(10);
                cout << "\nTeacher Found!\n";
                cout << "ID: " << t.id << endl;
                cout << "Name: " << t.name << endl;
                cout << "Subject: " << t.subject << endl;
                cout << "Qualification: " << t.qualification << endl;
                setColor(15);
                break;
            }
        }
    }
    file.close();
    
    if (!found) {
        setColor(12);
        cout << "\nTeacher with ID " << id << " not found!\n";
        setColor(15);
    }
    getch();
}

void deleteTeacher() {
    showHeader();
    cout << "\n[ DELETE TEACHER ]\n";
    
    int id;
    cout << "Enter Teacher ID to delete: ";
    if (!(cin >> id)) {
        setColor(12);
        cout << "Invalid Teacher ID!\n";
        setColor(15);
        cin.clear();
        cin.ignore(10000, '\n');
        getch();
        return;
    }
    
    ifstream file("teachers.txt");
    if (!file) {
        setColor(12);
        cout << "No teacher records found!\n";
        setColor(15);
        getch();
        return;
    }

    ofstream temp("temp.txt");
    if (!temp) {
        setColor(12);
        cout << "Error creating temporary file!\n";
        setColor(15);
        file.close();
        getch();
        return;
    }

    string line;
    bool found = false;
    
    while (getline(file, line)) {
        if (line.empty()) {
            temp << endl;
            continue;
        }
        
        size_t pos = line.find('|');
        if (pos != string::npos) {
            stringstream ss(line.substr(0, pos));
            int currentId;
            if (ss >> currentId) {
                if (currentId != id) {
                    temp << line << endl;
                } else {
                    found = true;
                }
            } else {
                temp << line << endl;
            }
        } else {
            temp << line << endl;
        }
    }
    
    file.close();
    temp.close();
    
    if (found) {
        remove("teachers.txt");
        rename("temp.txt", "teachers.txt");
        setColor(10);
        cout << "\nTeacher deleted successfully!\n";
        setColor(15);
    } else {
        remove("temp.txt");
        setColor(12);
        cout << "\nTeacher with ID " << id << " not found!\n";
        setColor(15);
    }
    getch();
}
