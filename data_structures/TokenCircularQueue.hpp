#ifndef TOKEN_CIRCULAR_QUEUE_HPP
#define TOKEN_CIRCULAR_QUEUE_HPP

#include<iostream>
using namespace std;

class TokenCircularQueue
{
    private:
    int * arr;
    int capacity;
    int front;
    int rear;
    int size;

    public:
    TokenCircularQueue()
    {
        capacity = 50;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    ~TokenCircularQueue()
    {
        delete[] arr;
    }

    bool isFull()
    {
        if(size == capacity)
        return true;
        else
        return false;
    }

    bool isEmpty()
    {
        if(size == 0)
        return true;
        else
        return false;
    }

    bool EnqueueToken(int token)
    {
        if(isFull())
        {
            cout<<"Token System Error: Daily maximum capacity reached.\n";
            return false;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = token;
        size++;
        return true;
    }

    bool DequeueToken(int & token)
    {
        if(isEmpty())
        return false;

        token = arr[front];
        front = (front + 1) % capacity;
        size--;
        return true;
    }

    void DisplayActiveTokens()
    {
        if(isEmpty())
        {
            cout<<"No active tokens waiting in line\n";
            return;
        }

        cout<<"Actice Token Queue Order: ";
        int index = front;
        for(int i=0; i<size; i++)
        {
            cout<<"[ " <<arr[index] <<" ]";
            index = (index + 1) % capacity;
        }
        cout<<"\n";
    }
};

#endif