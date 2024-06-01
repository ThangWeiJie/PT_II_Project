#include "Book.h"
#include <iostream>

using namespace std;

//Constructors
Book::Book(){
	bookID = Title = ISBN = "";
}
Book::Book(string id_0="", string title_0="", string isbn_0="") {
	bookID = id_0;
	Title = title_0;
	ISBN = isbn_0;
}

//Mutators
void Book::setBookID(string inputID) {
	bookID = inputID;
}

void Book::setTitle(string inputTitle) {
	Title = inputTitle;
}

void Book::setISBN(string inputISBN) {
	ISBN = inputISBN;
}

//Accessors
string Book::getBookID() const {
	return bookID;
}

string Book::getTitle() const {
	return Title;
}

string Book::getISBN() const {
	return ISBN;
}

//Functions
string Book::toUpper(string str){
    string tempStr="";
    for(int i=0;i<str.length();i++){
        tempStr+=toupper(str[i]);
    }
    return tempStr;
}

//Overloaded operators
bool Book::operator==(string search){
	search = toUpper(search);
	if((bookID.find(search)>=0) && (bookID.find(search)<bookID.length()))	return true;
	if((toUpper(Title).find(search)>=0) && (toUpper(Title).find(search)<Title.length()))	return true;
	if((toUpper(ISBN).find(search)>=0) && (toUpper(ISBN).find(search)<ISBN.length()))	return true;
	return false;
}
