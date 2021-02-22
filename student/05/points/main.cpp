#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;
std::vector<std::string> split(std::string string, char separator, bool skip_empty = false){

    std::vector<std::string> vector = {};
    std::string line = "";
    for (auto character : string){
        if (character == separator){
            if (skip_empty and line == ""){
                continue;
            }
            vector.push_back(line);
            line = "";
            continue;
        }
        line += (character);
    }
    vector.push_back(line);
    return vector;
}

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

    map <string, int> pelaajat = {};
    char separator = ':';
    string row;
    while(getline(tiedosto_olio, row)){
        vector<string> values_in_vector = split(row, separator, true);

        if (pelaajat.find(values_in_vector.at(0)) != pelaajat.end()){
            pelaajat.at(values_in_vector.at(0)) += stoi(values_in_vector.at(1));
        }
        else{
            pelaajat.insert({values_in_vector.at(0),stoi(values_in_vector.at(1))});
        }
    }
    cout << "Final scores:" << endl;
    for (auto tietopari : pelaajat){
        cout << tietopari.first << ": " << tietopari.second << endl;
    }
    tiedosto_olio.close();
    return 0;
}
