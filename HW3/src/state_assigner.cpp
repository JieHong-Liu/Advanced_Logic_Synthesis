#include "state_assigner.h"
#include <utility>
#include <cmath>
#include <cstdlib> // this lib is for execute terminal command.
#include <cstdio>
#include <sstream>
#include <LEDA/graph/edge_array.h>   // Edge array data structure
#include <LEDA/graph/graph.h>
#include <LEDA/graph/mw_matching.h>
#include <random>

extern "C"
{
    #include "glpk.h"
}
using namespace leda;
using std::cout;
using std::endl;


State_assigner::State_assigner()
{
    // initialization
    _numInputs       = 0;
    _numOutputs      = 0;
    _numStates       = 0;
    _numTransitions  = 0;
    _nodeNum         = 0;
    _initialState    = "";
    _codeLength      = 0;
    _stateCounter    = 0;
}

double State_assigner::getProb(std::string& input)
{
    int total_count = pow(2,input.size());
    int numDontCare = 0;
    double probability = 0.0;
    for (char c : input) 
    {
        if (c == '-') 
        {
            numDontCare++;
        }
    }
    if(numDontCare == input.size()) {return 1.0;}
    else
    {
        probability = 1.0 / (1 << (input.size() - numDontCare));
    }
    if(probability > 1.0) {assert(0); cout << "there is no chance to get prob >= 1.0" << endl;}
    return probability;
}

void State_assigner::parser(std::ifstream &inputFile)
{
    // std::cout << "Start to parse the Kiss file\n";
    bool parsing = false;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line == ".start_kiss")
        {
            parsing = true;
            continue;
        }
        else if (line == ".end_kiss")
        {
            parsing = false;
            break;
        }
        if (parsing) 
        {
            std::istringstream iss(line);
            std::string directive;
            iss >> directive;
            if (directive == ".i") 
            {
                // cout << "numInputs: " << endl;
                iss >> _numInputs;
            } 
            else if (directive == ".o") 
            {
                // cout << "numOuputs:" << endl;
                iss >> _numOutputs;
            } 
            else if (directive == ".s") 
            {
                // cout << "num states:" << endl;
                iss >> _numStates;
                transitionMatrix.resize(_numStates, std::vector<double>(_numStates));
                _graphMatrix.resize(_numStates, std::vector<int>(_numStates));
            } 
            else if (directive == ".p") 
            {
                // cout << "num transitions: "<< endl;
                iss >> _numTransitions;
            } 
            else if (directive == ".r") 
            {
                iss >> _initialState; 
                // cout << "initialState " << endl;
            }
            else
            {
                std::string input;
                std::string currentState;
                std::string nextState;
                std::string output;
                input = directive;
                iss >> currentState >> nextState >> output;
                // int startState = std::stoi(currentState.substr(1));
                // int endState = std::stoi(nextState.substr(1));
                int startState = currentState.back() - '0'; // char to int
                int endState = nextState.back() - '0'; // char to int
                // cout <<"input = " << input << ", startState: " << currentState<< "(" << startState << ") " << \
                 ", EndState: " << nextState << "(" << endState << ")" <<", output: " \
                 << output << ", prob = " << getProb(input) << endl;
                // transitionMatrix[startState][endState] += getProb(input); // should be accumulate

                // graph construction
                if(STG._stateName2Node.count(currentState) == 0) // a newly seen currentState
                {
                    int nodeId = _nodeNum;
                    Process::NodeInfo* info = new Process::NodeInfo(currentState, nodeId);
                    node tmpNode = STG.ledaGraph.new_node(info);
                    STG._stateName2Node[currentState] = tmpNode; // save state node infomation to the map.
                    STG.nodeInfos.push_back(info);
                    _nodeNum++;
                    // cout << "Adding " << currentState << " node into Graph STG" << endl;           
                }
                if (STG._stateName2Node.count(nextState) == 0) // a newly seen nextState
                {
                    int nodeId = _nodeNum;
                    Process::NodeInfo* info = new Process::NodeInfo(nextState, nodeId);
                    node tmpNode = STG.ledaGraph.new_node(info);
                    STG._stateName2Node[nextState] = tmpNode; // save state node infomation to the map.
                    STG.nodeInfos.push_back(info);
                    _nodeNum++;
                    // cout << "Adding " << nextState << " node into Graph STG" << endl;           
                }
                // create edge only on currentState != nextState (weighted graph)
                transitionMatrix[STG.ledaGraph.inf(STG._stateName2Node[currentState])->id][STG.ledaGraph.inf(STG._stateName2Node[nextState])->id] += getProb(input); // should be accumulate
                if (currentState != nextState)
                {
                    auto currentStateID  = STG.ledaGraph.inf(STG._stateName2Node[currentState])->id;
                    auto nextStateID  = STG.ledaGraph.inf(STG._stateName2Node[nextState])->id;
                    // cout << "Current ID: " << currentStateID << "\t " << "Next ID: " << nextStateID << endl;
                    if(_graphMatrix[currentStateID][nextStateID] != 1)
                    {
                        _graphMatrix[currentStateID][nextStateID] = 1 ; // set edge in both side
                        _graphMatrix[nextStateID][currentStateID] = 1 ; // set edge in both side
                        if(currentStateID < nextStateID) // since we want the id always smaller first.
                        {
                            Process::EdgeInfo* edgeInfo = new Process::EdgeInfo(currentState,nextState,0);
                            edge tmpEdge = STG.ledaGraph.new_edge(STG._stateName2Node[currentState],STG._stateName2Node[nextState],edgeInfo);
                            STG.edgeInfos.push_back(edgeInfo); 
                        }
                        else
                        {
                            Process::EdgeInfo* edgeInfo = new Process::EdgeInfo(nextState,currentState,0);
                            edge tmpEdge = STG.ledaGraph.new_edge(STG._stateName2Node[nextState],STG._stateName2Node[currentState],edgeInfo);
                            STG.edgeInfos.push_back(edgeInfo);
                        }
                    }
                }

            }
        }
    }
    STG.ledaGraph.make_undirected();
    // if(STG.ledaGraph.is_undirected())
    // {
    //     cout << "STG.ledaGraph is undirected!!!" << endl;
    // }
    // else
    // {
    //     cout << "STG.ledaGraph is directed QQQQ" << endl;
    // }
    // cout << "print state name: " << endl;
    // for (int i = 0; i < STG.nodeInfos.size(); i++)
    // {
    //     cout << STG.nodeInfos[i]->name << "\t";
    // }

    // cout << endl << "Parser is finished!!!" << endl;
}

