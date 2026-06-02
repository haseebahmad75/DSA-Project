#include"modules/StudentManager.hpp"
using namespace std;

int main()
{
    StudentManager sm;
    sm.addStudent(2, "Saddique", "Computer Science", 3.3f);
    sm.addStudent(4, "Ahmad", "Computer Science", 3.7f);
    sm.addStudent(6, "Haseeb", "Computer Science", 3.5f);
    sm.addStudent(8, "Faiq", "Computer Science", 3.4f);
    sm.addStudent(9, "Faizan", "Computer Science", 3.9f);

    Student * ptr = sm.SearchByRollNo(6); // saves the address of the student record
    sm.PrintStudentInfo(ptr);

    Student * ptr2 = sm.SearchByName("Faiq");
    sm.PrintStudentInfo(ptr2);

    sm.UpdateCGPA(2,3.5);

    sm.DeleteStudent(9);
    
    return 0;
}
