// Chapter 7 Exercise 12 - Part 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Programmer:Brenna Meyer
// Date 4/28/2025
//You should use either an Array or a Vector to store the names of students.If you use an Array, be sure it is large enough to store any possible number of students per class (100 should be enough).Collect the names in a loop, and be sure to use some type of sentinel value to end the request for students' names. Use a Parallel array or vector to store each student's numeric grades.Be sure the index of the student's name corresponds to the set of grades stored for each student.
//Validation should ensure all grades entered are positive and less than 101.
//Start the program menu that gives the user the ability to add students, add grades, display student names and grades, and final grades average according to the following chart :
//A: 90 - 100
//B : 80 - 89
//C : 70 - 79
//D : 60 - 69
//F : 0 - 59
//When computing the average drop, the lowest grade the student made.


#include <iostream>
#include<iomanip>
#include <string>
#include <fstream>
using namespace std;

const int maxStudents = 100;
const int maxTests = 4;
const string FILENAME = "TextFile1.txt";

// Function prototypes
int findStudent(const string& name);
void saveData();
void loadData();

//Student Data 
string names[maxStudents];
double grades[maxStudents][maxTests];
int studentCount = 0;

//Vaild input (0-100)
double getValidGrade(const string& prompt) {
    double grade;
    while (true) {
        cout << prompt;
        cin >> grade; 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
        else if (grade < 0 || grade > 100) {
            cout << "Grade must be 0-100. Try again.\n";
        }
        else {
            cin.ignore();
            return grade;
        }
    }
}

// Add students 
void addStudents() {
    cout << "Enter students name press the Enter button to finish.";
    while (studentCount < maxStudents) {
        cout << "Student #" << studentCount + 1 << ": ";
        string name;
        getline(cin, name);

        if (name.empty()) break;

        if (findStudent(name) != -1) {
            cout << "Student already exists!\n";
            continue;
        }

        names[studentCount] = name;
        studentCount++;
    }
    saveData();
}

//add all student grades
void addGrades() {
    if (studentCount == 0) {
        cout << "No students to add grades!\n";
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        cout << "\nEnter grades for " << names[i] << ":\n";
        for (int j = 0; j < maxTests; j++) {
            grades[i][j] = getValidGrade("Test #" + to_string(j + 1) + ": ");
        }
    }
    saveData();
}

// Display all students and their grades
void displayGrades() {
    if (studentCount == 0) {
        cout << "No grades to display.\n";
        return;
    }

    cout << "\nCurrent Grades\n";
    for (int i = 0; i < studentCount; i++) {
        cout << names[i] << ": ";
        for (int j = 0; j < maxTests; j++) {
            cout << grades[i][j] << " ";
        }
        cout << endl;
    }
}

// Calculate average
double calculateAverage(double testScores[]) {
    double sum = 0, lowest = testScores[0];
    for (int i = 1; i < maxTests; i++) {
        if (testScores[i] < lowest) lowest = testScores[i];
    }
    bool dropped = false;
    for (int i = 0; i < maxTests; i++) {
        if (!dropped && testScores[i] == lowest) dropped = true;
        else sum += testScores[i];
    }
    return sum / (maxTests - 1);
}
// Display final averages and letter grades
void displayFinalGrades() {
    if (studentCount == 0) {
        cout << "No grades to calculate.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\nFinal Grades\n";

    for (int i = 0; i < studentCount; i++) {
        double lowest = grades[i][0];
        for (int j = 1; j < maxTests; j++) {
            if (grades[i][j] < lowest) lowest = grades[i][j];
        }
        double sum = 0;
        bool dropped = false;
        for (int j = 0; j < maxTests; j++) {
            if (!dropped && grades[i][j] == lowest) {
                dropped = true;
            }
            else {
                sum += grades[i][j];
            }
        }
        double avg = sum / (maxTests - 1);

        char grade;
        if (avg >= 90) grade = 'A';
        else if (avg >= 80) grade = 'B';
        else if (avg >= 70) grade = 'C';
        else if (avg >= 60) grade = 'D';
        else grade = 'F';

        cout << names[i] << ": " << avg << " (" << grade << ")\n";
    }
}
void searchStudent() {
    if (studentCount == 0) {
        cout << "No students to search!\n";
        return;
    }

    cout << "Enter student name: ";
    string name;
    getline(cin, name);

    int index = findStudent(name);
    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    cout << "\nGrades For " << names[index] << ":\n";
    for (int j = 0; j < maxTests; j++) {
        cout << "Test #" << j + 1 << ": " << grades[index][j] << endl;
    }
}
void modifyGrades() {
    if (studentCount == 0) {
        cout << "No students to modify!\n";
        return;
    }

    cout << "Enter student name: ";
    string name;
    getline(cin, name);

    int index = findStudent(name);
    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    cout << "\nCurrent Grades For " << names[index] << ":\n";
    for (int j = 0; j < maxTests; j++) {
        cout << "Test #" << j + 1 << ": " << grades[index][j] << endl;
    }

    cout << "\n1. Change all grades\n"
        << "2. Change one grade\n"
        << "3. Cancel\n"
        << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        for (int j = 0; j < maxTests; j++) {
            grades[index][j] = getValidGrade("New grade for Test #" + to_string(j + 1) + ": ");
        }
        saveData();
    }
    else if (choice == 2) {
        cout << "Enter test number (1-" << maxTests << "): ";
        int testNum;
        cin >> testNum;
        cin.ignore();

        if (testNum < 1 || testNum > maxTests) {
            cout << "Invalid test number!\n";
        }
        else {
            grades[index][testNum - 1] = getValidGrade("New grade: ");
            saveData();
        }
    }
}
void saveData() {
    ofstream file(FILENAME);
    if (!file) {
        cout << "Error saving data to file!\n";
        return;
    }

    file << studentCount << endl;
    for (int i = 0; i < studentCount; i++) {
        file << names[i] << endl;
        for (int j = 0; j < maxTests; j++) {
            file << grades[i][j] << " ";
        }
        file << endl;
    }
}

int findStudent(const string& name) {
    for (int i = 0; i < studentCount; i++) {
        if (names[i] == name) return i;
    }
    return -1;
}

void loadData() {
    ifstream file(FILENAME);
    if (!file) {
        cout << "No existing data file found. Starting fresh.\n";
        return;
    }

    file >> studentCount;
    file.ignore();

    for (int i = 0; i < studentCount; i++) {
        getline(file, names[i]);
        for (int j = 0; j < maxTests; j++) {
            file >> grades[i][j];
        }
        file.ignore();
    }

    cout << "Loaded data for " << studentCount << " students.\n";
}

// Main menu
int main() {
    loadData();

    int choice;
    do {
        cout << "\nGrade Book Menu\n"
            << "1. Add Students\n"
            << "2. Add Grades\n"
            << "3. View All Grades\n"
            << "4. View Final Grades\n"
            << "5. Search Student\n"
            << "6. Modify Grades\n"
            << "7. Exit\n"
            << "Enter choice (1-7): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addStudents(); break;
        case 2: addGrades(); break;
        case 3: displayGrades(); break;
        case 4: displayFinalGrades(); break;
        case 5: searchStudent(); break;
        case 6: modifyGrades(); break;
        case 7:
            saveData();
            cout << "Exiting program.\n";
            break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}
