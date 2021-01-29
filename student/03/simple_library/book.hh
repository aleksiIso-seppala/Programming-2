#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"

class Book
{
public:
    Book(std::string author_, std::string title_, bool loaned_ = false);

    //methods
    void print() const;
    void loan(Date today);
    void renew();
    void give_back();
private:

    //attributes
    std::string author_;
    std::string title_;
    bool loaned_;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_HH
