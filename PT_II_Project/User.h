#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>
#include <vector>
#include "Book.h"
using namespace std;

const int MAX_BOOK_BORROW = 5;
const int BORROW_DURATION_DAY = 14;
const int OVERDUE_FEE_PER_DAY = 3;
const int SECS_PER_DAY = 24*60*60;

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
    vector<tm> dueDateTm;
    vector<string> dueDateString;
    vector<int> overDueDays, overDueFees;
public:
    //Constructors
    Customer();
    Customer(string, string, string, int, vector<Book*>, vector<tm>);

    //Accessors
    string getID() const;
    string getName() const;
    int getNumBookBorrow() const;
    string borrowDetails() const;

    //Mutators
    void setNumBook(int);

    //Functions
    void borrowBook(Book*);
    void returnBook(string);
    void pointToBook(string, vector<Book>&);
    void mkDueDateTm(string);
    void calculateOverDue();
    void print();

};

class Admin : public User{
public:
    Admin();
};

#endif