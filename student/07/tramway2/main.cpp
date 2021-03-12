#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "stop.hh"

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
void upper(string& line){

    string line_in_upper;
    for (char character : line){
        char c;
        c =toupper(character);
        line_in_upper += c;
    }
    line = line_in_upper;
}
bool read_and_check_input(map <string, vector<Stop>>& lines){

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
            if (line_split.size()  > 3 or line_split.size() < 2){
                file.close();
                cout << "Error: Invalid format in file." << endl;
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
            vector<Stop> empty_vector;
            if (lines.find(route) == lines.end()){
                lines.insert({route, empty_vector});
            }
            // check that there are no two same stops in a route
            for(unsigned long int i=0; i < lines.at(route).size(); i++){
                if (lines.at(route).at(i).get_name() == stop ){
                    file.close();
                    cout << "Error: Stop/line already exists." << endl;
                    return false;
                }
            }

            // check that there are no two same distances in a route
            for (unsigned long int i=0; i < lines.at(route).size(); i++){
                if (lines.at(route).at(i).get_distance(route) == distance){
                    file.close();
                    cout << "Error: Stop/line already exists." << endl;
                    return false;
                }
            }
            Stop new_stop = Stop(stop);
            new_stop.add_stop(route, distance);
            lines.at(route).push_back(new_stop);
        }

    }
    file.close();
    return true;
}

void print_lines(map <string, vector<Stop>> routes){

    cout << "All tramlines in alphabetical order:" << endl;
    for (auto route : routes){
        cout << route.first << endl;
    }
}

void print_single_line(map <string, vector<Stop>> routes, string route){

    for(unsigned long int i=0; i < routes.at(route).size(); i++){
        cout << routes.at(route).at(i).get_name() << " : " <<
                routes.at(route).at(i).get_distance(route) << endl;
    }
}
// Short and sweet main.
int main()
{
    print_rasse();
    map <string, vector<Stop>> routes;
    if (not read_and_check_input(routes)){
        return EXIT_FAILURE;
    }

    while(true){
        string line;
        cout << "tramway> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ');
        upper(parts.at(0));
        string command = parts.at(0);

        if (command == "LINES"){
            print_lines(routes);
        }

        else if (command == "LINE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string line = parts.at(1);
            if (routes.find(line) == routes.end()){
                cout << "Error: Line could not be found." << endl;
                continue;
            }
            print_single_line(routes, line);
        }

        else if (command == "STOPS"){

        }

        else if (command == "STOP"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
        }

        else if (command == "DISTANCE"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }
        }

        else if (command == "ADDLINE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
        }

        else if (command == "ADDSTOP"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }
        }

        else if (command == "REMOVE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
        }

        else if (command == "QUIT"){
            break;
        }

        else{
            cout << "Error: Invalid input." << endl;
            continue;
        }
    }


    return EXIT_SUCCESS;
}
