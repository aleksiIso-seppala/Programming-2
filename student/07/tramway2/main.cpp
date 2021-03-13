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

bool check_input(map<string, Route> routes, string route, string stop, double distance){

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
            if(not check_input(routes, route, stop, distance)){
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

void print_lines(map <string, Route> routes){

    cout << "All tramlines in alphabetical order:" << endl;
    for (auto route : routes){
        cout << route.first << endl;
    }
}

void print_single_line(map<string, Route> routes, string route){

    cout << "Line " << route <<
            " goes through these stops in the order they are listed:" << endl;

    map<double,string> distance_map = routes.at(route).get_distance_map();
    for(auto stop : distance_map){
        cout << stop.first << " : " << stop.second << endl;
    }
}

void print_stops(map<string, Route> routes){

    set<string> stops_in_set;

    for (auto route : routes){
        for(auto stop : route.second.get_map()){
            if (stops_in_set.find(stop.first) == stops_in_set.end()){
                stops_in_set.insert(stop.first);
            }

        }
    }
    cout << "All stops in alphabetical order:" << endl;
    for (auto stop : stops_in_set){
        cout << stop << endl;
    }
}

void stop(map<string, Route> routes, string stop){


    bool stop_found = false;
    for (auto route : routes){

            // if the stop is found, the corresponding line
            // is printed
            if (route.second.get_map().find(stop) != route.second.get_map().end()){

                // this is to ensure that the text is printed only once
                if(not stop_found){
                    cout << "Stop " << stop << " can be found on the following lines:" << endl;
                }
                cout << "- " << route.first << endl;
                stop_found = true;
                continue;
            }
    }
    // if a stop is not found, the following text is printed
    if(not stop_found){
        cout << "Stop could not be found" << endl;
        return;
    }

}

void distance(map<string, Route> routes, string route, string stop_1, string stop_2){

    map<string, double> map = routes.at(route).get_map();
    cout << "Distance between " << stop_1 << " and " << stop_2 << " is " <<
            abs(map.at(stop_1)-map.at(stop_2)) << endl;
}

void add_route(map<string, Route>& routes, string route){

    if (routes.find(route) != routes.end()){
        cout << "Error: Stop/line already exists." << endl;
        return;
    }
    Route new_route = Route(route);
    routes.insert({route, new_route});
    cout << "Line was added." << endl;
}

void add_stop(map<string, Route>& routes,string route,string stop,double distance){

    if(not check_input(routes, route, stop, distance)){
        cout << " Error: Stop/line already exists." << endl;
        return;
    }
    routes.at(route).add_stop(stop, distance);
    cout << "Stop was added." << endl;

}

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

vector<string> split_line_correctly(string line){

    vector<string> parts = split(line, ' ');
    vector<string> two_part_names = split(line, '"');

    if(two_part_names.size() <= 1){
        return parts;
    }

    return two_part_names;
}

// Short and sweet main.
int main()
{
    print_rasse();
    map <string, Route> routes;
    if (not read_input(routes)){
        return EXIT_FAILURE;
    }
    while(true){
        string line;
        cout << "tramway> ";
        getline(cin, line);
        vector<string> parts = split_line_correctly(line);
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
            string route = parts.at(1);
            if (routes.find(route) == routes.end()){
                cout << "Error: Line could not be found." << endl;
                continue;
            }
            print_single_line(routes, route);
        }

        else if (command == "STOPS"){
            print_stops(routes);
        }

        else if (command == "STOP"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            stop(routes, parts.at(1));
        }

        else if (command == "DISTANCE"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            if (routes.find(parts.at(1)) == routes.end()){
                cout << "Error: Line could not be found." << endl;
                continue;
            }
            distance(routes, parts.at(1), parts.at(2), parts.at(3));
        }

        else if (command == "ADDLINE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            add_route(routes, parts.at(1));
        }

        else if (command == "ADDSTOP"){
            if (parts.size() < 4){
                cout << "Error: Invalid input." << endl;
                continue;
            }

            double distance = stod(parts.at(3));
            add_stop(routes, parts.at(1), parts.at(2), distance);
        }

        else if (command == "REMOVE"){
            if (parts.size() < 2){
                cout << "Error: Invalid input." << endl;
                continue;
            }
            remove(routes, parts.at(1));
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
