#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(string row){

    vector<std::string> vector = {};
    string line = "";
    char separator = ' ';
        for (auto character : row){
            if (character == separator){
                vector.push_back(line);
                line = "";
                continue;
            }
            line += (character);
        }
        if (not (count(vector.begin(), vector.end(), line))){
            vector.push_back(line);
        }
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

    map <string, vector<int>> words;

    int index = 1;
    string rivi;
    while(getline(tiedosto_olio, rivi)){

        vector<string> vector_words = split(rivi);
        for (auto part : vector_words){
            if (words.find(part) != words.end()){
                words.at(part).push_back(index);
            }
            else{
                vector<int> vector_in_map;
                words.insert({part, vector_in_map});
                words.at(part).push_back(index);
            }

        }
        ++index;
    }

    for (auto tietopari : words){
        cout << tietopari.first << " " << tietopari.second.size() << ": ";
        for (int number : tietopari.second){
            cout << number ;
            if (number != tietopari.second.at(tietopari.second.size()-1)){
                cout << ", ";
            }
        }
        cout << endl;
    }
return 0;
}
