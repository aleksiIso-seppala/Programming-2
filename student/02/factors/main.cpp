#include <iostream>
#include <math.h>    /* sqrt */

using namespace std;

int main()
{
    int number = 0;

    cout << "Enter a positive number: ";
    cin >> number;
    if ( number <= 0) {
        cout << "Only positive numbers accepted" << endl;
    }


    int number_rooted = sqrt(number);
    int index = number_rooted;
    while (index > 0 ) {

        if (number % index == 0) {
            int number2 = 0;
            number2 = number / index;
            cout << number << " = " << index << " * " << number2 << endl;
            break;
        }
    --index;
    }


    return 0;
}
