#include "state_assigner.h"
#include <utility>
#include <cmath>
#include <cstdlib> // this lib is for execute terminal command.
#include <sstream>
extern "C"
{
    #include "glpk.h"
}

using std::cout;
using std::endl;


State_assigner::State_assigner()
{
    // initialization
    numInputs       = 0;
    numOutputs      = 0;
    numStates       = 0;
    numTransitions  = 0;
    initialState    = "";
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
            cout << "parsing..." << endl;
            std::istringstream iss(line);
            std::string directive;
            iss >> directive;
            if (directive == ".i") 
            {
                iss >> numInputs;
            } 
            else if (directive == ".o") 
            {
                iss >> numOutputs;
            } 
            else if (directive == ".s") 
            {
                iss >> numStates;
                transitionMatrix.resize(numStates, std::vector<double>(numStates));
            } 
            else if (directive == ".p") 
            {
                iss >> numTransitions;
            } 
            else if (directive == ".r") 
            {
                iss >> initialState; 
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
            }
        }
    }

    cout << "Parser is finished!!!" << endl;
}

void State_assigner::printCircuitStatus()
{
    cout << "Number of inputs: " << numInputs << endl;
    cout << "Number of outputs: " << numOutputs << endl;
    cout << "Number of states: " << numStates << endl;
    cout << "Number of transitions: " << numTransitions << endl;
    cout << "Initial state: " << initialState << endl;
}

void State_assigner::printTransitionMatrix()
{
    cout << "Transition Matrix:" << endl;
    for (int i = 0; i < numStates; ++i)
    {
        for (int j = 0; j < numStates; ++j)
        {
            cout << transitionMatrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void State_assigner::printLPMatrix()
{
    cout << "LP Matrix:" << endl;
    for (int i = 0; i < numStates+1; ++i)
    {
        for (int j = 0; j < numStates; ++j)
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
    cout << "numStates = " << numStates << endl;
    glp_add_cols(lp, numStates);
    
    // set col for glp
    for (int i = 1 ; i <= numStates ; i++)
    {
        glp_set_col_bnds(lp, i, GLP_DB, 0.0, 1.0); // DB is set for 0<=A<=1
        glp_set_obj_coef(lp, i, 1.0);
    }
    // set "subject to"
    glp_add_rows(lp, numStates+1);
    // set row for glp
    for (int i = 1; i <= numStates; i++)
    {
        glp_set_row_bnds(lp, i, GLP_FX, 0.0, 0.0);
    }
    glp_set_row_bnds(lp, numStates+1, GLP_FX, 1.0, 1.0); // A+B+.....+D=1


    int rowNum = numStates + 1;  
    int colNum = numStates;  
    int* ia = new int[rowNum * colNum + 1];  // i array 
    int* ja = new int[rowNum * colNum + 1];  // j array
    double* ar = new double[rowNum * colNum + 1];  // answer array
    
    // computer I-P^T
    LPMatrix.resize(numStates+1, std::vector<double>(numStates));
    // P^T part
    std::vector<std::vector<double>> transposed = transposeMatrix(transitionMatrix);
    std::vector<std::vector<double>> identityMatrix(numStates, std::vector<double>(numStates, 0));
    for (int i = 0; i < numStates; i++) 
    {
        identityMatrix[i][i] = 1;
    }
    std::vector<std::vector<double>> resultMatrix(numStates, std::vector<double>(numStates, 0));
    for (int i = 0 ; i < numStates; i++)
    {
        for (int j = 0; j < numStates ; j++)
        {
            resultMatrix[i][j] = identityMatrix[i][j] - transposed[i][j];
        }
    }
    // assign LPMatrix and fill 1 in the last row
    for (int i = 0; i < rowNum ; i++)
    {
        for (int j = 0; j < colNum; j++)
        {
            if(i == numStates)
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
    std::vector<double> stateProbs;
    for(int i = 1; i <= numStates; i++)
    {
        stateProbs.push_back(glp_get_col_prim(lp,i));
        cout << "S" << i << "= " << stateProbs[i-1] << endl;
    }
    // clear resource
    glp_delete_prob(lp);
    glp_free_env();

    // release dynamic memory.
    delete[] ia;
    delete[] ja;
    delete[] ar;

}


// Function to perform Markov Chain calculation with multiple iterations
std::vector<double> State_assigner::markovChain(const std::vector<std::vector<double>>& transitionMatrix, const std::vector<double>& initialVector) 
{
    int n = transitionMatrix.size();
    std::vector<double> result = initialVector;
    int iterations = n+1;
    for (int iter = 0; iter < iterations; iter++) {
        std::vector<double> tempResult(n, 0.0);
        
        // Perform the matrix multiplication v^T * P
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                tempResult[i] += result[j] * transitionMatrix[j][i];
            }
        }
        
        result = tempResult;
    }

    return result;
}


void State_assigner::testMarkovChain()
{
    // Define the initial vector
    std::vector<double> initialVector = {0.25, 0.25, 0.25, 0.25}; // assume every state have the same prob in the first time

    // Perform the Markov Chain calculation
    std::vector<double> result = markovChain(transitionMatrix, initialVector);

    // Print the result
    std::cout << "Result: ";
    for (double value : result) 
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < transitionMatrix.size(); i++)
    {
        for (int j = 0; j < transitionMatrix.size(); j++)
        {
            transitionMatrix[i][j] = transitionMatrix[i][j] * result[i];
        }
    }

}