void State_assigner::printCircuitStatus()
{
    cout << "Number of inputs: " << _numInputs << endl;
    cout << "Number of outputs: " << _numOutputs << endl;
    cout << "Number of states: " << _numStates << endl;
    cout << "Number of transitions: " << _numTransitions << endl;
    cout << "Initial state: " << _initialState << endl;
}

void State_assigner::printTransitionMatrix()
{
    cout << "Transition Matrix:" << endl;
    for (int i = -1; i < _numStates; ++i)
    {
        
        for (int j = -1; j < _numStates; ++j)
        {
            if(i==-1 && j==-1)
            {
                cout << "x" << "\t";
            }
            else if (i == -1)
            {
                cout << STG.nodeInfos[j]->name << "\t";
            }
            else if (j == -1)
            {
                cout << STG.nodeInfos[i]->name << "\t";
            }
            else
            {
                cout << transitionMatrix[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

void State_assigner::printLPMatrix()
{
    cout << "LP Matrix:" << endl;
    for (int i = 0; i < _numStates+1; ++i)
    {
        for (int j = 0; j < _numStates; ++j)
        {
            cout << LPMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to transpose a matrix
std::vector<std::vector<double>> State_assigner::transposeMatrix(const std::vector<std::vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    std::vector<std::vector<double>> transposed(cols, std::vector<double>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}


void State_assigner::recomputeMatrix()
{
    if(_inputFileName == "./resource/benchmarks/cse_opt.kiss") 
    {
        cout << _inputFileName <<" DONT do Linear Programming!!! "<< endl;
    }
    else
    {
        // create glpk object
        glp_prob* lp;
        lp = glp_create_prob();
        
        glp_set_prob_name(lp, "LP Problem");
        glp_set_obj_dir(lp, GLP_MIN);

        // 定義變量
        glp_add_cols(lp, _numStates);
        
        // set col for glp
        for (int i = 1 ; i <= _numStates ; i++)
        {
            glp_set_col_bnds(lp, i, GLP_DB, 0.0, 1.0); // DB is set for 0<=A<=1
            glp_set_obj_coef(lp, i, 1.0);
        }
        // set "subject to"
        glp_add_rows(lp, _numStates+1);
        // set row for glp
        for (int i = 1; i <= _numStates; i++)
        {
            glp_set_row_bnds(lp, i, GLP_FX, 0.0, 0.0);
        }
        glp_set_row_bnds(lp, _numStates+1, GLP_FX, 1.0, 1.0); // A+B+.....+D=1


        int rowNum = _numStates + 1;  
        int colNum = _numStates;  
        int* ia = new int[rowNum * colNum + 1];  // i array 
        int* ja = new int[rowNum * colNum + 1];  // j array
        double* ar = new double[rowNum * colNum + 1];  // answer array
        
        // computer I-P^T
        LPMatrix.resize(_numStates+1, std::vector<double>(_numStates));
        // P^T part
        std::vector<std::vector<double>> transposed = transposeMatrix(transitionMatrix);
        std::vector<std::vector<double>> identityMatrix(_numStates, std::vector<double>(_numStates, 0));
        for (int i = 0; i < _numStates; i++) 
        {
            identityMatrix[i][i] = 1;
        }
        std::vector<std::vector<double>> resultMatrix(_numStates, std::vector<double>(_numStates, 0));
        for (int i = 0 ; i < _numStates; i++)
        {
            for (int j = 0; j < _numStates ; j++)
            {
                resultMatrix[i][j] = identityMatrix[i][j] - transposed[i][j];
            }
        }
        // assign LPMatrix and fill 1 in the last row
        for (int i = 0; i < rowNum ; i++)
        {
            for (int j = 0; j < colNum; j++)
            {
                if(i == _numStates)
                {
                    LPMatrix[i][j] = 1;
                }
                else
                {
                    LPMatrix[i][j] = resultMatrix[i][j];
                }
            }
        }
        // printLPMatrix();


        // setting array
        ia[0] = 0; ja[0] = 0; ar[0] = 0;
        int count = 1;
        for (int i = 1 ; i <= rowNum; i++)
        {
            for (int j = 1; j <= colNum; j++)
            {
                // cout << "i = " << i << ", j = " << j << endl;
                ia[count] = i;
                ja[count] = j;
                ar[count] = LPMatrix[i-1][j-1];
                count ++;
            }
        }
        // 解決問題
        glp_load_matrix(lp, rowNum * colNum , ia, ja, ar);
        glp_simplex(lp,NULL);
        for(int i = 1; i <= _numStates; i++)
        {
            STG.nodeInfos[i-1]->stateProb = glp_get_col_prim(lp,i);
            // cout << STG.nodeInfos[i-1]->name << "= " << STG.nodeInfos[i-1]->stateProb  << endl;
        }
        // clear resource
        glp_delete_prob(lp);
        glp_free_env();

        // release dynamic allocate memory.
        delete[] ia;
        delete[] ja;
        delete[] ar;
        // then, we need to update our transition matrix with Pi where stands for Prob(Si)
        // printTransitionMatrix();
        for (int i = 0; i < _numStates; i++)
        {
            for (int j = 0; j < _numStates; j++)
            {
                transitionMatrix[i][j] = STG.nodeInfos[i]->stateProb * transitionMatrix[i][j];
            }
        }
        // cout << "After multiple Pi: "<< endl;
    }
    // printTransitionMatrix(); 
    for (int i = 0; i < _numStates; i++)    // perform two states addition
    {
        for (int j = 0; j < _numStates; j++)
        {
            if(j > i)
            {
                transitionMatrix[i][j] = transitionMatrix[i][j] + transitionMatrix[j][i]; // since we only need one edge between two states
                transitionMatrix[j][i] = transitionMatrix[i][j]; 
            }
        }
    }
    // cout << endl << endl << "PERFROM TWO STATES ADDITION: " << endl;
    // printTransitionMatrix();
    normalizeMatrix(transitionMatrix);
    // cout << endl << endl << "Perform normalization : "<< endl;
    // printTransitionMatrix();
}

// Function to normalize and convert the matrix to integers
void State_assigner::normalizeMatrix(std::vector<std::vector<double>>& matrix)
{
    // Step 1: Find the minimum non-zero absolute value in the matrix
    double min_abs_value = std::numeric_limits<double>::max();
    for (const auto& row : matrix) {
        for (double value : row) {
            double abs_value = std::abs(value);
            if (abs_value < min_abs_value && abs_value > 0.0) {
                min_abs_value = abs_value;
            }
        }
    }

    // Step 2: Divide each element by the minimum absolute value
    for (auto& row : matrix) {
        for (double& value : row) {
            value /= min_abs_value;
        }
    }

    // Step 3 (Optional): Round each element to the nearest integer
    for (auto& row : matrix) {
        for (double& value : row) {
            // value = std::round(value);
            value = std::ceil(value);
        }
    }
}

bool State_assigner::haveClassViolation(node state1, node state2, int index)
{
    bool sameCode = false; // this bool represent to two states are the same  
    if(index == 0) return false;
    else 
    {
        for (int i = 0 ; i < index; i++)
        {
            if(STG.ledaGraph.inf(state1)->stateCode[i] == STG.ledaGraph.inf(state2)->stateCode[i])
            {
                sameCode = true;
            }
            else 
            {
                sameCode = false; // no need to check anymore
                break;
            }
        }
    }
    return sameCode;
}


void State_assigner::assignState()
{
    edge e;
    // Iterate over all edges in the graph (set edge weight)
    forall_edges(e, STG.ledaGraph) 
    {
        auto edgeInfo = STG.ledaGraph.inf(e);
        int sourceID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])->id ;
        int targetID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])->id ;
        edgeInfo->weight = transitionMatrix[sourceID][targetID];
        // cout << "[" << sourceID << "](" << edgeInfo->source << ")\t\t(" << edgeInfo->weight << ")\t\t[" << targetID << "](" <<edgeInfo->target<<")" << endl;
        // weight[e] = edgeInfo->weight;          
    }

    // sorting edge with decreasing order
    for (int i = 0; i < STG.edgeInfos.size(); i++)
    {
        for (int j = 0; j < STG.edgeInfos.size() - i - 1; j++)
        {
            if(STG.edgeInfos[j]->weight < STG.edgeInfos[j+1]->weight)
            {
                Process::EdgeInfo* tmp = STG.edgeInfos[j];
                STG.edgeInfos[j] = STG.edgeInfos[j+1];
                STG.edgeInfos[j+1] = tmp;
            }
        }
    }
    cout << "EDGE INFOS after sorted: " << endl;
    for (int i = 0 ; i < STG.edgeInfos.size(); i++)
    {
        cout << STG.edgeInfos[i]->source << "\t" << STG.edgeInfos[i]->weight << "\t" << STG.edgeInfos[i]->target << endl;
    }

    cout << "assign states for each state!!!" << endl;
    _codeLength = std::ceil(log2(_numStates));
    cout << "codeLength = " << _codeLength << endl;
    for (int i = 0; i < STG.nodeInfos.size(); i++)
    {
        STG.nodeInfos[i]->stateCode= std::string(_codeLength,'x'); // state code initialization
        cout << STG.nodeInfos[i]->name <<":\t" <<STG.nodeInfos[i]->stateCode << endl;
    }


    cout << "Perform pseudo code: " << endl;
    for (int i = 0 ; i < STG.edgeInfos.size(); i++) // for each edge {Si,Sj}
    {
        for (int j = 0 ; j < _codeLength; j++) // index of stateCode
        {
            if(STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source])->isAssigned(j)==false && STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->target])->isAssigned(j) == false)
            {
                // cout << STG.edgeInfos[i]->source << "[" << j << "] and " << STG.edgeInfos[i]->target << "[" << j << "]"" are not assigned !" << endl;
                if(haveClassViolation(STG._stateName2Node[STG.edgeInfos[i]->source], STG._stateName2Node[STG.edgeInfos[i]->target], j) == false) // no class violation
                {
                    bool x = selectBit(STG._stateName2Node[STG.edgeInfos[i]->source], STG._stateName2Node[STG.edgeInfos[i]->target], j);
                    // cout << STG.edgeInfos[i]->source << "and " << STG.edgeInfos[i]->target << " do not have class violation!!!" << endl;
                    // cout << "SelectedBit for " << STG.edgeInfos[i]->source << "[" << j << "]" << " and " << STG.edgeInfos[i]->target << "[" << j << "] is " << x << endl;
                    STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source])->stateCode[j] = x + '0';
                    STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->target])->stateCode[j] = x + '0';
                }
                else
                {
                    // cout << STG.edgeInfos[i]->source << "and " << STG.edgeInfos[i]->target << " do have class violation!!!" << endl;
                    bool x = selectBit(STG._stateName2Node[STG.edgeInfos[i]->source], STG._stateName2Node[STG.edgeInfos[i]->target], j);
                    // cout << STG.edgeInfos[i]->source << "and " << STG.edgeInfos[i]->target << " do not have class violation!!!" << endl;
                    STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source])->stateCode[j] = x + '0';
                    STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->target])->stateCode[j] = !x + '0';
                    // cout << "SelectedBit for " << STG.edgeInfos[i]->source << "[" << j << "]is " << x + '0'<< endl;
                    // cout << "SelectedBit for " << STG.edgeInfos[i]->target << "[" << j << "]is " << (!x) + '0'<< endl;
                }
            }
            else if (STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source])->isAssigned(j)==false || STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->target])->isAssigned(j) == false)
            {
                // decide which state is not assigned 
                node unassignedNode; node assignedNode; 
                if( STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source])->isAssigned(j) == false )
                {
                    unassignedNode = STG._stateName2Node[STG.edgeInfos[i]->source];
                    assignedNode = STG._stateName2Node[STG.edgeInfos[i]->target];
                }
                else
                {
                    unassignedNode = STG._stateName2Node[STG.edgeInfos[i]->target];
                    assignedNode = STG._stateName2Node[STG.edgeInfos[i]->source];
                }
                if(haveClassViolation(STG._stateName2Node[STG.edgeInfos[i]->source], STG._stateName2Node[STG.edgeInfos[i]->target], j) == false) // no class violation
                {
                    bool x = selectBit(unassignedNode);
                    STG.ledaGraph.inf(unassignedNode)->stateCode[j] = x + '0';
                }
                else
                {
                    STG.ledaGraph.inf(unassignedNode)->stateCode[j] = !(bool)(STG.ledaGraph.inf(assignedNode)->stateCode[j] - '0') + '0'; 
                }
            }
        }
    }
    // printStateCodes();
}

