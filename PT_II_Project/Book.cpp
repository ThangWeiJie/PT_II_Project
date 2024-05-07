#include "Book.h"
#include <iostream>

using namespace std;

void Book::setBookID(string inputID) {
	bookID = inputID;
}

void Book::setTitle(string inputTitle) {
	Title = inputTitle;
}

void Book::setISBN(long inputISBN) {
	ISBN = inputISBN;
}

string Book::getBookID() const {
	return bookID;
}

string Book::getTitle() const {
	return Title;
}

long Book::getISBN() const {
	return ISBN;
}