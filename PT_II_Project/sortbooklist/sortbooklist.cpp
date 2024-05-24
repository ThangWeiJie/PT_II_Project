#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
enum ALPHABET {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,MISC};

int main(){
    fstream infile,outfile;
    vector<vector<string>> bookName(27);
    vector<vector<string>> ISBN(27);

    infile.open("books_ISBN.txt");
    outfile.open("database.txt");
    
    if(!infile){
        cout << "books_ISBN.txt not found";
        return 1;
    }
    if(!outfile){
        cout << "database.txt not found";
        return 1;
    }

    int i=0;
    while(!infile.eof()){
        string tempName;
        int firstAlp;
        string tempISBN;

        getline(infile,tempName,'\t');
        getline(infile,tempISBN);
        firstAlp = toupper(tempName[0]);


        if((firstAlp>=65)&&(firstAlp<=90)){
            bookName[firstAlp-65].push_back(tempName);
            ISBN[firstAlp-65].push_back(tempISBN);
        }
        else{
            bookName[MISC].push_back(tempName);
            ISBN[MISC].push_back(tempISBN);
        }
        
    }

    for(int i=0;i<bookName.size();i++){
        char firstAlp;
        for(int j=0;j<bookName[i].size();j++){
            if(i<26)    firstAlp = i+65;
            else    firstAlp = '$';
            outfile << "#" << firstAlp << setw(7) << setfill('0') << j+1 << "\t";
            outfile << bookName[i][j] << "\t";
            outfile << ISBN[i][j] << endl;
        }
    }

    cout << "database.txt updated" << endl;
    return 0;
}