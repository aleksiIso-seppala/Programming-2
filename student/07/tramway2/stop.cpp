#include <iostream>
#include "stop.hh"
#include <map>
#include <string>

Stop::Stop(std::string name):
    name_(name){

}

std::string Stop::get_name(){
    return name_;
}

double Stop::get_distance(std::string route){
    return distances_.at(route);
}

void Stop::add_stop(std::string route, double distance){
    distances_.insert({route, distance});
    return;
}

std::map<std::string, double> Stop::get_map(){
    return distances_;
}
