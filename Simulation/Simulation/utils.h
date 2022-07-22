// Utilities related to menu showing, component drawing, analysis and helper
// functions This file is completed by Yadong Hu, while in utils.cpp file, the
// implementation of these functions may be completed by Yusen Liu and Keyi Zhou

#pragma once
// C++ standard functions, size_t, atoi, malloc
#include <cstdlib>
// For changing the window size, change the colour and Sleep() functions
#include <Windows.h>
// C++ std::cout and cin
#include <iostream>
// For regular expressions
#include <regex>
// C++ file stream
#include <fstream>
// C++ std::string
#include <cstring>
// C++ formative output
#include <iomanip>
#include <sstream>
// C++ data structure std::vector
#include <vector>
// For sin() and random() functions
#include <cmath>
// For setting the random seeds to time related value
#include <ctime>

//***************** Yadong Hu *****************
// Define the console width and height
#define WIDTH 1200
#define HEIGHT 700
// Maximum data length and bit length
#define MAX_DATA_ARRAY 10
#define MAX_DATA_RESOLUTION 20
#define MAX_BIT_LENGTH 10000

typedef std::vector<double> code_t_i;

//***************** Keyi Zhou *****************
// Define the enum type data
enum _component_ {
  RESISTOR = 0,
  CAPACITOR = 1,
  INDUCTOR = 2,
  OP_AMP = 3,
  CURRENT_SOURCE = 4,
  VOLTAGE_SOURCE = 5,
  NOISE_SOURCE = 6,
  AC_SOURCE = 7,
  SWITCH = 8,
  GROUND = 9
};
enum _direction_ {
  VERTICAL = 0,
  HORIZONTAL = 1,
  V_POSITIVE = 2,
  V_NEGATIVE = 3,
  H_POSITIVE = 4,
  H_NEGATIVE = 5
};
enum _color_ {
  GREEN = 0,
  YELLOW = 1,
  BLUE = 2,
  RED = 3,
  CYAN = 4,
  MAGENTA = 5,
  WHITE = 6,
  GRAY = 7,
  DARK_YELLOW = 8,
  DARK_BLUE = 9,
  DARK_RED = 10,
  DARK_CYAN = 11,
  DARK_MAGENTA = 12,
  DARK_GREEN = 13,
  DARK_WHITE = 14,
  BLACK = 15
};
enum _size_ { NORMAL = 0, BIG = 1 };
enum _connect_ {
  UP_RIGHT = 0,
  UP_LEFT = 1,
  DOWN_LEFT = 2,
  DOWN_RIGHT = 3,
  HORI = 4,
  VERT = 5
};
enum _status_ { SUCCESS = 0, FAILED = 1 };
enum _circuit_ { IVConverter = 0, Comparator = 1, Decoder = 2 };
enum _mode_ { STRICT_MODE = 0, NORMAL_MODE = 1 };
//***************** Keyi Zhou *****************

//***************** Yadong Hu *****************
// To initialize the console window size
class _Initialize {
  friend class _DrawMenu;

 private:
  int columns, lines;

 public:
  _Initialize();
  ~_Initialize() {}
};
//***************** Yadong Hu *****************

//***************** Yusen Liu *****************
// Draw the main menu
class _DrawMenu {
 private:
  _Initialize init;

 public:
  _DrawMenu();
  void draw();
  void boundaries();
  void encode_item();
  void circuit_item();
  void decode_item();
  void help_item();
  void main_menu();
  static void clear_screen();
  int get_user_input();
  void select_menu_item(int input);
  void go_back_to_main();
  bool is_integer(std::string num);
  ~_DrawMenu() {}
};
//***************** Yusen Liu *****************

//***************** Keyi Zhou and Yadong Hu*****************
// Draw each component according to the properties
class _DrawComponent {
 private:
  _component_ component;
  _color_ color1, color2;
  _direction_ direction;
  _size_ size;
  std::string name;
  double noise_ratio, resistance, temperature, bandwidth;  // for thermal_noise
  int position_x, position_y;
  int port[10];
  double value;

 public:
  // Two types of conctructors
  _DrawComponent(_component_, _color_, _color_, _direction_, _size_,
                 std::string, double);
  _DrawComponent(_component_, std::string, std::string, _direction_, _size_,
                 std::string, std::string);
  void draw();
  // Get private data
  _component_ getComp() { return this->component; }
  _color_ getColor1() { return this->color1; }
  _color_ getColor2() { return this->color2; }
  _direction_ getDirection() { return this->direction; }
  _size_ getSize() { return this->size; }
  std::string getName() { return this->name; }
  double getValue() { return this->value; }
  int getPositionX() { return this->position_x; }
  int getPositionY() { return this->position_y; }
  int getPort(int);
  // Set private data
  void setThermalNoise(double, double, double, double);
  void setPort(int[]);
  void setPosition(int, int);
  int getSpaceNum();
  // Destructor
  ~_DrawComponent() {}
};
//***************** Keyi Zhou and Yadong Hu*****************

//***************** Keyi Zhou *****************
// Data analysis functions
class _Analyse {
 private:
 public:
  // Plot table
  static void outputTable(code_t_i t);
  // Plot square graph
  static void outputSquareGraph(code_t_i t, int position_x, int position_y,
                                _mode_ m);
  // Plot sin graph
  static void outputSinGraph(code_t_i t, int position_x, int position_y);
  // Calculate values at each analyse point
  static void calculateValues(_circuit_);
};
//***************** Keyi Zhou *****************

//***************** Yadong Hu *****************
// Some helpful tools
class _Helper {
 public:
  // Convert enum type colour name to WORD type hex values
  static WORD convertColorNameToHex(_color_, int);
  // Convert unit
  static std::string convertToUnitValue(double);
  // Cut the tailing zeros while using to_string() function
  static std::string cutTailingZeros(double);
  // Set the cursor at a point
  static void locateCursorAt(int, int);
  // Set the cursor at a pre-determined point1
  static void setCursorToBase1(std::string);
  // Set the cursor at a pre-determined point2
  static void setCursorToBase2(std::string);
  // Display the spaces needed
  static void displaySpaces(int);
  // Automatically connect components
  static void connectComponent(int, int, int, int, _connect_, _connect_);
  // Display error messages
  static void errorMessage(int, std::string);
  // Display success messages
  static void successMessage(int, std::string, std::string);
  // Clear screen
  static void clearScreen(int, int);
  // Read TXT files
  static _status_ readTXT(std::string, std::string, int, std::string, int);
  // Return a word from characters
  static std::vector<std::string> getWord(std::vector<std::string>, int);
};
//***************** Yadong Hu *****************
