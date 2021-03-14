/* Tramways
 *
 * Description:
 * the program implements an user interface for tramways.
 * The tramways are read from a file and stored in a
 * data structure. After that the user can do various
 * things by writing different commands to the interface.
 * The program checks all the users input and ends when
 * the users inputs the quit command. The program also ends
 * if the input file is not valid.
 *
 * The user can print all tramway routes, print all the stops in a
 * single route and print all the stops in the tramway system.
 * They can also find out all the routes that have a specific stop
 * and find out the distance between two stops in a route.
 *
 * the user can also edit the tramways in various ways.
 * the user can add new routes or stops. They can also remove
 * a stop from all routes.
 *
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 *
 * */



#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "route.hh"

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

// function splits a character line and returns a vector where they are split
std::vector<std::string> split(const std::string& s,
                               const char delimiter = ';', bool ignore_empty = false){
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

// function changes all the characters in an input
// to upper characters
void upper(string& line){

    string line_in_upper;
    for (char character : line){
        char c;
        c =toupper(character);
        line_in_upper += c;
    }
    line = line_in_upper;
}


// checks whether an input is valid. The input cannot have
// an already existing distance or name in the route
bool is_valid_input(map<string, Route> routes,
                    string route, string stop, double distance){

    // check that there are no two same stops in a route
    map<string, double> map = routes.at(route).get_map();

    if (map.find(stop) != map.end() ){
        return false;
    }


    // check that there are no two same distances in a route
    for (auto stop : map){
        if (stop.second == distance){
            return false;
        }
    }
    return true;
}

// reads the file given in a input
// and adds the routes and stops to
// the corresponding data structures
bool read_input(map <string, Route>& routes){

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

            // if route is not found, a new one is created
            if (routes.find(route) == routes.end()){
                Route new_route = Route(route);
                routes.insert({route, new_route});
            }
            // checking the input so that it is valid
            if(not is_valid_input(routes, route, stop, distance)){
                cout << " Error: Stop/line already exists." << endl;
                file.close();
                return false;
            }

            routes.at(route).add_stop(stop, distance);
        }

    }
    file.close();
    return true;
}


// prints all the routes in alphabetical order
void print_routes(map <string, Route> routes){

    cout << "All tramlines in alphabetical order:" << endl;
    for (auto route : routes){
        cout << route.first << endl;
    }
}

// prints all the stops in a single route.
// the stops are printed in order of distance
void print_single_route(map<string, Route> routes, string route){

    cout << "Line " << route <<
            " goes through these stops"
            " in the order they are listed:" << endl;

    map<double,string> distance_map = routes.at(route).get_distance_map();
    for(auto stop : distance_map){
        cout << " - " << stop.second << " : " << stop.first << endl;
    }
}

// prints all stops in ASCII-order
void print_stops(map<string, Route> routes){

    // the set is needed for storing the stops
    // in correct order.
    set<string> stops_in_set;

    // going through all the stops in the loop
    // and adding new ones to the set
    for (auto route : routes){
        for(auto stop : route.second.get_map()){
            if (stops_in_set.find(stop.first) == stops_in_set.end()){
                stops_in_set.insert(stop.first);
            }

        }
    }

    // printing the stops from the set
    cout << "All stops in alphabetical order:" << endl;
    for (auto stop : stops_in_set){
        cout << stop << endl;
    }
}


// prints all the routes in which a specific stop is in
void print_stop(map<string, Route> routes, string stop){


    bool stop_found = false;
    for (auto route : routes){
            map<string, double> map = route.second.get_map();
            // if the stop is found, the corresponding line
            // is printed
            if (map.find(stop) != map.end()){

                // this is to ensure that the text is printed only once
                if(not stop_found){
                    cout << "Stop " << stop << " can be found on the following lines:" << endl;
                }
                cout << " - " << route.first << endl;
                stop_found = true;
                continue;
            }
    }
    // if a stop is not found, the following text is printed
    if(not stop_found){
        cout << "Error: Stop could not be found" << endl;
        return;
    }

}
// prints the distance between two stops in a route
void distance(map<string, Route> routes, string route, string stop_1, string stop_2){

    map<string, double> map = routes.at(route).get_map();
    double stop_1_distance = map.at(stop_1);
    double stop_2_distance = map.at(stop_2);
    double distance;

    if (stop_1_distance > stop_2_distance){
        distance = stop_1_distance - stop_2_distance;
    }
    else{
        distance = stop_2_distance - stop_1_distance;
    }

    cout << "Distance between " << stop_1 << " and " << stop_2 << " is " <<
            distance << endl;
}


