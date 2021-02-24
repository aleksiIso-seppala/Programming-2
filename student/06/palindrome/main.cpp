#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------
    int string_length = s.size();


    if (string_length <= 1){
        return true;
    }

    else{
        if(s.at(0) != s.at(string_length-1)){
        return false;
        }
        s.erase((s.end()-1),s.end());
        s.erase(s.begin(), (s.begin()+1));
        return palindrome_recursive(s);
    }


  // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
