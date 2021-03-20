#include <iostream>
#include <vector>
#include <string>

using namespace std;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               const bool ignore_empty = false) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


int main()
{
    char character;
    string line;
    vector<char> parts;
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    while(true){
        cin >> character;
        if(character == '#'){
            break;
        }
        parts.push_back(character);
    }
    vector<char> operators;
    vector<int> operands;
    for(unsigned int i=0; i<parts.size();i++){
        if(isdigit(parts.at(i))){
            operands.push_back(parts.at(i));
        }
        else{
            if(i == 0){
                cout << "Error: Expression must start with a number" << endl;
                return EXIT_FAILURE;
            }
            operators.push_back(parts.at(i));
        }
    }
    if(operators.size() != operands.size()-1){
        if (operators.size() > operands.size()-1){
            cout << "Error: Too few operands" << endl;
            return EXIT_FAILURE;
        }
        else{
            cout << "Error: Too few operators" << endl;
            return EXIT_FAILURE;
        }
    }

    vector<int> calculate;

    for(unsigned int i=0; i<parts.size();i++){
        int sum = 0;
        if(isdigit(parts.at(i))){
            int number = (int)parts.at(i)-48;
            calculate.push_back(number);
            continue;
        }
        char operand = parts.at(i);
        if(operand == '+'){
            sum = (calculate.at(calculate.size()-1)) + (calculate.at(calculate.size()-2));
        }

        else if(operand == '-'){
            sum = abs((calculate.at(calculate.size()-1)) - (calculate.at(calculate.size()-2)));
        }

        else if(operand == '/'){
            if (calculate.at(calculate.size()-1) == 0){
                cout << "Error: Division by zero" << endl;
                return EXIT_FAILURE;
            }
            sum = (calculate.at(calculate.size()-2)) / (calculate.at(calculate.size()-1));
        }

        else if(operand == '*'){
            sum = (calculate.at(calculate.size()-1)) * (calculate.at(calculate.size()-2));
        }
        else{
            cout << "Error: Unknown character" << endl;
            return EXIT_FAILURE;
        }
        calculate.pop_back();
        calculate.pop_back();
        calculate.push_back(sum);
    }
    cout << "Correct: " << calculate.at(0) << " is the result" << endl;

}
