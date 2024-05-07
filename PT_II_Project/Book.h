#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
	string bookID;
	string Title;
	string ISBN;

public:
	Book(string, string, string);

	void setBookID(string);
	void setTitle(string);
	void setISBN(string);

	string getBookID() const;
	string getTitle() const;
	string getISBN() const;
};


#endif 

