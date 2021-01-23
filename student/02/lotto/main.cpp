#include <iostream>

using namespace std;

int main()
{
    unsigned long int total_balls = 0;
    cout << "Enter the total number of lottery balls: " << endl;
    cin >> total_balls;

    unsigned long int drawn_balls = 0;
    cout << "Enter the number of drawn balls: " << endl;
    cin >> drawn_balls;

    return 0;
}

int check_number (unsigned long int total_balls, unsigned long int drawn_balls) {

    if (total_balls <= 0 or drawn_balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
    }
    else if (total_balls < drawn_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls" << endl;
    }
    else {
        return 1;
    }
}
