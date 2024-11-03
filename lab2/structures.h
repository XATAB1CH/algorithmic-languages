#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <string>

struct Pipeline
{
    std::string kilometer_sign;
    int length_of_pipe;
    short int diameter;
    bool repair_indicator;
};

struct CS
{
    std::string name;
    int number_of_workshops;
    int workshops_in_work;
    short int efficiency;
};

#endif /* STRUCTURES_H_ */