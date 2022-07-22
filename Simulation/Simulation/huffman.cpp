// Huffman tree encoding and decoding functions implementation
// Referenced by https://github.com/ningke/huffman-codes/blob/master/huffman.cpp
// Modified by Yadong Hu for trasfering the normal functions into C++ style
// classes All comments were created by Yadong Hu Dec.5: Keyi Zhou added some
// her investigated codes

#include "huffman.h"

#include "utils.h"

// Builds a _Huffman Tree from an input of alphabet C, where C is a std::vector
// of (character, frequency) pairs.
HuffmanTree* _Huffman::build_tree(
    std::vector<std::pair<char, unsigned> >& alph) {
  // First build a min-heap
  // Build leaf nodes first
  std::priority_queue<HuffmanTree*, std::vector<HuffmanTree*>,
                      HuffmanTree::Compare>
      alph_heap;
  for (std::vector<std::pair<char, unsigned> >::iterator it = alph.begin();
       it != alph.end(); ++it) {
    HuffmanTree* leaf = new HuffmanTree(it->first, it->second);
    alph_heap.push(leaf);
  }
  // HuffmanTree algorithm: Merge two lowest weight leaf nodes until
  // only one node is left (root).
  HuffmanTree* root = NULL;
  while (alph_heap.size() > 1) {
    HuffmanTree *l, *r;
    l = alph_heap.top();
    alph_heap.pop();
    r = alph_heap.top();
    alph_heap.pop();
    root = new HuffmanTree(0, l->cfreq + r->cfreq, l, r);
    alph_heap.push(root);
  }

  return root;
}

// Prints the tree nodes in breadth-first order
void _Huffman::print_tree(HuffmanTree* t) {
  std::deque<std::pair<HuffmanTree*, int> > q;

  q.push_back(std::make_pair(t, 0));
  int curlevel = -1;
  while (!q.empty()) {
    HuffmanTree* parent = q.front().first;
    int level = q.front().second;
    q.pop_front();
    if (curlevel != level) {
      curlevel = level;
      std::cout << "Level " << curlevel << std::endl;
    }
    std::cout << parent->cfreq << " " << parent->c << std::endl;
    if (parent->left) q.push_back(std::make_pair(parent->left, level + 1));
    if (parent->right) q.push_back(std::make_pair(parent->right, level + 1));
  }
}

// Makes a lookup table (std::map) of (c -> code) from a HuffmanTree, where
// code is an unsigned long representing the binary code.
std::map<char, code_t> _Huffman::build_lookup_table(HuffmanTree* htree) {
  codetable lookup;
  std::deque<std::pair<HuffmanTree*, code_t> > q;

  q.push_back(make_pair(htree, code_t()));
  if (this->flag) {
    _Helper::locateCursorAt(4, 11);
    std::cout << "> Huffman tree leaves (character, binary code): ";
    _Helper::locateCursorAt(6, 12);
  }
  int i = 1;
  while (!q.empty()) {
    HuffmanTree *node, *lc, *rc;
    code_t code;
    node = q.front().first;
    code = q.front().second;
    q.pop_front();
    lc = node->left;
    rc = node->right;
    if (lc) {
      // HuffmanTree is always full (either no children or two children)
      // Left child is appended a 0 and right child a 1.
      code_t code_cp(code);
      q.push_back(make_pair(lc, (code.push_back(0), code)));
      q.push_back(make_pair(rc, (code_cp.push_back(1), code_cp)));
    } else {
      // Leaf node: contains the character
      lookup.insert(make_pair(node->c, code));
      if (this->flag) {
        std::cout << "(" << node->c << ", ";
        for (unsigned i = 0; i < code.size(); i++) {
          std::cout << code[i];
        }
        std::cout << ")";
        _Helper::locateCursorAt(6, 12 + i);
        i++;
      }
    }
  }
  return lookup;
}

// Look up the next valid code in @biter using @htree and returns the
// resulting std::string. Note the iterator @biter is advanced by the actual
// length of the next valid code, which varies.
char _Huffman::code_lookup(code_t::iterator& biter,
                           const code_t::iterator& biter_end,
                           const HuffmanTree* htree) {
  const HuffmanTree* node = htree;
  while (true) {
    if (!node->left) {
      // _Huffman tree is full: always contains both children or none.
      break;
    }
    if (biter == biter_end) {
      throw std::out_of_range("No more bits");
    }
    if (*biter) {
      node = node->right;
    } else {
      node = node->left;
    }
    ++biter;
  }
  return node->c;
}

// Encodes an input std::string. returns a byte std::vector.
code_t _Huffman::encode(std::string input, codetable& lookup) {
  code_t result;
  for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
    code_t b = lookup[*it];
    result.insert(result.end(), b.begin(), b.end());
  }
  return result;
}

