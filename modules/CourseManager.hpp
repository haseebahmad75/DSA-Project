#ifndef COURSE_MANAGER_HPP
#define COURSE_MANAGER_HPP

#include"StudentManager.hpp"
#include<iostream>
#include<string>
using namespace std;

class CourseManager
{
    private:
    StudentManager & sm; // reference to the student's data

    public:
    CourseManager(StudentManager & manager) : sm(manager) {}
    
    // Register a course to a specific student
    void registerCourseForStudent(int rollNo, string code, string name)
    {
        Student * stu = sm.SearchByRollNo(rollNo);

        if(stu == NULL)
        {
            cout<<"Registration Error: Cannot find student with Roll No: " <<rollNo <<"\n";
            return;
        }

        stu->registeredCourses.AddCourse(code,name);
        cout<<"Success: " <<stu->name <<" registered for " <<name <<"\n";
    }

    // Drop a course for a specific student
    void DropCourse(int rollNo, string code)
    {
        Student * stu = sm.SearchByRollNo(rollNo);

        if(stu == NULL)
        {
            cout<<"Drop Error: Cannot find student with Roll No: " <<rollNo <<"\n";
            return;
        }

        if(stu->registeredCourses.DropCourse(code))
        {
            cout<<"Success: Dropped course " <<code <<" for " <<stu->name <<"\n";
        }
        else
        {
            cout<<"Drop Error: Course " <<code <<" was not found in " <<stu->name <<"'s record \n";
        }
    }

    void viewStudentCourses(int rollNo)
    {
        Student * stu = sm.SearchByRollNo(rollNo);
        if(stu == NULL)
        {
            cout<<"Error: Cannot find student with Roll No " << rollNo << "\n";
            return;
        }
        cout << "\n--- Courses for " <<stu->name <<" (Roll No: " << rollNo << ") ---\n";
        stu->registeredCourses.Display();
    }
};

#endif