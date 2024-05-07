#include "Book.h"
#include <iostream>

using namespace std;

Book::Book(string id_0, string title_0, string isbn_0) {
	bookID = id_0;
	Title = title_0;
	ISBN = isbn_0;
}

void Book::setBookID(string inputID) {
	bookID = inputID;
}

void Book::setTitle(string inputTitle) {
	Title = inputTitle;
}

void Book::setISBN(string inputISBN) {
	ISBN = inputISBN;
}

string Book::getBookID() const {
	return bookID;
}

string Book::getTitle() const {
	return Title;
}

string Book::getISBN() const {
	return ISBN;
}