#include <iostream>
#include <fstream>
#include <string>



using namespace std;



// Maximum number of students
const int MAX_STUDENTS = 100;



// Student structure
struct Student {
    int reg;
    string name;
    int attendanceCount;

    // Constructor for initialization
    Student() : reg(0), name(""), attendanceCount(0) {}
};



// Global variables
// Array of students
Student students[MAX_STUDENTS]; 
// Number of students currently in the system
int studentCount = 0;          



// Function to display menu
void displayMenu() {
    cout << "\nStudent Attendance Management System\n";
    cout << "1. Add Student\n";
    cout << "2. Mark Attendance\n";
    cout << "3. View Attendance\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}



// Function to ignore string in int input
int regInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a valid Reg number: ";
    }
    return value;
}



// Function to add a new student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Cannot add more students. Limit reached!\n";
        return;
    }

    int reg;
    string name;
    cout << "Enter Student Reg Number: ";
    cin >> reg;
    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, name);

    students[studentCount].reg = reg;
    students[studentCount].name = name;
    students[studentCount].attendanceCount = 0;

    studentCount++;
    cout << "Student added successfully!\n";
}



// Function to mark attendance by ID
void markAttendance(int reg) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].reg == reg) {
            students[i].attendanceCount++;
            cout << "Attendance marked for: " << students[i].name << "\n";
            return;
        }
    }
    cout << "Student with reg " << reg << " not found!\n";
}



// Function to mark attendance by Name
void markAttendance(string name) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].name == name) {
            students[i].attendanceCount++;
            cout << "Attendance marked for: " << students[i].name << "\n";
            return;
        }
    }
    cout << "Student with name \"" << name << "\" not found!\n";
}




// Recursive function to view attendance
void viewAttendance(int index = 0) {
    if (studentCount == 0) {
        cout << "No students in the system.\n";
        return;
    }

    if (index< studentCount) {
        cout<< "REG: " << students[index].reg<<endl;
        cout<< ", Name: " << students[index].name<<endl;
        cout<< ", Attendance: " << students[index].attendanceCount << " days\n";
        viewAttendance(index + 1);
    }
}



// Function to save attendance to a file
void saveAttendanceToFile() {
    ofstream outFile("attendance.txt");
    for (int i = 0; i < studentCount; i++) {
        outFile << students[i].reg << "|" << students[i].name << "|" << students[i].attendanceCount << "\n";
    }
    outFile.close();
}



// Function to load attendance from a file
void loadAttendanceFromFile() {
    ifstream inFile("attendance.txt");
    if (!inFile) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    while (inFile >> students[studentCount].reg) {
        inFile.ignore(); // Ignore delimiter
        getline(inFile, students[studentCount].name, '|');
        inFile >> students[studentCount].attendanceCount;
        studentCount++;
    }
    inFile.close();
}




int main(){
    loadAttendanceFromFile();
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;


            case 2: {
                cout << "Mark attendance by Reg (1) or Name (2): ";
                int option;
                cin >> option;
                if (option == 1) {
                    int reg;
                    cout << "Enter Student Reg: ";
                    reg = regInt(); // Here is where regInt is called
                    markAttendance(reg);
                }
                 else {
                    string name;
                    cout << "Enter Student Name: ";
                    cin.ignore();
                    getline(cin, name);
                    markAttendance(name);
                }
                break;
            }


            case 3:
                viewAttendance();
                break;


            case 4:
                saveAttendanceToFile();
                cout << "Data saved. Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }


    } while (choice != 4);


    return 0;
}