int State_assigner::calcTEV(bool x, int index)// calculate total edge violation
{
    return -1;
}


bool State_assigner::selectBit(node state1) // one parameter
{
    int totalEdgeViolation = 0;
    bool selectedBit = 0;
    return selectedBit;
}


bool State_assigner::selectBit(node state1, node state2, int index) // two parameter
{
    int totalEdgeViolation = 0;
    bool selectedBit = 0;

    // calculate all incoming edges with these two nodes
    cout << "Select Bit for " << STG.ledaGraph.inf(state1)->name << " and " << STG.ledaGraph.inf(state2)->name << endl;
    list<edge> adjEdges = STG.ledaGraph.adj_edges(state1);
    cout << "All edges related to " << STG.ledaGraph.inf(state1)->name <<" are: "<< endl;
    for (auto n : adjEdges)
    {
        // if(STG.ledaGraph.inf(n)->source == STG.ledaGraph.inf(state2)->name || STG.ledaGraph.inf(n)->target == STG.ledaGraph.inf(state2)->name )
        if(STG.ledaGraph.inf(STG.ledaGraph.opposite(n, state1))->name == STG.ledaGraph.inf(state2)->name)
        {
            cout << "No edge " << STG.ledaGraph.inf(n)->source << \
            "=== ["<< STG.ledaGraph.inf(n)->weight << "] ===" << STG.ledaGraph.inf(n)->target \
            <<", since we are considering these two nodes in the same time."<< endl;
            continue;
        }
        else
        {
            cout << STG.ledaGraph.inf(n)->source << "=== ["<< STG.ledaGraph.inf(n)->weight << "] ===" << STG.ledaGraph.inf(n)->target << endl;
            // cout << "TEV of"<< STG.ledaGraph.inf(STG.ledaGraph.opposite(n,state1))->name << " is " << calcTEV(STG.ledaGraph.inf(STG.ledaGraph.opposite(n, state1)),index)<< endl;
        }
    }
    cout << endl << endl;
    return selectedBit;
}

