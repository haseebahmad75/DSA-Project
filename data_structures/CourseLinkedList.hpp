#ifndef COURSE_LINKED_LIST_HPP
#define COURSE_LINKED_LIST_HPP

#include"../models/Course.hpp"
#include<iostream>

class CourseLinkedList
{
    public:  // Changed from private to public so CourseManager can access head
    Node * head;

    public:
    CourseLinkedList() : head(nullptr) {}
    
    // Copy constructor - needed when Student objects are copied - deep copy, copy the data of member variables and allocate it on new memory
    CourseLinkedList(const CourseLinkedList& other) : head(nullptr)
    {
        if(other.head == nullptr) return;
        
        Node* current = other.head;
        while(current != nullptr)
        {
            AddCourse(current->courseCode, current->courseName);
            current = current->next;
        }
    }
    
    // Assignment operator - needed when Student objects are assigned
    CourseLinkedList& operator=(const CourseLinkedList& other)
    {
        if(this == &other) return *this; // Self-assignment check
        
        // Clear existing list
        while(head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
        // Copy from other
        if(other.head != nullptr)
        {
            Node* current = other.head;
            while(current != nullptr)
            {
                AddCourse(current->courseCode, current->courseName);
                current = current->next;
            }
        }
        
        return *this;
    }
    
    // Destructor - clean up memory
    ~CourseLinkedList()
    {
        while(head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void AddCourse(string code, string name)
    {
        Node * newNode = new Node(code, name);
        if(head == NULL)
        {
            head = newNode;
            return;
        }

        Node * temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        } 
        temp->next = newNode;
    }

    bool DropCourse(string code)
    {
        if(head == NULL)
        {
            std::cout<<"List is empty\n";
            return false;
        }
        // case 1: The course to drop is the very first one
        if(head->courseCode == code) 
        {
            Node * temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        // case 2: The course is at the end or middle
        Node * prev = head;
        Node * current = head->next;

        while(current->next != NULL)
        {
            if(current->courseCode == code)
            {
                prev->next = current->next; // skip the current node
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void Display()
    {
        if(head == NULL)
        {
            std::cout<<"No courses registered yet\n";
            return;
        }
        Node * temp = head;
        while(temp != NULL)
        {
            std::cout<<"Course Code: " <<temp->courseCode <<" || " <<" Course Name: " <<temp->courseName <<"\n";
            temp = temp->next;  // Move to the next node
        }
    }
};

#endif