#include "state_assigner.h"
#include <utility>
#include <cmath>
#include <cstdlib> // this lib is for execute terminal command.
#include <sstream>
#include <LEDA/graph/edge_array.h>   // Edge array data structure
#include <LEDA/graph/graph.h>
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
    _nodeNum        = 0;
    _initialState    = "";
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
    return probability;
}

void State_assigner::parser(std::ifstream &inputFile)
{
    std::cout << "Start to parse the Kiss file\n";
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
                iss >> _numInputs;
            } 
            else if (directive == ".o") 
            {
                iss >> _numOutputs;
            } 
            else if (directive == ".s") 
            {
                iss >> _numStates;
                transitionMatrix.resize(_numStates, std::vector<double>(_numStates));
                _graphMatrix.resize(_numStates, std::vector<int>(_numStates));
            } 
            else if (directive == ".p") 
            {
                iss >> _numTransitions;
            } 
            else if (directive == ".r") 
            {
                iss >> _initialState; 
            }
            else
            {
                std::string input;
                std::string currentState;
                std::string nextState;
                std::string output;
                input = directive;
                iss >> currentState >> nextState >> output;
                int startState = std::stoi(currentState.substr(1));
                int endState = std::stoi(nextState.substr(1));
                cout <<"input = " << input << ", startState: " << startState << \
                 ", EndState: " << endState << ", output: " \
                 << output << ", prob = " << getProb(input) << endl;
                transitionMatrix[startState][endState] += getProb(input); // should be accumulate
                // graph construction
                if(STG._stateName2Node.count(currentState) == 0) // a newly seen currentState
                {
                    int nodeId = _nodeNum;
                    Process::NodeInfo* info = new Process::NodeInfo(nextState, nodeId);
                    node tmpNode = STG.ledaGraph.new_node(info);
                    STG._stateName2Node[currentState] = tmpNode; // save state node infomation to the map.
                    STG.nodeInfos.push_back(info);
                    _nodeNum++;
                    cout << "Adding " << currentState << " node into Graph STG" << endl;           
                }
                if (STG._stateName2Node.count(nextState) == 0) // a newly seen nextState
                {
                    int nodeId = _nodeNum;
                    Process::NodeInfo* info = new Process::NodeInfo(nextState, nodeId);
                    node tmpNode = STG.ledaGraph.new_node(info);
                    STG._stateName2Node[nextState] = tmpNode; // save state node infomation to the map.
                    STG.nodeInfos.push_back(info);
                    _nodeNum++;
                    cout << "Adding " << nextState << " node into Graph STG" << endl;           
                }
                // create edge only on currentState != nextState (weighted graph)
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
    if(STG.ledaGraph.is_undirected())
    {
        cout << "STG.ledaGraph is undirected!!!" << endl;
    }
    else
    {
        cout << "STG.ledaGraph is directed QQQQ" << endl;
    }


    cout << endl << "Parser is finished!!!" << endl;
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
    for (int i = 0; i < _numStates; ++i)
    {
        for (int j = 0; j < _numStates; ++j)
        {
            cout << transitionMatrix[i][j] << "\t";
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
    // first, we need to formulate our linear programming problem

    // create glpk object
    glp_prob* lp;
    lp = glp_create_prob();
    
    glp_set_prob_name(lp, "LP Problem");
    glp_set_obj_dir(lp, GLP_MIN);

    // 定義變量
    cout << "numStates = " << _numStates << endl;
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
            ia[count] = i;
            ja[count] = j;
            ar[count] = LPMatrix[i-1][j-1];
            count ++;
        }
    }
    // 解決問題
    glp_load_matrix(lp, rowNum * colNum , ia, ja, ar);
    glp_simplex(lp,NULL);
    // 取得結果
    for(int i = 1; i <= _numStates; i++)
    {
        STG.nodeInfos[i-1]->stateProb = glp_get_col_prim(lp,i);
        cout << "S" << i-1 << "= " << STG.nodeInfos[i-1]->stateProb  << endl;
    }
    // clear resource
    glp_delete_prob(lp);
    glp_free_env();

    // release dynamic allocate memory.
    delete[] ia;
    delete[] ja;
    delete[] ar;

    // then, we need to update our transition matrix with Pi where stands for Prob(Si)
    printTransitionMatrix();
    for (int i = 0; i < _numStates; i++)
    {
        for (int j = 0; j < _numStates; j++)
        {
            transitionMatrix[i][j] = STG.nodeInfos[i]->stateProb * transitionMatrix[i][j];
        }
    }
    cout << "After multiple Pi: "<< endl;
    printTransitionMatrix(); 
    for (int i = 0; i < _numStates; i++)
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
    printTransitionMatrix();
    normalizeMatrix(transitionMatrix);
    printTransitionMatrix();
}

void State_assigner::setEdgeWeight()
{
    edge e;
    // Iterate over all edges in the graph
    forall_edges(e, STG.ledaGraph) 
    {
        auto edgeInfo = STG.ledaGraph.inf(e);
        int sourceID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->source])->id ;
        int targetID = STG.ledaGraph.inf(STG._stateName2Node[edgeInfo->target])->id ;
        edgeInfo->weight = transitionMatrix[sourceID][targetID];
        cout << "[" << sourceID << "]\t(" << edgeInfo->weight << ")\t[" << targetID << "]" << endl;          
    }
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
            value = std::round(value);
        }
    }
}
