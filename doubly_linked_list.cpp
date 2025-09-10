/**
 * @author - Vireak Ny
 * @file doubly_linked_list.cpp -  This file implements the functions in
 * doubly_linked_list.h
 *
 */

/**
 * @file doubly_linked_list.cpp
 * @brief This file implements the functions in doubly_linked_list.h
 *
 * This file defines a basic doubly linked list and common operations like
 * insertion, removal, movement of nodes, and printing.
 *
 * For GitHub Repository
 * @see https://github.com/Vixeln/Milestone1
 *
 * @date 09/09/2025 - Added file heading and empty implementations so that the
 * progrma compiles
 * @date 09/09/2025 - Added function implementations
 * @author Vireak Ny
 */
// TODO: ask Baxter why there are 2 blocks of comments on file heading
#include "doubly_linked_list.h"
#include "dll_node.h"
#include <iostream>
#include <ostream>

extern void logToFileAndConsole(std::string msg);

DoublyLinkedList::DoublyLinkedList() {
  this->tail = nullptr;
  this->head = nullptr;
} ///< Constructor: Initializes an empty list.
DoublyLinkedList::~DoublyLinkedList() {
  this->clear(); // I'not sure if I have to clear to properly destruct the list,
                 // but I'm doing it just to be safe
}; ///< Destructor: Deletes all nodes.

// I'm personally not a fan of having to initialize stuff, but I'm just doing it
// for now
/**
 * @brief Helper function for making the first node in an empty list
 *
 * @param firstNode
 * @param list
 */
static void initializeFirstNode(DllNode *firstNode, DoublyLinkedList *list) {
  list->head = firstNode;
  list->tail = firstNode;
}

/**
 * @brief Helper function to find the first node with the provided key
 *
 * @details This function is used for moving or removing nodes
 * @param key
 * @param list
 * @return DllNode*
 */
static DllNode *findNode(int key, DoublyLinkedList *list) {
  DllNode *currentNode = list->head;

  while (currentNode != nullptr) {
    if (currentNode->key == key)
      break;

    currentNode = currentNode->next;
  }

  return currentNode;
}

/**
 * @brief Helper function that removes a node from the link and patching up the
 * pointer connections.
 *
 * @warning It does NOT delete the node. Make sure to properly delete the
 * returned node.
 * @param targetNode
 * @return DllNode*
 */
static DllNode *softRemove(DllNode *targetNode) {
  DllNode *prevNode, *nextNode;

  prevNode = targetNode->prev;
  nextNode = targetNode->next;

  prevNode->next = nextNode;
  nextNode->prev = prevNode;

  return targetNode;
};

/**
 * @brief Returns whether the list is empty or not
 *
 * @return true
 * @return false
 */
bool DoublyLinkedList::isEmpty() {
  return (this->head == nullptr);
}; ///< Checks if the list is empty.

/**
 * @brief Insert a new node with the provided key at the head of the list
 *
 * @param key
 */
void DoublyLinkedList::insertAtHead(int key) {
  // TODO Potentially some memory leaks or dangling pointers
  DllNode *newHead, *oldHead;

  newHead = new DllNode(key);
  oldHead = this->head;

  if (!this->isEmpty()) {
    // Connect old and new nodes
    oldHead->prev = newHead;
    newHead->next = oldHead;

    // Update head. Must do this->head, do not use oldHead.
    this->head = newHead;
  } else
    initializeFirstNode(newHead, this);
}; ///< Inserts a node at the head.

/**
 * @brief Insert a new node with the provided key at the tail of the list
 *
 * @param key
 */
void DoublyLinkedList::insertAtTail(int key) {
  DllNode *newTail, *oldTail;

  newTail = new DllNode(key);
  oldTail = this->tail;

  if (!this->isEmpty()) {
    // Connect old and new nodes
    oldTail->next = newTail;
    newTail->prev = oldTail;

    // Update head. Must do this->tail, do not use oldTail.
    this->tail = newTail;
  } else
    initializeFirstNode(newTail, this);
}; ///< Inserts a node at the tail.

/**
 * @brief Remove the first node from the head with the provided key.
 *
 * @param key
 */
void DoublyLinkedList::remove(int key) {
  DllNode *targetNode = findNode(key, this);

  if (targetNode != nullptr) { // Potential circular list issue
    if (targetNode == this->head)
      removeHeaderNode();
    else if (targetNode == this->tail)
      removeTailNode();
    else {
      softRemove(targetNode);

      delete targetNode;
      targetNode = nullptr;
    };
  } else {
    std::cout << "Could not remove node because it could not be found."
              << std::endl;
  }
}; ///< Removes a node with a specific key.

/**
 * @brief Remove the node at the head of the list
 *
 */
void DoublyLinkedList::removeHeaderNode() {
  DllNode *currentHead = this->head;
  DllNode *newHead = currentHead->next; // Problematic if list is empty
  currentHead->next = nullptr;

  if (newHead != nullptr)
    newHead->prev = nullptr; // Fixes bad access when the list is 1 element long
  delete currentHead;

  this->head = newHead;
}; ///< Removes the head node.

