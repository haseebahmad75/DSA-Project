#ifndef COMPLAINT_MANAGER_HPP
#define COMPLAINT_MANAGER_HPP

#include"../data_structures/ComplaintQueue.hpp"
#include"../data_structures/TokenCircularQueue.hpp"
#include<iostream>
#include<string>
using namespace std;

class ComplaintManager
{
    private:
    ComplaintQueue complaints;
    TokenCircularQueue tokens;

    int complaintID;
    int tokenNumber;

    public:
    ComplaintManager()
    {
        complaintID = 5001;
        tokenNumber = 101;
    }

    // COMPLAINTS
    
    void FileComplaint(int rollNo, string desc)
    {
        complaints.Enqueue(complaintID, rollNo, desc);
        cout<<"Complaint registered successfully! Complaint ID: " <<complaintID <<"\n";
        complaintID++;
    }

    void resolveComplaint()
    {
        if(complaints.isEmpty())
        {
            cout<<"System Update: All complaints are fully resolved. Queue is clear!\n";
            return;
        }

        complaints.Dequeue();
        cout<<"Status: Resolved and Dropped from queue successfully! \n";

    }

    // TOKENS

    void IssueToken()
    {
       if(tokens.EnqueueToken(tokenNumber))
       {
        cout<<"Token issued. Please take token ticket.\n";
        tokenNumber++;
       }
    }

    void serveNextToken()
    {
        int target = 0;
        if(tokens.DequeueToken(target))
        {
            cout<<"Now serving token [" <<target <<" ]. Please proceed to desk\n";
        }
        else
        {
            cout<<"Alert: No tokens currently waiting in the seating area.\n";
        }
    }

    void ViewTokenQueue()
    {
        tokens.DisplayActiveTokens();
    }
};

#endif