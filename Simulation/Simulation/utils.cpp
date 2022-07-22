// The implementation of Util.h functions
// This file is created and completed by Yadong Hu, Keyi Zhou and Yusen Liu

#include "utils.h"

#include "huffman.h"
#include "layouts.h"
#include "submenu.h"

//***************** Yadong Hu *****************
// To initialize the console window size
_Initialize::_Initialize() : columns(145), lines(39) {
  // Set the console exactly on the middle of computer screen
  HWND hwnd = GetForegroundWindow();
  int cx = GetSystemMetrics(SM_CXSCREEN);
  int cy = GetSystemMetrics(SM_CYSCREEN);
  SetWindowPos(hwnd, HWND_TOP, (cx - WIDTH) / 2, (cy - HEIGHT) / 2, WIDTH,
               HEIGHT, 0);
}
//***************** Yadong Hu *****************

//***************** Yusen Liu *****************
// Draw the main menu
_DrawMenu::_DrawMenu() { main_menu(); }
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Draw the main menu
void _DrawMenu::main_menu() {
  clear_screen();
  boundaries();

  // The title of this calculator
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  _Helper::locateCursorAt(42, 5);
  SetConsoleTextAttribute(consolehwnd, 0x0b);
  std::cout << "< Signal Receiving and Decoding Circuit Verification >";
  SetConsoleTextAttribute(consolehwnd, 0x0F);
  _Helper::locateCursorAt(62, 8);
  std::cout << "Version: 1.3";  // This number should be changed after the
                                // project is done
  _Helper::locateCursorAt(45, 10);
  std::cout << "CopyRight 2020 Yadong Hu, Yusen Liu, Keyi Zhou";

  // Show the menu items
  _Helper::locateCursorAt(23, this->init.lines - 8);
  std::cout << "> 1. Encode";
  _Helper::locateCursorAt(this->init.columns - 40, this->init.lines - 8);
  std::cout << "> 2. Circuit";
  _Helper::locateCursorAt(23, this->init.lines - 6);
  std::cout << "> 3. Decode";
  _Helper::locateCursorAt(this->init.columns - 40, this->init.lines - 6);
  std::cout << "> 4. Help";

  int _input = get_user_input();
  select_menu_item(_input);
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Clear the screen
void _DrawMenu::clear_screen() {
  /*
  for (int i = 0; i < 40; i++) {
          for (int j = 0; j < 145; j++) {
                  _Helper::locateCursorAt(j, i);
                  std::cout << " ";
          }
  }
  */
  system("cls");
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Draw the outline boundaries
void _DrawMenu::boundaries() {
  // Draw the boundaries to form a "page"
  _Helper::locateCursorAt(0, 1);
  std::cout << "◤";
  _Helper::locateCursorAt(this->init.columns - 1, 1);
  std::cout << "◥";
  _Helper::locateCursorAt(0, this->init.lines);
  std::cout << "◣";
  _Helper::locateCursorAt(this->init.columns - 1, this->init.lines);
  std::cout << "◢";

  // Draw the left edge of the window
  for (int i = 2; i < this->init.lines; i++) {
    _Helper::locateCursorAt(0, i);
    std::cout << "|";
  }
  for (int i = 2; i < this->init.lines; i++) {
    _Helper::locateCursorAt(1, i);
    std::cout << "|";
  }
  // Draw the right edge of the window
  for (int i = 2; i < this->init.lines; i++) {
    _Helper::locateCursorAt(this->init.columns, i);
    std::cout << "|";
  }
  for (int i = 2; i < this->init.lines; i++) {
    _Helper::locateCursorAt(this->init.columns - 1, i);
    std::cout << "|";
  }
  // Draw the upper edge of the window
  for (int i = 2; i < this->init.columns - 1; i++) {
    _Helper::locateCursorAt(i, 0);
    std::cout << "_";
  }
  for (int i = 2; i < this->init.columns - 1; i++) {
    _Helper::locateCursorAt(i, 1);
    std::cout << "_";
  }
  // Draw the lower edge of the window
  for (int i = 2; i < this->init.columns - 1; i++) {
    _Helper::locateCursorAt(i, this->init.lines);
    std::cout << "_";
  }
  for (int i = 2; i < this->init.columns - 1; i++) {
    _Helper::locateCursorAt(i, this->init.lines - 1);
    std::cout << "_";
  }
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Obtain user input
int _DrawMenu::get_user_input() {
  int input;
  std::string input_string;
  bool valid_input = false;
  int menu_items = 5;

  do {
    for (int i = 2; i < this->init.columns - 2; i++) {
      _Helper::locateCursorAt(i, this->init.lines - 3);
      std::cout << " ";
    }
    _Helper::locateCursorAt(4, this->init.lines - 3);
    std::cout << "> Select item: ";
    std::cin >> input_string;
    valid_input = is_integer(input_string);
    // if input is not an integer, print an error message
    if (valid_input == false) {
      for (int i = 2; i < this->init.columns - 2; i++) {
        _Helper::locateCursorAt(i, this->init.lines - 2);
        std::cout << " ";
      }
      _Helper::locateCursorAt(4, this->init.lines - 2);
      std::cout << "<Enter an integer!>";
    } else {  // if it is an int, check whether in range
      input = std::stoi(input_string);  // convert to int
      if (input >= 0 && input <= menu_items) {
        valid_input = true;
      } else {
        for (int i = 2; i < this->init.columns - 2; i++) {
          _Helper::locateCursorAt(i, this->init.lines - 2);
          std::cout << " ";
        }
        _Helper::locateCursorAt(4, this->init.lines - 2);
        std::cout << "<Invalid menu item!>";
        valid_input = false;
      }
    }
  } while (valid_input == false);

  return input;
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Select memu item
void _DrawMenu::select_menu_item(int input) {
  switch (input) {
    case 1:
      encode_item();
      break;
    case 2:
      circuit_item();
      break;
    case 3:
      decode_item();
      break;
    case 4:
      help_item();
      break;
    default:
      exit(1);
      break;
  }
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Go back to main menu
void _DrawMenu::go_back_to_main() {
  /*
  std::string input;
  do {
          _Helper::locateCursorAt(4, this->init.lines - 2);
          std::cout << "> Enter 'b' or 'B' to go back to main menu: ";
          std::cin >> input;
  } while (input != "b" && input != "B");
  */
  main_menu();
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Judge if is integer
bool _DrawMenu::is_integer(std::string num) {
  return std::regex_match(num, std::regex("[+-]?[0-9]+"));
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Encode menu layout
void _DrawMenu::encode_item() {
  clear_screen();
  boundaries();

  _Helper::locateCursorAt(67, 3);
  std::cout << "< Encode >";
  // Give out the instructions to the user
  _Helper::locateCursorAt(2, 5);
  std::cout
      << "> Welcome! This is the encode function. You can input the words and "
         "the encoding result using Huffman coding will be displayed.";
  _Helper::locateCursorAt(2, 7);
  std::cout << "> This function simulates the function of the transmitter side "
               "of the signal (converting text to '01' code and transmitting "
               "as a sine wave).";
  _Helper::locateCursorAt(2, 9);
  std::cout << "> E.g.";
  _Helper::locateCursorAt(2, 11);
  std::cout << "  TEXT: 'Hello My Great World!'";
  _Helper::locateCursorAt(2, 13);
  std::cout << "  Transferred into:";
  _Helper::locateCursorAt(2, 15);
  std::cout << "  01_CODE: "
               "'10101111000000111000110110111001100111011111011001000010101111"
               "0110100011001000'";

  _Helper::locateCursorAt(2, 17);
  std::cout << "> For best performance, please enter a sentence with at least "
               "2 words and no more than 7 words.";

  _Helper::locateCursorAt(2, 20);
  std::cout << "> Press '0' to turn back.";

  // The diagram of the encoding circuit can be displayed here
  std::string encode_input;
  _Helper::locateCursorAt(4, this->init.lines - 4);
  std::cout << "> Please input the words to be encoded: ";
  getchar();
  std::getline(std::cin, encode_input);
  if (encode_input == "0") go_back_to_main();

  // use another screen to display the result
  clear_screen();
  boundaries();
  _Helper::locateCursorAt(63, 3);
  std::cout << "< Encode Results >";
  code_t_i ci;
  _Huffman h;
  h.huffmanEncode(encode_input, 1);
  ci = h.transferBtoI(h.getCodeT());
  double num = 0;
  for (unsigned int i = 0; i < ci.size(); i++) {
    num = (double)(rand() % 100) / (double)100 - 0.5;
    ci[i] += num;
  }
  //_Analyse::outputSquareGraph(ci, 4, 10, STRICT_MODE);
  _Helper::locateCursorAt(74, 6);
  std::cout << "> Square wave of the binary code (Only 16 bits are shown):";
  _Analyse::outputSquareGraph(ci, 74, 8, NORMAL_MODE);
  _Helper::locateCursorAt(74, 18);
  std::cout << "> Sine wave of the binary code (Transmiting wave):";
  _Analyse::outputSinGraph(ci, 74, 20);
  h.huffmanDecode();

  _Helper::locateCursorAt(4, this->init.lines - 4);
  std::cout << "> Press '0' to turn back.";
  _Helper::locateCursorAt(4, this->init.lines - 6);
  std::cout << "> Binary results have been saved in rawData.txt";
  get_user_input();
  go_back_to_main();
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Show circuit layout
void _DrawMenu::circuit_item() {
  clear_screen();
  int flag = 1;
  while (flag) {
    _SetLayout::IVConverter();
    _SetLayout::Comparator();
    flag = _TemplateFunction::IVConverter(_SetLayout::Decoder());
  }
  go_back_to_main();
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Decode menu layout
void _DrawMenu::decode_item() {
  clear_screen();
  boundaries();

  std::string _filename = "decodedData.txt";
  std::ifstream infile(_filename, std::ios::in);
  if (!infile) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  std::string _line;
  std::vector<std::string> _v;
  while (getline(infile, _line, '\r')) {
    _v.push_back(_line);
  }
  infile.close();

  // Give out the instructions to the user
  _Helper::locateCursorAt(67, 3);
  std::cout << "< Decode >";
  _Helper::locateCursorAt(2, 5);
  std::cout
      << "> Welcome! This is the encoding function.You can input the words and "
         "the encoding result using Huffman coding will be displayed.";
  _Helper::locateCursorAt(2, 7);
  std::cout << "> Notice that, you should first run the 2 - Circuit function "
               "before obtaining correct data from this function.";
  _Helper::locateCursorAt(2, 9);
  std::cout << "> Original sentence is:";
  _Helper::locateCursorAt(2, 11);
  std::string orCode = _v.at(0);
  std::cout << "  " << _v.at(0);
  _Helper::locateCursorAt(2, 13);
  std::cout << "> Original binary code is:";
  _Helper::locateCursorAt(2, 15);
  _filename = "rawData.txt";
  std::ifstream infile2(_filename, std::ios::in);
  if (!infile2) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line = "";
  _v.clear();
  while (getline(infile2, _line, '\r')) {
    _v.push_back(_line);
  }
  infile2.close();
  std::vector<double> squarewave_o;
  for (unsigned i = 0; i < _v.at(0).size(); i++) {
    squarewave_o.push_back(_v.at(0).at(i) - 48);
  }
  std::cout << "  " << _v.at(0);
  _Helper::locateCursorAt(2, 19);
  std::cout << "> Comparator output binary code is:";
  _Helper::locateCursorAt(2, 21);
  _filename = "noiseData.txt";
  std::ifstream infile3(_filename, std::ios::in);
  if (!infile3) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line = "";
  _v.clear();
  while (getline(infile3, _line, '\n')) {
    _v.push_back(_line);
  }
  infile3.close();
  std::vector<double> squarewave;
  for (unsigned i = 0; i < _v.size(); i++) {
    squarewave.push_back(stof(_v.at(i)));
  }
  std::cout << "  ";
  for (unsigned i = 0; i < squarewave.size(); i++) {
    if (squarewave.at(i) >= 0.5)
      std::cout << 1;
    else
      std::cout << 0;
  }

  _filename = "decodedDataFinal.txt";
  std::ifstream infile4(_filename, std::ios::in);
  if (!infile4) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line = "";
  _v.clear();
  while (getline(infile4, _line, '\r')) {
    _v.push_back(_line);
  }
  infile4.close();

  _Helper::locateCursorAt(2, 23);
  std::cout << "> Decoder output is:";
  _Helper::locateCursorAt(2, 25);
  std::cout << "  " + _v.at(0);

  _Helper::locateCursorAt(74, 9);
  std::cout
      << "> Square wave of original binary code (Only 16 bits are shown):";
  _Analyse::outputSquareGraph(squarewave_o, 74, 11, NORMAL_MODE);
  _Helper::locateCursorAt(74, 19);
  std::cout << "> Square wave of comparator output binary code (As noise added):";
  _Analyse::outputSquareGraph(squarewave, 74, 21, STRICT_MODE);

  _Helper::locateCursorAt(2, 29);
  if (orCode == _v.at(0)) {
    std::cout << "> The result is correct! The noise has been removed through "
                 "this circuit!";
  } else {
    std::cout << "> The result is not correct! Try to set smaller noise ratio "
                 "or different capacitor property!";
  }

  // The diagram of the encoding circuit can be displayed here
  std::string encode_input = "";
  while (encode_input != "0") {
    _Helper::locateCursorAt(4, this->init.lines - 4);
    std::cout << "> Please enter 0 to turn back:";
    std::cin >> encode_input;
  }
  go_back_to_main();
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Help menu layout
void _DrawMenu::help_item() {
  clear_screen();
  boundaries();

  //Give out the instructions to the user
  _Helper::locateCursorAt(67, 3);
  std::cout << "< HELP >";
  _Helper::locateCursorAt(2, 5);
  std::cout << "> Welcome! This is a calculater aimed at simulating the whole data processing procedure for ADC using Huffman coding.";
  _Helper::locateCursorAt(2, 7);
  std::cout << "> The procedure is divided into three parts and represents the different parts in practical application, they are:";
  _Helper::locateCursorAt(2, 8);
  std::cout << "  Encoder, Receiver circuits and Decoder.";
  _Helper::locateCursorAt(2, 10);
  std::cout << "> You can use these menu items to get a graph of the circuit and get the physical quantity of the components in the circuit.";
  _Helper::locateCursorAt(2, 12);
  std::cout << "> Example of the component is shown below :";

  //Capacitor
  _Helper::locateCursorAt(12, 14);
  std::cout << "> Capacitor :";
  _DrawComponent capacitor(CAPACITOR, YELLOW, CYAN, HORIZONTAL, NORMAL, "C1", 1e-9);
  capacitor.setPosition(12, 16);
  capacitor.draw();

  //Inductor
  _Helper::locateCursorAt(12, 20);
  std::cout << "> Inductor :";
  _DrawComponent inductor(INDUCTOR, YELLOW, DARK_CYAN, HORIZONTAL, NORMAL, "L1", 1e-9);
  inductor.setPosition(12, 22);
  inductor.draw();

  //Resistor
  _Helper::locateCursorAt(45, 14);
  std::cout << "> Resistor :";
  _DrawComponent resistor(RESISTOR, YELLOW, DARK_BLUE, HORIZONTAL, NORMAL, "R1", 1e-9);
  resistor.setPosition(45, 16);
  resistor.draw();

  //Op-amp
  _Helper::locateCursorAt(80, 14);
  std::cout << "> Op-amp :";
  _DrawComponent op_amp(OP_AMP, YELLOW, RED, HORIZONTAL, BIG, "CA3140E", 0);
  op_amp.setPosition(80, 16);
  op_amp.draw();

  //Current source
  _Helper::locateCursorAt(45, 20);
  std::cout << "> Current Source :";
  _DrawComponent currentSource(CURRENT_SOURCE, YELLOW, DARK_GREEN, VERTICAL, NORMAL, "I0", 0.32);
  currentSource.setPosition(45, 22);
  currentSource.draw();

  //Noise Source
  _Helper::locateCursorAt(12, 26);
  std::cout << "> Noise Source :";
  _DrawComponent noiseSource(NOISE_SOURCE, YELLOW, GRAY, VERTICAL, NORMAL, "", 0);
  noiseSource.setPosition(12, 28);
  noiseSource.setThermalNoise(1.0, 10000, 27, 1000000);
  noiseSource.draw();

  //Ground
  _Helper::locateCursorAt(45, 26);
  std::cout << "> Ground :";
  _DrawComponent ground3(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "Ground", 0);
  ground3.setPosition(45, 28);
  ground3.draw();

  _Helper::locateCursorAt(2, 31);
  std::cout << "> Note: The current label 'in_file_array' indicates its values are stored in files in the form of array.";

  _Helper::locateCursorAt(2, 33);
  std::cout << "> Press '0' to see the example circuit.";

  int a = 1;
  while (a) {
    a = get_user_input();
  }
  clear_screen();
  boundaries();
  _Helper::locateCursorAt(67, 3);
  std::cout << "< ADDER CIRCUIT >";
  _Helper::locateCursorAt(2, 5);
  std::cout << "> An adder circuit is shown below: ";

  // Input resistor 1
  _DrawComponent resistor_e1(RESISTOR, YELLOW, GREEN, HORIZONTAL, NORMAL, "R1", 1e4);
  resistor_e1.setPosition(12, 15);
  resistor_e1.draw();

  // Input resistor 2
  _DrawComponent resistor_e2(RESISTOR, YELLOW, GREEN, HORIZONTAL, NORMAL, "R2", 1e4);
  resistor_e2.setPosition(12, 17);
  resistor_e2.draw();

  // The op-amp
  _DrawComponent op_amp_e(OP_AMP, YELLOW, RED, HORIZONTAL, BIG, "", 0);
  op_amp_e.setPosition(30, 14);
  op_amp_e.draw();

  // The pull-up resistor
  _DrawComponent resistor_p1(RESISTOR, YELLOW, GREEN, VERTICAL, NORMAL, "R3", 1e4);
  resistor_p1.setPosition(50, 7);
  resistor_p1.draw();
  _DrawComponent resistor_p2(RESISTOR, YELLOW, GREEN, VERTICAL, NORMAL, "R4", 1e4);
  resistor_p2.setPosition(50, 9);
  resistor_p2.draw();

  //Ground
  _DrawComponent grounde1(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  grounde1.setPosition(46, 7);
  grounde1.draw();



  // Connector
  _Helper::connectComponent(grounde1.getPort(0), grounde1.getPort(1), resistor_p1.getPort(0), resistor_p1.getPort(1), DOWN_RIGHT, VERT);
  _Helper::connectComponent(resistor_p2.getPort(2) - 1, resistor_p2.getPort(3) - 1, op_amp_e.getPort(0), op_amp_e.getPort(1), DOWN_LEFT, UP_RIGHT);
  _Helper::connectComponent(resistor_e1.getPort(1) + 1, resistor_e1.getPort(3), resistor_e2.getPort(1), resistor_e2.getPort(3), HORI, UP_LEFT);
  _Helper::connectComponent(resistor_e2.getPort(1) + 1, resistor_e2.getPort(3), op_amp_e.getPort(2), op_amp_e.getPort(3), HORI, HORI);
  _Helper::connectComponent(op_amp_e.getPort(4), op_amp_e.getPort(5), op_amp_e.getPort(4) + 40, op_amp_e.getPort(5), HORI, HORI);
  _Helper::locateCursorAt(50, 14);
  std::cout << "┛ ";

  int num_1;
  _Helper::locateCursorAt(2, 25);
  std::cout << "> Press enter the first number to be added (1 or 0). Number 1: ";
  std::cin >> num_1;

  int num_2;
  _Helper::locateCursorAt(2, 27);
  std::cout << "> Press enter the second number to be added (1 or 0). Number 2: ";
  std::cin >> num_2;

  int sum;
  sum = num_1 ^ num_2;
  _Helper::locateCursorAt(2, 29);
  std::cout << "> The sum of nember 1 and number 2 is " << sum << std::endl;

  _Helper::locateCursorAt(2, 33);
  std::cout << "> Press '0' to turn back.";
  int b = 1;
  while (b) {
    b = get_user_input();
  }
  go_back_to_main();

}
//***************** Yusen Liu *****************

//***************** Keyi Zhou *****************
// Constructor 1 of drawcomponent class
_DrawComponent::_DrawComponent(_component_ cp, _color_ c1, _color_ c2,
                               _direction_ d, _size_ s, std::string n,
                               double v) {
  // Initialize the parameters
  for (int i = 0; i < 10; i++) {
    this->port[i] = 0;
  }
  this->component = cp;
  this->color1 = c1;
  this->color2 = c2;
  this->direction = d;
  this->size = s;
  this->name = n;
  this->value = v;
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
// Constructor 2 of drawcomponent class
_DrawComponent::_DrawComponent(_component_ cp, std::string xc1, std::string xc2,
                               _direction_ d, _size_ s, std::string xn,
                               std::string xv) {
  // Convert std::string type into each component's data type
  // Initialize the temp variables
  _color_ c1 = WHITE, c2 = WHITE;
  std::string n;
  double v;
  const char* _string_to_double = xv.data();

  // Initialize the colour
  if (xc1 == "GREEN") {
    c1 = GREEN;
  } else if (xc1 == "YELLOW") {
    c1 = YELLOW;
  } else if (xc1 == "BLUE") {
    c1 = BLUE;
  } else if (xc1 == "RED") {
    c1 = RED;
  } else if (xc1 == "CYAN") {
    c1 = CYAN;
  } else if (xc1 == "MAGENTA") {
    c1 = MAGENTA;
  } else if (xc1 == "WHITE") {
    c1 = WHITE;
  } else if (xc1 == "GRAY") {
    c1 = GRAY;
  } else if (xc1 == "DARK_YELLOW") {
    c1 = DARK_YELLOW;
  } else if (xc1 == "DARK_BLUE") {
    c1 = DARK_BLUE;
  } else if (xc1 == "DARK_RED") {
    c1 = DARK_RED;
  } else if (xc1 == "DARK_CYAN") {
    c1 = DARK_CYAN;
  } else if (xc1 == "DARK_MAGENTA") {
    c1 = DARK_MAGENTA;
  } else if (xc1 == "DARK_GREEN") {
    c1 = DARK_GREEN;
  } else if (xc1 == "DARK_WHITE") {
    c1 = DARK_WHITE;
  } else if (xc1 == "BLACK") {
    c1 = BLACK;
  } else {
    std::cout << "Utils.cpp: _DrawComponent color transfer error!";
  }

  if (xc2 == "GREEN") {
    c2 = GREEN;
  } else if (xc2 == "YELLOW") {
    c2 = YELLOW;
  } else if (xc2 == "BLUE") {
    c2 = BLUE;
  } else if (xc2 == "RED") {
    c2 = RED;
  } else if (xc2 == "CYAN") {
    c2 = CYAN;
  } else if (xc2 == "MAGENTA") {
    c2 = MAGENTA;
  } else if (xc2 == "WHITE") {
    c2 = WHITE;
  } else if (xc2 == "GRAY") {
    c2 = GRAY;
  } else if (xc2 == "DARK_YELLOW") {
    c2 = DARK_YELLOW;
  } else if (xc2 == "DARK_BLUE") {
    c2 = DARK_BLUE;
  } else if (xc2 == "DARK_RED") {
    c2 = DARK_RED;
  } else if (xc2 == "DARK_CYAN") {
    c2 = DARK_CYAN;
  } else if (xc2 == "DARK_MAGENTA") {
    c2 = DARK_MAGENTA;
  } else if (xc2 == "DARK_GREEN") {
    c2 = DARK_GREEN;
  } else if (xc2 == "DARK_WHITE") {
    c2 = DARK_WHITE;
  } else if (xc2 == "BLACK") {
    c2 = BLACK;
  } else {
    std::cout << "Utils.cpp: _DrawComponent color transfer error!";
  }

  // Initialize the display name
  if (xn == "#") {
    n = "";
  } else {
    n = xn;
  }

  // Initialize the display value
  if (xv == "#") {
    v = 0;
  } else if (xv == "in_file_array") {
    v = 0;
  } else {
    v = atof(_string_to_double);
  }

  // Initialize the parameters
  for (int i = 0; i < 10; i++) {
    this->port[i] = 0;
  }
  this->component = cp;
  this->color1 = c1;
  this->color2 = c2;
  this->direction = d;
  this->size = s;
  this->name = n;
  this->value = v;
}
//***************** Keyi Zhou *****************

//***************** Yadong Hu and Keyi Zhou *****************
// Draw each component according to the properties
void _DrawComponent::draw() {
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  // The following codes used:
  // _Helper::convertToUnitValue(getValue()):
  //											to display the value in correct
  //unit
  // SetConsoleTextAttribute(consolehwnd,
  // _Helper::convertColorNameToHex(getColor1(), 0)):
  //											to set the background or
  //foreground colour
  // Helper::locateCursorAt(getPositionX(), getPositionY() + 1):
  //											to set the cursor at correct
  //position

  switch (this->component) {
    case RESISTOR:
      if (this->size == BIG) {
        std::cout << " " << getName() << "="
                  << _Helper::convertToUnitValue(getValue()) << "Ω\n";
        std::cout << "┏━━━━━━━━┓ "
                  << "\n"
                  << "┫        ┣ \n"
                  << "┗━━━━━━━━┛ "
                  << "\n";
      } else {
        if (this->direction == HORIZONTAL) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << getName() << "="
                    << _Helper::convertToUnitValue(getValue()) << "Ω";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << "━━";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 1));
          std::cout << "   ";
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << "━━";
        } else if (this->direction == VERTICAL) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          _Helper::locateCursorAt(getPositionX() + 3, getPositionY() + 3);
          std::cout << getName() << "="
                    << _Helper::convertToUnitValue(getValue()) << "Ω";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 2);
          std::cout << "┃ ";
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 4);
          std::cout << "┃ ";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 1));
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 3);
          std::cout << "  ";
          SetConsoleTextAttribute(consolehwnd, 0x00);
        }
      }
      break;
    case CAPACITOR:
      if (this->size == BIG) {
        std::cout << "" << getName() << "="
                  << _Helper::convertToUnitValue(getValue()) << "F\n";
        std::cout << "┃  ┃ "
                  << "\n"
                  << "┫  ┣"
                  << "\n"
                  << "┃  ┃ "
                  << "\n";
      } else {
        if (this->direction == HORIZONTAL) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << getName() << "="
                    << _Helper::convertToUnitValue(getValue()) << "F";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << "━━";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 1));
          std::cout << " ";
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << " ";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 1));
          std::cout << " ";
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << "━━";
        }
      }
      break;
    case INDUCTOR:
      if (this->size == BIG) {
        std::cout << "" << getName() << "="
                  << _Helper::convertToUnitValue(getValue()) << "F\n";
        std::cout << "  /\\    /\\"
                  << "\n"
                  << "━   \\  /  \\  ━"
                  << "\n"
                  << "     \\/    \\/"
                  << "\n";
      } else {
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor1(), 0));
        std::cout << "" << getName() << "="
                  << _Helper::convertToUnitValue(getValue()) << "H";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "━ ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "⌒⌒⌒";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "━";
      }
      break;
    case OP_AMP:
      if (this->size == NORMAL) {
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
        std::cout << "+◣┃  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor1(), 0));
        std::cout << getName();
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 2);
        std::cout << "━";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "◣ ";
        _Helper::locateCursorAt(getPositionX() + 1, getPositionY() + 3);
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "    ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << ">━ ";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 4);
        std::cout << "━";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "◤";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 5);
        std::cout << "-◤┃ ";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
      } else {
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
        std::cout << "-◣┃  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor1(), 0));
        std::cout << getName();
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 2);
        std::cout << "━";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "◣ ";
        _Helper::locateCursorAt(getPositionX() + 1, getPositionY() + 3);
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "    ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << ">━ ";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 4);
        std::cout << "━";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 1));
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "◤";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 5);
        std::cout << "+◤┃ ";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
      }
      break;
    case CURRENT_SOURCE:
      if (this->size == BIG) {
        std::cout << " " << getName() << "="
                  << "_in_file_array"
                  << "A\n";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◢";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◣ \n";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << "  ↑  \n";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◥";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << "  ";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◤ \n";
      } else {
        if (this->direction == VERTICAL) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 2));
          std::cout << "↑";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << " " << getName() << ":"
                    << "in_file_array"
                    << "";
        }
      }
      break;
    case VOLTAGE_SOURCE:
      if (this->size == BIG) {
        std::cout << " " << getName() << "="
                  << _Helper::convertToUnitValue(getValue()) << "V\n";
        std::cout << "    ┃\n"
                  << "  ┃ ┃\n"
                  << "￣┃ ┃￣\n"
                  << "    ┃\n";
      } else {
        if (this->direction == H_NEGATIVE) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << getName() << "="
                    << _Helper::convertToUnitValue(getValue()) << "V\n";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 0));
          std::cout << "┛┣ ";
        } else if (this->direction == H_POSITIVE) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << getName() << "="
                    << _Helper::convertToUnitValue(getValue()) << "V\n";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 0));
          std::cout << "┫┗ ";
        }
        SetConsoleTextAttribute(consolehwnd, 0x0F);
      }
      break;
    case NOISE_SOURCE:
      if (this->size == BIG) {
        std::cout << "Noise"
                  << "\n";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◢";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << " + ";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◣ \n";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << "       \n";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◥";
        SetConsoleTextAttribute(consolehwnd, 0xF0);
        std::cout << "www";
        SetConsoleTextAttribute(consolehwnd, 0x0F);
        std::cout << "◤ \n";
      } else {
        if (this->direction == VERTICAL) {
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor2(), 2));
          std::cout << "ww";
          SetConsoleTextAttribute(
              consolehwnd, _Helper::convertColorNameToHex(getColor1(), 0));
          std::cout << " Noise";
          _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
          SetConsoleTextAttribute(consolehwnd, 0x0F);
          std::cout << "┃ ";
        }
      }
      break;
    case AC_SOURCE:
      std::cout << "AC:" << getName() << "="
                << _Helper::convertToUnitValue(getValue()) << "V\n";
      SetConsoleTextAttribute(consolehwnd, 0xF0);
      std::cout << "∽";
      SetConsoleTextAttribute(consolehwnd, 0x0F);
      break;
    case SWITCH:
      if (this->size == BIG || 1) {
        std::cout << " " << getName() << "\n";
        std::cout << "   /  \n";
        std::cout << "━ /   ━ \n";
      }
      break;
    case GROUND:
      if (this->size == BIG) {
        std::cout << " ┃\n";
        std::cout << "====\n";
        std::cout << " ￣\n";
        std::cout << getName() << "\n";
      } else {
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "┃";
        _Helper::locateCursorAt(getPositionX(), getPositionY() + 1);
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor2(), 0));
        std::cout << "▽";
        SetConsoleTextAttribute(consolehwnd,
                                _Helper::convertColorNameToHex(getColor1(), 0));
        std::cout << " " + getName();
        SetConsoleTextAttribute(consolehwnd, 0x0F);
      }
      break;
    default:
      std::cout << "ERROR";
      break;
  }
}
//***************** Yadong Hu and Keyi Zhou *****************

