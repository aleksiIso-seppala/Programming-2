#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
   int seed_value;
   cout << "Enter a seed value: ";
   cin >> seed_value;

   default_random_engine gen(seed_value);
   uniform_int_distribution<int> distr(lower, upper);

   while(1){
       cout << endl;
       cout << "Your drawn random number is " << distr(gen) << endl;

       char command;
       cout << "Press c to continue or q to quit: ";
       cin >> command;

       if (command == 'c'){
           continue;
       }
       if (command == 'q'){
           break;
       }
   }
}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
