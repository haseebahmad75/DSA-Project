#pragma once
#include<string>
#include"../data_structures/CourseLinkedList.hpp"
struct Student
{
    int rollNo;
    string name;
    string department;
    float cgpa;

    // Every student have their own list of courses
    CourseLinkedList registeredCourses;

    // initializer list initializes values during object creation
     
    // default constructor
    Student() : rollNo(0), name(""), department(""), cgpa(0.0f) {}
    
    // parameterized constructor
    Student(int rollNo, string name, string department, float cgpa) :
    rollNo(rollNo), name(name), department(department), cgpa(cgpa) {}
    
};