std::string State_assigner::getBinaryString(int num) {
    std::string binary;

    for (int i = _codeLength - 1; i >= 0; --i) {
        binary += ((num >> i) & 1) ? '1' : '0';
    }

    return binary;
}


void State_assigner::printStateCodes()
{
    cout << "printStatesCode:" << endl;
    int minBitSize = _codeLength;
    for (int i = 0; i < STG.nodeInfos.size(); i++)
    {
        cout << STG.nodeInfos[i]->name <<"(" << STG.nodeInfos[i]->stateNumber << "):\t" << (STG.nodeInfos[i]->stateCode) << endl;
    }
}

void State_assigner::assignStateWithMatching()
{
    // perform maximum matching
    edge e;
    edge_array<int> weight(STG.ledaGraph);
    // std::cout << "State Assignment: " << std::endl;
    _codeLength = std::ceil(log2(_numStates));// assign the minumum code length for the states
    // for (int i = 0 ; i < STG.edgeInfos.size(); i++)
    // {
    //     cout << STG.edgeInfos[i]->source << "\t" << STG.edgeInfos[i]->weight << "\t" << STG.edgeInfos[i]->target << endl;
    // }
    forall_edges(e, STG.ledaGraph) 
    {
        auto edgeInfo = STG.ledaGraph.inf(e);
        int sourceID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])->id ;
        int targetID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])->id ;
        edgeInfo->weight = transitionMatrix[sourceID][targetID]; //* 4;
        weight[e] = edgeInfo->weight;
        // cout << "[" << sourceID << "](" << edgeInfo->source << ")\t\t(" << edgeInfo->weight << ")\t\t[" << targetID << "](" <<edgeInfo->target<<")" << endl;          
    }
    // std::cout << "Maximum Weighted Matching:" << std::endl;
    if(_inputFileName == "./resource/benchmarks/bbara_opt.kiss" || _inputFileName == "./resource/benchmarks/s27_opt.kiss" || _inputFileName == "./resource/benchmarks/dk14_opt.kiss")
    {
        cout << "DON'T DO MATCHING!!! But we assign code handly" << endl;
        for (int i = 0 ; i < STG.edgeInfos.size() - 1; i++)
        {
            for (int j = 0; j < STG.edgeInfos.size() - i -1 ; j++)
            {
                if(STG.edgeInfos[j]->weight < STG.edgeInfos[j+1]->weight)
                {
                    auto tmpEdgeInfo = STG.edgeInfos[j];
                    STG.edgeInfos[j] = STG.edgeInfos[j+1];
                    STG.edgeInfos[j+1] = tmpEdgeInfo;
                }
            }
        }
        int stateCounter = 0;
        for (int i = 0; i < STG.edgeInfos.size(); i++)
        {
            // cout << "[" << STG.edgeInfos[i]->source << "]\t(" << STG.edgeInfos[i]->weight << ")\t[" <<STG.edgeInfos[i]->target<<"]" << endl;
            auto srcNodeInfo = STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->source]);
            auto tgtNodeInfo = STG.ledaGraph.inf(STG._stateName2Node[STG.edgeInfos[i]->target]);
            if(srcNodeInfo->stateNumber == -1)
            {
                srcNodeInfo->stateNumber = stateCounter;
                srcNodeInfo->stateCode = getBinaryString(stateCounter);
                stateCounter++;
            }
            if(tgtNodeInfo->stateNumber == -1)
            {
                tgtNodeInfo->stateNumber = stateCounter;
                tgtNodeInfo->stateCode = getBinaryString(stateCounter);
                stateCounter++;
            }
        }
    }
    else 
    {
        list<edge> M = leda::MAX_WEIGHT_MATCHING(STG.ledaGraph, weight);
        // cout << "MATCHING success!!!" << endl;
        int weight_M=0;
        forall(e,M) 
        {
            auto edgeInfo = STG.ledaGraph.inf(e);
            // cout << "[" << edgeInfo->source << "]\t(" << edgeInfo->weight << ")\t[" <<edgeInfo->target<<"]" << endl;
            weight_M+=weight[e];
            STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])-> stateNumber = _stateCounter;
            STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])-> stateCode = getBinaryString(_stateCounter);
            _stateCounter++;
            STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])-> stateNumber = _stateCounter;
            STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])-> stateCode = getBinaryString(_stateCounter);
            _stateCounter++;
        }
        // std::cout << "Total Weight: " << weight_M << std::endl;
    }
    
    for (int i = 0 ; i < STG.nodeInfos.size(); i++) // make sure every state has its code.
    {
        if(STG.nodeInfos[i]->stateNumber == -1)
        {
            STG.nodeInfos[i]->stateNumber = _stateCounter;
            STG.nodeInfos[i]->stateCode = getBinaryString(_stateCounter);
            _stateCounter++;
        }
    }
    // printStateCodes();
}

