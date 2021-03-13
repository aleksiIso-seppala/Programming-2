#ifndef STOP_HH
#define STOP_HH
#endif // STOP_HH
#include <string>

class Stop
{
public:

    Stop(std::string name, double distance);

    // below are the methods used
    std::string get_name();

    double get_distance();

private:

    std::string name_;
    double distance_;
};
