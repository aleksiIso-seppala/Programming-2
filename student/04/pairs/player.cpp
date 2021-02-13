#include "player.hh"
#include "card.hh"
#include <iostream>


// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.
Player::Player(const std::string name):
    name(name){

}

std::string Player::get_name() const{
    return name;
}

unsigned int Player::number_of_pairs() const{
    return pairs;
}

void Player::print() const{

    std::cout << "*** " << name << " has " << pairs << " pair(s)." << std::endl;
}

void Player::add_card(){
    pairs = pairs + 1;
}
