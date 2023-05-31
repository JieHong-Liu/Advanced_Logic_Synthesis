#include <LEDA/core/tuple.h>
#include <LEDA/core/string.h>
#include <LEDA/core/array.h>
#include <LEDA/core/d_array.h>
using namespace leda;

int main()
{
  array<int>A(1,100);
  int i;
  for(i=A.low();i<= A.high(); i++)
  {
      A[i]=i;
  }
  std::cout << "A.low="  << A.low() << std::endl;
  std::cout << "A.high=" << A.high() << std::endl; 
  d_array<string,string> D;
  D["hello"] = "mother"; D["world"] = "fucker";
  string s;
  forall_defined(s,D)
  {
      std::cout << s << " " << D[s] << std::endl;
  }
    
  
  return 0;
}
