#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

// Structure to store student details and marks
struct Student {
    string name;
    int rollNumber;
    int biology;
    int physics;
    int chemistry;
    int totalMarks;
    int schoolRank;
    int classRank;
};

// Function to calculate the total marks of a student
int calculateTotalMarks(const Student& student) {
    return student.biology + student.physics + student.chemistry;
}

// Function to compare two students based on total marks (for sorting)
bool compareStudents(const Student& student1, const Student& student2) {
    return student1.totalMarks > student2.totalMarks;
}

// Function to calculate ranks for all students
void calculateRanks(vector<Student>& students) {
    sort(students.begin(), students.end(), compareStudents);

    int rank = 1;
    for (int i = 0; i < students.size(); i++) {
        students[i].schoolRank = rank;

        if (i > 0 && students[i].totalMarks < students[i - 1].totalMarks)
            rank = i + 1;

        students[i].classRank = (rank - 1) / 40 + 1;
    }
}

// Function to print student ranks to console
void printRanks(const vector<Student>& students) {
    cout << "School Ranks:" << endl;
    for (const Student& student : students) {
        cout << "Student Name: " << student.name << endl;
        cout << "School Rank: " << student.schoolRank << endl;
        cout << "Class Rank: " << student.classRank << endl;
        cout << "---------------------------------------" << endl;
    }
}

// Function to write student ranks to a file
void writeRanksToFile(const vector<Student>& students, const string& fileName) {
    ofstream outputFile(fileName);

    if (outputFile.is_open()) {
        for (const Student& student : students) {
            outputFile << "Student Name: " << student.name << endl;
            outputFile << "School Rank: " << student.schoolRank << endl;
            outputFile << "Class Rank: " << student.classRank << endl;
            outputFile << "---------------------------------------" << endl;
        }

        outputFile.close();
        cout << "Ranks have been written to the file successfully." << endl;
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
}

int main() {
    // Read student marks from a file
    ifstream inputFile("student_marks.txt");

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }

    vector<Student> students;

    while (!inputFile.eof()) {
        Student student;
        inputFile >> student.name >> student.rollNumber >> student.biology >> student.physics >> student.chemistry;

        student.totalMarks = calculateTotalMarks(student);
        students.push_back(student);
    }

    inputFile.close();

    // Calculate ranks
    calculateRanks(students);

    // Print ranks to console
    printRanks(students);

    // Write ranks to a file
    writeRanksToFile(students, "student_ranks.txt");

    return 0;
}
