#ifndef BOOK_HPP
#define BOOK_HPP

#include<string>
using namespace std;

struct Book
{
    int bookID;
    string title;
    string author;
    bool isIssued;

    Book * left; // pointer to left child (smaller bookID)
    Book * right; // pointer to right child (larger bookID)

    Book(int id, string t, string a)
    {
        bookID = id;
        title = t;
        author = a;
        isIssued = false;
        left = nullptr;
        right = nullptr;
    }
};

#endif