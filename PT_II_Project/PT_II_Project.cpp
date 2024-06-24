#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Book.h"
#include "User.h"
#include "Inventory.h"
#include "searchBook.h"
using namespace std;

const time_t currTime = time(NULL);

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
		int copy, ttlCopy;
		getline(inFile, bookHolder.bookID, '\t');
		getline(inFile, bookHolder.Title, '\t');
		inFile >> bookHolder.ISBN >> copy >> ttlCopy;
		inFile.ignore();
		bookHolder.inventory.setCopy(copy);
		bookHolder.inventory.setTotal(ttlCopy);
		
		bookVector.push_back(bookHolder);
	}

	inFile.close();
}

bool checkID_Psw(fstream &inFile,string inputID, string inputPsw){
	string ID,Psw;
	while(!inFile.eof()){
		getline(inFile,ID,'\t');
		//Find matched userID
		if(inputID==ID){
			getline(inFile,Psw,'\t');
			//Check input password
			if(inputPsw==Psw)	break;
			else{
				cout << "Wrong Password" << endl;
				system("pause");
				return false;
			}
		}
		else	inFile.ignore(1000,'\n');
		if(inFile.eof()){
			cout << "User not found" << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

bool login(Customer &customer, vector<Book> &bookVector){
	system("cls");
	fstream inFile;
	inFile.open("customerdata.txt");
	if(!inFile.is_open()){
		cout << "customerdata error. Please try again later.";
		getchar();
		exit(1);
	}

	string inputID,inputPsw;
	cout << "Enter User ID: ";
	cin >> inputID;
	cout << "Enter password: ";
	cin >> inputPsw;

	if(!checkID_Psw(inFile,inputID,inputPsw))	return false;
	else{
		customer.setID(inputID);
		customer.setPsw(inputPsw);
	}

	//Fetching customerdata
	string userName;
	int numBook;
	string borrowDate;

	getline(inFile,userName,'\t');
	inFile >> numBook;
	customer.setName(userName);
	customer.setNumBook(numBook);
	for(int i=0;i<numBook;i++){
        string bookID;
        getline(inFile, bookID, ',');
		inFile >> borrowDate;
		customer.pointToBook(bookID,bookVector);
		customer.mkBorrowTm(borrowDate);
    }

	cout << "Login successful! Welcome " << userName << endl;
	system("pause");
	return true;
}

bool login(Admin &admin){
	system("cls");
	fstream inFile;
	inFile.open("admindata.txt");
	if(!inFile.is_open()){
		cout << "admindata error. Please try again later.";
		getchar();
		exit(1);
	}

	string inputID,inputPsw;
	cout << "Enter User ID: ";
	cin >> inputID;
	cout << "Enter password: ";
	cin >> inputPsw;

	if(!checkID_Psw(inFile,inputID,inputPsw))	return false;
	else{
		admin.setID(inputID);
		admin.setPsw(inputPsw);
	}

	string adminName;
	inFile >> adminName;
	admin.setName(adminName);

	cout << "Login successful! Welcome " << adminName << endl;
	system("pause");
	return true;
}

//User function 1. Search for books
//void searchBook(){
//	system("cls");
//	cout << "Search result";
//}

//User function 2. Borrow books
void borrowBook(Customer &customer, Book *book){
	customer.borrowBook(book);
}
void borrowBook(Customer &customer, vector<Book> &books){
	system("cls");
	string userInput = "";

	cout << "Enter the book ID/ISBN to borrow: ";
	cin >> userInput;
	for(int i=0;i<books.size();i++){
        if(books[i].getBookID() == userInput){
			borrowBook(customer, &books[i]);
			cout << "Book found" << endl;
			break;
		}
		else if(books[i].getBookID() == userInput){
			borrowBook(customer, &books[i]);
			cout << "Book found" << endl;
			break;
		}
		else if(i+1 >= books.size()){
			cout << "Book not found" << endl;
		}
    }
	system("pause");
}

//Show user menu
int userFunction(Customer &customer, vector<Book> &bookVector) {
	do{
		system("cls");

		int userAction;
		cout << "\t\tUser Menu" << endl;

		cout << "\t1. Search for books\n";
		cout << "\t2. Borrow books\n";
		cout << "\t3. Check status\n";
		cout << "\t4. Logout\n\n";
		cout << "Enter action: ";
		cin >> userAction;

		switch (userAction)
		{
		case 1:
			searchBook(bookVector);
			break;
		case 2:
			borrowBook(customer, bookVector);
			break;
		case 3:
			cout << "WIP" << endl;
			break;
		case 4:
			cout << "Successfully logout..." << endl;
			system("pause");
			return 0;
		default:
			cout << "Please enter number between 1-4" << endl;
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
	int totalCopy;

	cout << "Enter ID of new book: ";
	cin >> newID;
	cin.ignore();

	cout << "Enter title of new book: ";
	getline(cin, newTitle);

	cout << "Enter ISBN of new book: ";
	cin >> newISBN;

	cout << "Enter the amount of copy: ";
	cin >> totalCopy;

	Book newBook(newID, newTitle, newISBN, totalCopy, totalCopy);
	bookVector.push_back(newBook);

	inFile << "\n" << newBook.getBookID() << "\t" << newBook.getTitle() << "\t" << newBook.getISBN() << "\t" << newBook.inventory.getInStock() << " " << newBook.inventory.getTotal();
}

void deleteBook(vector<Book>& bookVector) {
	string bookID;
    cout << "Enter the ID of the book to delete: ";
    cin >> bookID;

    auto it = find_if(bookVector.begin(), bookVector.end(), [&bookID](const Book& book) {
        return book.getBookID() == bookID;
    });

    if (it != bookVector.end()) {
        bookVector.erase(it);
        cout << "Book deleted successfully." << endl;

        // Update the database file
        ofstream outFile("bookdata.txt");
        if (outFile.is_open()) {
            for (const auto& book : bookVector) {
                outFile << book.getBookID() << "\t" << book.getTitle() << "\t" << book.getISBN() << "\t" << book.inventory.getInStock() << " " << book.inventory.getTotal();
				if(&book != &*bookVector.rbegin())	outFile << endl;
            }
            outFile.close();
        } else {
            cout << "Error updating bookdata file." << endl;
        }
    } else {
        cout << "Book with ID " << bookID << " not found." << endl;
    }
    system("pause");
}

void editBook(vector <Book>& bookVector) {
	string bookID;
	cout << "Enter ID of book to edit: ";
	cin >> bookID;

	Book* selectedBook;
	for (int i = 0; i < bookVector.size(); i++) {
		if (bookVector[i].getBookID() == bookID) {
			selectedBook = &bookVector[i];

			string newID;
			cout << "Change ID of book: ";
			cin >> newID;
			selectedBook->setBookID(newID);

			string newTitle;
			cout << "Change title of book: ";
			cin.ignore();
			getline(cin, newTitle);
			selectedBook->setTitle(newTitle);

			string newISBN;
			cout << "Change ISBN of book: ";
			cin >> newISBN;
			selectedBook->setISBN(newISBN);

			ofstream outFile("bookdata.txt");
			if (outFile.is_open()) {
				for (const auto& book : bookVector)
				{
					outFile << book.getBookID() << "\t" << book.getTitle() << "\t" << book.getISBN() << "\t" << book.inventory.getInStock() << " " << book.inventory.getTotal();
					if(&book != &*bookVector.rbegin())	outFile << endl;
				}
				outFile.close();
			}
			else {
				cout << "Error updating";
			}
			break;
		}
		else if(i+1 >= bookVector.size()) { 
			cout << "Book not found." << endl; 
			break;
		}
	}

	selectedBook = nullptr;

	system("pause");
}

void adminFunction(Admin admin, vector<Book> &bookVector) {
	system("cls");
	cout << "\t\tAdmin Menu" << endl;

	int adminAction;
    do {
        cout << "\t1. Add Book\n";
        cout << "\t2. Delete Book\n";
		cout << "\t3. Edit Book Info\n";
        cout << "\t4. Exit Admin Menu\n";
        cout << "Enter action: ";
        cin >> adminAction;

        switch (adminAction) {
            case 1:
                addBook(bookVector);
                break;
            case 2:
                deleteBook(bookVector);
                break;
            case 3:
				editBook(bookVector);
                break;
			case 4:
				return;
            default:
                cout << "Please enter number between 1-4" << endl;
                system("pause");
                break;
        }
    } while (true);
}

int main()
{
	vector<Book> bookVector;
	int actionNum;
	bool _loginSuccess=0;

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
			case 1:{
				Customer customer;
				_loginSuccess = login(customer,bookVector);
				if(_loginSuccess)	userFunction(customer,bookVector);
				break;}
			case 2:{
				Admin admin;
				_loginSuccess = login(admin);
				if(_loginSuccess)	adminFunction(admin,bookVector);
				break;}
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


