#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

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

    for( std::map<std::string, Person*>::iterator
         iter = all_patients_.begin();
         iter != all_patients_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
}

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

void Hospital::enter(Params params)
{
    std::string patient = params.at(0);
    if (current_patients_.find(patient) != current_patients_.end()){
        std::cout << ALREADY_EXISTS << patient << std::endl;
        return;
    }

    if (all_patients_.find(patient) == all_patients_.end()){
        Person* new_patient = new Person(patient);
        all_patients_.insert({patient, new_patient});
    }

    current_patients_.insert(patient);

    CarePeriod* new_careperiod = new CarePeriod(utils::today, all_patients_.at(patient));
    care_periods_.push_back(new_careperiod);
    std::cout << PATIENT_ENTERED << std::endl;

}

void Hospital::leave(Params params)
{
    std::string patient = params.at(0);
    if (current_patients_.find(patient) == current_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    Date date = utils::today;

    for(unsigned int i=0;i<care_periods_.size();i++){
        if(care_periods_.at(i)->get_patient() == patient and care_periods_.at(i)->is_open()){
            care_periods_.at(i)->close_period(date);
        }
    }
    current_patients_.erase(patient);
    std::cout << PATIENT_LEFT << std::endl;

}

void Hospital::assign_staff(Params params)
{
    std::string staff = params.at(0);
    std::string patient = params.at(1);

    if (staff_.find(staff) == staff_.end()){
        std::cout << CANT_FIND << staff << std::endl;
        return;
    }

    if (current_patients_.find(patient) == current_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

    unsigned int i = 0;
    for(i=0;i<care_periods_.size();i++){
        if(care_periods_.at(i)->get_patient() == patient and care_periods_.at(i)->is_open()){
            break;
        }
    }
    std::cout << STAFF_ASSIGNED << patient << std::endl;
    care_periods_.at(i)->assign_staff(staff);

}

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
    all_patients_.at(patient)->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

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

void Hospital::print_patient_info(Params params)
{
    std::string patient = params.at(0);

    if(all_patients_.find(patient) == all_patients_.end()){
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }

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
    std::cout << "* Medicines:";
    all_patients_.at(patient)->print_medicines("  - ");
}

void Hospital::print_care_periods_per_staff(Params params)
{

    std::string staff_member = params.at(0);

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

    if (not care_periods_found){
        std::cout << "None" << std::endl;
    }

}
void Hospital::print_all_medicines(Params)
{
    // collecting all the medicines to a set
    std::set<std::string> medicines;
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
            for (auto medicine__ : patient.second->get_medicines()){
                if (medicine == medicine__){
                    std::cout << "* " << patient.second->get_id() << std::endl;
                }
            }
        }
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    for (auto patient : all_patients_){
        std::cout << patient.first << std::endl;
        std::vector<std::string> param;
        param.push_back(patient.first);
        print_patient_info(param);
    }
}

void Hospital::print_current_patients(Params)
{
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


