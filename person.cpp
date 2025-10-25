#include "person.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <numeric>

using namespace std;

// Default constructor
Person::Person() : firstName(""), lastName(""), examGrade(0), finalGrade(0.0) {}

// Parameterized constructor
Person::Person(const string& first, const string& last) 
    : firstName(first), lastName(last), examGrade(0), finalGrade(0.0) {}

// Getters
string Person::getFirstName() const { return firstName; }
string Person::getLastName() const { return lastName; }
vector<int> Person::getHomeworkGrades() const { return homeworkGrades; }
int Person::getExamGrade() const { return examGrade; }
double Person::getFinalGrade() const { return finalGrade; }

// Setters
void Person::setFirstName(const string& first) { firstName = first; }
void Person::setLastName(const string& last) { lastName = last; }

void Person::setHomeworkGrades(const vector<int>& grades) {
    homeworkGrades = grades;
}

void Person::setExamGrade(int grade) {
    examGrade = grade;
}

// Calculation methods
void Person::calculateFinalGrade(bool useMedian) {
    if (homeworkGrades.empty()) {
        finalGrade = examGrade;
        return;
    }

    double homeworkScore;
    if (useMedian) {
        vector<int> sortedGrades = homeworkGrades;
        sort(sortedGrades.begin(), sortedGrades.end());
        size_t size = sortedGrades.size();
        if (size % 2 == 0) {
            homeworkScore = (sortedGrades[size/2 - 1] + sortedGrades[size/2]) / 2.0;
        } else {
            homeworkScore = sortedGrades[size/2];
        }
    } else {
        double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0.0);
        homeworkScore = sum / homeworkGrades.size();
    }

    finalGrade = homeworkScore * 0.4 + examGrade * 0.6;
    finalGrade = round(finalGrade * 100) / 100;
}

double Person::calculateFinalGradeAverage() const {
    if (homeworkGrades.empty()) return examGrade;
    double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0.0);
    double homeworkAvg = sum / homeworkGrades.size();
    return round((homeworkAvg * 0.4 + examGrade * 0.6) * 100) / 100;
}

double Person::calculateFinalGradeMedian() const {
    if (homeworkGrades.empty()) return examGrade;
    vector<int> sortedGrades = homeworkGrades;
    sort(sortedGrades.begin(), sortedGrades.end());
    size_t size = sortedGrades.size();
    double homeworkMed;
    if (size % 2 == 0) {
        homeworkMed = (sortedGrades[size/2 - 1] + sortedGrades[size/2]) / 2.0;
    } else {
        homeworkMed = sortedGrades[size/2];
    }
    return round((homeworkMed * 0.4 + examGrade * 0.6) * 100) / 100;
}

// Input overload
istream& operator>>(istream& is, Person& person) {
    cout << "Enter first name: ";
    is >> person.firstName;
    cout << "Enter last name: ";
    is >> person.lastName;
    
    cout << "Enter homework grades (enter -1 to finish): ";
    vector<int> homework;
    int grade;
    while (is >> grade && grade != -1) {
        homework.push_back(grade);
    }
    person.setHomeworkGrades(homework);
    
    cout << "Enter exam grade: ";
    is >> person.examGrade;
    
    return is;
}

// Output overload
ostream& operator<<(ostream& os, const Person& person) {
    os << "Name: " << person.firstName << " " << person.lastName << endl;
    os << "Homework grades: ";
    for (int grade : person.homeworkGrades) {
        os << grade << " ";
    }
    os << endl << "Exam grade: " << person.examGrade;
    os << endl << "Final grade: " << fixed << setprecision(2) << person.finalGrade;
    return os;
}

// Random score generation
void Person::generateRandomScores(int homeworkCount) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> gradeDist(1, 10);
    
    homeworkGrades.clear();
    for (int i = 0; i < homeworkCount; ++i) {
        homeworkGrades.push_back(gradeDist(generator));
    }
    
    examGrade = gradeDist(generator);
}

// Comparison function
bool Person::compareByName(const Person& a, const Person& b) {
    if (a.lastName != b.lastName) {
        return a.lastName < b.lastName;
    }
    return a.firstName < b.firstName;
}