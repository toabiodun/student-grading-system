#include "person.h"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

// Constructor
Person::Person() : firstName(""), lastName(""), exam(0), finalGrade(0.0) {}

Person::Person(const string& first, const string& last) 
    : firstName(first), lastName(last), exam(0), finalGrade(0.0) {}

// Copy constructor
Person::Person(const Person& other) {
    firstName = other.firstName;
    lastName = other.lastName;
    homework = other.homework;
    exam = other.exam;
    finalGrade = other.finalGrade;
}

// Copy assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        homework = other.homework;
        exam = other.exam;
        finalGrade = other.finalGrade;
    }
    return *this;
}

// Destructor
Person::~Person() {
    // Vector will automatically clean up
}

// Input operator
istream& operator>>(istream& is, Person& person) {
    cout << "Enter first name: ";
    is >> person.firstName;
    cout << "Enter last name: ";
    is >> person.lastName;
    
    cout << "Enter homework scores (enter -1 to finish): ";
    person.homework.clear();
    int score;
    while (is >> score && score != -1) {
        if (score >= 0 && score <= 10) {
            person.homework.push_back(score);
        }
        cout << "Enter next homework score (-1 to finish): ";
    }
    
    cout << "Enter exam score: ";
    is >> person.exam;
    
    return is;
}

// Output operator
ostream& operator<<(ostream& os, const Person& person) {
    os << left << setw(15) << person.firstName 
       << setw(15) << person.lastName 
       << fixed << setprecision(2) << person.finalGrade;
    return os;
}

// Calculate final grade using average
double Person::calculateFinalGradeAverage() const {
    if (homework.empty()) return exam * 0.6;
    
    double hwAverage = accumulate(homework.begin(), homework.end(), 0.0) / homework.size();
    return 0.4 * hwAverage + 0.6 * exam;
}

// Calculate final grade using median
double Person::calculateFinalGradeMedian() const {
    if (homework.empty()) return exam * 0.6;
    
    vector<int> sortedHomework = homework;
    sort(sortedHomework.begin(), sortedHomework.end());
    
    double hwMedian;
    size_t size = sortedHomework.size();
    if (size % 2 == 0) {
        hwMedian = (sortedHomework[size/2 - 1] + sortedHomework[size/2]) / 2.0;
    } else {
        hwMedian = sortedHomework[size/2];
    }
    
    return 0.4 * hwMedian + 0.6 * exam;
}

// Calculate final grade based on user choice
void Person::calculateFinalGrade(bool useMedian) {
    if (useMedian) {
        finalGrade = calculateFinalGradeMedian();
    } else {
        finalGrade = calculateFinalGradeAverage();
    }
}

// Generate random scores
void Person::generateRandomScores(int numHomework, int minScore, int maxScore) {
    homework.clear();
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(minScore, maxScore);
    
    for (int i = 0; i < numHomework; ++i) {
        homework.push_back(distribution(generator));
    }
    
    exam = distribution(generator);
}

// Compare by name for sorting
bool Person::compareByName(const Person& a, const Person& b) {
    if (a.lastName == b.lastName) {
        return a.firstName < b.firstName;
    }
    return a.lastName < b.lastName;
}
