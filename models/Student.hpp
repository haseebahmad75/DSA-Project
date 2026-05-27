#include<string>
using namespace std;
struct Student
{
    int rollNo;
    string name;
    string department;
    float cgpa;

    // initializer list initializes values during object creation
     
    // default constructor
    Student() : rollNo(0), name(""), department(""), cgpa(0.0f) {}
    
    // parameterized constructor
    Student(int rollNo, string name, string department, float cgpa) :
    rollNo(rollNo), name(name), department(department), cgpa(cgpa) {}
    
};
