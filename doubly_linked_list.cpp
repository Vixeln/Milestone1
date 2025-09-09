/**
 * @author - Vireak Ny
 * @file doubly_linked_list.cpp -  This file implements the functions in doubly_linked_list.h
 *
 */

/**
 * @file doubly_linked_list.cpp
 * @brief This file implements the functions in doubly_linked_list.h
 *
 * This file defines a basic doubly linked list and common operations like
 * insertion, deletion, and movement of nodes.
 *
 * @date 09/09/2025 - Added implementations and file heading
 * @author Vireak Ny
 */
//TODO: ask Baxter why there are 2 blocks of comments on file heading
#include "doubly_linked_list.h"
#include "dll_node.h"
#include "json.hpp"
#include <iostream>
#include <ostream>

DoublyLinkedList::DoublyLinkedList() {
  this->tail = nullptr;
  this->head = nullptr;
} ///< Constructor: Initializes an empty list.
DoublyLinkedList::~DoublyLinkedList() {

}; ///< Destructor: Deletes all nodes.

bool DoublyLinkedList::isEmpty() {
  return (this->head == nullptr);
}; ///< Checks if the list is empty.

void DoublyLinkedList::insertAtHead(int key) {
  DllNode *node = new DllNode(key);
  node->next = this->head;
  if (this->head != nullptr)
    this->head->prev = node;
  this->head = node;
}; ///< Inserts a node at the head.
void DoublyLinkedList::insertAtTail(int key) {};   ///< Inserts a node at the tail.
void DoublyLinkedList::remove(int key) {};         ///< Removes a node with a specific key.
void DoublyLinkedList::removeHeaderNode() {};      ///< Removes the head node.
void DoublyLinkedList::removeTailNode() {};        ///< Removes the tail node.
void DoublyLinkedList::moveNodeToHead(int key){}; ///< Moves a node to the head.
void DoublyLinkedList::moveNodeToTail(int key){}; ///< Moves a node to the tail.
void DoublyLinkedList::clear(){};                 ///< Deletes all nodes.
void DoublyLinkedList::printList() {
  DllNode *currentNode = this->head;

  std::cout << "Here are the List contents: " << std::endl;
  while (currentNode != nullptr) {
    std::cout << "Node key: " << currentNode->key << std::endl;
    currentNode = currentNode->next;
  };
  // Pointers should hopefully end up as null pointers after loop

  std::cout << "End of List" << std::endl;
}; ///< Prints the list from head to tail.

void DoublyLinkedList::reversePrintList() {
  DllNode *currentNode = this->tail;

  std::cout << "Here are the List contents: " << std::endl;
  while (currentNode != nullptr) {
    std::cout << "Node key: " << currentNode->key << std::endl;
    currentNode = currentNode->prev;
  };
  // Pointers should hopefully end up as null pointers after loop

  std::cout << "End of List" << std::endl;
}; ///< Prints the list from tail to head.
