# include <iostream>
# include <vector>
# include <string>

# include "../../include/tile_map.hpp"

int main() {
   bool passed = true;

  // First Test: 3 vars 3 clauses:
  {
     std::vector<std::string> innerstart;
       innerstart.push_back("start_gadget");
       innerstart.push_back("warp_start");
       innerstart.push_back("warp");
       innerstart.push_back("warp");
       innerstart.push_back("warp");
       innerstart.push_back("warp_end");
     std::vector<std::string> innervar;
       innervar.push_back("variable_gadget");
       innervar.push_back("warp_start");
       innervar.push_back("warp");
       innervar.push_back("warp");
       innervar.push_back("warp");
       innervar.push_back("warp_end");
     std::vector<std::string> innerend;
       innerend.push_back("check_in");
       innerend.push_back("clause_gadget");
       innerend.push_back("clause_gadget");
       innerend.push_back("clause_gadget");
       innerend.push_back("finish_gadget");

     std::vector< std::vector<std::string> > outer;
       outer.push_back(innerstart);
       outer.push_back(innervar);
       outer.push_back(innervar);
       outer.push_back(innerend);

     if (compareChunkMaps(createChunkMap(3,3),outer)) { std::cout << "Test 1 (3 vars and 3 clauses) failed" << std::endl;  }
  }
// Second Test: 2 vars, 4 clauses
  {
     std::vector<std::string> innerstart;
       innerstart.push_back("start_gadget");
       innerstart.push_back("warp_start");
       innerstart.push_back("warp");
       innerstart.push_back("warp");
       innerstart.push_back("warp");
       innerstart.push_back("warp");
       innerstart.push_back("warp_end");
     std::vector<std::string> innervar;
       innervar.push_back("variable_gadget");
       innervar.push_back("warp_start");
       innervar.push_back("warp");
       innervar.push_back("warp");
       innervar.push_back("warp");
       innervar.push_back("warp");
       innervar.push_back("warp_end");
     std::vector<std::string> innerend;
       innerend.push_back("check_in");
       innerend.push_back("clause_gadget");
       innerend.push_back("clause_gadget");
       innerend.push_back("clause_gadget");
       innerend.push_back("clause_gadget");
       innerend.push_back("finish_gadget");

     std::vector< std::vector<std::string> > outer;
       outer.push_back(innerstart);
       outer.push_back(innervar);
       outer.push_back(innerend);

     if (compareChunkMaps(createChunkMap(2,4),outer)) { std::cout << "Test 2 (2 vars and 4 clauses) failed" << std::endl; }
  }

  if (passed) { std::cout << "All tests passed" << std::endl; }
}

bool compareChunkMaps(std::vector< std::vector<std::string> > Chunk1, std::vector< std::vector<std::string> > Chunk2) {
  return Chunk1 == Chunk2;
}
