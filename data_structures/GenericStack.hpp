#ifndef GENERIC_STACK_HPP
#define GENERIC_STACK_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct StackNode
{
    T data;
    StackNode * next;

    StackNode(const T& val) : data(val), next(nullptr) {}
};

template <typename T>
class GenericStack
{
    private:
    StackNode<T>* topNode;
    int currentSize;

    public:
    GenericStack() : topNode(nullptr), currentSize(0) {}

    ~GenericStack() {
        clear();
    }

    bool isEmpty()
    {
        if(topNode == nullptr)
        return true;
        else
        return false;
    }

    int size()
    {
        return currentSize;
    }

    void push(const T& val)
    {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->next = topNode;
        topNode = newNode;
        currentSize++;
    }

    T pop()
    {
        if(isEmpty())
        {
            throw std::underflow_error("Stack Underflow: Cannot pop from an empty history tracker.");
        }
        StackNode<T> * temp = topNode;
        T poppedData = temp->data;

        topNode = topNode->next;
        delete temp;
        currentSize--;

        return poppedData;
    }

    T peek()
    {
        if(isEmpty())
        {
            throw std::underflow_error("Stack Error: Cannot peek inside an empty history tracker.");
        }
        return topNode->data;
    }

    void clear()
    {
        while(!isEmpty())
        pop();
    }
};

#endif