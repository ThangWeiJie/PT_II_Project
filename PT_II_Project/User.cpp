#include "User.h"

#include <iostream>
using namespace std;

//Class User:
//Constructors
//User::User(){}
User::User(string ID="", string ps="", string n=""){
    userID = ID;
    password = ps;
    name = n;
}


//Class Customer:
//Constructors
//Customer::Customer(){}
Customer::Customer(string ID="", string ps="", string n="", int numBook = 0, vector<Book*> books={}, vector<tm> borrowtm={}){
    userID = ID;
    password = ps;
    name = n;
    numBookBorrow = numBook;
    borrowedBooks = books;
    borrowTime = borrowtm;
}

//Accessors

//Mutators

//Functions
void Customer::borrowBook(Book*){

}

void Customer::returnBook(){

}