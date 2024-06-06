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
    //User();
    User(string, string, string);
};

class Customer : public User{
protected:
    int numBookBorrow;
    vector<Book*> borrowedBooks;
    vector<tm> borrowTime;
public:
    //Constructors
    //Customer();
    Customer(string, string, string, int, vector<Book*>, vector<tm>);

    //Functions
    void borrowBook(Book*);
    void returnBook();

};

#endif