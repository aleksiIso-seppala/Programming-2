#include <iostream>
#include "stop.hh"
#include <string>

Stop::Stop(std::string name, double distance):
    name_(name), distance_(distance){

}

std::string Stop::get_name(){
    return name_;
}

double Stop::get_distance(){
    return distance_;
}


