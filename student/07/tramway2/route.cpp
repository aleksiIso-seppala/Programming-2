/*
 *  * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 * */

#include <iostream>
#include "route.hh"
#include <string>
#include <map>

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
}
