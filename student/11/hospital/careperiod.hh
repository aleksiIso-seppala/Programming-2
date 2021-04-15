/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username  : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 *
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

    // closes a care period by adding a end date to it
    void close_period(Date);

    // assigns staff for a care period
    void assign_staff(std::string);

    // prints the start date of a care period
    void print_start();

    // prints the end date of a care period,
    // prints nothing if the periods is still
    // open.
    void print_end();

    // prints all the staff in a care period
    void print_staff();

    // getter function for getting the patients name
    std::string get_patient();

    // function check if a care period is still open
    bool is_open();
    bool find_staff(std::string);

private:
    Person* patient_;
    Date start_;
    Date end_;

    bool open_period_ = true;

    std::set<std::string> assigned_staff_;
    // More attributes and methods
};

#endif // CAREPERIOD_HH
