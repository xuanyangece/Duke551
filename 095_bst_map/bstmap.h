#include <cstdlib>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL){};
  };
  Node * head;

 public:
  BstMap<K, V>() : head(NULL){};

  BstMap<K, V>(const BstMap & rhs) : head(NULL) { assignHelper(rhs.head); }

  void assignHelper(Node * curt) {
    if (curt == NULL)
      return;
    add(curt->key, curt->value);
    assignHelper(curt->left);
    assignHelper(curt->right);
  }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      deleteAll(this->head);
      this->head = NULL;
      assignHelper(rhs.head);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) { this->head = addHelper(head, key, value); }

  // need to implement
  virtual ~BstMap<K, V>() {
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

  Node * addHelper(Node * curt, const K & key, const V & value) {
    if (curt == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }

    if (curt->key == key) {
      curt->value = value;
      return curt;
    }

    if (key < curt->key) {
      curt->left = addHelper(curt->left, key, value);
    }
    else {
      curt->right = addHelper(curt->right, key, value);
    }

    return curt;
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curt = this->head;
    while (curt != NULL) {
      if (key < curt->key) {
        curt = curt->left;
      }
      else if (key > curt->key) {
        curt = curt->right;
      }
      else {
        return curt->value;
      }
    }
    throw std::invalid_argument("argument not valid");
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
        curt->value = temp->value;

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
