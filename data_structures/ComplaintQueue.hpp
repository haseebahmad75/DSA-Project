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

    ComplaintNode * getFront()
    {
        return front;
    }
};

#endif