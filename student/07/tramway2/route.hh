#ifndef ROUTE_HH
#define ROUTE_HH

#endif // ROUTE_HH
#include <string>
#include <map>
#include <vector>
class Route
{
public:

    Route(std::string name);

    // below are the methods used
    std::string get_name();

    std::map<std::string, double> get_map();

    std::map<double, std::string> get_distance_map();

    void add_stop(std::string, double);

    void remove_stop(std::string);

private:

    std::string name_;
    std::map<std::string, double> stops_;
    std::map<double, std::string> stops_distance_key_;
};
