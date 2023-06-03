#include <LEDA/graph/graph.h>
#include <vector>
#include <unordered_map>
class NodeInfo
{
public:
    std::string getName();
private:
    std::string name;   
};

class Graph
{
public:    
    void clear()
    {
        this->name.clear();
        this->ledaGraph.clear();
        this->source = nullptr;
        this->_stateName2Node.clear();
        this->nodeInfos.clear();
    }
private:
    leda::GRAPH<NodeInfo *, int> ledaGraph;
    std::string name;
    leda::node source;
    std::vector<NodeInfo*> nodeInfos;
    std::unordered_map<std::string, leda::node> _stateName2Node;
};

