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
#include "json.hpp"

DoublyLinkedList::DoublyLinkedList() {

} ///< Constructor: Initializes an empty list.
DoublyLinkedList::~DoublyLinkedList() {

}; ///< Destructor: Deletes all nodes.

bool DoublyLinkedList::isEmpty() {return false;};               ///< Checks if the list is empty.
void DoublyLinkedList::insertAtHead(int key) {};   ///< Inserts a node at the head.
void DoublyLinkedList::insertAtTail(int key) {};   ///< Inserts a node at the tail.
void DoublyLinkedList::remove(int key) {};         ///< Removes a node with a specific key.
void DoublyLinkedList::removeHeaderNode() {};      ///< Removes the head node.
void DoublyLinkedList::removeTailNode() {};        ///< Removes the tail node.
void DoublyLinkedList::moveNodeToHead(int key){}; ///< Moves a node to the head.
void DoublyLinkedList::moveNodeToTail(int key){}; ///< Moves a node to the tail.
void DoublyLinkedList::clear(){};                 ///< Deletes all nodes.
void DoublyLinkedList::printList(){};             ///< Prints the list from head to tail.
void DoublyLinkedList::reversePrintList(){};      ///< Prints the list from tail to head.
