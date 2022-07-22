// Set the build-in templates

#pragma once
#include "utils.h"

//***************** Yusen Liu *****************
class _SetLayout {
 private:
  double data[MAX_DATA_ARRAY][MAX_DATA_RESOLUTION];
  double rawData[2][MAX_BIT_LENGTH];

 public:
  // Some kinds of circuits (not all finished yet)
  _SetLayout() { system("cls"); }
  static int RLC();
  static int Diodes();
  static int IVConverter();
  static int Comparator();
  static int Decoder();
};
//***************** Yusen Liu *****************
