#include"modules/StudentManager.hpp"
#include"modules/CourseManager.hpp"
#include"modules/LibraryManager.hpp"
using namespace std;

int main()
{
    LibraryManager lm;

    lm.AddNewBook(500, "The C++ Programming Language", "Bjarne Stroustrup");
    lm.AddNewBook(200, "Introduction to Algorithms", "CLRS");
    lm.AddNewBook(800, "Design Patterns", "Gang of Four");
    lm.AddNewBook(100, "Clean Code", "Robert C. Martin");

    lm.ViewLibraryCatalog();

    lm.IssueBook(100);
    lm.IssueBook(200);

    lm.ReturnBook(100);
    lm.IssueBook(100);
}
