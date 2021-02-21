#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if (not tiedosto_olio){
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map <string, int> pelaajat;
    char separator = ':';
    string rivi;
    string points;
    while(getline(tiedosto_olio, rivi)){
        string name = "";

        getline(tiedosto_olio, name, separator);
        getline(tiedosto_olio, points, '\n');
        if (pelaajat.find(name) != pelaajat.end()){
            pelaajat.at(name) += stoi(points);
        }
        else{
            pelaajat.insert({name, stoi(points)});
        }

    }
    cout << "Final scores:" << endl;
    for (auto tietopari : pelaajat){
        cout << tietopari.first << ": " << tietopari.second << endl;
    }
    tiedosto_olio.close();
    return 0;
}
