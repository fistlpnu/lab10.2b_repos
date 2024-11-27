#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


enum Specialization { COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS, PHYSICS_INFORMATICS, LABOR_EDUCATION };


struct Student {
    string surname;
    int course;
    Specialization specialization;
    int physicsGrade;
    int mathGrade;
    union {
        int programmingGrade;
        int numericMethodsGrade;
        int pedagogyGrade;
    };
};


void inputStudents(Student students[], int numStudents);
void displayStudentsTable(Student students[], int numStudents);
void sortStudents(Student students[], int numStudents);
void createIndexArray(int indexArray[], int numStudents);
int binarySearch(Student students[], int indexArray[], int numStudents, string surname, int course, Specialization specialization);
void showMenu(Student students[], int& numStudents);
int getValidIntInput(string prompt, int min, int max);

int main() {
    int numStudents;
    cout << "Enter the number of students: ";
    numStudents = getValidIntInput("", 1, 100);

    Student students[100];
    showMenu(students, numStudents);
    return 0;
}

void inputStudents(Student students[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        cout << "\nEntering data for student #" << (i + 1) << ":\n";

        cout << "Surname: ";
        cin >> students[i].surname;

        students[i].course = getValidIntInput("Course (1-5): ", 1, 5);

        cout << "Specialization (0 - Comp. Sci., 1 - Informatics, 2 - Math & Econ, 3 - Physics & Info, 4 - Labor Ed.): ";
        int spec;
        spec = getValidIntInput("", 0, 4);


        if (spec == 0) students[i].specialization = COMPUTER_SCIENCE;
        else if (spec == 1) students[i].specialization = INFORMATICS;
        else if (spec == 2) students[i].specialization = MATH_ECONOMICS;
        else if (spec == 3) students[i].specialization = PHYSICS_INFORMATICS;
        else students[i].specialization = LABOR_EDUCATION;

        students[i].physicsGrade = getValidIntInput("Physics grade (0-5): ", 0, 5);
        students[i].mathGrade = getValidIntInput("Math grade (0-5): ", 0, 5);


        if (students[i].specialization == COMPUTER_SCIENCE) {
            students[i].programmingGrade = getValidIntInput("Programming grade (0-5): ", 0, 5);
        }
        else if (students[i].specialization == INFORMATICS) {
            students[i].numericMethodsGrade = getValidIntInput("Numeric Methods grade (0-5): ", 0, 5);
        }
        else {
            students[i].pedagogyGrade = getValidIntInput("Pedagogy grade (0-5): ", 0, 5);
        }
    }
}

void displayStudentsTable(Student students[], int numStudents) {
    cout << "\n" << setw(5) << "No" << setw(15) << "Surname" << setw(8) << "Course"
        << setw(15) << "Specialization" << setw(10) << "Physics" << setw(10) << "Math"
        << setw(15) << "Subject\n";
    cout << string(80, '-') << endl;

    for (int i = 0; i < numStudents; i++) {
        cout << setw(5) << (i + 1)
            << setw(15) << students[i].surname
            << setw(8) << students[i].course;

        
        if (students[i].specialization == COMPUTER_SCIENCE) cout << setw(15) << "Comp. Sci.";
        else if (students[i].specialization == INFORMATICS) cout << setw(15) << "Informatics";
        else if (students[i].specialization == MATH_ECONOMICS) cout << setw(15) << "Math & Econ";
        else if (students[i].specialization == PHYSICS_INFORMATICS) cout << setw(15) << "Physics & Info";
        else cout << setw(15) << "Labor Ed.";

        cout << setw(10) << students[i].physicsGrade
            << setw(10) << students[i].mathGrade;

        
        if (students[i].specialization == COMPUTER_SCIENCE) {
            cout << setw(15) << students[i].programmingGrade;
        }
        else if (students[i].specialization == INFORMATICS) {
            cout << setw(15) << students[i].numericMethodsGrade;
        }
        else {
            cout << setw(15) << students[i].pedagogyGrade;
        }
        cout << endl;
    }
}

void sortStudents(Student students[], int numStudents) {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = i + 1; j < numStudents; j++) {
            
            if (students[i].course > students[j].course ||
                (students[i].course == students[j].course && students[i].specialization > students[j].specialization) ||
                (students[i].course == students[j].course && students[i].specialization == students[j].specialization && students[i].surname < students[j].surname)) {
                swap(students[i], students[j]);
            }
        }
    }
}

void showMenu(Student students[], int& numStudents) {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Input student data\n";
        cout << "2. Display students table\n";
        cout << "3. Sort students\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        choice = getValidIntInput("", 0, 3);

        switch (choice) {
        case 1:
            inputStudents(students, numStudents);
            break;
        case 2:
            displayStudentsTable(students, numStudents);
            break;
        case 3:
            sortStudents(students, numStudents);
            cout << "Students sorted.\n";
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);
}


int getValidIntInput(string prompt, int min, int max) {
    int input;
    while (true) {
        if (!prompt.empty()) cout << prompt;
        cin >> input;

        if (cin.fail() || input < min || input > max) {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
        }
        else {
            cin.ignore(10000, '\n');
            return input;
        }
    }
}