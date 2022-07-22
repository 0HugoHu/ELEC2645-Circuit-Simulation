#define DISABLE_WARNING_PUSH _Pragma("GCC diagnostic push")
#define DISABLE_WARNING_POP _Pragma("GCC diagnostic pop")

//  MAIN ENTRY
//
//  Code statistic - Contribution:
//  
//  File Name      |     Lines     |    Yadong Hu   |    Yusen Liu    |    KeyiZhou
//	--------------------------------------------------------------------------------
//  Simulation.cpp        28              100%               0%               0%
//  utils.h               222              16%              38%              46%   
//  utils.cpp             1867             38%              39%              23% 
//  submenu.h             16              100%               0%               0%
//  submenu.cpp           1039             45%              37%              15%
//  layouts.h             21                0%              80%              20%    
//  layouts.cpp           636              21%              39%              40%
//  huffman.h             109              44%               0%              56%
//  huffman.cpp           469              37%               0%              63%
//  --------------------------------------------------------------------------------
//  Total                 4413          1835(37.56%)    1412(30.70%)     1495(31.74%)
//

#include "utils.h"

int main() {
  // Start the whole program
  _DrawMenu d;
  // Used for debug
  _Helper::locateCursorAt(0, 80);
  return 0;
}
