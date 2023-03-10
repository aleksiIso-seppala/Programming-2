#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int encrypt_text(string encryption_key, string line){

    int length = line.length();
    for (int i = 0; i <= length - 1; i++){
        for (int j = 97; j <= 122; j++){
            char character = j;
            if (line.at(i) == character){
                char encrypted_letter = encryption_key.at(j-97);
                string encrypted{encrypted_letter};
                line.replace(i, 1, encrypted);
                break;
            }
        }
    }
    cout << "Encrypted text: " << line << endl;
    return EXIT_SUCCESS;
}

bool check_lowercase(string line){

    int length = line.length();
    for (int i = 0; i<= length - 1; i++) {
        int ascii_character = line.at(i);
        if (ascii_character < 97 or ascii_character > 122){
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }
    }
    return true;
}

bool check_key(string encryption_key){

    if ( encryption_key.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    }
    if ( not check_lowercase(encryption_key)){
        return false;
    }

    for (int i = 97; i<= 122; i++) {
        char character = i;
        if ( encryption_key.find(character) == string::npos){
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    string encryption_key = "";
    cout << "Enter the encryption key: ";
    getline(cin, encryption_key);
    if (not check_key(encryption_key)){
        exit (EXIT_FAILURE);
    }

    string line = "";
    cout << "Enter the text to be encrypted: ";
    getline(cin, line);
    if (not check_lowercase(line)){
        exit (EXIT_FAILURE);
    }
    encrypt_text(encryption_key, line);

    return 0;
}
