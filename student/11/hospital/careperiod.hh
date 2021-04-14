/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "utils.hh"
#include "person.hh"
#include "date.hh"
#include <string>
#include <set>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    void close_period(Date);
    void assign_staff(std::string);
    void print_start();
    void print_end();
    void print_staff();
    std::string get_patient();
    bool is_open();
    bool find_staff(std::string);

private:
    Person* patient_;
    Date start_;
    Date end_;
    Date not_set_;

    std::set<std::string> assigned_staff_;
    // More attributes and methods
};

#endif // CAREPERIOD_HH
