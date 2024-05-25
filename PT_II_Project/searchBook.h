#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Book.h"
using namespace std;

const int MAX_RESULT_READ = 10;

string borderLine(){
    return (string(110,'-')+"\n");
}

void showSearchResult(vector<Book> result){
    cout << right << setw(50) << "Book List" << endl;
    cout << borderLine();
    cout << right << setw(5) << "No" << " |" << setw(7) << "ID" << setw(6) << "|" << setw(38) << "Title" << setw(33) << "|" << setw(8) << "ISBN" << endl;
    cout << borderLine();

    for(int i=0;i<result.size()&&i<MAX_RESULT_READ;i++){
        string titleL0 = result[i].getTitle();
        string titleL1 = " ";
        if(titleL0.length()>70){
            for(int j=70;j>0;j--){
                if(!isalpha(titleL0[j])){
                    titleL1 = titleL0.substr(j,70);
                    titleL0.erase(j);
                    break;
                }
            }
        }

        cout << right << setw(5) << i+1 << ".| " << left << setw(11) << result[i].getBookID()  << "|" << setw(70) << titleL0 << "| "  << result[i].getISBN() << endl;
        cout << setw(6) << " " << "|" << setw(12) << " " << "|" << setw(70) << titleL1 << "| " << endl;
    }
    cout << borderLine();
}

void searchBook(vector<Book> books){
    system("cls");
    string userSearch = "Pr";
    vector<Book> booksMatched;

    for(int i=0;i<books.size();i++){
        if(books[i] == userSearch)  booksMatched.push_back(books[i]);
    }
    showSearchResult(booksMatched);
    cout << "Search by Book Title, Author or ISBN: ";
    cin.ignore();
    getline(cin,userSearch);

    system("pause");
}