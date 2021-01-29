#include "book.hh"
#include "date.hh"
#include <iostream>
#include <string>

Book::Book(std::string author_, std::string title_, bool loaned_):
    author_(author_), title_(title_), loaned_(loaned_){

}

void Book::print() const{
    std::cout << author_ << " : " << title_ << std::endl;
    if (not loaned_){
        std::cout << "- available" << std::endl;
        return;
    }
    std::cout << "- loaned: ";
    loan_date_.print();
    std::cout << "- to be returned: ";
    return_date_.print();
}

void Book::loan(Date today){
    if (loaned_){
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }

    loaned_ = true;
    loan_date_ = today;
    today.advance(28);
    return_date_ = today;
    return;
}

void Book::renew(){
    if (not loaned_){
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }
    return_date_.advance(28);
}
void Book::give_back(){
    loaned_ = false;
}
