#include <iostream>


int main()
{
    int numero = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> numero;

    int i = 1;
    while ( i <= numero ) {
        std::cout << i << std::endl;
        ++i;
    }
}
