#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
#include <string>

class Player
{
public:
    Player(std::string name);

    //metodit
    std::string get_name();
    int get_points();
    void add_points(int points);
    bool has_won();
private:
    //attribuutit
    std::string name;
    int score;

};

#endif // PLAYER_HH
