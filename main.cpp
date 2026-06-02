#include"modules/StudentManager.hpp"
using namespace std;

int main()
{
    StudentManager sm;
    sm.initSystem();
    sm.addStudent(6, "Haseeb", "Computer Science", 3.5f);
    sm.addStudent(8, "Faiq", "Computer Science", 3.4f);
    cout<<"Added student record successfully\n";
    sm.saveSystemState();
    return 0;
}
