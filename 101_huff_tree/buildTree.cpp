#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;

  // traverse counts
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] > 0)
      pq.push(new Node(i, counts[i]));
  }

  // build tree from removing top two
  while (pq.size() > 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();

    // new node
    Node * newParent = new Node(left, right);
    pq.push(newParent);
  }

  Node * root = pq.top();
  pq.pop();

  return root;
}
