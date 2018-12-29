#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T data) : data(data), next(NULL), prev(NULL) {}
  };
  Node * head;
  Node * tail;
  int size;
  class IndexOutOfBound : public std::exception
  {
    const char * what() { return "Invalid index!"; }
  };

 protected:
  void removeAll() {
    Node * curt = this->head;
    while (curt != NULL) {
      Node * post = curt->next;
      delete curt;
      curt = post;
    }
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
  }

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    for (Node * curt = rhs.head; curt != NULL; curt = curt->next) {
      addBack(curt->data);
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      this->removeAll();
      for (Node * p = rhs.head; p != NULL; p = p->next) {
        this->addBack(p->data);
      }
    }
    return *this;
  }

  ~LinkedList() { this->removeAll(); }

  void addFront(const T & item) {
    Node * newNode = new Node(item);
    if (this->size == 0) {
      this->tail = newNode;
    }
    else {
      newNode->next = this->head;
      this->head->prev = newNode;
    }
    this->size += 1;
    this->head = newNode;
  }

  void addBack(const T & item) {
    Node * newNode = new Node(item);
    if (this->size == 0) {
      this->head = newNode;
    }
    else {
      this->tail->next = newNode;
      newNode->prev = this->tail;
    }
    this->size += 1;
    this->tail = newNode;
  }

  bool remove(const T & item) {
    Node * p;
    for (p = this->head; p != NULL; p = p->next) {
      if (p->data == item)
        break;
    }

    if (p == NULL)
      return false;

    Node * front = p->prev;
    Node * back = p->next;
    if (front != NULL && back != NULL) {
      front->next = back;
      back->prev = front;
    }
    else if (front == NULL && back != NULL) {
      back->prev = NULL;
      this->head = back;
    }
    else if (front != NULL && back == NULL) {
      front->next = NULL;
      this->tail = front;
    }
    else {
      this->tail = NULL;
      this->head = NULL;
    }
    this->size -= 1;
    delete p;
    return true;
  }

  T & operator[](int index) {
    if (index < 0 || index >= this->size) {
      throw IndexOutOfBound();
    }

    Node * p;
    for (p = this->head; p != NULL && index > 0; p = p->next) {
      index--;
    }

    return p->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= this->size) {
      throw IndexOutOfBound();
    }

    Node * p;
    for (p = this->head; p != NULL && index > 0; p = p->next) {
      index--;
    }

    return p->data;
  }

  int find(const T & item) {
    int answer = 0;
    Node * p;
    for (p = this->head; p != NULL; p = p->next) {
      if (p->data == item)
        return answer;
      answer++;
    }

    return -1;
  }

  int getSize() const { return this->size; }

  friend void testList(void);
};

#endif
