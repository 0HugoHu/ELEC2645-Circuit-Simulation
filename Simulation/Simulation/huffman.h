// Huffman tree encoding and decoding functions
// Referenced by https://github.com/ningke/huffman-codes/blob/master/huffman.cpp
// Modified by Yadong Hu for trasfering the normal functions into C++ style
// classes All comments were created by Yadong Hu

#pragma once
// C++ standard data structure: std::vector, queue and map
#include <map>
#include <queue>
#include <vector>
// C++ std::string
#include <string>
// C++ debug tool assert() function
#include <cassert>
// Solving the std:: conflict problem
#include <stdexcept>
// C++ std::cout and cin
#include <iostream>
// C++ printf
#include <cstdio>

// A Huffman Tree Node
struct HuffmanTree {
  // character in an alphabet
  char c;
  // frequency of c.
  int cfreq;
  struct HuffmanTree* left;
  struct HuffmanTree* right;
  HuffmanTree(char c, int cfreq, struct HuffmanTree* left = NULL,
              struct HuffmanTree* right = NULL)
      : c(c), cfreq(cfreq), left(left), right(right) {}
  ~HuffmanTree() { delete left, delete right; }
  // Compare two tree nodes
  class Compare {
   public:
    bool operator()(HuffmanTree* a, HuffmanTree* b) {
      return a->cfreq > b->cfreq;
    }
  };
};

// Original decoded std::vector
typedef std::vector<bool> code_t;

// Double type decoded std::vector
typedef std::vector<double> code_t_i;

// Codetable based on binary tree
typedef std::map<char, code_t> codetable;

//***************** Yadong Hu *****************
class _Huffman {
 public:
  // Builds a _Huffman Tree from an input of alphabet C
  HuffmanTree* build_tree(std::vector<std::pair<char, unsigned> >& alph);

  // Prints the tree nodes in breadth-first order
  void print_tree(HuffmanTree* t);

  // Makes a lookup table (std::map) of (c -> code) from a HuffmanTree
  std::map<char, code_t> build_lookup_table(HuffmanTree* htree);

  // Look up the next valid code in @biter using @htree and returns the
  // resulting std::string.
  char code_lookup(code_t::iterator& biter, const code_t::iterator& biter_end,
                   const HuffmanTree* htree);

  // Encodes an input std::string. returns a byte std::vector.
  code_t encode(std::string input, codetable& lookup);

  // Decodes a compressed std::string represented by a bit std::vector
  // (std::vector<char>)
  std::string decode(code_t& compressed, const HuffmanTree* htree);

  // Make frequency table from a std::string.
  std::vector<std::pair<char, unsigned> > make_freq_table(std::string inp);

  // Convert the bit std::vector to C++ std::string
  std::string bitvec_to_string(code_t& bitvec);

  // Convert std::string to bit std::vector
  code_t string_to_bitvec(std::string packed);

  // Convert the bit std::vector into hex value
  void hexdump(const unsigned char* bytes, int nbytes);

  // Huffman encode and decode entry
  void huffmanEncode(std::string s, int flag);
  void huffmanDecode();
  void huffmanDecode(code_t t);

  // Transfer from bool std::vector into double std::vector
  code_t_i transferBtoI(code_t);

  // Return the original decoded std::vector
  code_t getCodeT() { return this->t; }

 private:
  // Specify the data type
  std::vector<std::pair<char, unsigned> > cfvec;
  std::string s;
  HuffmanTree* htree;
  codetable ctbl;
  code_t t, new_t;
  std::string packed;
  int flag;
};
//***************** Yadong Hu *****************
