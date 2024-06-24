#include "User.h"

#include <iostream>
using namespace std;

//Base Class User:
//Constructors
User::User(string ID="", string ps="", string n=""){
    userID = ID;
    password = ps;
    name = n;
}

//Mutators
void User::setID(string id)    {userID = id;}
void User::setPsw(string psw)   {password = psw;}
void User::setName(string n)    {name = n;}


//Derived Class Customer:
//Constructors
Customer::Customer():User("","",""){}
Customer::Customer(string ID="", string ps="", string n="", int numBook = 0, vector<Book*> books={}, vector<tm> vectm={}) : User(ID,ps,n) {
    numBookBorrow = numBook;
    borrowedBooks = books;
    dueDateTm = vectm;
}

//Mutators
void Customer::setNumBook(int n)    {numBookBorrow = n;}

//Functions
void Customer::borrowBook(Book*){

}

void Customer::returnBook(){

}

void Customer::pointToBook(string bookID, vector<Book> &books){
    if(bookID.length()<9)   bookID.insert(2,9-bookID.length(),'0');
    for(int i=0;i<books.size();i++){
        if(books[i].getBookID() == bookID)  borrowedBooks.push_back(&books[i]);
    }
}

void Customer::mkDueDateTm(string dateString){
    tm duetm={};
    int year,month,day;
    year = stoi(dateString.substr(0,4));
    month = stoi(dateString.substr(4,2));
    day = stoi(dateString.substr(6,2));

    duetm.tm_year = year - 1900;
    duetm.tm_mon = month - 1;
    duetm.tm_mday = day;

    dueDateTm.push_back(duetm);
}

void Customer::calculateOverDue(){
    for(int i=0;i<borrowedBooks.size();i++){
        time_t currTime = time(NULL);
        time_t dueTime = mktime(&dueDateTm[i]);

        int overDueDay = difftime(currTime,dueTime)/SECS_PER_DAY;
        overDueDays.push_back(overDueDay);

        int overDueFee = 0;
        if(overDueDay > 0)  overDueFee = overDueDay*OVERDUE_FEE_PER_DAY;
        else    overDueFee = 0;
        overDueFees.push_back(overDueFee);
    }
}

void Customer::print(){
    cout << "User ID: " << userID << "\tName: " << name << endl;
    cout << "Borrowed Books: " << numBookBorrow << "Books" << endl;
    char dueDate[100];
    for(int i=0;i<numBookBorrow;i++){
        strftime(dueDate, 50, "%d %B %Y", &dueDateTm[i]);
        cout << "Book#" << i+1 << ": " << borrowedBooks[i]->getTitle() << "\tDue Date: " << dueDate << "\tOverDue:" << overDueDays[i] << " days(RM" << overDueFees[i] << ")" << endl;
    }
}

//Derived Class Admin:
//Constructors
Admin::Admin():User("","",""){}