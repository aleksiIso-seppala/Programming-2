#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods

    // method for setting a credit limit
    void set_credit_limit(int limit);

    // method for saving money
    void save_money(int amount);
    // method for printing an account
    void print() const;
    // method for taking money from an account
    void take_money(int amount);

    // method for transferring money
    void transfer_to(Account account, int amount);

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    bool has_credit_;
    std::string owner_;
    int credit_limit_ = 0;
    int money_ = 0;
    std::string iban_ = "";

};

#endif // ACCOUNT_HH
