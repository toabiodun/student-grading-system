#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::vector<int> homeworkGrades;
    int examGrade;
    double finalGrade;

public:
    // Constructors
    Person();
    Person(const std::string& first, const std::string& last);
    
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
    
    // Utility methods
    void generateRandomScores(int homeworkCount);
    static bool compareByName(const Person& a, const Person& b);
    
    // Input/Output
    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

#endif