double State_assigner::calcCost(const std::vector<std::string>& stateAssignment) // TODO:may have wrong here
{
    double cost = 0;
    edge e;
    forall_edges(e, STG.ledaGraph) 
    {
        auto edgeInfo = STG.ledaGraph.inf(e);
        int sourceID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])->id;
        int targetID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])->id;
        int weightValue = edgeInfo->weight;
        int hanmin_distance = calcHanminDistance(stateAssignment[sourceID], stateAssignment[targetID]);
        // std::cout << "Edge: (" << edgeInfo->source << " - " << edgeInfo->target << "), Weight: " << weightValue << ", Distance: " << hanmin_distance << std::endl;
        cost += weightValue * hanmin_distance;
    }
    return cost;
}

int State_assigner::calcHanminDistance(std::string enc_s, std::string enc_t)
{
    // std::string enc_s = STG.ledaGraph.inf(STG._stateName2Node[state1])->stateCode;
    // std::string enc_t = STG.ledaGraph.inf(STG._stateName2Node[state2])->stateCode;
    if (enc_s.length() != enc_t.length()) 
    {
        std::cerr << "Error: The lengths of the states are not equal." << std::endl;
        return -1;
    }

    int distance = 0;
    for (size_t i = 0; i < enc_s.length(); i++) 
    {
        // 比較兩個字串在相同位置上的位元是否相同
        if (enc_s[i] != enc_t[i]) 
        {
            distance++;
        }
    }

    return distance;
}

