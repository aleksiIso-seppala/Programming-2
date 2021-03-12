#ifndef STOP_HH
#define STOP_HH
#endif // STOP_HH
#include <string>
#include <map>
class Stop
{
public:

    Stop(std::string name);

    // below are the methods used
    std::string get_name();

    double get_distance(std::string route);

    void add_stop(std::string route, double distance);
private:

    std::string name_;
    std::map<std::string, double> distances_;
};
