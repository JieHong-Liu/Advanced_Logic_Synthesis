#include <fstream>
#include "state_assigner.h"
#include <iostream>
using namespace std;


int main()
{
    State_assigner SA;
    std::ifstream infile("./resource/benchmarks/paper_example.kiss");
    if(!infile.is_open()) 
    {
        cerr << "OPEN FAILED!!!" << endl;
    }
    else
    {
        cout << "IFSTREAM WORKS!" << endl;
    }
    SA.parser(infile);  // parse the input and create conditional transition matrix
    SA.printCircuitStatus();
    SA.printTransitionMatrix();
    SA.recomputeMatrix();

    cout << "SA is ok to call!!!" << endl;
    return 0;
}