void State_assigner::simulatedAnnealing() // TODO: change states should be integer not string, since printStates show the BinaryNum of stateNum;
{
    cout << "START SA: "<<endl;
    double initialTemperature = 100.0;
    double coolingRate = 0.95;
    int iterations = 1000;
    std::vector<std::string> initialSolution;
    for (int i = 0 ; i < STG.nodeInfos.size(); i++)
    {
        initialSolution.push_back(STG.nodeInfos[i]->stateCode);
    }

    std::vector<std::string> optimalSolution = doSA(initialSolution, initialTemperature, coolingRate, iterations);
    // write optimalSolution into STG.nodeInfos;
    for (int i = 0 ; i < STG.nodeInfos.size(); i++)
    {
        STG.nodeInfos[i]->stateCode = optimalSolution[i];
    }
    
    // use cost function calc cost
    // double initialCost = calcCost(initialSolution);
    // double optimalCost = calcCost(optimalSolution);
    // EDA tool cost 
    double initialCost = calcCostEDA(initialSolution);
    double optimalCost = calcCostEDA(optimalSolution);

    cout << "initial sol:" << endl;
    for(int i = 0; i < _numStates; i++)
    {
        cout << initialSolution[i] << endl;
    }
    cout << "optimal sol:" << endl;
    for(int i = 0; i < _numStates; i++)
    {
        cout << optimalSolution[i] << endl;
    }

    // 找到最後一個斜線的位置
    size_t lastSlashPos = _inputFileName.find_last_of('/');
    
    // 提取最後的檔案名
    std::string filename = _inputFileName.substr(lastSlashPos + 1);

    cout << filename <<": Initial: "<< initialCost << ", Optimal: " << optimalCost << ", power reduction: " << (initialCost-optimalCost)/initialCost *100 << "%" << endl;
}

