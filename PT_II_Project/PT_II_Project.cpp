#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Book.h"
using namespace std;

void bookList() {
	system("cls");
	string inputID, inputTitle, inputISBN;

	fstream inFile;
	inFile.open("database.txt");

	vector<string> bookIDDatabase;
	vector<string> bookTitleDatabase;
	vector<string> isbnDatabase;
	vector<Book> bookObjectVector;

	if (!inFile.is_open()) {cout << "Database error. Please try again later.";}

	while (!inFile.eof()) {
		getline(inFile, inputID, '\t');
		bookIDDatabase.push_back(inputID);

		getline(inFile, inputTitle, '\t');
		bookTitleDatabase.push_back(inputTitle);

		getline(inFile, inputISBN);
		isbnDatabase.push_back(inputISBN);
	}

	for (size_t i = 0; i < bookIDDatabase.size(); i++) {
		Book placeholder(bookIDDatabase[i], bookTitleDatabase[i], isbnDatabase[i]);
		bookObjectVector.push_back(placeholder);
	}

	Book exElement = bookObjectVector[0];
	cout << exElement.getBookID() << exElement.getTitle() << exElement.getISBN();

	inFile.close();
}

void userFunction() {
	system("cls");

	int userAction;
	cout << "\t\tMenu" << endl;

	cout << "\t1. Search for books\n";
	cout << "\t2. Borrow books\n";
	cout << "\t3. Reservation\n";
	cout << "\t4. Check status\n\n";
	cout << "Enter action: ";
	cin >> userAction;

	switch (userAction)
	{
	case 1:
		bookList();
		break;
	case 2:
		cout << "WIP";
		break;
	case 3:
		cout << "WIP";
		break;
	default:
		break;
	}
}

void adminFunction() {
	system("cls");
	cout << "\t\tMenu";
}

int main()
{
	int actionNum;

	cout << "ABC Library System" << endl;
	cout << "Please select an action: 1. Login as user" << endl;
	cout << "                         2. Login as admin" << endl;
	cout << "Enter action: ";
	cin >> actionNum;

	switch (actionNum)
	{
	case 1:
		userFunction();
		break;
	case 2:
		adminFunction();
		break;
	case 3:
		return 0;
		break;
	default:
		break;
	}


}


