#include <LEDA/graph/graph.h>
#include <LEDA/graph/mw_matching.h>

using namespace leda;

int main()
{
  graph G; 

  node n1=G.new_node();
  node n2=G.new_node(); node n3=G.new_node();
  node n4=G.new_node(); 

  edge e1=G.new_edge(n1,n2);
  edge e2=G.new_edge(n2,n3); 
  edge e3=G.new_edge(n3,n4);
  edge e4=G.new_edge(n2,n4);

  edge_array<int> weight(G);
  weight[e1]=6;  weight[e2]=9;  weight[e3]=27;
  weight[e4]=9;  
 
  list<edge> M_min=MIN_WEIGHT_PERFECT_MATCHING(G,weight);

  std::cout << "Minimum Weighted Perfect Matching:" << std::endl;
  int weight_M_min=0;
  edge e;
  forall(e,M_min) {G.print_edge(e); weight_M_min+=weight[e];}
  std::cout << " weight: " << weight_M_min << std::endl;
  
  list<edge> M_max=MAX_WEIGHT_PERFECT_MATCHING(G,weight);

  std::cout << "Maximum Weighted Perfect Matching:" << std::endl;
  int weight_M_max=0;
  forall(e,M_max) {G.print_edge(e); weight_M_max+=weight[e];}
  std::cout << " weight: " << weight_M_max << std::endl;

  return 0;
}