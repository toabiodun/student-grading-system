#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
#include "person.h"

using namespace std;

// FUNCTION PROTOTYPES
void displayMenu();
void manualInput(vector<Person>& students, bool useMedian);
void generateRandomStudents(vector<Person>& students, bool useMedian);
bool readFromFile(vector<Person>& students, bool useMedian);
void displayResults(const vector<Person>& students);

void displayMenu() {
    cout << "\n=== Student Grading System ===" << endl;
    cout << "1. Enter students manually" << endl;
    cout << "2. Generate random students" << endl;
    cout << "3. Read from file" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose option: ";
}

void manualInput(vector<Person>& students, bool useMedian) {
    cout << "=== MANUAL INPUT MODE ===" << endl;
    char choice;
    int studentCount = 0;
    
    do {
        Person student;
        cout << "Enter student " << studentCount + 1 << " data (FirstName LastName): ";
        cin >> student;
        student.generateRandomScores(5);
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
        studentCount++;
        
        cout << "SUCCESS: Student " << student.getFirstName() << " " << student.getLastName() << " added!" << endl;
        
        cout << "Add another student? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');
    
    cout << "COMPLETED: Manual input finished. Total students: " << studentCount << endl;
}

void generateRandomStudents(vector<Person>& students, bool useMedian) {
    cout << "=== GENERATING RANDOM STUDENTS ===" << endl;
    vector<string> firstNames = {"John", "Jane", "Bob", "Alice", "Charlie", "Diana"};
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia"};
    
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(static_cast<unsigned int>(seed));
    
    uniform_int_distribution<int> nameDist(0, static_cast<int>(firstNames.size() - 1));
    uniform_int_distribution<int> countDist(3, 10);
    
    int numStudents = countDist(generator);
    
    cout << "Generating " << numStudents << " random students..." << endl;
    
    for (int i = 0; i < numStudents; ++i) {
        Person student(firstNames[nameDist(generator)], lastNames[nameDist(generator)]);
        student.generateRandomScores(5);
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
    }
    
    cout << "SUCCESS: Generated " << numStudents << " random students!" << endl;
}

bool readFromFile(vector<Person>& students, bool useMedian) {
    cout << "=== READING FROM FILE ===" << endl;
    ifstream file("Students.txt");
    if (!file) {
        cout << "ERROR: Cannot open Students.txt - File not found!" << endl;
        return false;
    }
    
    string header;
    getline(file, header);
    
    string firstName, lastName;
    int hw, exam;
    int loadedCount = 0;
    
    cout << "Loading student data from file..." << endl;
    
    while (file >> firstName >> lastName) {
        Person student(firstName, lastName);
        vector<int> homework;
        
        for (int i = 0; i < 5; ++i) {
            file >> hw;
            homework.push_back(hw);
        }
        
        file >> exam;
        
        student.setHomeworkGrades(homework);
        student.setExamGrade(exam);
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
        loadedCount++;
    }
    
    file.close();
    
    cout << "SUCCESS: File loaded! Loaded " << loadedCount << " students." << endl;
    return true;
}

void displayResults(const vector<Person>& students) {
    cout << "\n=== DISPLAYING RESULTS ===" << endl;
    cout << "Showing grades for " << students.size() << " students:" << endl;
    cout << "\nName            Surname         Final (Avg.) | Final (Med.)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    
    for (const auto& student : students) {
        double avgGrade = student.calculateFinalGradeAverage();
        double medGrade = student.calculateFinalGradeMedian();
        
        cout << left << setw(15) << student.getFirstName() 
             << setw(15) << student.getLastName()
             << fixed << setprecision(2)
             << setw(12) << avgGrade << " | "
             << setw(12) << medGrade << endl;
    }
    
    cout << "SUCCESS: Results displayed!" << endl;
}

int main() {
    vector<Person> students;
    bool useMedian = false;
    char medianChoice;
    
    // POSITIVE STARTUP MESSAGES
    cout << "===========================================" << endl;
    cout << "  STUDENT GRADING SYSTEM - READY" << endl;
    cout << "  Program compiled and running successfully!" << endl;
    cout << "===========================================" << endl << endl;
    
    cout << "Use median for final grade calculations? (y/n): ";
    cin >> medianChoice;
    
    // Clear the input buffer
    cin.ignore(1000, '\n');
    
    useMedian = (medianChoice == 'y' || medianChoice == 'Y');
    
    cout << "Calculation method: " << (useMedian ? "MEDIAN" : "AVERAGE") << endl << endl;
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        // Clear the input buffer after reading choice
        cin.ignore(1000, '\n');
        
        switch (choice) {
            case 1:
                manualInput(students, useMedian);
                break;
            case 2:
                generateRandomStudents(students, useMedian);
                break;
            case 3:
                if (readFromFile(students, useMedian)) {
                    cout << "SUCCESS: Data loaded from Students.txt" << endl;
                } else {
                    cout << "ERROR: Failed to load data from file." << endl;
                }
                break;
            case 4:
                cout << "Thank you for using Student Grading System!" << endl;
                cout << "Program completed successfully. Goodbye!" << endl;
                break;
            default:
                cout << "ERROR: Invalid choice! Please enter 1-4." << endl;
        }
        
        if (choice >= 1 && choice <= 3 && !students.empty()) {
            cout << "Sorting students by name..." << endl;
            sort(students.begin(), students.end(), Person::compareByName);
            displayResults(students);
        }
        
        cout << endl;
        
    } while (choice != 4);
    
    return 0;
}