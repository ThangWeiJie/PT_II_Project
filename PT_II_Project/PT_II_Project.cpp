#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "Book.h"
#include "User.h"
#include "Inventory.h"
using namespace std;

const int MAX_RESULT_READ = 10;
const int TITLE_LENGTH_perROW = 63;

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
	else {cout << "Loading Book List..." << endl;}

	while(!inFile.eof()){
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

void loadCustomers(vector<Customer> &customers, vector<Book> &books){
	fstream inFile;
	inFile.open("customerdata.txt");

	if(!inFile.is_open()){
		cout << "customerdata error. Please try again later.";
		getchar();
		exit(1);
	}
	else {cout << "Loading Customer List..." << endl;}

	while(!inFile.eof()){
		Customer customerHolder;
		getline(inFile, customerHolder.userID, '\t');
		getline(inFile, customerHolder.password, '\t');
		getline(inFile, customerHolder.name, '\t');
		inFile >> customerHolder.numBookBorrow;
		for(int i=0; i<customerHolder.getNumBookBorrow(); i++){
			string bookID;
			string dueDate;
			inFile.ignore(1);
			getline(inFile, bookID, ',');
			inFile >> dueDate;
			customerHolder.pointToBook(bookID, books);
			customerHolder.mkDueDateTm(dueDate);
		}
		customerHolder.calculateOverDue();

		customers.push_back(customerHolder);
		inFile.ignore(100,'\n');
	}

	inFile.close();
}

void loadAdmins(vector<Admin> &admins){
	fstream inFile;
	inFile.open("admindata.txt");

	if(!inFile.is_open()){
		cout << "admindata error. Please try again later.";
		getchar();
		exit(1);
	}
	else {cout << "Loading Admin List..." << endl;}

	while(!inFile.eof()){
		Admin adminHolder;
		getline(inFile, adminHolder.userID, '\t');
		getline(inFile, adminHolder.password, '\t');
		getline(inFile, adminHolder.name);
		admins.push_back(adminHolder);
	}

	inFile.close();
}

bool pointToCustomer(Customer *&customer, vector<Customer> &customerList, string inputID){
	for(int i=0; i<customerList.size(); i++){
		if(inputID==customerList[i].getID()){
			customer = &customerList[i];
			break;
		}
		else if(i+1 >= customerList.size()){
			cout << "User not found" << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

bool pointToAdmin(Admin *&admin, vector<Admin> &adminList, string inputID){
	for(int i=0; i<adminList.size(); i++){
		if(inputID==adminList[i].getID()){
			admin = &adminList[i];
			break;
		}
		else if(i+1 >= adminList.size()){
			cout << "User not found" << endl;
			system("pause");
			return false;
		}
	}
	return true;
}

bool login(Customer *&customer, vector<Book> &bookVector, vector<Customer> &customerList){
	system("cls");

	string inputID,inputPsw;
	cout << "Enter User ID: ";
	cin >> inputID;
	cout << "Enter password: ";
	cin >> inputPsw;

	if(!pointToCustomer(customer,customerList,inputID))	return false;
	if(inputPsw!=customer->getPsw()){
		cout << "Wrong Password" << endl;
		system("pause");
		return false;
	}
	
	cout << "Login successful! Welcome " << customer->getName() << endl;
	system("pause");
	return true;
}

bool login(Admin *&admin, vector<Admin> &adminList){
	system("cls");

	string inputID,inputPsw;
	cout << "Enter Admin ID: ";
	cin >> inputID;
	cout << "Enter password: ";
	cin >> inputPsw;

	if(!pointToAdmin(admin,adminList,inputID))	return false;
	if(inputPsw!=admin->getPsw()){
		cout << "Wrong Password" << endl;
		system("pause");
		return false;
	}
	
	cout << "Login successful! Welcome " << admin->getName() << endl;
	system("pause");
	return true;
}

void updateData(vector<Customer> &customers, vector<Book> &books){
	fstream outFile;
	remove("customerdata.txt");
	outFile.open("customerdata.txt", ios::out);
	if(!outFile.is_open()){
		cout << "customerdata error. Please try again later.";
		getchar();
		exit(1);
	}
	for (const auto& customer : customers) {
        outFile << customer.getID() << "\t" << customer.getPsw() << "\t" << customer.getName() << "\t" << customer.getNumBookBorrow() << " " << customer.borrowDetails();
		if(&customer != &*customers.rbegin())	outFile << endl;
    }

	outFile.close();
	outFile.open("bookdata.txt");
	if(!outFile.is_open()){
		cout << "bookdata error. Please try again later.";
		getchar();
		exit(1);
	}
	for (const auto& book : books) {
        outFile << book.getBookID() << "\t" << book.getTitle() << "\t" << book.getISBN() << "\t" << book.inventory.getInStock() << " " << book.inventory.getTotal();
		if(&book != &*books.rbegin())	outFile << endl;
    }

	outFile.close();	
}

//User function 1. Search for books
string borderLine(){
    return (string(110,'-')+"\n");
}

string pop(string &str,int i){
    string temp;
    temp = str.substr(i,TITLE_LENGTH_perROW);
    str.erase(i);
    return temp;
}

void showSearchResult(vector<Book *> result, int p){
    cout << right << setw(60) << "Book List" << endl;
    cout << borderLine();
    cout << right << setw(5) << "No" << " |" << setw(6) << "ID" << setw(6) << "|" << setw(TITLE_LENGTH_perROW/2+3) << "Title" << setw(TITLE_LENGTH_perROW/2-1) << "|"
        << setw(9) << "ISBN" << setw(7) << "|" << setw(8) << "Status" << endl;
    cout << borderLine();

    for(int i=(p*10);(i<result.size())&&(i<MAX_RESULT_READ+(p*10));i++){
        string titleL0 = result[i]->getTitle();
        string titleL1 = " ";
        if(titleL0.length()>TITLE_LENGTH_perROW){
            for(int j=TITLE_LENGTH_perROW;j>0;j--){
                if(!isalpha(titleL0[j])){
                    titleL1 = pop(titleL0, j);
                    break;
                }
            }
        }

        cout << right << setw(5) << i+1 << ".| " << left << setw(10) << result[i]->getBookID()  << "|" << setw(TITLE_LENGTH_perROW) << titleL0 << "| " 
            << setw(13) << result[i]->getISBN() << " | " << result[i]->inventory.status() << endl;
        cout << right << setw(7) << "|" << setw(12) << "|" << left << setw(TITLE_LENGTH_perROW) << titleL1 << "|               |" << endl;
    }
    cout << borderLine();
}

void searchBook(Customer *customer, vector<Book> &books){
    string userSearch = "";
    int userAction = 1, page = 0, totalPage = 0, bookNo;
    bool _back = false;
    vector<Book *> booksMatched;

    do{
        system("cls");

        for(int i=0;i<books.size();i++){
            if(books[i] == userSearch)  booksMatched.push_back(&books[i]);
        }
        totalPage = ceil(booksMatched.size()/float(MAX_RESULT_READ));
        showSearchResult(booksMatched, page);

        cout << "Searching keyword: " << left << setw(13) << userSearch.substr(0,10)+((userSearch.length()>10)? "...":"") << right << setw(77) << "Page " + to_string(page+1) + "/" + to_string(totalPage) << endl;
        cout << "\nSelect action:(1. Search book / 2. Borrow book / " << ((page>0)? "3. Previous page / " : "")
             << ((page<totalPage-1)? "4. Next page / " : "") << "0. Back to user menu)" << endl << "=>";
        cin >> userAction;
        switch(userAction){
            case 1:
                cout << "\nSearch by Book ID, Book Title or ISBN: ";
                cin.ignore();
                getline(cin,userSearch);
                page = 0;
                break;
            case 2:
                cout << "\nInsert the No. of book:(1-" << booksMatched.size() << ") ";
                cin >> bookNo;
                customer->borrowBook(booksMatched[bookNo-1]);
				system("pause");
                break;
            case 3:
                if(page>0) page-=1;
                break;
            case 4:
                if(page<totalPage-1) page+=1;
                break;
            case 0:
                _back = true;
                break;
            default:
                cout << "Invalid Action Number" << endl;
                system("pause");
                break;
        }
        
        booksMatched.clear();
    }while(!_back);
        system("pause");
}

//User function 2. Borrow books
void borrowBook(Customer *customer, vector<Book> &books){
	system("cls");

	string userInput = "";

	cout << "Enter the book ID/ISBN to borrow: ";
	cin >> userInput;
	for(int i=0;i<books.size();i++){
        if(books[i].getBookID() == userInput){
			customer->borrowBook(&books[i]);
			break;
		}
		else if(books[i].getBookID() == userInput){
			customer->borrowBook(&books[i]);
			break;
		}
		else if(i+1 >= books.size()){
			cout << "Book not found" << endl;
		}
    }
	system("pause");
}

//Show user menu
int userFunction(Customer *customer, vector<Book> &bookVector, vector<Customer> &customerVector) {
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
			searchBook(customer, bookVector);
			break;
		case 2:
			borrowBook(customer, bookVector);
			break;
		case 3:
			system("cls");
			customer->print();
			system("pause");
			break;
		case 4:
			updateData(customerVector, bookVector);
			cout << "Successfully logout, Have a nice day! " << customer->getName() << endl;
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

//Admin function 1. Add Book
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

//Admin function 2. Delete Book
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

//Admin function 3. Edit Book Info
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

//Admin function 4. Issue Book return
void bookReturn(vector<Book> &books, vector<Customer> &customers){
	system("cls");
	Customer *returner;
	string custID;
	cout << "Enter customer ID of returner: ";
	cin >> custID;
	if(!pointToCustomer(returner,customers,custID))	return;

	string bookID;
	cout << "Enter the Book ID of the book return: ";
	cin >> bookID;

	returner->returnBook(bookID);
	updateData(customers, books);
}

//Show admin menu
void adminFunction(Admin *admin, vector<Book> &bookVector, vector<Customer> &customerVector) {
	int adminAction;
    do {
		system("cls");
		cout << "\t\tAdmin Menu" << endl;
        cout << "\t1. Add Book\n";
        cout << "\t2. Delete Book\n";
		cout << "\t3. Edit Book Info\n";
		cout << "\t4. Issue Book return\n";
        cout << "\t5. Logout\n\n";
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
				bookReturn(bookVector, customerVector);
				break;
			case 5:
				cout << "Successfully logout, Have a nice day! " << admin->getName() << endl;
				system("pause");
				return;
            default:
                cout << "Please enter number between 1-5" << endl;
                system("pause");
                break;
        }
    } while (true);
}

int main()
{
	vector<Book> bookVector;
	vector<Customer> customerVector;
	vector<Admin> adminVector;
	int actionNum;
	bool _loginSuccess=0;

	loadBooks(bookVector);
	loadCustomers(customerVector, bookVector);
	loadAdmins(adminVector);
	
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
				Customer *customer;
				_loginSuccess = login(customer,bookVector,customerVector);
				if(_loginSuccess)	userFunction(customer,bookVector,customerVector);
				break;}
			case 2:{
				Admin *admin;
				_loginSuccess = login(admin, adminVector);
				if(_loginSuccess)	adminFunction(admin,bookVector,customerVector);
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


