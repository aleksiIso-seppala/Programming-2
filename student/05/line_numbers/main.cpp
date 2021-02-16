#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file = "";
    cout << "Input file: ";
    getline(cin, input_file);

    string output_file = "";
    cout << "Output file: ";
    getline(cin, output_file);

    ifstream tiedosto_olio(input_file);
    ofstream tiedost_olio_2(output_file);
    if (not tiedosto_olio) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
    }
    else if (not tiedost_olio_2) {
       cout << "Error! The file " << output_file << " cannot be opened." << endl;
    }
    else {
        int index = 1;
        string rivi;
        string rivi2;
        while ( getline(tiedosto_olio, rivi)) {
            string line = rivi;
            tiedost_olio_2 << index << " " << line << endl;
            ++index;
        }
        tiedosto_olio.close();
        tiedost_olio_2.close();
    }
    return 0;
}
