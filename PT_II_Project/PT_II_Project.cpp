#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Book.h"
#include "User.h"
#include "Stock.h"
#include "searchBook.h"
using namespace std;

//loadBooks initialize bookvector from bookdata.txt
void loadBooks(vector<Book> &bookVector) {
	system("cls");
	fstream inFile;
	inFile.open("bookdata.txt");

	if(!inFile.is_open()){
		cout << "bookdata error. Please try again later.";
		getchar();
		exit(1);
	}
	else	{cout << "Loading Book List..." << endl;}

	for(int i=0; !inFile.eof(); i++){
		Book bookHolder;
		getline(inFile, bookHolder.bookID, '\t');

		getline(inFile, bookHolder.Title, '\t');

		getline(inFile, bookHolder.ISBN);
		
		bookVector.push_back(bookHolder);
	}

	inFile.close();
}

void loadUsers(){
	system("cls");
	fstream inFile;
	inFile.open("userdata.txt");

	if(!inFile.is_open()){
		cout << "userdata error. Please try again later.";
		getchar();
		exit(1);
	}

}

//User function 1. Search for books
//void searchBook(){
//	system("cls");
//	cout << "Search result";
//}

//Show user menu
int userFunction(vector<Book> &bookVector) {
	do{
		system("cls");

		int userAction;
		cout << "\t\tUser Menu" << endl;

		cout << "\t1. Search for books\n";
		cout << "\t2. Borrow books\n";
		cout << "\t3. Reservation\n";
		cout << "\t4. Check status\n";
		cout << "\t5. Logout\n\n";
		cout << "Enter action: ";
		cin >> userAction;

		switch (userAction)
		{
		case 1:
			searchBook(bookVector);
			break;
		case 2:
			cout << "WIP" << endl;
			break;
		case 3:
			cout << "WIP" << endl;
			break;
		case 4:
			cout << "WIP" << endl;
			break;
		case 5:
			cout << "Successfully logout..." << endl;
			system("pause");
			return 0;
		default:
			cout << "Please enter number between 1-5" << endl;
			system("pause");
			break;
		}

	}while(true);
	return 0;
}

void addBook(vector<Book> &bookVector) {

	fstream inFile;
	inFile.open("bookdata.txt", ios_base::app);

	string newID;
	string newTitle;
	string newISBN;

	cout << "Enter ID of new book: ";
	cin >> newID;
	cin.ignore();

	cout << "Enter title of new book: ";
	getline(cin, newTitle);

	cout << "Enter ISBN of new book: ";
	cin >> newISBN;

	Book newBook(newID, newTitle, newISBN);
	bookVector.push_back(newBook);

	inFile << "\n" << newBook.getBookID() << "\t" << newBook.getTitle() << "\t" << newBook.getISBN();
}

void deleteBook(vector<Book>& bookVector) {

}



void adminFunction() {
	system("cls");
	cout << "\t\tAdmin Menu" << endl;

	vector<Book> bookVector;

	addBook(bookVector);
}

int main()
{
	vector<Book> bookVector;
	int actionNum;

	loadBooks(bookVector);
	
	do{
		system("cls");
		cout << "ABC Library System" << endl;
		cout << "Please select an action: 1. Login as user" << endl;
		cout << "                         2. Login as admin" << endl;
		cout << "                         3. Exit program" << endl;
		cout << "Enter action: ";
		cin >> actionNum;

		switch (actionNum)
		{
			case 1:
				userFunction(bookVector);
				break;
			case 2:
				adminFunction();
				break;
			case 3:
				return 0;
			default:
				cout << "Please enter number between 1-3" << endl;
				system("pause");
				break;
		}
	}while(true);

	return 0;
}