/**
 * @brief Remove the node at the tail of the list
 *
 */
void DoublyLinkedList::removeTailNode() {
  DllNode *currentTail = this->tail;
  DllNode *newTail = currentTail->prev;
  currentTail->prev = nullptr;

  if (newTail != nullptr)
    newTail->next = nullptr; // Fixes bad access when the list is 1 element long
  delete currentTail;

  this->tail = newTail;

}; ///< Removes the tail node.

/**
 * @brief Move the first node with the provided key to the head of the list. It
 * finds the first node from the head of the list
 *
 * @param key
 */
void DoublyLinkedList::moveNodeToHead(int key) {
  // My approach involves changing the connections of the target node instead of
  // copying and deleting the target node. This is so that the node can still be
  // accessed by even after being moved so as to avoid invalid pointers
  DllNode *targetNode = findNode(key, this);

  if (targetNode != nullptr) { // Potential circular list issue
    /*Do nothing because it is already the head*/
    if (targetNode == this->head) {
    } else {
      // Clean up connections in target node's oriignal location
      // The following code is similar to remove() but doesn't delete the
      // object. Will come up with better function set up later.
      DllNode *prevNode, *nextNode;

      prevNode = targetNode->prev;
      nextNode = targetNode->next;

      prevNode->next = nextNode;
      if (nextNode != nullptr)
        // If condiiton is just patch up code, will
        // find better solution later.
        nextNode->prev = prevNode;
      if (targetNode == this->tail)
        this->tail = prevNode;

      // Set up connections for target node as new head
      DllNode *oldHead = this->head;
      DllNode *newHead = targetNode; // Could be problematic if list is empty

      oldHead->prev = newHead;
      newHead->prev = nullptr;
      newHead->next = oldHead;

      // Update head pointer to new node
      this->head = newHead;
    }
  } else {
    std::cout << "Could not move node because it could not be found"
              << std::endl;
  }

  // Why are we taking in a key? does that mean we have to search for the node
  // with the key and then find that node?
  // what if there are duplicate nodes?

}; ///< Moves a node to the head.

/**
 * @brief Move the first node with the provided key to the tail of the list. It
 * finds the first node from the head of the list
 *
 * @param key
 */
void DoublyLinkedList::moveNodeToTail(int key) {
  // My approach is very similar the implementation of moveNodeToHead(int), just
  // with different nodes
  DllNode *targetNode = findNode(key, this);

  if (targetNode != nullptr) { // Potential circular list issue
    /*Do nothing because it is already the head*/
    if (targetNode == this->tail) {
    } else {
      // Clean up connections in target node's oriignal location
      // The following code is similar to remove() but doesn't delete the
      // object. Will come up with better function set up later.
      DllNode *prevNode, *nextNode;

      prevNode = targetNode->prev;
      nextNode = targetNode->next;

      nextNode->prev = prevNode;
      if (prevNode != nullptr)
        // If condiiton is just patch up code, will
        // find better solution later.
        prevNode->next = nextNode;
      if (targetNode == this->head)
        this->head = nextNode;

      // Set up connections for target node as new head
      DllNode *oldTail = this->tail;
      DllNode *newTail = targetNode; // Could be problematic if list is empty

      oldTail->next = newTail;
      newTail->next = nullptr;
      newTail->prev = oldTail;

      // Update head pointer to new node
      this->tail = newTail;
    }
  } else {
    std::cout << "Could not move node because it could not be found"
              << std::endl;
  }

  // Why are we taking in a key? does that mean we have to search for the node
  // with the key and then find that node?
  // what if there are duplicate nodes?

}; ///< Moves a node to the tail.

/**
 * @brief Remove all elements from the list
 *
 */
void DoublyLinkedList::clear() {
  DllNode *currentNode = this->head;
  DllNode *nextNode;

  while (currentNode != nullptr) {
    nextNode = currentNode->next;
    delete currentNode;
    currentNode = nextNode;
  }

  this->head = nullptr;
  this->tail = nullptr;
}; ///< Deletes all nodes.

/**
 * @brief Print the the contents of the list from the head to the tail of the
 * list. The direction is the reverse of reversePrintList()
 *
 */
void DoublyLinkedList::printList() {
  DllNode *currentNode = this->head;

  logToFileAndConsole("Here are the List contents: ");

  while (currentNode != nullptr) {
    currentNode->printNode();
    currentNode = currentNode->next;
  };
  // Pointers should hopefully end up as null pointers after loop

  logToFileAndConsole("End of List");
}; ///< Prints the list from head to tail.

/**
 * @brief Print the the contents of the list from the tail to the head of the
 * list. The direction is the reverse of printNode()
 *
 */
void DoublyLinkedList::reversePrintList() {
  DllNode *currentNode = this->tail;

  logToFileAndConsole("Here are the List contents: ");
  while (currentNode != nullptr) {
    currentNode->printNode();
    currentNode = currentNode->prev;
  };
  // Pointers should hopefully end up as null pointers after loop

  logToFileAndConsole("End of List");
}; ///< Prints the list from tail to head.
