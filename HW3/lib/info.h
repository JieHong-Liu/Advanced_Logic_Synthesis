#include <LEDA/graph/graph.h>
#include <vector>
#include <unordered_map>

namespace Process // a namespace avoid to confuse with LEDA/graph
{
    struct NodeInfo
    {
        NodeInfo(std::string name, int id)
        {
            this->name = name;
            this->id = id;
            this->stateProb = 0.0;
        }
        std::string name;
        int id; 
        double stateProb;
    };
    struct EdgeInfo
    {
        EdgeInfo(std::string src, std::string tgt, double wgt)
        {
            this->source = src;
            this->target = tgt;
            this->weight = wgt;
        }
        std::string source;
        std::string target;
        double weight;
    };
    struct Graph
    {
        Graph()
        {
            // Graph Constructor
            this->clear();
        };
        ~Graph()
        {
            for (NodeInfo* info : nodeInfos)  // dynamically release memory.
            {
                delete info;
            }
            for (EdgeInfo* info : edgeInfos)  // dynamically release memory.
            {
                delete info;
            }
        }
        void clear()
        {
            this->name.clear();
            this->ledaGraph.clear();
            this->_stateName2Node.clear();
            this->nodeInfos.clear();
        }
        leda::GRAPH<NodeInfo *, EdgeInfo* > ledaGraph; // leda graph, first represent to Node class, and second for double value.
        std::string name;
        std::vector<NodeInfo*> nodeInfos;
        std::vector<EdgeInfo*> edgeInfos;
        std::unordered_map<std::string, leda::node> _stateName2Node;
    };
}

