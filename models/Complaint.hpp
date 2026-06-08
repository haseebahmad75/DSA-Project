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

    ComplaintNode(int id, int rollNo, string description)
    {
        complaintID = id;
        stuRollNo = rollNo;
        desc = description;
        next = nullptr;
    }
};

#endif