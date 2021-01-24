#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int check_lowercase(string line){

    int length = line.length();
    for (int i = 0; i<= length - 1; i++) {
        int ascii_character = line.at(i);
        if (ascii_character < 97 or ascii_character > 122){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int check_key(string encryption_key){

    if ( encryption_key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }
    check_lowercase(encryption_key);

    for (int i = 97; i<= 122; i++) {
        char character = i;
        if ( encryption_key.find(character) == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z" << endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int main()
{
    string encryption_key = "";
    cout << "Enter the encryption key: " << endl;
    getline(cin, encryption_key);
    check_key(encryption_key);
    return 0;
}
