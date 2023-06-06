#ifndef STATE_ASSIGNER_H
#define STATE_ASSIGNER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <info.h> // include graph and nodeinfo class. 

class State_assigner
{
public:
    State_assigner();   //constructor
    void printCircuitStatus();
    void printTransitionMatrix(); // print the transition matrix
    void printLPMatrix(); // print the transition matrix
    void parser(std::ifstream& inputFile); // a parser parse kiss file into our class
    void recomputeMatrix(); // recompute transition matrix with considering Prob(Si)
    void setEdgeWeight(); // assign weight to each weighted undirected edge.
    void assignState();
    void printStateCodes();
    void assignStateWithMatching();
private:
    Process::Graph STG;
    int _nodeNum;
    int _numInputs;
    int _numOutputs;
    int _numStates;
    int _numTransitions;
    int _codeLength;
    int _stateCounter;
    std::string _initialState;
    std::string getBinaryString(int num);
    double getProb(std::string& input); // compute p_{i,j} for all states
    void normalizeMatrix(std::vector<std::vector<double>>& matrix);
    bool haveClassViolation(leda::node state1, leda::node state2, int index);
    bool selectBit(leda::node state1); // two parameter
    bool selectBit(leda::node state1, leda::node state2, int index); // two parameter
    int calcTEV(bool x, int index);
    std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix);
    std::vector<std::vector<double>>    transitionMatrix; // a matrix record the conditional transition probability matrix
    std::vector<std::vector<double>>    LPMatrix;
    std::vector<std::vector<int>>       _graphMatrix;  // to make sure there is the edge exist .

};

#endif