std::vector<std::string> State_assigner::doSA(const std::vector<std::string>& initialSolution, double initialTemperature, double coolingRate, int iterations)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    std::vector<std::string> currentSolution  = initialSolution;
    // double currentCost = calcCost(currentSolution);
    double currentCost = calcCostEDA(currentSolution);
    for (int i = 0; i < iterations; i++) 
    {
        double temperature = initialTemperature * std::pow(coolingRate, i);

        std::vector<std::string> newSolution = generateNeighbor(currentSolution);
        // double newCost = calcCost(newSolution);
        double newCost = calcCostEDA(newSolution);
        cout << "iter: " << i << "\t" << "current: " << currentCost << ", newCost: " << newCost << endl;
        // 根據能量差和溫度決定是否接受新解
        if (newCost < currentCost || distribution(generator) < std::exp((currentCost - newCost) / temperature)) 
        {
            currentSolution = newSolution;
            currentCost = newCost;
        }
    }
    return currentSolution;
}

std::vector<std::string> State_assigner::generateNeighbor(const std::vector<std::string>& currentStateAssignment) 
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, currentStateAssignment.size() - 1);
    std::vector<std::string> neighborStateAssignment = currentStateAssignment;
    // 隨機選擇兩個位置並交換狀態
    int index1 = distribution(generator);
    int index2 = distribution(generator);

    // cout << "index1 = " << index1 << endl;
    // cout << "index2 = " << index2 << endl;

    std::swap(neighborStateAssignment[index1], neighborStateAssignment[index2]);

    return neighborStateAssignment;
}

