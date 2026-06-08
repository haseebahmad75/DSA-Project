#ifndef BOOK_BST_HPP
#define BOOK_BST_HPP

#include"../models/Book.hpp"
#include<iostream>
#include<string>
using namespace std;

class BookBST
{
    private:
    Book * root; 

    Book * RecursiveInsert(Book * node, int id, string & title, string & author)
    {
        if(node == NULL)
        {
            return new Book(id, title, author);
        }

        if(id < node->bookID)
        {
            node->left = RecursiveInsert(node->left, id, title, author);
        }
        else if(id > node->bookID)
        {
            node->right = RecursiveInsert(node->right, id, title, author);
        }
        else
        {
            cout<<"Warning: Book ID " <<id <<" already exists in catalog.\n";
        }
        return node;
    }

    Book * RecursiveSearch(Book * node, int id)
    {
        if(node == NULL || node->bookID == id) // null means the node is not found
        {
            return node;
        }

        if(id < node->bookID)
        {
            return RecursiveSearch(node->left, id);
        }

        if(id > node->bookID)
        {
            return RecursiveSearch(node->right, id);
        }
    }

    void DisplayInOrder(Book * node)
    {
        if(node == NULL) return;
        
        DisplayInOrder(node->left);

        cout<<"Book ID: " <<node->bookID <<" | Title: " <<node->title 
            <<" | Author: " <<node->author <<" | Status: " <<(node->isIssued ? "Borrowed " : "Available ") <<"\n";
        
        DisplayInOrder(node->right);
    }

    void ClearTree(Book * node)
    {
        if(node == nullptr) return;

        /* First, delete left subtree
           Then delete right subtree
           And then delete current node */
        
        ClearTree(node->left);
        ClearTree(node->right);
        delete node;
    }

    public:
    BookBST()
    {
        root = nullptr;
    }

    // this is a destructor function that is automatically called when an object is destroyed
    ~BookBST()
    {
        ClearTree(root);
    }

    void Insert(int id, string title, string author)
    {
        root = RecursiveInsert(root, id, title, author);
    }

    Book * Search(int id)
    {
        return RecursiveSearch(root, id);
    }

    void DisplayCatalog()
    {
        if(root == nullptr)
        {
            cout<<"The library catalog is empty\n";
            return;
        }
        DisplayInOrder(root);
    }

};

#endif