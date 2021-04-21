#ifndef GIRAFFE_HH
#define GIRAFFE_HH
#include "mammal.hh"

#endif // GIRAFFE_HH

class Giraffe: public Mammal
{
public:
    Giraffe();
    void make_noise(std::ostream& output) const;

};