// Decodes a compressed std::string represented by a bit std::vector
// (std::vector<char>)
// @compressed, using a HuffmanTree @htree.
// Returns the original std::string.
std::string _Huffman::decode(code_t& compressed, const HuffmanTree* htree) {
  std::string result;
  code_t::iterator biter = compressed.begin();
  while (true) {
    try {
      result += code_lookup(biter, compressed.end(), htree);
    } catch (const std::out_of_range& oor) {
      // Iterator exhausted.
      // std::cout << &oor;
      break;
    }
  }
  return result;
}

// Tests
// Make frequency table from a std::string.
std::vector<std::pair<char, unsigned> > _Huffman::make_freq_table(
    std::string inp) {
  std::map<char, unsigned> cfmap;
  std::vector<std::pair<char, unsigned> > cfvec;
  for (unsigned i = 0; i < inp.size(); i++) {
    if (cfmap.find(inp[i]) == cfmap.end()) {
      cfmap.insert(std::make_pair(inp[i], 1));
    }
    cfmap[inp[i]] += 1;
  }
  for (std::map<char, unsigned>::iterator it = cfmap.begin(); it != cfmap.end();
       ++it) {
    cfvec.push_back(std::make_pair(it->first, it->second));
  }
  return cfvec;
}

// Convert the bit std::vector to C++ std::string
std::string _Huffman::bitvec_to_string(code_t& bitvec) {
  std::string result;
  size_t nbits;
  nbits = bitvec.size() & 7;
  // Write the number of "hanging bits" at the first byte
  result += static_cast<char>(nbits);  // at most 7
  char byte = 0;
  for (unsigned i = 0; i < bitvec.size(); i++) {
    unsigned boff = i & 7;
    byte |= bitvec[i] << boff;
    if (boff == 7) {
      // Write a byte
      result += byte;
      byte = 0;
    }
  }
  if (nbits) {
    result += byte;
  }
  return result;
}

// Convert std::string to bit std::vector
code_t _Huffman::string_to_bitvec(std::string packed) {
  code_t result;
  assert(packed.size());
  if (packed.size() == 1) {
    assert(packed[0] == 0);
    return result;
  }
  unsigned nbits = packed[0];
  for (std::string::iterator it = packed.begin() + 1; it != packed.end();
       ++it) {
    for (unsigned i = 0; i < 8; i++) {
      result.push_back((*it >> i) & 1);
    }
  }
  // fix the last byte
  if (nbits) {
    for (unsigned i = 0; i < (8 - nbits); i++) {
      result.pop_back();
    }
  }
  return result;
}

// Convert the bit std::vector into hex value
// Not used in these program, just for testing
void _Huffman::hexdump(const unsigned char* bytes, int nbytes) {
  /*
  int i, j;
  for (i = 0; i < nbytes; i += 16) {
          printf("%06x: ", i);
          for (j = 0; j < 16; j++) {
                  if (i + j < nbytes) {
                          printf("%02x ", bytes[i + j]);
                  }
                  else {
                          printf("   ");
                  }
          }
          printf(" ");
          for (j = 0; j < 16; j++)
                  if (i + j < nbytes)
                          printf("%c", isprint(bytes[i + j]) ? bytes[i + j] :
  '.'); printf("\n");
  }
  */
}

