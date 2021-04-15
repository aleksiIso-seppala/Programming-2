/*
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username  : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 *
 * */

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
    open_period_ = false;
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
    if (open_period_){
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
    return open_period_;
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
