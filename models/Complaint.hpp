#ifndef COMPLAINT_HPP
#define COMPLAINT_HPP

#include<string>
using namespace std;

class ComplaintNode
{
    public:
    int complaintID;
    int stuRollNo;
    string desc;
    ComplaintNode * next;

    ComplaintNode(int id, int rollNo, string desc)
    {
        complaintID = id;
        stuRollNo = rollNo;
        desc = desc;
        next = nullptr;
    }
};

#endif