//***************** Yadong Hu *****************
// The entry of huffman encoding function
void _Huffman::huffmanEncode(std::string s, int flag) {
  this->flag = flag;
  this->s = s;
  this->cfvec = make_freq_table(this->s);
  this->htree = build_tree(cfvec);
  // print_tree(htree);
  this->ctbl = build_lookup_table(this->htree);
  this->t = encode(this->s, this->ctbl);
  _Helper::locateCursorAt(4, 6);
  if (this->flag) {
    std::cout << "> Encoded (Compression ratio: " << (this->t.size() + 7) / 8
              << "/" << this->s.size() << " or "
              << ((float)(this->t.size() / 8) / this->s.size()) << ")";
    std::string _filename_temp = "rawData.txt";
    std::ofstream outfile(_filename_temp, std::ios::out);
    _Helper::locateCursorAt(4, 8);
    std::cout << "> Binary Code: ";
    _Helper::locateCursorAt(4, 9);
    std::cout << "  ";
    for (unsigned int i = 0; i < this->t.size(); i++) {
      if (this->t[i] == true) {
        outfile.put('1');
      } else {
        outfile.put('0');
      }
      std::cout << this->t[i];
    }
    outfile.close();
  }
  this->packed = bitvec_to_string(this->t);
  // hexdump((unsigned char*)(packed.c_str()), packed.size());
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// The entry of huffman decoding function
void _Huffman::huffmanDecode() {
  // Decode
  code_t t1 = string_to_bitvec(this->packed);
  assert(std::equal(this->t.begin(), this->t.end(), t1.begin()));
  std::string s1 = decode(t1, this->htree);
  std::string _filename_temp = "decodedData.txt";
  std::ofstream outfile(_filename_temp, std::ios::out);
  for (unsigned int i = 0; i < s1.length(); i++) {
    outfile.put(s1[i]);
  }
  outfile.close();
  // std::cout << "Decoded:" << s1 << std::endl;
  delete this->htree;
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
void _Huffman::huffmanDecode(code_t t1) {
  std::string s1 = decode(t1, this->htree);
  std::string _filename_temp = "decodedDataFinal.txt";
  std::ofstream outfile(_filename_temp, std::ios::out);
  for (unsigned int i = 0; i < s1.length(); i++) {
    outfile.put(s1[i]);
  }
  outfile.close();
  // std::cout << "Decoded:" << s1 << std::endl;
}
//***************** Yadong Hu *****************

//***************** Yadong Hu *****************
// Transfer from bool std::vector into double std::vector
code_t_i _Huffman::transferBtoI(code_t t) {
  code_t_i t_n;
  for (unsigned int i = 0; i < t.size(); i++) {
    if (t[i] == true)
      t_n.push_back(1);
    else
      t_n.push_back(0);
  }
  return t_n;
}
//***************** Yadong Hu *****************

//***************** Keyi Zhou *****************
// Reference:
// https://jensen-lee.blog.csdn.net/article/details/105240060?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control
struct Node {
  double weight;
  std::string ch;
  std::string code;
  int lchild, rchild, parent;
};
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
void Select(Node huffTree[], int* a, int* b, int n)
// Find the the characters with the smallest two weight and also with no parent
// node and then connect
{
  int i;
  double weight = 0;
  // search for the smallest number
  for (i = 0; i < n; i++) {
    if (huffTree[i].parent != -1)
      // judge if the node is selected already
      continue;
    else {
      if (weight == 0) {
        weight = huffTree[i].weight;
        *a = i;
      } else {
        if (huffTree[i].weight < weight) {
          weight = huffTree[i].weight;
          *a = i;
        }
      }
    }
  }

  weight = 0;
  // search for the second smallest number
  for (i = 0; i < n; i++) {
    if (huffTree[i].parent != -1 || (i == *a))
      // exclude the selected number
      continue;
    else {
      if (weight == 0) {
        weight = huffTree[i].weight;
        *b = i;
      } else {
        if (huffTree[i].weight < weight) {
          weight = huffTree[i].weight;
          *b = i;
        }
      }
    }
  }

  // int temp;
  // if (huffTree[*a].weight > huffTree[*b].weight)
  //{
  //	temp = *a;
  //	*a = *b;
  //	*b = temp;
  //}
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
void Huff_Tree(Node huffTree[], int w[], std::string ch[], int n) {
  for (int i = 0; i < 2 * n - 1; i++) {
    huffTree[i].parent = -1;
    huffTree[i].lchild = -1;
    huffTree[i].rchild = -1;
    huffTree[i].code = "";
  }
  for (int i = 0; i < n; i++) {
    huffTree[i].weight = w[i];
    huffTree[i].ch = ch[i];
  }

  // Huffman Tree building
  for (int k = n; k < 2 * n - 1; k++) {
    int i1 = 0;
    int i2 = 0;
    Select(huffTree, &i1, &i2, k);
    huffTree[i1].parent = k;
    huffTree[i2].parent = k;
    huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
    huffTree[k].lchild = i1;
    huffTree[k].rchild = i2;
  }
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
void Huff_Code(Node huffTree[], int n) {
  int i, j, k;
  std::string s = "";
  for (i = 0; i < n; i++) {
    s = "";
    j = i;
    while (huffTree[j].parent != -1) {
      k = huffTree[j].parent;
      if (j == huffTree[k].lchild) {
        s = s + "0";
      } else {
        s = s + "1";
      }
      j = huffTree[j].parent;
    }
    std::cout << "Character " << huffTree[i].ch << " is coded as：";
    for (int l = s.size() - 1; l >= 0; l--) {
      std::cout << s[l];
      huffTree[i].code += s[l];  // save code
    }
    std::cout << std::endl;
  }
}
//***************** Keyi Zhou *****************

//***************** Keyi Zhou *****************
std::string Huff_Decode(Node huffTree[], int n, std::string s) {
  std::cout << "After decoding：";
  std::string temp = "", str = "";
  // Save the charater after decoding
  for (int i = 0; i < s.size(); i++) {
    temp = temp + s[i];
    for (int j = 0; j < n; j++) {
      if (temp == huffTree[j].code) {
        str = str + huffTree[j].ch;
        temp = "";
        break;
      } else if (i == s.size() - 1 && j == n - 1 && temp != "")
      // Not finding after tranversal
      {
        str = "Error in decoding！";
      }
    }
  }
  return str;
}
//***************** Keyi Zhou *****************
