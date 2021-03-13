#include <iostream>
#include "route.hh"
#include <string>
#include <vector>

Route::Route(std::string name):
    name_(name){

}

std::string Route::get_name(){
    return name_;
}

std::map<std::string, double> Route::get_map(){
    return stops_;
}

void Route::add_stop(std::string stop,double distance){

    stops_distance_key_.insert({distance,stop});

    stops_.insert({stop, distance});

}

std::map<double, std::string> Route::get_distance_map(){
    return stops_distance_key_;
}

void Route::remove_stop(std::string stop){

    double distance = stops_.at(stop);
    stops_.erase(stop);
    stops_distance_key_.erase(distance);
    if (stops_.find(stop) != stops_.end()){
        std::cout << "Stop found" << std::endl;
    }
    if (stops_distance_key_.find(distance) != stops_distance_key_.end()){
        std::cout << "Stop found" << std::endl;
    }
}
