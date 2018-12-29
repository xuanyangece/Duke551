#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  // leaf
  if (this->sym != NO_SYM) {
    assert(this->left == NULL);
    assert(this->right == NULL);

    // up date map
    theMap.insert(std::make_pair(this->sym, b));
  }
  else {
    // recurse left
    this->left->Node::buildMap(b.plusZero(), theMap);
    // recurse right
    this->right->Node::buildMap(b.plusOne(), theMap);
  }
}
