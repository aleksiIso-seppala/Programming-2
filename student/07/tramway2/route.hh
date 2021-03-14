/* Class: Route
 *
 * depicts a single route in the tramway system
 *
 * Writer of the program
 * Name : Aleksi Iso-Seppälä
 * Student-id : H292168
 * username : fsalis
 * E-Mail : aleksi.iso-seppala@tuni.fi
 **/

#ifndef ROUTE_HH
#define ROUTE_HH

#endif // ROUTE_HH
#include <string>
#include <map>
class Route
{
public:

    Route(std::string name);

    // below are the methods used

    // returns the name of the route
    std::string get_name();

    // returns the map in which the stops are stored
    std::map<std::string, double> get_map();

    // returns a map where the stops are stored
    // in order of the distance
    std::map<double, std::string> get_distance_map();

    // adds a new stop to both maps
    void add_stop(std::string, double);

    // removes a stop from both maps
    void remove_stop(std::string);

private:

    // the route has a name, and two maps in which the
    // stops are stored. stops_ have the stops normally
    // with the stops name being the key and its
    // distance the payload. stops_distance_key_ has
    // the same information but the name and distance
    // are reversed.

    std::string name_;
    std::map<std::string, double> stops_;
    std::map<double, std::string> stops_distance_key_;
};
