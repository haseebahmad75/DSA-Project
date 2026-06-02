#ifndef COURSE_HPP
#define COURSE_HPP

#include<string>
using namespace std;
struct Node
{
    string courseCode;
    string courseName;
    Node* next;

    Node(string code, string name)
    {
        courseCode = code;
        courseName = name;
        next = nullptr;
    }
};

#endif

