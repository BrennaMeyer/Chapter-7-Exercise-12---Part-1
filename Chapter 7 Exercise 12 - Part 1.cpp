// Chapter 7 Exercise 12 - Part 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Programmer:Brenna Meyer
// Date 4/27/2025
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
using namespace std;

const int maxStudents = 100;
const int maxTests = 4;

//Student Data 
string names[maxStudents];
double grades[maxStudents][maxTests];
int studentCount = 0;

//Vaild input (0-100)
double getVaildGrade(const string& prompt) {
    double grade;
    while (true) {
        cout << prompt;
        cin >> grade; 
        if (grade >= 0 && grade <= 100) return grade;
        cout << "Error, enter grade 0-100.\n";
    }
}
// Add students 
void addStudents() {
    cin.ignore();
    cout << "Enter students name press the Enter button to finish.";
        while (studentCount < maxStudents) {
            cout << "Student #" << studentCount + 1 << ":";
            getline(cin, names[studentCount]);
            if (names[studentCount].empty()) break;
            studentCount++;
        }
}
//add all student grades
void addGrades() {
    for (int i = 0; i < studentCount;i++) {
        cout << "Enter Grades for" << names[i] << ":\n";
        for (int j = 0; j < maxTests;j++) {
            grades[i][j] = getVaildGrade("Test #" + to_string(j + 1) + ":");
        }
    }
}
// Display all students and their grades
void displayGrades() {
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
    cout << fixed << setprecision(2);
    cout << "\nFinal Grades\n";
    for (int i = 0; i < studentCount; i++) {
        double avg = calculateAverage(grades[i]);
        char letter = (avg >= 90) ? 'A' :
            (avg >= 80) ? 'B' :
            (avg >= 70) ? 'C' :
            (avg >= 60) ? 'D' : 'F';
        cout << names[i] << ": " << avg << " (" << letter << ")\n";
    }
}
// Main menu
int main() {
    int choice;
    do {
        cout << "\nGrade Book Menu\n"
            << "1. Add Students\n"
            << "2. Add Grades\n"
            << "3. View Grades\n"
            << "4. View Final Grades\n"
            << "5. Exit\n"
            << "Enter choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1: addStudents(); break;
        case 2: if (studentCount > 0) addGrades();
              else cout << "No students added yet!\n"; break;
        case 3: if (studentCount > 0) displayGrades();
              else cout << "No data to display!\n"; break;
        case 4: if (studentCount > 0) displayFinalGrades();
              else cout << "No data to calculate!\n"; break;
        case 5: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}