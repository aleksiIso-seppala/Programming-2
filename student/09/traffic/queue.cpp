#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) :
    cycle_(cycle),
    size_(0),
    light_("RED"),
    current_cycle_(cycle)
{}

void Queue::enqueue(string reg){

    if(light_ == "GREEN"){
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
        --current_cycle_;
        if(current_cycle_ == 0){
            light_ = "RED";
        }
        return;
    }

    Vehicle* new_vehicle = new Vehicle;
    new_vehicle->reg_num = reg;
    new_vehicle->next = first_;

    if (size_ > 0){
        first_->prev = new_vehicle;
    }
    first_ = new_vehicle;
    ++size_;

    if(size_ == 1){
        last_ = first_;
    }

}

void Queue::switch_light(){

    if (light_ == "GREEN"){
        light_ = "RED";
    }
    else{
        light_ = "GREEN";
    }
    if (size_ == 0){
        std::cout << light_ << ": No vehicles waiting in traffic lights" << endl;
        return;
    }
    std::cout << light_ << ": Vehicle(s) ";
    while(size_ > 0){
        Vehicle* second = last_->prev;
        string reg = last_->reg_num;
        delete last_;
        last_ = second;
        --size_;
        --current_cycle_;
        std::cout << reg << " ";
        if (current_cycle_ < 1){
            break;
        }
    }
    current_cycle_ = cycle_;
    std::cout << "can go on" << std::endl;
    light_ = "RED";
    return;


}

void Queue::print(){

    Vehicle* current = last_;

    if(size_ == 0){
        std::cout << light_ << ": No vehicles waiting in traffic lights" << std::endl;
        return;
    }
    std::cout << light_ << ": Vehicle(s) ";
    while (current != nullptr)
    {
        std::cout << current->reg_num << " ";
        current = current->prev;
    }
    std::cout << "waiting in traffic lights" << std::endl;
}

void Queue::reset_cycle(unsigned int cycle){
    cycle_ = cycle;
    current_cycle_ = cycle;
}

Queue::~Queue(){

    Vehicle* current = last_;
    while (current != nullptr)
    {
        Vehicle* tmp = current->prev;
        delete current;
        current = tmp;
    }
}