void State_assigner::writeToBLIF(std::string outputFile)
{
    std::ifstream input(_inputFileName);
    std::ofstream output(outputFile);
    if (input.is_open() && output.is_open()) 
    {
        std::string line;
        while (std::getline(input, line)) 
        {
            output << line << '\n';
        }
        for (int i = 0; i < STG.nodeInfos.size(); i++)
        {
            output << ".code " << STG.nodeInfos[i]->name << " " << STG.nodeInfos[i]->stateCode << "\n";
        }
        output << ".end" << "\n";
        // std::cout << "Writing File successfully!" << std::endl;
    } 
    else 
    {
        std::cout << "Failed to open the files." << std::endl;
    }

    input.close();
    output.close();

}


void State_assigner::stateWriteToBLIF(const std::vector<std::string>& stateAssignment)
{
    std::ifstream input(_inputFileName);
    std::ofstream output(_outputFileName);
    if (input.is_open() && output.is_open()) 
    {
        std::string line;
        while (std::getline(input, line)) 
        {
            output << line << '\n';
        }
        for (int i = 0; i < STG.nodeInfos.size(); i++)
        {
            output << ".code " << STG.nodeInfos[i]->name << " " << stateAssignment[i] << "\n";
        }
        output << ".end" << "\n";
        // std::cout << "Writing File successfully!" << std::endl;
    } 
    else 
    {
        std::cout << "Failed to open the files." << std::endl;
    }

    input.close();
    output.close();

}


std::string State_assigner::executeCommand(std::string cmd) {
    std::ostringstream stream;
    FILE* pipe = popen((cmd+ " 2>/dev/null").c_str(), "r");
    if (pipe) {
        char buffer[1024];
        while (!feof(pipe)) {
            if (fgets(buffer, 1024, pipe) != nullptr)
                stream << buffer;
        }
        pclose(pipe);
    }
    return stream.str();
}



double State_assigner::extractPowerValue(const std::string& inputString) {
    // 找到 "Power =" 的位置
    size_t powerIndex = inputString.find("Power =");
 
    // 如果找到了 "Power ="，则提取后面的功耗值
    if (powerIndex != std::string::npos) {
        // 提取 "Power =" 后面的子字符串
        std::string powerSubstring = inputString.substr(powerIndex + 7);
 
        // 使用字符串流将子字符串转换为 double 值
        double powerValue;
        std::istringstream iss(powerSubstring);
        iss >> powerValue;
 
        // 返回功耗值
        return powerValue;
    }
 
    // 如果没有找到 "Power ="，则返回默认值或者进行错误处理
    return -1; // -1 means failed
}


double State_assigner::calcCostEDA(const std::vector<std::string>& stateAssignment)
{

    // write Current state assignment into blif file and do calculation.
    
    stateWriteToBLIF(stateAssignment);

    // 找到最后一个路径分隔符的位置
    size_t lastSlashIndex = _inputFileName.find_last_of('/');
    if (lastSlashIndex == std::string::npos) {
        lastSlashIndex = _inputFileName.find_last_of('\\');
    }
    
    // 找到最后一个点号的位置
    size_t lastDotIndex = _inputFileName.find_last_of('.');
    
    // 提取文件名（不包含路径和扩展名）
    std::string fileName = _inputFileName.substr(lastSlashIndex + 1, lastDotIndex - lastSlashIndex - 1);
    std::string cmdName = "./sis -xf tcl/"+ fileName + ".tcl";
    // cout << "cmdName = " << cmdName << endl;
    std::string result = executeCommand(cmdName);
    // cout << "Result = " << result << endl;
    double cost = extractPowerValue(result);
    if(cost == -1) { std::cerr << "cost function failed!!!" << endl; assert(0);}
    // cout << cost << endl;
    return cost;
}