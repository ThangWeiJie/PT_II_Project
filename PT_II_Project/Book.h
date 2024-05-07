#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
	string bookID;
	string Title;
	long ISBN;

public:
	void setBookID(string);
	void setTitle(string);
	void setISBN(long);

	string getBookID() const;
	string getTitle() const;
	long getISBN() const;
};


#endif 

