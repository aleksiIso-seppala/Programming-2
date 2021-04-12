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
