#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "stop.hh"
#include <set>

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

bool check_input(map<string, vector<Stop>>& routes, string route, string stop, double distance){

    // check that there are no two same stops in a route
    for(unsigned long int i=0; i < routes.at(route).size(); i++){
        if (routes.at(route).at(i).get_name() == stop ){
            return false;
        }
    }

    // check that there are no two same distances in a route
    for (unsigned long int i=0; i < routes.at(route).size(); i++){
        if (routes.at(route).at(i).get_distance(route) == distance){
            return false;
        }
    }
    return true;
}
bool read_input(map <string, vector<Stop>>& routes){

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
            if (routes.find(route) == routes.end()){
                routes.insert({route, empty_vector});
            }

            if(not check_input(routes, route, stop, distance)){
                cout << " Error: Stop/line already exists." << endl;
                file.close();
                return false;
            }
            Stop new_stop = Stop(stop);
            new_stop.add_stop(route, distance);
            routes.at(route).push_back(new_stop);
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

    cout << "Line " << route <<
            " goes through these stops in the order they are listed:" << endl;
    for(unsigned long int i=0; i < routes.at(route).size(); i++){
        cout << "- " << routes.at(route).at(i).get_name() << " : " <<
                routes.at(route).at(i).get_distance(route) << endl;
    }
}

void print_stops(map<string, vector<Stop>> routes){

    set<string> stops_in_set;

    for (auto route : routes){
        for(unsigned long int i=0; i < route.second.size(); i++){
            if (stops_in_set.find(route.second.at(i).get_name()) == stops_in_set.end()){
                stops_in_set.insert(route.second.at(i).get_name());
            }

        }
    }
    cout << "All stops in alphabetical order:" << endl;
    for (auto stop : stops_in_set){
        cout << stop << endl;
    }
}

void stop(map<string, vector<Stop>> routes, string stop){


    // because we can't access a single stop without a route
    // we need to find a route which has the stop
    map<string, double> stops;
    for (auto route : routes){
        for(unsigned long int i=0; i < route.second.size(); i++){

            // if the stop is found, the correct things are printed
            // and the function ends.
            if (route.second.at(i).get_name() == stop){
                map<string, double> stops = route.second.at(i).get_map();

                cout << "Stop " << stop << " can be found on the following lines:" << endl;
                for (auto line : stops){
                    cout << "- " << line.first << endl;
                }
                return;
            }
        }
    }
    cout << "Stop could not be found" << endl;
    return;

}

void distance(map<string, vector<Stop>> routes, string route, string stop_1, string stop_2){

    double stop_1_distance;
    double stop_2_distance;
    for (unsigned long int i=0; i < routes.at(route).size(); i++){
        if (routes.at(route).at(i).get_name() == stop_1){
            stop_1_distance = routes.at(route).at(i).get_distance(route);
        }
        if (routes.at(route).at(i).get_name() == stop_2){
            stop_2_distance = routes.at(route).at(i).get_distance(route);
        }
    }
    cout << "Distance between " << stop_1 << " and " << stop_2 << " is " <<
            abs(stop_1_distance-stop_2_distance) << endl;
}

void add_line(map<string, vector<Stop>>& routes, string route){

    if (routes.find(route) != routes.end()){
        cout << "Error: Stop/line already exists." << endl;
        return;
    }

    vector<Stop> empty_vector;
    routes.insert({route, empty_vector});
    cout << "Line was added." << endl;
}

void add_stop(map<string, vector<Stop>>& routes,string route,string stop,double distance){

    if(not check_input(routes, route, stop, distance)){
        cout << " Error: Stop/line already exists." << endl;
        return;
    }

    // Check if the stop already exists as an object
    bool stop_exist = false;
    for (auto route : routes){
        for(unsigned long int i=0; i < route.second.size(); i++){

            // if the stop exists, we can just modify the object
            if (route.second.at(i).get_name() == stop and stop_exist == false){
                stop_exist = true;
                route.second.at(i).add_stop(route.first, distance);
                break;
            }
        }
    }

    // if the stop doesn't exist, we need to add a new object
    if (not stop_exist){
        Stop new_stop = Stop(stop);
        new_stop.add_stop(route, distance);
    }

    // now we need to add the new stop to the correct place in the vector
    for (unsigned long int i=0; i<routes.at(route).size(); i++){
        if(routes.at(route).at(i).get_name() == stop){

        }
    }



}
// Short and sweet main.
int main()
{
    print_rasse();
    map <string, vector<Stop>> routes;
    if (not read_input(routes)){
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
            add_line(routes, parts.at(1));
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
