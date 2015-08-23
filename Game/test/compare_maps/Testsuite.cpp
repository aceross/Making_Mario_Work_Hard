# include <iostream>
# include <vector>
# include <string>

# include "../../include/tile_map.hpp"

bool compareChunkMaps(std::vector< std::vector<std::string> > Chunk1,
                      std::vector< std::vector<std::string> > Chunk2);

void Print(std::vector< std::vector<std::string> >, std::vector< std::vector<std::string> >);

int main() {
   TileMap t;
   bool passed = true;

  // First Test: 3 vars 3 clauses:

   std::vector<std::string> innerstart;
     innerstart.push_back("start_gadget");
     innerstart.push_back("warp_start");
     innerstart.push_back("warp");
     innerstart.push_back("warp");
     innerstart.push_back("warp");
     innerstart.push_back("warp_end");
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

     t.CreateChunkMap(3,3);

     std::cout << "Outer[0][0] : " << outer[0][0] << std::endl;
     std::cout << "t[0][0] : " << t.test_map_[0][0] << std::endl;

   if (t.test_map_ == outer) {
     std::cout << "Test 1 Passed" << std::endl;
   } else {
     std::cout << "Test 1 (3 vars and 3 clauses) failed" << std::endl;
     Print(t.test_map_,outer);
     passed = false;
   }

// Second Test: 2 vars, 4 clauses
   std::vector<std::string> innerstartb;
     innerstartb.push_back("start_gadget");
     innerstartb.push_back("warp_start");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp_end");
     innerstartb.push_back("warp_start");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp");
     innerstartb.push_back("warp_end");
   std::vector<std::string> innervarb;
     innervarb.push_back("variable_gadget");
     innervarb.push_back("warp_start");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp_end");
     innervarb.push_back("warp_start");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp");
     innervarb.push_back("warp_end");
   std::vector<std::string> innerendb;
     innerendb.push_back("check_in");
     innerendb.push_back("clause_gadget");
     innerendb.push_back("clause_gadget");
     innerendb.push_back("clause_gadget");
     innerendb.push_back("clause_gadget");
     innerendb.push_back("finish_gadget");

   std::vector< std::vector<std::string> > outerb;
     outerb.push_back(innerstartb);
     outerb.push_back(innervarb);
     outerb.push_back(innerendb);

  t.CreateChunkMap(2,4);
   if (compareChunkMaps(t.test_map_, outerb)) {
     std::cout << "Test 2 Passed" << std::endl;
  }
  else {
     std::cout << "Test 2 (2 vars and 4 clauses) failed" << std::endl;
     Print(t.test_map_,outerb);
     passed = false;
  }


  if (passed) { std::cout << "All tests passed" << std::endl; }
}

bool compareChunkMaps(std::vector< std::vector<std::string> > Chunk1, std::vector< std::vector<std::string> > Chunk2) {
  return Chunk1 == Chunk2;
}

void Print(std::vector< std::vector<std::string> > a, std::vector< std::vector<std::string> > b) {
  for(int i = 0; i < a.size(); ++i) {
    for(int j = 0; j < a[i].size(); ++j) {
      std::cout << a[i][j] << " " << b[i][j] << " " << (a[i][j] == b[i][j]) << std::endl;
//      std::cout << a[i][j] << std::endl;
    }
  }
}