//***************** Yadong Hu *****************
// Set properties
void _DrawComponent::setThermalNoise(double noise_ratio, double resistance,
                                     double temperature, double bandwidth) {
  this->noise_ratio = noise_ratio;
  this->resistance = resistance;
  this->temperature = temperature;
  this->bandwidth = bandwidth;
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Set properties
void _DrawComponent::setPort(int _port[]) {
  for (int i = 0; i < 10; i++) {
    this->port[i] = _port[i];
  }
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Set properties
void _DrawComponent::setPosition(int x, int y) {
  // Specify the ports according to component type
  this->position_x = x;
  this->position_y = y;
  _Helper::locateCursorAt(x, y);
  switch (this->component) {
    case RESISTOR:
      // Resistor behaves exactly the same as capacitor
    case CAPACITOR:
      if (this->direction == VERTICAL) {
        port[0] = x;
        port[1] = y + 1;
        port[2] = x;
        port[3] = y + 6;
      } else {
        port[0] = x - 2;
        port[1] = y + 1;
        port[2] = x + 6;
        port[3] = y + 1;
      }
      break;
    case INDUCTOR:
      break;
    case OP_AMP:
      port[0] = x - 2;
      port[1] = y + 2;
      port[2] = x - 1;
      port[3] = y + 4;
      port[4] = x + 7;
      port[5] = y + 3;
      port[6] = x + 3;
      port[7] = y;
      port[8] = x + 3;
      port[9] = y + 6;
      break;
    case CURRENT_SOURCE:
      if (this->direction == VERTICAL) {
        port[0] = x;
        port[1] = y - 1;
        port[2] = x;
        port[3] = y + 1;
      } else {
      }
      break;
    case VOLTAGE_SOURCE:
      if (this->direction == VERTICAL) {
      } else {
        port[0] = x - 2;
        port[1] = y + 1;
        port[2] = x + 3;
        port[3] = y + 1;
      }
      break;
    case NOISE_SOURCE:
      if (this->direction == VERTICAL) {
        port[0] = x;
        port[1] = y - 1;
        port[2] = x;
        port[3] = y + 1;
      } else {
      }
      break;
    case AC_SOURCE:
      break;
    case SWITCH:
      break;
    case GROUND:
      if (this->direction == VERTICAL) {
        port[0] = x;
        port[1] = y;
      } else {
      }
      break;
  }
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// No use now
int _DrawComponent::getSpaceNum() { return this->position_x; }
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Return the component port
int _DrawComponent::getPort(int num) { return this->port[num]; }
//***************** Yadong Hu *****************

//***************** Keyi Zhou *****************
// Calculate values at each analyse point
void _Analyse::calculateValues(_circuit_ _c) {
  switch (_c) {
    case IVConverter: {
      return;
    }
  }
}
//***************** Keyi Zhou *****************

//***************** Yadong Hu *****************
// Plot square graph
void _Analyse::outputSquareGraph(code_t_i t, int position_x, int position_y,
                                 _mode_ m) {
  // Two modes: STRICT_MODE: 5 levels between 0-1
  //			  NORMAL_MODE: 2 levels between 0-1

  // Store the last displayed value for showing the connectors
  double last = 0;
  for (int i = 0; i < t.size() && i < 16; i++) {
    // STRICT_MODE
    if (m == STRICT_MODE) {
      if (t[i] >= 0.875) {
        // Showing the connectors
        if (last == 0) {
          for (int j = 0; j < 4; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 0.25) {
          for (int j = 0; j < 3; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 0.5) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 0.75) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 1) {
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y);
        std::cout << "++++";
        last = 1;
      } else if (t[i] >= 0.625) {
        // Showing the connectors
        if (last == 0) {
          for (int j = 0; j < 3; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 2 + j);
            std::cout << "+";
          }
        } else if (last == 0.25) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 2 + j);
            std::cout << "+";
          }
        } else if (last == 0.5) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 2 + j);
            std::cout << "+";
          }
        } else if (last == 0.75) {
        } else if (last == 1) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y - j);
            std::cout << "+";
          }
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y + 1);
        std::cout << "++++";
        last = 0.75;
      } else if (t[i] >= 0.375) {
        // Showing the connectors
        if (last == 0) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 3 + j);
            std::cout << "+";
          }
        } else if (last == 0.25) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 3 + j);
            std::cout << "+";
          }
        } else if (last == 0.5) {
        } else if (last == 0.75) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 1) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 - j);
            std::cout << "+";
          }
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y + 2);
        std::cout << "++++";
        last = 0.5;
      } else if (t[i] >= 0.125) {
        // Showing the connectors
        if (last == 0) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 4 + j);
            std::cout << "+";
          }
        } else if (last == 0.25) {
        } else if (last == 0.5) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 2 + j);
            std::cout << "+";
          }
        } else if (last == 0.75) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 1) {
          for (int j = 0; j < 3; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + j);
            std::cout << "+";
          }
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y + 3);
        std::cout << "++++";
        last = 0.25;
      } else {
        // Showing the connectors
        if (last == 0) {
        } else if (last == 0.25) {
          for (int j = 0; j < 1; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 3 + j);
            std::cout << "+";
          }
        } else if (last == 0.5) {
          for (int j = 0; j < 2; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 2 + j);
            std::cout << "+";
          }
        } else if (last == 0.75) {
          for (int j = 0; j < 3; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 1) {
          for (int j = 0; j < 4; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 0 + j);
            std::cout << "+";
          }
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y + 4);
        std::cout << "++++";
        last = 0;
      }
      _Helper::locateCursorAt(position_x + 4 * i, position_y + 5);
      std::cout << "--------";
    }
    // NORMAL_MODE
    else {
      if (t[i] >= 0.5) {
        if (last == 0) {
          for (int j = 0; j < 4; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + 1 + j);
            std::cout << "+";
          }
        } else if (last == 1) {
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y);
        std::cout << "++++";
        last = 1;
      } else {
        if (last == 0) {
        } else if (last == 1) {
          for (int j = 0; j < 4; j++) {
            _Helper::locateCursorAt(position_x + 4 * i, position_y + j);
            std::cout << "+";
          }
        }
        _Helper::locateCursorAt(position_x + 4 * i, position_y + 4);
        std::cout << "++++";
        last = 0;
      }
      _Helper::locateCursorAt(position_x + 4 * i, position_y + 5);
      std::cout << "--------";
    }
  }
  _Helper::locateCursorAt(position_x, position_y + 6);
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Plot sin graph
void _Analyse::outputSinGraph(code_t_i t, int position_x, int position_y) {
  // Draw the sin wave according to the bit value
  for (int i = 0; i < t.size() && i < 16; i++) {
    _Helper::locateCursorAt(position_x + 4 * i, position_y + 3);
    std::cout << "+";
    if (t[i] >= 0.5) {
      _Helper::locateCursorAt(position_x + 4 * i + 1, position_y + 1);
      std::cout << "/";
      _Helper::locateCursorAt(position_x + 4 * i + 2, position_y + 0);
      std::cout << "+";
      _Helper::locateCursorAt(position_x + 4 * i + 3, position_y + 1);
      std::cout << "\\";
    } else {
      _Helper::locateCursorAt(position_x + 4 * i + 1, position_y + 5);
      std::cout << "\\";
      _Helper::locateCursorAt(position_x + 4 * i + 2, position_y + 6);
      std::cout << "+";
      _Helper::locateCursorAt(position_x + 4 * i + 3, position_y + 5);
      std::cout << "/";
    }
    _Helper::locateCursorAt(position_x + 4 * i, position_y + 7);
    std::cout << "--------";
  }
}
//***************** Yadong Hu *****************

