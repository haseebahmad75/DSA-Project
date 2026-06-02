#pragma once
#include"../data_structures/DynamicArray.hpp"
#include"../utils/FileManager.hpp"
#include"../models/Student.hpp"
using namespace std;

class StudentManager
{
    private:
    DynamicArray<Student> studentRecords;
    const string fileName = "D:/Smart University System/students.txt";

    public:
    void initSystem()
    {
        FileManager::loadStudents(fileName,studentRecords);
    }

    void addStudent(int rollNo, string name, string dept, float cgpa)
    {
        Student s = {rollNo,name,dept,cgpa};
        studentRecords.push_back(s);
    }

    void saveSystemState()
    {
        FileManager::saveStudents(fileName, studentRecords);
    }
};