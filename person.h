#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<int> homeworkGrades;  // Changed from 'homework'
    int examGrade;                    // Changed from 'exam'
    double finalGrade;

public:
    // Constructors (Rule of Three)
    Person();
    Person(const std::string& first, const std::string& last);
    Person(const Person& other);
    ~Person();
    
    // Assignment operator
    Person& operator=(const Person& other);
    
    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::vector<int> getHomeworkGrades() const;
    int getExamGrade() const;
    double getFinalGrade() const;
    
    // Setters
    void setFirstName(const std::string& first);
    void setLastName(const std::string& last);
    void setHomeworkGrades(const std::vector<int>& grades);
    void setExamGrade(int grade);
    
    // Calculation methods
    void calculateFinalGrade(bool useMedian);
    double calculateFinalGradeAverage() const;
    double calculateFinalGradeMedian() const;
    
    // Input/Output overloads
    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    
    // Utility methods
    void generateRandomScores(int homeworkCount);
    static bool compareByName(const Person& a, const Person& b);
    
    // Helper methods
    double calculateAverage() const;
    double calculateMedian() const;
    bool isValidGrade(int grade) const;
};

#endif