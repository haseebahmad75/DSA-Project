#ifndef LIBRARY_MANAGER_HPP
#define LIBRARY_MANAGER_HPP

#include"../data_structures/BookBST.hpp"
#include<iostream>
#include<string>
using namespace std;

class LibraryManager
{
    private:
    BookBST book;

    public:
    void AddNewBook(int id, string title, string author)
    {
        book.Insert(id, title, author);
    }

    void IssueBook(int id)
    {
        Book * targetBook = book.Search(id);
        if(targetBook == NULL)
        {
            cout<<"Library Error: Book with ID " <<targetBook->bookID <<" does not exist in our inventory\n";
            return;
        }

        if(targetBook->isIssued)
        {
            cout<<"Library Error: " <<targetBook->title <<" is already checked out\n";
            return;
        }

        targetBook->isIssued = true;
        cout<<"Success: " <<targetBook->title <<" has been checked out successfully\n";
    }

    void ReturnBook(int id)
    {
        Book * b = book.Search(id);

        if(b == nullptr)
        {
            cout<<"Library Error: Book with ID " <<id <<" does not belong to the library\n";
        }

        b->isIssued = false;
        cout<<"Success: " <<b->title <<" returned safely. Inventory status updated\n";
    }

    void ViewLibraryCatalog()
    {
        cout << "\n========================================================\n";
        cout << "                UNIVERSITY LIBRARY CATALOG              \n";
        cout << "========================================================\n";
        book.DisplayCatalog();
        cout << "========================================================\n";
    }
};

#endif