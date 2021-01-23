#include <iostream>

using namespace std;

string check_number (long int total_balls, long int drawn_balls) {

    string pass = "z";
    if (total_balls <= 0 or drawn_balls <= 0) {
        cout << "The number of balls must be a positive number." << endl;
        return pass;
    }
    else if (total_balls < drawn_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return pass;
    }
    else {
        pass = "q";
        return pass;
    }
}

long int factorial (long int number) {

    long int n = 1;
    for (long int i = 1; i <= number; i++) {
        n = n * i;
    }
    return n;
}

long int calculate_probability (long int total_balls, long int drawn_balls) {

    long int total_drawn = total_balls - drawn_balls;
    total_drawn = factorial(total_drawn);

    total_balls = factorial(total_balls);

    drawn_balls = factorial (drawn_balls);

    return (total_balls / (total_drawn * drawn_balls));
}

int main() {
    long int total_balls = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> total_balls;

    long int drawn_balls = 0;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    string pass_number = "q";
    pass_number = check_number(total_balls, drawn_balls);

    if (pass_number == "q") {
        long int probability = 0;
        probability = calculate_probability(total_balls, drawn_balls);
        cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << probability << endl;
    }

    return 0;

}

