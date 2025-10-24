#include "person.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <numeric>

using namespace std;

// Default constructor - FIXED variable names
Person::Person() : firstName(""), lastName(""), examGrade(0), finalGrade(0.0) {}

// Parameterized constructor - FIXED variable names
Person::Person(const string& first, const string& last) 
    : firstName(first), lastName(last), examGrade(0), finalGrade(0.0) {}

// Copy constructor - FIXED variable names
Person::Person(const Person& other) 
    : firstName(other.firstName), lastName(other.lastName),
      homeworkGrades(other.homeworkGrades), examGrade(other.examGrade),
      finalGrade(other.finalGrade) {}

// Destructor
Person::~Person() {
    // Vector will automatically clean up
}

// Assignment operator - FIXED variable names
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homeworkGrades = other.homeworkGrades;
        examGrade = other.examGrade;
        finalGrade = other.finalGrade;
    }
    return *this;
}

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
    for (int grade : grades) {
        if (!isValidGrade(grade)) {
            throw invalid_argument("Invalid homework grade: " + to_string(grade));
        }
    }
    homeworkGrades = grades;
}

void Person::setExamGrade(int grade) {
    if (!isValidGrade(grade)) {
        throw invalid_argument("Invalid exam grade: " + to_string(grade));
    }
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
        homeworkScore = calculateMedian();
    } else {
        homeworkScore = calculateAverage();
    }

    finalGrade = homeworkScore * 0.4 + examGrade * 0.6;
    finalGrade = round(finalGrade * 100) / 100;
}

double Person::calculateFinalGradeAverage() const {
    if (homeworkGrades.empty()) return examGrade;
    double homeworkAvg = calculateAverage();
    return round((homeworkAvg * 0.4 + examGrade * 0.6) * 100) / 100;
}

double Person::calculateFinalGradeMedian() const {
    if (homeworkGrades.empty()) return examGrade;
    double homeworkMed = calculateMedian();
    return round((homeworkMed * 0.4 + examGrade * 0.6) * 100) / 100;
}

// Helper calculation methods
double Person::calculateAverage() const {
    if (homeworkGrades.empty()) return 0.0;
    double sum = accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0.0);
    return sum / homeworkGrades.size();
}

double Person::calculateMedian() const {
    if (homeworkGrades.empty()) return 0.0;
    
    vector<int> sortedGrades = homeworkGrades;
    sort(sortedGrades.begin(), sortedGrades.end());
    
    size_t size = sortedGrades.size();
    if (size % 2 == 0) {
        return (sortedGrades[size/2 - 1] + sortedGrades[size/2]) / 2.0;
    } else {
        return sortedGrades[size/2];
    }
}

// Input overload - FIXED variable names
istream& operator>>(istream& is, Person& person) {
    cout << "Enter first name: ";
    is >> person.firstName;
    cout << "Enter last name: ";
    is >> person.lastName;
    
    cout << "Enter homework grades (enter -1 to finish): ";
    vector<int> homework;
    int grade;
    while (is >> grade && grade != -1) {
        if (person.isValidGrade(grade)) {
            homework.push_back(grade);
        } else {
            cout << "Invalid grade! Enter grade between 0-10: ";
        }
    }
    person.setHomeworkGrades(homework);
    
    cout << "Enter exam grade: ";
    int exam;
    while (is >> exam) {
        if (person.isValidGrade(exam)) {
            person.setExamGrade(exam);
            break;
        } else {
            cout << "Invalid grade! Enter grade between 0-10: ";
        }
    }
    
    return is;
}

// Output overload - FIXED variable names
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

// Random score generation - FIXED parameters
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

// Validation
bool Person::isValidGrade(int grade) const {
    return grade >= 0 && grade <= 10;
}