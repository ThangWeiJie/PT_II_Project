#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
using namespace std;

class Book {
private:
	string bookID;
	string Title;
	string ISBN;
	int copyInStock， totalCopy;

public:
	//Constructors
	Book();
	Book(string, string, string);

	//Accessor
	void setBookID(string);
	void setTitle(string);
	void setISBN(string);
	//Mutator
	string getBookID() const;
	string getTitle() const;
	string getISBN() const;

	//Functions
	string toUpper(string);

	//Overloaded operator
	bool operator==(string);


	friend void bootSystem(vector<Book>&);

	~Book() {};
};


#endif 

