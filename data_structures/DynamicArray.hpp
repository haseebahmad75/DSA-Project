#pragma once
#include<iostream>
#include<stdexcept> // gives standard exception classes
using namespace std;

template<class T> // makes the class generic(works with any data type)
class DynamicArray
{
    private:
    T * arr; 
    int capacity;
    int size;

    void resize()
    {
        capacity = capacity * 2;  // Update capacity first!
        T *temp = new T[capacity]; // new double-sized array
        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    public:
    DynamicArray()
    {
        capacity = 4;
        size = 0;
        arr = new T[capacity];
    }

    void push_back(const T& element) // const means cannot modify value inside function
    {
        if(size == capacity)
        {
            resize();
        }
        arr[size] = element;
        size++;
    }

    T& get(int index) // T& returns the original stored value so it could be modified directly
    {
        if(index < 0 || index >= size)
        {
            throw out_of_range("Index is out of range");
        }
        return arr[index];
    }

    void removeAt(int index)
    {
        if(index < 0 || index >= size)
        {
            throw out_of_range("Index is out of bounds for deletion.");
        }

        for(int i = index; i < size - 1; i++)
        {
            arr[i] = arr[i+1];
        }
        
        size--;
    }

    int getSize()
    {
        return size;
    }
};