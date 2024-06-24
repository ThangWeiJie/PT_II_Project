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
Customer::Customer(string ID="", string ps="", string n="", int numBook = 0, vector<Book*> books={}, vector<tm> vectm={}){
    User(ID,ps,n);
    numBookBorrow = numBook;
    borrowedBooks = books;
    borrowTm = vectm;
}

//Mutators
void Customer::setNumBook(int n)    {numBookBorrow = n;}

//Functions
void Customer::borrowBook(Book*){

}

void Customer::returnBook(){

}

void Customer::pointToBook(string bookID, vector<Book> books){
    if(bookID.length()<9)   bookID.insert(2,9-bookID.length(),'0');
    for(int i=0;i<books.size();i++){
            if(books[i] == bookID)  borrowedBooks.push_back(&books[i]);
    }
}

void Customer::mkBorrowTm(string dateString){
    tm temptm={};
    int year,month,day;
    year = stoi(dateString.substr(0,4));
    month = stoi(dateString.substr(4,2));
    day = stoi(dateString.substr(6,2));

    temptm.tm_year = year - 1900;
    temptm.tm_mon = month - 1;
    temptm.tm_mday = day;

    borrowTm.push_back(temptm);
}

//Derived Class Admin:
//Constructors
Admin::Admin():User("","",""){}
