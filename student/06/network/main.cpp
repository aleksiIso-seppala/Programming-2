#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using namespace std;

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
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
void save (string user1, string user2, map<string, vector<string>>& users){

    if (users.find(user1) != users.end()){
        users.at(user1).push_back(user2);
    }
    else{
        vector<string> empty_vector;
        users.insert({user1, empty_vector});
        users.at(user1).push_back(user2);
    }
}


void print (string user, map<string, vector<string>> users, int& dots){

    if( dots == 0){
        cout << user << endl;
        dots += 2;
    }

    if (users.find(user) == users.end()){
        cout << string(dots, '.') << user << endl;
        dots -= 2;
        return;
    }
    int current_dots = dots;
    for(auto name : users.at(user)){
        dots = current_dots;
        cout << string(dots, '.') << name << endl;
        if (users.find(name) == users.end()){
            if (dots > 2){
                dots -= 2;
            }
            continue;
        }
        else{
            dots += 2;
            print(name, users, dots);
        }
    }
}

int count (string user, map<string, vector<string>> users, int& network_size){

    if (users.find(user) == users.end()){
        return 0;
    }
    network_size += users.at(user).size();

    for (auto name : users.at(user)){
        if (users.find(name) == users.end()){
            continue;
        }
        else{
            count(name, users, network_size);
            continue;
        }
    }
    return network_size;
}

int depth (string user, map<string, vector<string>> users, int depth_amount = 1){

    int max_depth = depth_amount;
    if (users.find(user) == users.end()){
        return max_depth;
    }
    for (const string& name : users.at(user)){
        int current_depth = depth(name, users, depth_amount + 1);
        max_depth = max(max_depth, current_depth);
    }

    return max_depth;
}

int main()
{
    // TODO: Implement the datastructure here
    map<string, vector<string>> users;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            save(id1, id2, users);
            // TODO: Implement the command here!

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int dots = 0;
            print(id, users, dots);
            // TODO: Implement the command here!

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int amount = 0;
            cout << count(id, users, amount) << endl;
            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            int depth_amount = 1;
            cout << depth(id, users, depth_amount) << endl;
            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
