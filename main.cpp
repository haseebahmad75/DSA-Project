#include"modules/StudentManager.hpp"
#include"modules/CourseManager.hpp"
#include"modules/LibraryManager.hpp"
#include"modules/ComplaintManager.hpp"
using namespace std;

int main()
{
    ComplaintManager cm;

    cm.FileComplaint(6, "Fans are not working in LT.");
    cm.FileComplaint(8, "University gates are closed.");
    cm.FileComplaint(10, "No cold drinking water available in scorching heat.");

    cm.resolveComplaint();

    cm.IssueToken();
    cm.IssueToken();
    cm.IssueToken();
    cm.IssueToken();
    cm.IssueToken();

    cm.ViewTokenQueue();

    cm.serveNextToken();
    cm.serveNextToken();

    cm.ViewTokenQueue();



}
