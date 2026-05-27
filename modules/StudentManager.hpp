#include"data_structures/DynamicArray.hpp"
#include"models/Student.hpp"
using namespace std;

class StudentManager
{
    private:
    DynamicArray<Student> studentRecords;

    public:
    void addStudent(int rollNo, string name, string dept, float cgpa)
    {
        Student s = {rollNo,name,dept,cgpa};
        studentRecords.push_back(s);
    }

};
