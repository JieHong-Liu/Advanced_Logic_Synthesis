#include <fstream>
#include "state_assigner.h"
#include <iostream>
#include <chrono>

using namespace std;


int main(int argc, char* argv[])
{
     auto start = std::chrono::high_resolution_clock::now();
    if(argc != 3)
    {
        cerr << "Usage: ./bin/sa input.kiss output.blif" << endl; 
        return -1;
    }
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    State_assigner SA;
    SA.setInputFileName(inputFileName);
    SA.setOutputFileName(outputFileName);
    std::ifstream infile(inputFileName);
    if(!infile.is_open()) 
    {
        cerr << "OPEN FAILED!!!" << endl;
    }
    else
    {
        cout << "IFSTREAM WORKS!" << endl;
    }
    SA.parser(infile);  // parse the input and create conditional transition matrix and create node for stg.ledagraph
    // SA.printCircuitStatus();
    // SA.printTransitionMatrix();
    SA.recomputeMatrix(); // calculate each state probability (not switching probability)
    // SA.setEdgeWeight(); // translate STG to weighted undirected graph (integer type)
    // SA.assignState();
    SA.assignStateWithMatching();
    SA.simulatedAnnealing();
    SA.writeToBLIF(outputFileName);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << inputFileName << ": " <<" Time elapsed: " << duration.count() << " ms" << std::endl;

    return 0;
}