//***************** Yusen Liu *****************
// Convert enum type colour name to WORD type hex values
WORD _Helper::convertColorNameToHex(_color_ _c, int _num) {
  // the _num 0 means: use the _c colour to change the background colour
  //			1 means: use the _c colour to change the foreground
  //colour 			2 means: use the _c colour to change the background colour while
  //maintaing the foreground as white

  if (_num == 0) {
    switch (_c) {
      case GREEN:
        return 0x0a;
      case YELLOW:
        return 0x0e;
      case BLUE:
        return 0x09;
      case RED:
        return 0x0c;
      case CYAN:
        return 0x0b;
      case MAGENTA:
        return 0x0d;
      case WHITE:
        return 0x0f;
      case GRAY:
        return 0x08;
      case DARK_GREEN:
        return 0x02;
      case DARK_YELLOW:
        return 0x06;
      case DARK_BLUE:
        return 0x01;
      case DARK_RED:
        return 0x04;
      case DARK_CYAN:
        return 0x03;
      case DARK_MAGENTA:
        return 0x05;
      case DARK_WHITE:
        return 0x07;
      case BLACK:
        return 0x00;
      default:
        return 0x00;
    }
  } else if (_num == 1) {
    switch (_c) {
      case GREEN:
        return 0xa0;
      case YELLOW:
        return 0xe0;
      case BLUE:
        return 0x90;
      case RED:
        return 0xc0;
      case CYAN:
        return 0xb0;
      case MAGENTA:
        return 0xd0;
      case WHITE:
        return 0xf0;
      case GRAY:
        return 0x80;
      case DARK_GREEN:
        return 0x20;
      case DARK_YELLOW:
        return 0x60;
      case DARK_BLUE:
        return 0x10;
      case DARK_RED:
        return 0x40;
      case DARK_CYAN:
        return 0x30;
      case DARK_MAGENTA:
        return 0x50;
      case DARK_WHITE:
        return 0x70;
      case BLACK:
        return 0x00;
      default:
        return 0x00;
    }
  } else if (_num == 2) {
    switch (_c) {
      case GREEN:
        return 0xaf;
      case YELLOW:
        return 0xef;
      case BLUE:
        return 0x9f;
      case RED:
        return 0xcf;
      case CYAN:
        return 0xb1;
      case MAGENTA:
        return 0xd1;
      case WHITE:
        return 0xff;
      case GRAY:
        return 0x8f;
      case DARK_GREEN:
        return 0x2f;
      case DARK_YELLOW:
        return 0x6f;
      case DARK_BLUE:
        return 0x1f;
      case DARK_RED:
        return 0x4f;
      case DARK_CYAN:
        return 0x3f;
      case DARK_MAGENTA:
        return 0x5b;
      case DARK_WHITE:
        return 0x7f;
      case BLACK:
        return 0x0f;
      default:
        return 0x0f;
    }
  }
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Convert unit
std::string _Helper::convertToUnitValue(double value) {
  // Convert the large or small value into unit value
  if (value >= 1000000000)
    return cutTailingZeros(value / 1000000000) + "G";
  else if (value >= 1000000)
    return cutTailingZeros(value / 1000000) + "M";
  else if (value >= 1000)
    return cutTailingZeros(value / 1000) + "k";
  else if (value < 0.000000001)
    return cutTailingZeros(value * 1000000000000) + "p";
  else if (value < 0.000001)
    return cutTailingZeros(value * 1000000000) + "n";
  else if (value < 0.001)
    return cutTailingZeros(value * 1000000) + "μ";
  else if (value < 1)
    return cutTailingZeros(value * 1000) + "m";
  else
    return cutTailingZeros(value);
}
//***************** Yusen Liu *****************

//***************** Yusen Liu *****************
// Cut the tailing zeros while using to_string() function
std::string _Helper::cutTailingZeros(double temp) {
  // See my individual diary for this part
  auto res = std::to_string(temp);
  const std::string format("$1");
  try {
    std::regex r("(\\d*)\\.0{6}|");
    std::regex r2("(\\d*\\.{1}0*[^0]+)0*");
    res = std::regex_replace(res, r2, format);
    res = std::regex_replace(res, r, format);
  } catch (const std::exception& e) {
    return res;
  }
  return res;
}
//***************** Yusen Liu *****************

//***************** Keyi Zhou *****************
// Set the cursor at a point
void _Helper::locateCursorAt(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
// Set the cursor at a pre-determined point 1
void _Helper::setCursorToBase1(std::string text) {
  COORD coord;
  coord.X = 4;
  coord.Y = 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  std::cout << text << std::endl;
  std::cout << "\n\n";
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
// Set the cursor at a pre-determined point 2
void _Helper::setCursorToBase2(std::string text) {
  COORD coord;
  coord.X = 4;
  coord.Y = 22;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
  std::cout << text << std::endl;
  std::cout << "\n\n";
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
// No use now
void _Helper::displaySpaces(int _num) {
  for (int i = 0; i < _num; i++) {
    std::cout << " ";
  }
}
//***************** Keyi Zhou *****************

//***************** Yadong Hu *****************
// Automatically connect components
void _Helper::connectComponent(int _p1, int _p1p, int _p2, int _p2p,
                               _connect_ init, _connect_ end) {
  // 0:right to left, 1:left to right, -1:default
  int _hori_direction = -1;
  // 0:bottom to top, 1:top to bottom, -1:default
  int _vert_direction = -1;
  // From port
  int from[2] = {_p1, _p1p};
  // To port
  int to[2] = {_p2, _p2p};
  int offset[2] = {to[0] - from[0], to[1] - from[1]};
  _Helper::locateCursorAt(from[0], from[1]);
  int offset_s[2] = {offset[0], offset[1]};
  _Helper::locateCursorAt(from[0], from[1]);
  // Display the initial corner
  switch (init) {
    case UP_RIGHT:
      std::cout << "┗";
      break;
    case UP_LEFT:
      std::cout << "┛ ";
      break;
    case DOWN_RIGHT:
      std::cout << "┏";
      break;
    case DOWN_LEFT:
      std::cout << "┓ ";
      break;
    case HORI:
      std::cout << "━━";
      break;
    case VERT:
      std::cout << "┃ ";
      break;
    default:
      break;
  }
  // if connect from left to right, then output "-"
  if (offset[0] > 0) {
    while (offset[0] > 0) {
      std::cout << "━";
      offset[0]--;
    }
    _hori_direction = 1;
  }
  // if connect from right to left, then output "-" and reset the cursor
  else if (offset[0] < 0) {
    for (int i = 0; offset[0] < 0; i = i++) {
      _Helper::locateCursorAt(from[0] - i, from[1]);
      std::cout << "━";
      offset[0]++;
    }
    _hori_direction = 0;
  }
  // if then connect from top to bottom, then output "|"
  if (offset[1] > 0) {
    _Helper::locateCursorAt(from[0] + offset_s[0], from[1]);
    if (_hori_direction == 0) {
      std::cout << "┏";
    } else if (_hori_direction == 1) {
      std::cout << "┓ ";
    }
    for (int i = 1; offset[1] > 0; i++) {
      _Helper::locateCursorAt(from[0] + offset_s[0], from[1] + i);
      std::cout << "┃ ";
      offset[1]--;
    }
    _vert_direction = 1;
  }
  // if then connect from bottom to top, then output "|" and reset the cursor
  else if (offset[1] < 0) {
    _Helper::locateCursorAt(from[0] + offset_s[0], from[1]);
    if (_hori_direction == 0) {
      std::cout << "┗";
    } else if (_hori_direction == 1) {
      std::cout << "┛ ";
    }
    for (int i = 1; offset[1] < 0; i++) {
      _Helper::locateCursorAt(from[0] + offset_s[0], from[1] - i);
      std::cout << "┃ ";
      offset[1]++;
    }
    _vert_direction = 0;
  }
  _Helper::locateCursorAt(from[0] + offset_s[0], from[1] + offset_s[1]);
  // Display the end corner
  switch (end) {
    case UP_RIGHT:
      std::cout << "┗";
      break;
    case UP_LEFT:
      std::cout << "┛ ";
      break;
    case DOWN_RIGHT:
      std::cout << "┏";
      break;
    case DOWN_LEFT:
      std::cout << "┓ ";
      break;
    case HORI:
      std::cout << "━";
      break;
    case VERT:
      std::cout << "┃ ";
      break;
    default:
      break;
  }
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Display error messages
void _Helper::errorMessage(int _position, std::string _text) {
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  // Locate the cursor at given position
  locateCursorAt(7, _position);
  SetConsoleTextAttribute(consolehwnd, _Helper::convertColorNameToHex(RED, 0));
  // Display red text
  std::cout << _text;
  // Display for 2 seconds
  Sleep(2000);
  locateCursorAt(7, _position);
  // Clear the input content
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  for (int i = 0; i < 110; i++) {
    std::cout << " ";
  }
  // Relocate the cursor
  locateCursorAt(7, _position);
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Display success messages
void _Helper::successMessage(int _position, std::string _text,
                             std::string _text2) {
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  // Locate the cursor at given position
  locateCursorAt(7, _position);
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(GREEN, 0));
  // Display green text
  std::cout << _text;
  locateCursorAt(7, _position + 1);
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_CYAN, 0));
  // Display the cyan count down text
  std::cout << _text2 + " " << 3 << " seconds...";
  int _length = _text2.length();
  // For each 1 second, change the text
  for (int i = 0; i < 3; i++) {
    locateCursorAt(7, _position + 2);
    Sleep(1000);
    locateCursorAt(7 + _length + 1, _position + 1);
    std::cout << 2 - i;
  }
  // Clear the input text
  locateCursorAt(7, _position);
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  for (int i = 0; i < 110; i++) {
    std::cout << " ";
  }
  // Relocate the cursor
  locateCursorAt(7, _position);
}
//***************** Yadong Hu *****************

//***************** Yusen Liu *****************
// Clear screen
void _Helper::clearScreen(int _position, int _lines) {
  // Clear the part of screen by std::cout spaces
  _Helper::locateCursorAt(0, _position);
  for (int j = 0; j < _lines; j++) {
    for (int i = 0; i < 120; i++) {
      std::cout << " ";
    }
  }
}
//***************** Yusen Liu *****************

//***************** Yadong Hu and Keyi Zhou *****************
// Read TXT files
_status_ _Helper::readTXT(std::string _file, std::string _component,
                          int _position, std::string _changedValue, int _flag) {
  // Input file
  std::string _filename = _file + ".txt";
  // Temp file
  std::string _filename_temp = "temp.txt";
  std::ifstream infile(_filename, std::ios::in);
  if (!infile) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  std::ofstream outfile(_filename_temp, std::ios::out);
  if (!outfile) {
    std::cout << "open eror!" << std::endl;
    exit(1);
  }
  // _line: store the each line text
  std::string _line, _tmp;
  // _target: the target line
  int _target = -999;
  // _v: the full content read from input file
  std::vector<std::string> _v;

  // read all content by line
  while (getline(infile, _line, '\r')) {
    _v.push_back(_line);
  }
  infile.close();
  const char* _p_o = _filename.data();
  // delete the original file
  ::remove(_p_o);
  for (auto _line : _v) {
    // if found the component name at this line
    if (_line.find(_component) != std::string::npos) {
      // mark _target as 0
      _target = 0;
    }
    // if _traget equals the given position
    if (_target == _flag) {
      // reset _target
      _target = -999;
      std::vector<std::string> _data;
      std::stringstream _input(_line);
      // split the line by comma
      while (std::getline(_input, _tmp, ',')) _data.push_back(_tmp);
      _data.at(_position) = _changedValue;
      for (int i = 0; i < _data.size(); i++) {
        int _length = _data.at(i).length();
        const char* _temp = _data.at(i).data();
        for (int j = 0; j < _length; j++) {
          // output the changed data
          outfile.put(_temp[j]);
        }
        if (i != _data.size() - 1)
          // if a word is finished, output comma
          outfile.put(',');
      }
      outfile.put('\r');
    }
    // if not this line, output the same contents as read from input
    else {
      for (int i = 0; i < _line.length(); i++) {
        outfile.put(_line[i]);
      }
      outfile.put('\r');
    }
    _target++;
  }
  outfile.close();
  const char* _p_n = _filename_temp.data();
  // rename the temp file to original name
  ::rename(_p_n, _p_o);
  return SUCCESS;
}
//***************** Yadong Hu and Keyi Zhou *****************

//***************** Keyi Zhou *****************
// Return a word from characters
std::vector<std::string> _Helper::getWord(std::vector<std::string> _v, int _p) {
  std::string _line;
  std::vector<std::string> _w;
  std::stringstream _ss(_v.at(_p));
  // Use the comma as a seperator to read by word
  while (getline(_ss, _line, ',')) {
    _w.push_back(_line);
  }
  return _w;
}
//***************** Keyi Zhou *****************
