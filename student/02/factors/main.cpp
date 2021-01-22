#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    while ( number <= 0 ) {
        cout << "Enter a positive number: ";
        cin >> number;
        if ( number <= 0) {
            cout << "Only positive numbers accepted" << endl;
        }


    }
    return 0;
}
