#include <fstream>
#include "state_assigner.h"
#include <iostream>
using namespace std;


int main()
{
    State_assigner SA;
    std::ifstream infile("./resource/benchmarks/bbara_opt.kiss");
    if(!infile.is_open()) 
    {
        cerr << "OPEN FAILED!!!" << endl;
    }
    else
    {
        cout << "IFSTREAM WORKS!" << endl;
    }
    SA.parser(infile);  // parse the input and create conditional transition matrix and create node for stg.ledagraph
    SA.printCircuitStatus();
    SA.printTransitionMatrix();
    SA.recomputeMatrix(); // calculate each state probability (not switching probability)
    // SA.setEdgeWeight(); // translate STG to weighted undirected graph (integer type)
    // SA.assignState();
    SA.assignStateWithMatching();
    cout << "SA is ok to call!!!" << endl;
    return 0;
}

