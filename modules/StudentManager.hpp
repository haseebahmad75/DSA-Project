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
    void InitSystem()
    {
        FileManager::LoadStudents(fileName,studentRecords);
    }

    void AddStudent(int rollNo, string name, string dept, float cgpa)
    {
        cout << "Adding student: " << rollNo << " - " << name << "\n";
        Student s = {rollNo,name,dept,cgpa};
        cout << "Student object created\n";
        studentRecords.push_back(s);
        cout << "Student added to records\n";
    }

    void SaveSystemState()
    {
        FileManager::SaveStudents(fileName, studentRecords);
    }

    Student* SearchByRollNo(int rollNo) // returns the address of that student
    {
        for(int i = 0; i < studentRecords.getSize(); i++)
        {
            if(studentRecords.get(i).rollNo == rollNo)
            {
                return &(studentRecords.get(i));
            }
        }
        return nullptr;
    }

    Student * SearchByName(string name)
    {
        for(int i = 0; i < studentRecords.getSize(); i++)
        {
            if(studentRecords.get(i).name == name)
            {
                return &(studentRecords.get(i));
            }
        }
        return nullptr;
    }

    void UpdateCGPA(int rollNo, float nCGPA)
    {
        Student * ptr = SearchByRollNo(rollNo);

        if(ptr == NULL)
        {
            cout<<"Error: Student with " <<rollNo <<" not found!\n"; 
            return;
        }

        if(nCGPA < 0.0f || nCGPA > 4.0f)
        {
            cout<<"Update Error: Invalid CGPA value.\n";
            return;
        }

        ptr->cgpa = nCGPA;
        cout<<"Success: CGPA for " <<ptr->name <<" updated to " <<nCGPA <<".\n";

    }

    void DeleteStudent(int rollNo)
    {
        int targetIndex = -1;

        for(int i = 0; i < studentRecords.getSize(); i++) // gets the index number of where the student with that rollNo is stored
        {
            if(studentRecords.get(i).rollNo == rollNo)
            {
                targetIndex = i;
                break;
            }
        }

        if(targetIndex == -1)
        {
            cout<<"Error: Student with Roll No " <<rollNo <<" not found!\n";
            return;
        }
 
        studentRecords.removeAt(targetIndex);
        cout<<"Success: Student with Roll No " <<rollNo <<" has been deleted!\n";
    }

    void PrintStudentInfo(Student* ptr)
    {
        if(ptr == NULL)
        {
            cout<<"Error! Student record not found!\n";
            return;
        }

        cout<<"\n===================================";
        cout<<"\nRoll Number: " <<ptr->rollNo;
        cout<<"\nName: " <<ptr->name;
        cout<<"\nDepartment: " <<ptr->department;
        cout<<"\nCGPA: " <<ptr->cgpa;
        cout<<"\n===================================\n";
    }

};