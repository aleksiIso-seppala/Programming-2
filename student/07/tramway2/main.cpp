#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

std::vector<std::string> split(const std::string& s, const char delimiter = ';', bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool read_and_check_input(map <string, map<string, double>>& lines){

    string filename;
    cout << "Give a name for input file: ";
    getline(cin, filename);

    ifstream file(filename);
    if (not file){
        cout << "Error: File could not be read." << endl;
        return false;
    }
    else{
        string line;
        while ( getline(file, line)){
            vector<string> line_split = split(line);
            if (line_split.size()  > 3){
                file.close();
                return false;
            }
            if (line_split.size() == 2){
                line_split.push_back("0");
            }
            if (line_split.at(2) == ""){
                line_split.at(2) = "0";
            }

            string route = line_split.at(0);
            string stop = line_split.at(1);
            double distance = stod(line_split.at(2));
            map<string, double> empty_map;
            if (lines.find(route) == lines.end()){
                lines.insert({route, empty_map});
            }

            // check that there are no two same stops in a route
            if (lines.at(route).find(stop) != lines.at(route).end()){
                file.close();
                return false;
            }

            // check that there are no two same distances in a route
            for (auto pair : lines.at(route)){
                if (pair.second == distance){
                    file.close();
                    return false;
                }
            }

            lines.at(route).insert({stop, distance});
        }

    }
    file.close();
    return true;
}

// Short and sweet main.
int main()
{
    print_rasse();
    map <string, map<string, double>> lines;
    if (not read_and_check_input(lines)){
        return EXIT_FAILURE;
    }



    return EXIT_SUCCESS;
}
