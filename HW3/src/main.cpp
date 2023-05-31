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
    SA.parser(infile);
    cout << "SA is ok to call!!!" << endl;
    return 0;
}

