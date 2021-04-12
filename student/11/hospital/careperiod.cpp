#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::close_period()
{
    end_ = utils::today;
}

void CarePeriod::assign_staff(std::string staff)
{
    assigned_staff_.insert(staff);
}

void CarePeriod::print_start()
{
    start_.print();
}

void CarePeriod::print_end()
{
    if (end_ == not_set_){
        return;
    }
    end_.print();
}

void CarePeriod::print_staff()
{
    if (assigned_staff_.size() == 0){
        std::cout << " None";
        return;
    }
    for(auto member : assigned_staff_){
        std::cout << " " << member;
    }
}
