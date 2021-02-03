#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

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
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
