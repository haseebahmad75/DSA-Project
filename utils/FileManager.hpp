#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include"../data_structures/DynamicArray.hpp"
#include"../models/Student.hpp"
using namespace std;

class FileManager
{
    public:
    inline static bool SaveStudents(string fileName, DynamicArray<Student> & students)
    {
        ofstream file(fileName);
        if(!file.is_open())
        {
            cout<<"Error: Could not open " <<fileName <<" for writing";
            return false;
        }

        for(int i = 0; i < students.getSize(); i++)
        {
            Student s = students.get(i);
            file << s.rollNo <<","
                 << s.name <<","
                 << s.department <<","
                 << s.cgpa <<"\n";
        }
        file.close();
        return true;
    }

    inline static bool LoadStudents(string fileName, DynamicArray<Student> & students)
    {
        ifstream file(fileName);
        if(!file.is_open())
        {
            cout<<"Error: No data file found for " <<fileName;
            return false;
        }

        string line;
        // Skip the header line
        getline(file, line);
        
        while(getline(file,line))
        {
            if(line.empty()) continue;

            stringstream ss(line); // it is a tool to treat string as a stream
            string rollStr, name, dept, cgpaStr;

            if(getline(ss,rollStr, ',') &&
              getline(ss,name, ',') &&
              getline(ss, dept, ',') &&
              getline(ss, cgpaStr, ','))
            {
                int rollNo = stoi(rollStr);
                float cgpa = stof(cgpaStr);

                Student loadedStudent(rollNo, name, dept, cgpa);
                students.push_back(loadedStudent);
            }
        }
        file.close();
        return true;
    }
};