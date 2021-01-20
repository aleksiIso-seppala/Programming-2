#include <iostream>

using namespace std;

int main()
{
    double asteet = 0;
    cout << "Enter a temperature: ";
    cin >> asteet;

    double asteet_Fahrenheit = asteet * 1.8 + 32;
    double asteet_Celsius = ( asteet - 32) / 1.8;

    cout << asteet << " degrees Celsius is " << asteet_Fahrenheit << " degrees Fahrenheit" << endl;
    cout << asteet << " degrees Fahrenheit is " << asteet_Celsius << " degrees Celsius" << endl;

    // Write your code here

    return 0;
}
