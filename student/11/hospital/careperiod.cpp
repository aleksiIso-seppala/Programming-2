#include "careperiod.hh"
#include "utils.hh"
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

void CarePeriod::close_period(Date date)
{
    end_ = date;
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

std::string CarePeriod::get_patient()
{
    return patient_->get_id();
}

bool CarePeriod::is_open()
{
    if (end_ == not_set_){
        return true;
    }
    return false;
}

bool CarePeriod::find_staff(std::string staff)
{
    for(auto member : assigned_staff_){
        if (member == staff){
            return true;
        }
    }
    return false;
}
