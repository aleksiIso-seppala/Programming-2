#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
{
    Account::generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(int limit){
    if (not has_credit_){
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return;
    }
    credit_limit_ = limit;
}

void Account::save_money(int amount){
    money_ = money_ + amount;
}

void Account::print() const{
    std::cout << owner_ << " : " << iban_ << " : " << money_ << " euros" << std::endl;
}

void Account::take_money(int amount){
    if (has_credit_){
        int balance = money_ + credit_limit_;
        if ((balance - amount) < 0){
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }
        else {
            money_ = money_ - amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;
        }
    }
    else {
        if (amount > money_){
            money_ = money_ - amount;
            return;
        }
        else{
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return;
        }
    }
}

void Account::transfer_to(Account account, int amount){
    take_money(amount);
    account.save_money(amount);
}
