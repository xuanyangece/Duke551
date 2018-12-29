#include <cstdlib>
#include <iostream>

#include "set.h"

template<typename K>
class BstSet : public Set<K>
{
  class Node
  {
   public:
    K key;
    Node * left;
    Node * right;

    Node(K key) : key(key), left(NULL), right(NULL){};
  };
  Node * head;

 public:
  BstSet<K>() : head(NULL){};

  BstSet<K>(const BstSet & rhs) : head(NULL) { assignHelper(rhs.head); }

  void assignHelper(Node * curt) {
    if (curt == NULL)
      return;
    add(curt->key);
    assignHelper(curt->left);
    assignHelper(curt->right);
  }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      deleteAll(this->head);
      this->head = NULL;
      assignHelper(rhs.head);
    }
    return *this;
  }

  virtual void add(const K & key) { this->head = addHelper(head, key); }

  // need to implement
  virtual ~BstSet<K>() {
    deleteAll(this->head);
    this->head = NULL;
  }

  void deleteAll(Node * curt) {
    if (curt == NULL)
      return;

    deleteAll(curt->left);
    deleteAll(curt->right);

    delete curt;
  }

  Node * addHelper(Node * curt, const K & key) {
    if (curt == NULL) {
      Node * ans = new Node(key);
      return ans;
    }

    if (curt->key == key) {
      return curt;
    }

    if (key < curt->key) {
      curt->left = addHelper(curt->left, key);
    }
    else {
      curt->right = addHelper(curt->right, key);
    }

    return curt;
  }

  virtual bool contains(const K & key) const {
    Node * curt = this->head;
    while (curt != NULL) {
      if (key < curt->key) {
        curt = curt->left;
      }
      else if (key > curt->key) {
        curt = curt->right;
      }
      else {
        return true;
      }
    }
    return false;
  }

  virtual void remove(const K & key) { this->head = removeHelper(this->head, key); }

  Node * removeHelper(Node * curt, const K & key) {
    if (curt == NULL)
      return NULL;

    Node * temp = NULL;
    if (curt->key == key) {
      if (curt->left == NULL) {
        temp = curt->right;
        delete curt;
        return temp;
      }
      else if (curt->right == NULL) {
        temp = curt->left;
        delete curt;
        return temp;
      }
      else {
        temp = curt->left;
        Node * parent = curt;
        bool isOnly = true;

        while (temp->right != NULL) {
          isOnly = false;
          parent = temp;
          temp = temp->right;
        }

        curt->key = temp->key;

        // or call helper
        if (isOnly) {
          parent->left = temp->left;
        }
        else {
          parent->right = temp->left;
        }

        delete temp;
        return curt;
      }
    }
    else if (curt->key < key) {
      curt->right = removeHelper(curt->right, key);
    }
    else {
      curt->left = removeHelper(curt->left, key);
    }

    return curt;
  }
};
