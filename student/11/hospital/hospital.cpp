/*
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username  : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 * */

#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

// Deallocator for the various elements created in the program
Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocating all patients
    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocating all care periods.
    while (care_periods_.size() != 0){
        delete care_periods_.at(care_periods_.size()-1);
        care_periods_.pop_back();
    }
}


// this function rectuits a new staff member for the hospital
void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

// Allows a new or a returning patient to enter the hospital
void Hospital::enter(Params params)
{
    std::string patient = params.at(0);

    // first we need to check if the patient is in the hospital already
    if (current_patients_.find(patient) != current_patients_.end()){
        std::cout << ALREADY_EXISTS << patient << std::endl;
        return;
    }

    // this is to check whether the patient is a new patient or
    // a returning one. If he is new, a new Person object is
    // created.
    if (all_patients_.find(patient) == all_patients_.end()){
        Person* new_patient = new Person(patient);
        all_patients_.insert({patient, new_patient});
    }

    // creating a new care period and adding the patient and
    // and the care period to the correct structures.
    current_patients_.insert(patient);
    CarePeriod* new_careperiod = new CarePeriod(utils::today,
                                                all_patients_.at(patient));
    care_periods_.push_back(new_careperiod);

    std::cout << PATIENT_ENTERED << std::endl;
}

// This function allows the patient to leave the hospital.
// Basically it closes the care period and removes the patient
// from current patients.
void Hospital::leave(Params params)
{
    std::string patient = params.at(0);

    // check for if the patient even is in the hospital
    if (current_patients_.find(patient) == current_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    Date date = utils::today;

    // going through the care periods and finding the correct one to close
    for(unsigned int i=0;i<care_periods_.size();i++){
        if(care_periods_.at(i)->get_patient() == patient
                and care_periods_.at(i)->is_open())
        {
            care_periods_.at(i)->close_period(date);
        }
    }

    current_patients_.erase(patient);
    std::cout << PATIENT_LEFT << std::endl;

}

// Assigns new staff for a patients care period
void Hospital::assign_staff(Params params)
{
    std::string staff = params.at(0);
    std::string patient = params.at(1);

    // check for if the staff member is in the hospital
    if (staff_.find(staff) == staff_.end()){
        std::cout << CANT_FIND << staff << std::endl;
        return;
    }

    // check for if the patient is in the hospital
    if (current_patients_.find(patient) == current_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    // going through the care periods to find the one to add staff for
    unsigned int i = 0;
    for(i=0;i<care_periods_.size();i++){
        if(care_periods_.at(i)->get_patient() == patient
                and care_periods_.at(i)->is_open())
        {
            care_periods_.at(i)->assign_staff(staff);
            break;
        }
    }
    std::cout << STAFF_ASSIGNED << patient << std::endl;

}

// adds medicine for a current patient, medicine cannot
// be added to a patient not in the hospital
void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::set<std::string>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    all_patients_.at(patient)->
            add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}


// removes medicine from a a current patient, medicine cannot
// be removed from a patient not in the hospital
void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::set<std::string>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    all_patients_.at(patient)->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

// prints all the information about a patient, including
// their care periods, the staff assigned to them and
// their medicines.
void Hospital::print_patient_info(Params params)
{
    std::string patient = params.at(0);

    // check for if the patient has been in the hospital
    if(all_patients_.find(patient) == all_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    // going through the care periods to find the one the
    // patient is in and printing the correct information
    for (unsigned int i=0; i<care_periods_.size();i++){

        if (care_periods_.at(i)->get_patient() == patient){
            std::cout << "* Care period: ";
            care_periods_.at(i)->print_start();
            std::cout << " - ";
            care_periods_.at(i)->print_end();
            std::cout << std::endl;

            std::cout << "  - Staff:";
            care_periods_.at(i)->print_staff();
            std::cout << std::endl;
        }
    }

    // printing all the medicines assigned to the patients
    std::cout << "* Medicines:";
    all_patients_.at(patient)->print_medicines("  - ");
}


// prints all the care periods that a staff member is part of.
void Hospital::print_care_periods_per_staff(Params params)
{

    std::string staff_member = params.at(0);

    // check for if the staff member is in the hospital
    if (staff_.find(staff_member) == staff_.end()){
        std::cout << CANT_FIND << staff_member << std::endl;
        return;
    }

    // going through the care periods to find the ones in
    // which a staff member is part of, also printing the
    // correct information.)
    bool care_periods_found = false;
    for (unsigned int i=0; i<care_periods_.size();i++){
        if (care_periods_.at(i)->find_staff(staff_member)){
            care_periods_.at(i)->print_start();
            std::cout << " - ";
            care_periods_.at(i)->print_end();
            std::cout << std::endl;

            std::cout << "* Patient: "
            << care_periods_.at(i)->get_patient() << std::endl;

            care_periods_found = true;
        }
    }

    // if the staff member is not in any care periods
    // the following will be printed
    if (not care_periods_found){
        std::cout << "None" << std::endl;
    }

}

// printing all the medicines assigined to patients
// in alphabetical order
void Hospital::print_all_medicines(Params)
{
    // collecting all the medicines to a set
    std::set<std::string> medicines;

    // going through all the patients to find all medicines
    // that are prescribed for them
    for (auto patient : all_patients_){
        for (auto medicine : patient.second->get_medicines()){
            if(medicines.find(medicine) == medicines.end()){
                medicines.insert(medicine);
            }
        }
    }
    if (medicines.size() == 0){
        std::cout << "None" << std::endl;
        return;
    }
    // printing all the medicines in the correct order
    for (auto medicine : medicines){
        std::cout << medicine << " prescribed for" << std::endl;
        for (auto patient : all_patients_){
            for (auto medicine_ : patient.second->get_medicines()){
                if (medicine == medicine_){
                    std::cout << "* " << patient.second->get_id() << std::endl;
                }
            }
        }
    }
}

// prints all staff members in alphabetical order
void Hospital::print_all_staff(Params)
{
    // if no staff is in the hospital, prints
    // the following
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    // going through the staff members and printing them
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

// printing all the patients and their information.
// Uses print_patient_information to print the
// information
void Hospital::print_all_patients(Params)
{
    // if no patients have been to the hospital
    // prints the following
    if (all_patients_.empty() ){
        std::cout << "None" << std::endl;
        return;
    }

    // going through all patients and using
    // the print_patient_info to print
    // the correct lines.
    for (auto patient : all_patients_){
        std::cout << patient.first << std::endl;
        std::vector<std::string> param;
        param.push_back(patient.first);
        print_patient_info(param);
    }
}

// prints all the current patients and their information
// works in the same way as print_all_patients, but for
// current patients only
void Hospital::print_current_patients(Params)
{
    // if there are no currecnt patients,
    // prints the following
    if (current_patients_.empty() ){
        std::cout << "None" << std::endl;
        return;
    }

    // going through the current patients and
    // uses the print_patient_information function
    // to print the correct information.
    for (auto patient : current_patients_){
        std::cout << patient << std::endl;
        std::vector<std::string> param;
        param.push_back(patient);
        print_patient_info(param);
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}



