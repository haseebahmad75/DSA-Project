#ifndef COMPLAINTQUEUE_HPP
#define COMPLAINTQUEUE_HPP

#include"../models/Complaint.hpp"
#include<iostream>
using namespace std;

class ComplaintQueue
{
    private:
    ComplaintNode * front;
    ComplaintNode * rear;

    public:
    ComplaintQueue() : front(nullptr), rear(nullptr) {}

    ~ComplaintQueue() // to free all dynamically allocated nodes
    {
        while(!isEmpty())
        {
            Dequeue();
        }
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void Enqueue(int id, int rollNo, string desc)
    {
        ComplaintNode * newNode = new ComplaintNode(id, rollNo, desc);
        if(isEmpty())
        {
            front =  rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    bool Dequeue()
    {
        if(isEmpty()) return false;

        ComplaintNode * temp = front;
        front = front->next;

        if(front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        return true;
    }

    // Remove from rear (last added) - for undo functionality
    bool DequeueFromRear()
    {
        if(isEmpty()) return false;

        // Special case: only one element
        if(front == rear)
        {
            delete front;
            front = rear = nullptr;
            return true;
        }

        // Traverse to find second-to-last node
        ComplaintNode * current = front;
        while(current->next != rear)
        {
            current = current->next;
        }

        // Delete the last node (rear)
        delete rear;
        rear = current;
        rear->next = nullptr;
        
        return true;
    }

    void Display() const 
    {
        if (front == nullptr) 
        {
            cout << "[Complaint Queue] No active complaints in the system.\n";
            return;
        }

        cout << "\n--- Current Active Complaints Queue ---\n";
        ComplaintNode* temp = front;
        
        while (temp != nullptr) 
        {
            cout << "ID: " << temp->complaintID
                  << " | Student Roll No: " << temp->stuRollNo 
                  << " | Details: " << temp->desc << "\n";
            
            temp = temp->next;
        }
        cout << "---------------------------------------\n";
    }

    ComplaintNode * getFront()
    {
        return front;
    }
};

#endif