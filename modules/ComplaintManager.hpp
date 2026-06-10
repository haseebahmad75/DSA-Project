#ifndef COMPLAINT_MANAGER_HPP
#define COMPLAINT_MANAGER_HPP

#include"../data_structures/ComplaintQueue.hpp"
#include"../data_structures/TokenCircularQueue.hpp"
#include"../data_structures/GenericStack.hpp"
#include<iostream>
#include<string>
using namespace std;

struct ComplaintAction
{
    string type;
    int complaintID;
    int stuRollNo;
    string desc;
};

class ComplaintManager
{
    private:
    ComplaintQueue complaints;
    TokenCircularQueue tokens;

    int complaintID;
    int tokenNumber;

    GenericStack<ComplaintAction> undoStack;
    GenericStack<ComplaintAction> redoStack;

    public:
    ComplaintManager()
    {
        complaintID = 5001;
        tokenNumber = 101;
    }

    // COMPLAINTS
    
    void FileComplaint(int rollNo, string desc)
    {
        // Store action with CURRENT ID before incrementing
        ComplaintAction action = {"ADD", complaintID, rollNo, desc};
        
        complaints.Enqueue(complaintID, rollNo, desc);
        cout<<"Complaint registered successfully! Complaint ID: " <<complaintID <<"\n";
        
        undoStack.push(action);
        redoStack.clear();
        
        complaintID++;  // Increment AFTER storing in action
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

    void executeUndo()
    {
        if(undoStack.isEmpty())
        {
            cout<<"[Undo System] Alert: No complaints left to revert.\n";
            return;
        }

        ComplaintAction lastAction = undoStack.pop();
        redoStack.push(lastAction);

        if(lastAction.type == "ADD")
        {
            // Remove from REAR (newest/last added complaint) - for undo
            complaints.DequeueFromRear();
            cout<<"[Undo Action]: Removed newest Complaint ID " <<lastAction.complaintID <<" from queue\n";
            
            complaintID--;  // Decrement the ID counter
        }
    }

    void executeRedo()
    {
        if(redoStack.isEmpty())
        {
            cout<<"[Redo System] Alert: Already at the latest action state\n";
            return;
        }

        ComplaintAction actionToRedo = redoStack.pop();
        undoStack.push(actionToRedo);

        if (actionToRedo.type == "ADD") {
            // Re-add complaint to queue with original ID
            complaints.Enqueue(actionToRedo.complaintID, actionToRedo.stuRollNo, actionToRedo.desc);
            cout << "[Redo Action] Re-inserted Complaint ID " << actionToRedo.complaintID << " back into the queue.\n";
            
            complaintID++;  
        }
    }

    void viewActiceComplaints()
    {
        complaints.Display();
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