// adds a new route to the route map.
// also creates a new route object.
void add_route(map<string, Route>& routes, string route){

    if (routes.find(route) != routes.end()){
        cout << "Error: Stop/line already exists." << endl;
        return;
    }
    Route new_route = Route(route);
    routes.insert({route, new_route});
    cout << "Line was added." << endl;
}

// adds a stop to a specific route. The new stop and distance go
// through check_input function to ensure valid inputs
void add_stop(map<string, Route>& routes,string route,string stop,double distance){

    // checking whether the input is valid.
    if(not is_valid_input(routes, route, stop, distance)){
        cout << " Error: Stop/line already exists." << endl;
        return;
    }

    // adding the stop to the route
    routes.at(route).add_stop(stop, distance);
    cout << "Stop was added." << endl;

}

// function removes a stop from all routes.
void remove(map<string, Route>& routes, string stop){

    // going through all the routes to find, which
    // ones have the stop to be removed. If one is
    // found, the stop is removed.
    bool stop_removed = false;

    for (auto route : routes){
        map<string, double> map = route.second.get_map();
        if (map.find(stop) != map.end()){
            routes.at(route.first).remove_stop(stop);
            stop_removed = true;
            continue;
        }
        else{
            continue;
        }
    }

    // if no stops were removed, prints the correct text
    if (not stop_removed){
        cout << "Error: Stop could not be found." << endl;
        return;
    }
    cout << "Stop was removed from all lines." << endl;
}

// function splits the line correctly, accounting for
// stop and route names with multiple words
vector<string> split_line_correctly(string line){

    vector<string> parts = split(line, ' ');
    vector<string> parts_to_return;

    string word;
    string word_string;

    // going through the split words, and finding the ones
    // which have quotation marks.
    for (unsigned int i=0 ; i<parts.size(); i++){
        word = parts.at(i);

        // if the words first letter is a quotation mark
        // we need check if it also end in a quotation mark.
        // if it doesnt, we can just add the word to the word_string
        // with the quotation marks removed.
        if(word.at(0) == '"'){
            if(word.at(word.size()-1) == '"'){
                word.erase(word.begin());
                word.pop_back();
                parts_to_return.push_back(word);
                continue;
            }
            else{
                word.erase(word.begin());
                word_string += word;
                continue;
            }
        }

        // if the word ends in a quotation mark,
        // we can remove it and add the rest of the word
        // to the word_string. The string is then added to
        // the parts_to_return.
        if(word.at(word.size()-1) == '"'){
            word.pop_back();
            word_string += " " + word;
            parts_to_return.push_back(word_string);
            word_string = "";
            continue;

        }

        // if the word doesn't have quotation marks,
        // we need to check whether word_string is
        // empty. If it isn't, we can add it to the word_string
        else{
            if (word_string == ""){
                parts_to_return.push_back(word);
            }
            else{
                word_string += " " + word;
            }
        }
    }
    return parts_to_return;

}

// Short and sweet main.
int main()
{
    print_rasse();
    map <string, Route> routes;
    if (not read_input(routes)){
        return EXIT_FAILURE;
    }

    // this main loop is looped as long as the user
    // enters the quit command.
    while(true){
        string line;
        cout << "tramway> ";
        getline(cin, line);

        // the given line is split into parts, which are then
        // used in the commands
        vector<string> parts = split_line_correctly(line);
        upper(parts.at(0));
        string command = parts.at(0);

        if (command == "LINES"){
            print_routes(routes);
        }

        else if (command == "LINE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string route = parts.at(1);
            if (routes.find(route) == routes.end()){
                cout << "Error: Line could not be found." << endl;
                continue;
            }
            print_single_route(routes, route);
        }

        else if (command == "STOPS"){
            print_stops(routes);
        }

        else if (command == "STOP"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string stop = parts.at(1);
            print_stop(routes, stop);
        }

        else if (command == "DISTANCE"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }

            string route = parts.at(1);
            string stop_1 = parts.at(2);
            string stop_2 = parts.at(3);
            if (routes.find(route) == routes.end()){
                cout << "Error: Line could not be found." << endl;
                continue;
            }
            distance(routes, route, stop_1, stop_2);
        }

        else if (command == "ADDLINE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string route = parts.at(1);
            add_route(routes, route);
        }

        else if (command == "ADDSTOP"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string route = parts.at(1);
            string stop = parts.at(2);
            double distance = stod(parts.at(3));

            add_stop(routes, route, stop, distance);
        }

        else if (command == "REMOVE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            string stop = parts.at(1);
            remove(routes, stop);
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
