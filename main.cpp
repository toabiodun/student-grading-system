#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
#include "person.h"

using namespace std;

void displayMenu() {
    cout << "\n=== Student Grading System ===" << endl;
    cout << "1. Enter students manually" << endl;
    cout << "2. Generate random students" << endl;
    cout << "3. Read from file" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose option: ";
}

void manualInput(vector<Person>& students, bool useMedian) {
    char choice;
    do {
        Person student;
        cin >> student;
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
        
        cout << "Add another student? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void generateRandomStudents(vector<Person>& students, bool useMedian) {
    vector<string> firstNames = {"John", "Jane", "Bob", "Alice", "Charlie", "Diana"};
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia"};
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> nameDist(0, firstNames.size() - 1);
    uniform_int_distribution<int> countDist(3, 10);
    
    int numStudents = countDist(generator);
    
    for (int i = 0; i < numStudents; ++i) {
        Person student(firstNames[nameDist(generator)], lastNames[nameDist(generator)]);
        student.generateRandomScores(5); // 5 homework assignments
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
    }
    
    cout << "Generated " << numStudents << " random students." << endl;
}

bool readFromFile(vector<Person>& students, bool useMedian) {
    ifstream file("Students.txt");
    if (!file) {
        cout << "Error: Cannot open Students.txt" << endl;
        return false;
    }
    
    // Skip header
    string header;
    getline(file, header);
    
    string firstName, lastName;
    int hw, exam;
    
    while (file >> firstName >> lastName) {
        Person student(firstName, lastName);
        vector<int> homework;
        
        for (int i = 0; i < 5; ++i) {
            file >> hw;
            homework.push_back(hw);
        }
        
        file >> exam;
        
        // In real implementation, you'd set homework scores
        student.calculateFinalGrade(useMedian);
        students.push_back(student);
    }
    
    file.close();
    return true;
}

void displayResults(const vector<Person>& students, bool useMedian) {
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
}

int main() {
    vector<Person> students;
    bool useMedian = false;
    char medianChoice;
    
    cout << "Use median for calculations? (y/n): ";
    cin >> medianChoice;
    useMedian = (medianChoice == 'y' || medianChoice == 'Y');
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                manualInput(students, useMedian);
                break;
            case 2:
                generateRandomStudents(students, useMedian);
                break;
            case 3:
                if (readFromFile(students, useMedian)) {
                    cout << "Data loaded successfully from Students.txt" << endl;
                }
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        
        if (choice >= 1 && choice <= 3 && !students.empty()) {
            // Sort students by name
            sort(students.begin(), students.end(), Person::compareByName);
            displayResults(students, useMedian);
        }
        
    } while (choice != 4);
    
    return 0;
}
