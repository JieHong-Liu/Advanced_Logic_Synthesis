#ifndef STATE_ASSIGNER_H
#define STATE_ASSIGNER_H
#include <fstream>
#include <iostream>
class State_assigner
{
public:
    State_assigner();   //constructor
    void parser(std::ifstream& inputFile); // a parser parse kiss file into our class
private:
    int state_code;

};

#endif