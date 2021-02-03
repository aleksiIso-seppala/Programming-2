#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);

    }
}

// TODO: Implement your solution here

bool same_values(std::vector<int> ints){
    int first_number = ints.at(0);
    for (int number : ints){
        if (first_number != number){
                return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(std::vector<int> ints){
    int vector_size = ints.size() - 1;
    for (int number = 0; number <= vector_size; ++number){
        if (number == 0){
            continue;
        }
        if ( ints.at(number-1) > ints.at(number)){
                return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector<int> ints){
    int vector_size = ints.size() -1 ;
    for (int number = 0; number <= vector_size; ++number){
        int arithmetic_number = ints.at(1) - ints.at(0);
        if (number == 0){
            continue;
        }
        if (ints.at(number) - ints.at(number-1) != arithmetic_number){
            return false;
        }
    }

    return true;
}

bool is_geometric_series(std::vector<int> ints){

    int vector_size = ints.size() - 1;
    for (int number = 0; number <= vector_size; ++number){
        if (ints.at(number) == 0){
            return false;
        }
        if (number == 0){
            continue;
        }
        int geometric_number = ints.at(1) / ints.at(0);

        if (ints.at(number) / ints.at(number-1) != geometric_number){
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
