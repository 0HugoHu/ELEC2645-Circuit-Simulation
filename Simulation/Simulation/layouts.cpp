// Implementation of the build-in templates

#include "layouts.h"

#include "huffman.h"

// Not finished yet
int _SetLayout::RLC() { return 0; }
int _SetLayout::Diodes() { return 0; }

//***************** Yadong Hu *****************
int _SetLayout::IVConverter() {
  // Load data from IVConverter.txt
  std::string _filename = "IVConverter.txt";
  std::ifstream infile(_filename, std::ios::in);
  if (!infile) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  std::string _line;
  // the std::vector _v stored all read-in data (per line)
  // while _w stored all the splited data from _v (per word)
  std::vector<std::string> _v, _w;
  while (getline(infile, _line, '\r')) {
    _v.push_back(_line);
  }
  infile.close();

  // Set-up layout
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_CYAN, 0));
  _Helper::setCursorToBase1("★");
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  _Helper::locateCursorAt(6, 1);
  std::cout << " Huffman Encode & Decode Examination Diagram: ";
  int port[10] = {0};

  // Noise Source
  _w = _Helper::getWord(_v, 1);
  _DrawComponent noiseSource(NOISE_SOURCE, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                             _w.at(2), _w.at(3));
  noiseSource.setPosition(4, 13);
  noiseSource.setThermalNoise(1.0, 10000, 27, 1000000);
  noiseSource.draw();

  // Current Souce
  _w = _Helper::getWord(_v, 5);
  _DrawComponent currentSource(CURRENT_SOURCE, _w.at(0), _w.at(1), VERTICAL,
                               NORMAL, _w.at(2), _w.at(3));
  currentSource.setPosition(18, 13);
  currentSource.draw();

  // Capacitor
  _w = _Helper::getWord(_v, 8);
  _DrawComponent capacitor(CAPACITOR, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                           _w.at(2), _w.at(3));
  capacitor.setPosition(9, 9);
  capacitor.draw();

  // Ground
  _DrawComponent ground(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "Ground", 0);
  ground.setPosition(18, 16);
  ground.draw();

  // Amplifier
  _w = _Helper::getWord(_v, 11);
  _DrawComponent op_amp(OP_AMP, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                        _w.at(2), _w.at(3));
  op_amp.setPosition(40, 6);
  op_amp.draw();

  // Resistor-feedback
  _w = _Helper::getWord(_v, 14);
  _DrawComponent resistor_f(RESISTOR, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                            _w.at(2), _w.at(3));
  resistor_f.setPosition(60, 13);
  resistor_f.draw();

  // Capacitor-feedback
  _w = _Helper::getWord(_v, 17);
  _DrawComponent capacitor_f(CAPACITOR, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                             _w.at(2), _w.at(3));
  capacitor_f.setPosition(60, 16);
  capacitor_f.draw();

  // Ground
  _DrawComponent ground2(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  ground2.setPosition(38, 8);
  ground2.draw();

  // Voltage
  _w = _Helper::getWord(_v, 20);
  _DrawComponent voltage_plus(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_POSITIVE,
                              NORMAL, _w.at(2), _w.at(3));
  voltage_plus.setPosition(48, 4);
  voltage_plus.draw();

  _w = _Helper::getWord(_v, 23);
  _DrawComponent voltage_minus(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_NEGATIVE,
                               NORMAL, _w.at(2), _w.at(3));
  voltage_minus.setPosition(48, 11);
  voltage_minus.draw();

  // Ground
  _DrawComponent ground3(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  ground3.setPosition(55, 5);
  ground3.draw();

  // Ground
  _DrawComponent ground4(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  ground4.setPosition(55, 12);
  ground4.draw();

  // Connectors (to draw the lines between each component)
  _Helper::connectComponent(noiseSource.getPort(2), noiseSource.getPort(3) + 1,
                            currentSource.getPort(2), currentSource.getPort(3),
                            UP_RIGHT, UP_LEFT);
  _Helper::connectComponent(capacitor.getPort(0), capacitor.getPort(1),
                            noiseSource.getPort(0), noiseSource.getPort(1),
                            HORI, VERT);
  _Helper::connectComponent(capacitor.getPort(2), capacitor.getPort(3),
                            currentSource.getPort(0), currentSource.getPort(1),
                            HORI, VERT);
  _Helper::connectComponent(ground.getPort(0), ground.getPort(1),
                            currentSource.getPort(2), currentSource.getPort(3),
                            VERT, VERT);
  _Helper::connectComponent(capacitor.getPort(2) + 4, capacitor.getPort(3),
                            op_amp.getPort(2) - 2, op_amp.getPort(3), HORI,
                            HORI);
  _Helper::connectComponent(resistor_f.getPort(0) - 2, resistor_f.getPort(1),
                            op_amp.getPort(2) - 1, op_amp.getPort(3), HORI,
                            DOWN_RIGHT);
  _Helper::connectComponent(resistor_f.getPort(2), resistor_f.getPort(3),
                            capacitor_f.getPort(2), capacitor_f.getPort(3),
                            DOWN_LEFT, UP_LEFT);
  _Helper::connectComponent(resistor_f.getPort(0) + 1, resistor_f.getPort(1),
                            capacitor_f.getPort(0), capacitor_f.getPort(1),
                            DOWN_RIGHT, UP_RIGHT);
  _Helper::connectComponent(op_amp.getPort(0), op_amp.getPort(1),
                            ground2.getPort(0), ground2.getPort(1), HORI,
                            DOWN_RIGHT);
  _Helper::connectComponent(op_amp.getPort(4), op_amp.getPort(5),
                            op_amp.getPort(4) + 32, op_amp.getPort(5), HORI,
                            HORI);
  _Helper::connectComponent(resistor_f.getPort(2) + 1, resistor_f.getPort(3),
                            op_amp.getPort(4) + 28, op_amp.getPort(5), HORI,
                            DOWN_RIGHT);
  _Helper::connectComponent(voltage_plus.getPort(0), voltage_plus.getPort(1),
                            op_amp.getPort(6), op_amp.getPort(7), HORI, VERT);
  _Helper::connectComponent(voltage_minus.getPort(0), voltage_minus.getPort(1),
                            op_amp.getPort(8), op_amp.getPort(9), HORI,
                            UP_RIGHT);
  _Helper::connectComponent(voltage_plus.getPort(2), voltage_plus.getPort(3),
                            ground3.getPort(0), ground3.getPort(1), HORI,
                            DOWN_LEFT);
  _Helper::connectComponent(voltage_minus.getPort(2), voltage_minus.getPort(3),
                            ground4.getPort(0), ground4.getPort(1), HORI,
                            DOWN_LEFT);

  _Helper::locateCursorAt(op_amp.getPort(4) + 25, op_amp.getPort(5) - 1);
  std::cout << "IVC Out";
  _Helper::locateCursorAt(5, op_amp.getPort(5) - 2);
  std::cout << "Circuit Begins:";
  // return the end line position
  return 0;
}
//***************** Yadong Hu *****************

//***************** Yusen Liu *****************
int _SetLayout::Comparator() {
  // The comparator diagram
  // Load data from IVConverter.txt
  std::string _filename = "Comparator.txt";
  std::ifstream infile(_filename, std::ios::in);
  if (!infile) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  std::string _line;
  // the std::vector _v stored all read-in data (per line)
  // while _w stored all the splited data from _v (per word)
  std::vector<std::string> _v, _w;
  while (getline(infile, _line, '\n')) {
    _v.push_back(_line);
  }
  infile.close();

  // Curve smoothing capacitor
  _w = _Helper::getWord(_v, 1);
  _DrawComponent capacitor_c(CAPACITOR, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                             _w.at(2), _w.at(3));
  capacitor_c.setPosition(87, 8);
  capacitor_c.draw();

  // Pull-up resistors at the positive input
  _w = _Helper::getWord(_v, 10);
  _DrawComponent resistor_c3(RESISTOR, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                             _w.at(2), _w.at(3));
  resistor_c3.setPosition(97, 4);
  resistor_c3.draw();
  _w = _Helper::getWord(_v, 13);
  _DrawComponent resistor_c4(RESISTOR, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                             _w.at(2), _w.at(3));
  resistor_c4.setPosition(97, 8);
  resistor_c4.draw();

  // Ground for r2
  _DrawComponent groundc1(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc1.setPosition(97, 25);
  groundc1.draw();

  // The op-amp
  _w = _Helper::getWord(_v, 37);
  _DrawComponent op_amp_c(OP_AMP, _w.at(0), _w.at(1), HORIZONTAL, BIG, _w.at(2),
                          _w.at(3));
  op_amp_c.setPosition(121, 7);
  op_amp_c.draw();

  // Pull-up resistor at the negative input
  _w = _Helper::getWord(_v, 4);
  _DrawComponent resistor_c1(RESISTOR, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                             _w.at(2), _w.at(3));
  resistor_c1.setPosition(97, 16);
  resistor_c1.draw();
  _w = _Helper::getWord(_v, 7);
  _DrawComponent resistor_c2(RESISTOR, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                             _w.at(2), _w.at(3));
  resistor_c2.setPosition(97, 20);
  resistor_c2.draw();

  // Ground for r4
  _DrawComponent groundc2(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc2.setPosition(97, 13);
  groundc2.draw();

  // The feedback resistor
  _w = _Helper::getWord(_v, 16);
  _DrawComponent resistor_cf(RESISTOR, _w.at(0), _w.at(1), HORIZONTAL, NORMAL,
                             _w.at(2), _w.at(3));
  resistor_cf.setPosition(126, 20);
  resistor_cf.draw();

  // Push-up resistor at the output
  _w = _Helper::getWord(_v, 19);
  _DrawComponent resistor_cpush(RESISTOR, _w.at(0), _w.at(1), VERTICAL, NORMAL,
                                _w.at(2), _w.at(3));
  resistor_cpush.setPosition(81, 19);
  resistor_cpush.draw();

  // Supply rail 1
  _w = _Helper::getWord(_v, 22);
  _DrawComponent voltage_plus_c1(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_POSITIVE,
                                 NORMAL, _w.at(2), _w.at(3));
  voltage_plus_c1.setPosition(106, 15);
  voltage_plus_c1.draw();

  // Ground for supply rail 1
  _DrawComponent groundc3(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc3.setPosition(111, 17);
  groundc3.draw();

  // Supply rail 2
  _w = _Helper::getWord(_v, 25);
  _DrawComponent voltage_plus_c2(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_POSITIVE,
                                 NORMAL, _w.at(2), _w.at(3));
  voltage_plus_c2.setPosition(106, 4);
  voltage_plus_c2.draw();

  // Ground for supply rail 2
  _DrawComponent groundc4(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc4.setPosition(111, 6);
  groundc4.draw();

  // Supply rail 3
  _w = _Helper::getWord(_v, 28);
  _DrawComponent voltage_plus_c3(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_POSITIVE,
                                 NORMAL, _w.at(2), _w.at(3));
  voltage_plus_c3.setPosition(84, 15);
  voltage_plus_c3.draw();

  // Ground for supply rail 3
  _DrawComponent groundc5(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc5.setPosition(89, 17);
  groundc5.draw();

  // Supply rail positive for op-amp
  _w = _Helper::getWord(_v, 31);
  _DrawComponent voltage_plus_c4(VOLTAGE_SOURCE, _w.at(0), _w.at(1), H_POSITIVE,
                                 NORMAL, _w.at(2), _w.at(3));
  voltage_plus_c4.setPosition(128, 4);
  voltage_plus_c4.draw();

  // Ground for supply rail positive
  _DrawComponent groundc6(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc6.setPosition(133, 6);
  groundc6.draw();

  // Supply rail negative for op-amp
  _w = _Helper::getWord(_v, 34);
  _DrawComponent voltage_minus_c5(VOLTAGE_SOURCE, _w.at(0), _w.at(1),
                                  H_NEGATIVE, NORMAL, _w.at(2), _w.at(3));
  voltage_minus_c5.setPosition(128, 15);
  voltage_minus_c5.draw();

  // Ground for supply rail negative
  _DrawComponent groundc7(GROUND, YELLOW, MAGENTA, VERTICAL, NORMAL, "", 0);
  groundc7.setPosition(133, 17);
  groundc7.draw();

  // Connector
  _Helper::connectComponent(capacitor_c.getPort(2), capacitor_c.getPort(3),
                            capacitor_c.getPort(2) + 2, capacitor_c.getPort(3),
                            HORI, HORI);
  _Helper::connectComponent(capacitor_c.getPort(0), capacitor_c.getPort(1),
                            capacitor_c.getPort(0) - 6, capacitor_c.getPort(1),
                            HORI, HORI);
  _Helper::connectComponent(op_amp_c.getPort(4), op_amp_c.getPort(5),
                            op_amp_c.getPort(4) + 10, op_amp_c.getPort(5) + 18,
                            HORI, VERT);
  _Helper::connectComponent(resistor_cf.getPort(2), resistor_cf.getPort(3),
                            resistor_cf.getPort(2) + 6, resistor_cf.getPort(3),
                            HORI, HORI);
  _Helper::connectComponent(op_amp_c.getPort(0), op_amp_c.getPort(1),
                            op_amp_c.getPort(0) - 24, op_amp_c.getPort(1), HORI,
                            HORI);
  _Helper::connectComponent(op_amp_c.getPort(2), op_amp_c.getPort(3),
                            op_amp_c.getPort(2) - 2, op_amp_c.getPort(3) + 10,
                            HORI, VERT);
  _Helper::connectComponent(
      resistor_cpush.getPort(2), resistor_cpush.getPort(3) - 1,
      resistor_cpush.getPort(2), resistor_cpush.getPort(3) + 3, VERT, VERT);
  _Helper::connectComponent(voltage_plus_c1.getPort(2),
                            voltage_plus_c1.getPort(3),
                            voltage_plus_c1.getPort(2) + 2,
                            voltage_plus_c1.getPort(3) + 1, HORI, VERT);
  _Helper::connectComponent(voltage_plus_c2.getPort(2),
                            voltage_plus_c2.getPort(3),
                            voltage_plus_c2.getPort(2) + 2,
                            voltage_plus_c2.getPort(3) + 1, HORI, VERT);
  _Helper::connectComponent(voltage_plus_c3.getPort(2),
                            voltage_plus_c3.getPort(3),
                            voltage_plus_c3.getPort(2) + 2,
                            voltage_plus_c3.getPort(3) + 1, HORI, VERT);
  _Helper::connectComponent(voltage_plus_c4.getPort(2),
                            voltage_plus_c4.getPort(3),
                            voltage_plus_c4.getPort(2) + 2,
                            voltage_plus_c4.getPort(3) + 1, HORI, VERT);
  _Helper::connectComponent(voltage_minus_c5.getPort(2),
                            voltage_minus_c5.getPort(3),
                            voltage_minus_c5.getPort(2) + 2,
                            voltage_minus_c5.getPort(3) + 1, HORI, VERT);
  _Helper::connectComponent(voltage_plus_c1.getPort(0),
                            voltage_plus_c1.getPort(1), resistor_c1.getPort(0),
                            resistor_c1.getPort(1), HORI, VERT);
  _Helper::connectComponent(voltage_plus_c2.getPort(0),
                            voltage_plus_c2.getPort(1), resistor_c3.getPort(0),
                            resistor_c3.getPort(1), HORI, DOWN_RIGHT);
  _Helper::connectComponent(
      voltage_plus_c3.getPort(0), voltage_plus_c3.getPort(1),
      resistor_cpush.getPort(0), resistor_cpush.getPort(1), HORI, VERT);
  _Helper::connectComponent(voltage_plus_c4.getPort(0) + 1,
                            voltage_plus_c4.getPort(1), op_amp_c.getPort(6),
                            op_amp_c.getPort(7), DOWN_RIGHT, VERT);
  _Helper::connectComponent(voltage_minus_c5.getPort(0),
                            voltage_minus_c5.getPort(1), op_amp_c.getPort(8),
                            op_amp_c.getPort(9), HORI, VERT);
  _Helper::connectComponent(resistor_c1.getPort(2), resistor_c1.getPort(3) - 1,
                            resistor_c2.getPort(0), resistor_c2.getPort(1),
                            VERT, VERT);
  _Helper::connectComponent(resistor_cf.getPort(0), resistor_cf.getPort(1),
                            resistor_cf.getPort(0) - 26, resistor_cf.getPort(1),
                            HORI, HORI);
  _Helper::connectComponent(resistor_c3.getPort(2), resistor_c3.getPort(3) - 1,
                            resistor_c4.getPort(0), resistor_c4.getPort(1),
                            VERT, VERT);
  _Helper::connectComponent(resistor_c4.getPort(2), resistor_c4.getPort(3) - 2,
                            resistor_c4.getPort(2), resistor_c4.getPort(3) - 1,
                            VERT, VERT);
  _Helper::connectComponent(resistor_c2.getPort(2), resistor_c2.getPort(3) - 2,
                            resistor_c2.getPort(2), resistor_c2.getPort(3) - 1,
                            VERT, VERT);
  _Helper::connectComponent(resistor_cpush.getPort(2),
                            resistor_cpush.getPort(3) + 3,
                            resistor_cpush.getPort(2) + 57,
                            resistor_cpush.getPort(3) + 3, UP_RIGHT, UP_LEFT);

  _Helper::locateCursorAt(97, 9);
  std::cout << "╋";
  _Helper::locateCursorAt(118, 21);
  std::cout << "┻";
  _Helper::locateCursorAt(138, 21);
  std::cout << "┫ ";

  _Helper::locateCursorAt(72, 19);
  std::cout << "Comp Out";
  return 0;
}
//***************** Yusen Liu *****************

//***************** Keyi Zhou *****************
int _SetLayout::Decoder() {
  _Helper::locateCursorAt(5, 19);
  std::cout << "Circuit Ends: ";
  _Helper::locateCursorAt(3, 20);
  HANDLE consolehwnd;
  consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
  std::string _bitI = "";
  std::string _chrt = "";

  std::string _filename = "IVConverter.txt";
  std::ifstream infile(_filename, std::ios::in);
  if (!infile) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  std::string _line;
  // the std::vector _v stored all read-in data (per line)
  // while _w stored all the splited data from _v (per word)
  std::vector<std::string> _v, _w;
  while (getline(infile, _line, '\r')) {
    _v.push_back(_line);
  }
  infile.close();
  _w = _Helper::getWord(_v, 2);
  double noise_ratio = stof(_w.at(0));

  _filename = "rawData.txt";
  std::ifstream infile2(_filename, std::ios::in);
  if (!infile2) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line = "";
  _v.clear();
  _w.clear();
  while (getline(infile2, _line, '\n')) {
    _v.push_back(_line);
  }
  infile2.close();
  _bitI = _v.at(0);
  std::vector<double> binary_code;
  std::vector<bool> binary_code_b;
  for (unsigned i = 0; i < _bitI.length(); i++) {
    binary_code.push_back(double(_bitI.at(i)) - 48);
  }
  double num = 0.0;
  _bitI = "";
  std::string _filename2 = "noiseData.txt";
  std::ofstream outfile0(_filename2, std::ios::out);
  std::string outputtemp;
  for (unsigned int i = 0; i < binary_code.size(); i++) {
    num = ((double)(rand() % 50) / (double)100 - 0.25) / (1 / noise_ratio / 10);
    binary_code[i] += num;
    if (binary_code[i] >= 0.5) {
      binary_code_b.push_back(1);
      outputtemp = _Helper::cutTailingZeros(binary_code[i]);
      for (unsigned int j = 0; j < outputtemp.length(); j++) {
        outfile0.put(outputtemp[j]);
      }
      outfile0.put('\n');
      _bitI += "1";
    } else {
      _bitI += "0";
      binary_code_b.push_back(0);
      outputtemp = _Helper::cutTailingZeros(binary_code[i]);
      for (unsigned int j = 0; j < outputtemp.length(); j++) {
        outfile0.put(outputtemp[j]);
      }
      outfile0.put('\n');
    }
  }
  outfile0.close();

  _filename = "decodedData.txt";
  std::ifstream infile3(_filename, std::ios::in);
  if (!infile3) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line = "";
  // the std::vector _v stored all read-in data (per line)
  // while _w stored all the splited data from _v (per word)
  _v.clear();
  _w.clear();
  while (getline(infile3, _line, '\n')) {
    _v.push_back(_line);
  }
  infile3.close();

  code_t_i ci;
  _Huffman h;
  h.huffmanEncode(_v.at(0), 0);
  h.huffmanDecode(binary_code_b);

  _filename = "decodedDataFinal.txt";
  std::ifstream infile4(_filename, std::ios::in);
  if (!infile4) {
    std::cout << "open error!" << std::endl;
    exit(1);
  }
  _line;
  // the std::vector _v stored all read-in data (per line)
  // while _w stored all the splited data from _v (per word)
  _v.clear();
  _w.clear();
  while (getline(infile4, _line, '\n')) {
    _v.push_back(_line);
  }
  infile4.close();
  _chrt = _v.at(0);
  _Helper::locateCursorAt(3, 20);
  std::cout << " ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
               "━━━━━━━━━━━━━━━┫";
  _Helper::locateCursorAt(3, 21);
  std::cout
      << " ┃                                                                  ";
  _Helper::locateCursorAt(3, 22);
  std::cout << " ┃       ┏━━━━━━━━━━━━━━━━━━━━━━━━━━┓          "
               "┏━━━━━━━━━━━━━━━━━━━━━━━━━┓";
  _Helper::locateCursorAt(3, 23);
  std::cout << " ┃ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_GREEN, 0));
  std::cout << "┏┓┏┓ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  std::cout
      << " ┃┏━━━━━━━━━━━━━━━━━━━━━━━━┓┃          ┃┏━━━━━━━━━━━━━━━━━━━━━━━┓┃";
  _Helper::locateCursorAt(3, 24);
  std::cout << " ┃ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_GREEN, 0));
  std::cout << "┛┗┛┗ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  std::cout << " ┃┃      ";
  std::cout << std::setw(23);
  std::cout << "      ┃┃ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_GREEN, 0));
  std::cout << "  010101 ";
  SetConsoleTextAttribute(consolehwnd, 0x0f);
  std::cout << "┃┃    ";
  std::cout << std::setw(24);
  std::cout << "     ┃┃\n";
  _Helper::locateCursorAt(3, 25);
  std::cout << " ┗━━━━━> ┃┃ ";
  std::cout << std::setw(47) << "┃┃   ━━━━ > ┃┃  ";
  std::cout << std::setw(25) << "┃┃";
  _Helper::locateCursorAt(3, 26);
  std::cout << "         ┃┃     ";
  std::cout << std::setw(24);
  std::cout << " ┃┃ ";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(DARK_GREEN, 0));
  std::cout << " Decoding";
  SetConsoleTextAttribute(consolehwnd,
                          _Helper::convertColorNameToHex(WHITE, 0));
  std::cout << "┃┃    ";
  std::cout << std::setw(23);
  std::cout << "   ┃┃";
  _Helper::locateCursorAt(3, 27);
  std::cout << "         ┃┗━━━━━━━━━━━━━━━━━━━━━━━━┛┃          "
               "┃┗━━━━━━━━━━━━━━━━━━━━━━━┛┃";
  _Helper::locateCursorAt(3, 28);
  std::cout << "         ┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛          "
               "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛";
  _Helper::locateCursorAt(3, 29);
  std::cout
      << "                   ◢_____◣                             ◢____◣       ";

  _Helper::locateCursorAt(16, 25);
  if (_bitI.length() < 21) {
    for (int j = 0; j < _bitI.length(); j++) {
      std::cout << _bitI[j];
    }
    Sleep(10);
    _Helper::locateCursorAt(16, 25);
  } else {
    for (int i = 0; i <= (_bitI.length() - 21); i++) {
      for (int j = 0; j < 21; j++) {
        std::cout << _bitI[j + i];
      }
      Sleep(10);
      /*
      if((_bitI.length()-i)<20)
      {
              for (int j = 0; j <= (_bitI.length() - i); j++)
              {
                      cout << _bitI[j+i];
              }
              Sleep(10);
              break;			//omit??
      }
      */
      _Helper::locateCursorAt(16, 25);
    }
  }
  /*
  _Helper::locateCursorAt(64, 26);
  int n = _chrt.length() - 30>0?(_chrt.length() - 30):1;
  for (int i = 0; i < n; i++)
  {
          for (int j = 0; j < _chrt.length() && j < 30; j++)
          {
                  cout << _chrt[j + i];
          }
          Sleep(50);
          _Helper::locateCursorAt(64, 26);
  }*/
  if (_chrt.length() < 20) {
    _Helper::locateCursorAt(54, 25);
    for (int j = 0; j < _chrt.length(); j++) {
      std::cout << _chrt[j];
    }
    Sleep(10);
    _Helper::locateCursorAt(54, 25);
    _Helper::locateCursorAt(20, 32);
  } else {
    _Helper::locateCursorAt(54, 25);
    for (int i = 0; i < (_chrt.length() - 20); i++) {
      for (int j = 0; j < _chrt.length() && j < 20; j++) {
        std::cout << _chrt[j + i];
      }
      Sleep(10);
      _Helper::locateCursorAt(54, 25);
    }
    _Helper::locateCursorAt(20, 32);
  }

  return 32;
}
//***************** Keyi Zhou *****************
