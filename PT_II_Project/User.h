#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
#include <vector>
#include "Book.h"
using namespace std;

const int MAX_BOOK_BORROW = 5;

class User{
protected:
    string userID, password, name;
public:
    //Constructors
    User(string, string, string);

    //Mutators
    void setID(string);
    void setPsw(string);
    void setName(string);
};

class Customer : public User{
protected:
    int numBookBorrow;
    vector<Book*> borrowedBooks;
    vector<tm> borrowTm;
public:
    //Constructors
    Customer();
    Customer(string, string, string, int, vector<Book*>, vector<tm>);

    //Mutators
    void setNumBook(int);

    //Functions
    void borrowBook(Book*);
    void returnBook();
    void pointToBook(string, vector<Book>);
    void mkBorrowTm(string);
};

class Admin : public User{
public:
    Admin();
};

#endif
