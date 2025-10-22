#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<int> homework;
    int exam;
    double finalGrade;

public:
    // Constructors
    Person();
    Person(const std::string& first, const std::string& last);
    
    // Rule of Three
    Person(const Person& other); // Copy constructor
    Person& operator=(const Person& other); // Copy assignment operator
    ~Person(); // Destructor
    
    // Input/Output methods
    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    
    // Calculation methods
    double calculateFinalGradeAverage() const;
    double calculateFinalGradeMedian() const;
    void calculateFinalGrade(bool useMedian = false);
    
    // Random generation
    void generateRandomScores(int numHomework, int minScore = 0, int maxScore = 10);
    
    // Getters
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    double getFinalGrade() const { return finalGrade; }
    
    // Setters
    void setFinalGrade(double grade) { finalGrade = grade; }
    
    // Sorting
    static bool compareByName(const Person& a, const Person& b);
};

#endif
