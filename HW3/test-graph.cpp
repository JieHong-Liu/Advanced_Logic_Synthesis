#include <LEDA/graph/graph.h>
#include <LEDA/graph/basic_graph_alg.h>

using namespace leda;
int main()
{
    GRAPH<string, string> G;
    node n0,n1,n2,n3,n4,n5,n6;

    n0 = G.new_node("A");
    n1 = G.new_node("B");
    n2 = G.new_node("C");
    n3 = G.new_node("D");
    n4 = G.new_node("E");
    n5 = G.new_node("F");
    n6 = G.new_node("G");

    G.new_edge(n5, n0);
    G.new_edge(n5, n1);
    G.new_edge(n5, n2);
    G.new_edge(n1, n3);
    G.new_edge(n0, n4);
    G.new_edge(n4, n6);

    // DFS
    node_array<bool> reached(G, false); // DFS expect value false for all nodes.
    list<node> LN1 =DFS(G,n5,reached); 
    node v;
    std::cout << "LN1: "; 
    forall(v,LN1) 
    {
        G.print_node(v);
    }
    std::cout << std::endl << std::endl;

    //first variant of BFS
    node_array<int> dist1(G,-1);   
                        //BFS expects value -1 for all nodes
    list<node> LN2=BFS(G,n5,dist1); // save the distance between n5 and all nodes

    forall_nodes(v,G) 
    {
        G.print_node(v);
        std::cout << " dist1[v]=" << dist1[v] << std::endl;
    }   
        //dist1[v]=-1 for [4],[6], dist1[v]=0 for [5], 
        //dist1[v]=1 for [0],[1],[2], dist1[v]=2 for [3]

    std::cout << "LN2: ";
    forall(v,LN2) G.print_node(v);
    std::cout << std::endl << std::endl; // prints LN2: [5][0][1][2][4][3][6]
}
