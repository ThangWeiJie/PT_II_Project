#include <iostream>
#include <string>
using namespace std;
enum ALPHABET {A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,MISC};

int main(){
    string tempName = "Benjamin";
    int firstAlp;
    char chr;
    firstAlp = toupper(tempName[0]);

    chr = firstAlp;

    cout << char(firstAlp);

    return 0;
}