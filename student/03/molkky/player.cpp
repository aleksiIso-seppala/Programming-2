#include "player.hh"
#include <iostream>
#include <string>

Player::Player(std::string name):
    name(name){

}

std::string Player::get_name(){
    return name;
}
int Player::get_points(){
    return score;
}
void Player::add_points(int points){
    score += points;
    if (score > 50){
        std::cout << name << " gets penalty points!" << std::endl;
        score = 25;
    }
    return;
}

bool Player::has_won(){
    if (score == 50){
        return true;
    }
    return false;
}
