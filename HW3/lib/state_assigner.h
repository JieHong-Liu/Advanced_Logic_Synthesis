#ifndef STATE_ASSIGNER_H
#define STATE_ASSIGNER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


class State_assigner
{
public:
    State_assigner();   //constructor
    void printCircuitStatus();
    void printTransitionMatrix(); // print the transition matrix
    void printLPMatrix(); // print the transition matrix
    void parser(std::ifstream& inputFile); // a parser parse kiss file into our class
    void recomputeMatrix(); // recompute transition matrix with considering Prob(Si)
    std::vector<double> markovChain(const std::vector<std::vector<double>>& transitionMatrix, const std::vector<double>& initialVector);
    void testMarkovChain();
private:
    int numInputs;
    int numOutputs;
    int numStates;
    int numTransitions;
    std::string initialState;
    double getProb(std::string& input); // compute p_{i,j} for all states
    std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& matrix);
    std::vector<std::vector<double>> transitionMatrix; // a matrix record the conditional transition probability matrix
    std::vector<std::vector<double>> LPMatrix;
};

#endif