#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number;
    int number_squared = number * number * number;

    if ( number_squared < 0 or number_squared < number) {
        cout << "Error! The cube of " << number << " is not " << number_squared << "." << endl;
    }
    else {
      cout << "The cube of " << number << " is " << number_squared << "." << endl;
    }
    return 0;
}
