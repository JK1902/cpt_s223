#ifndef TEMPLATE_CLASSES_HPP
#define TEMPLATE_CLASSES_HPP
// **************************************************************************************
// CLASS TEMPLATES: Node & List
// **************************************************************************************
//
// TEMPLATE FOR <Node>:
// **************************************************************************************
template <typename DATATYPE>
class Node {
 public:
  DATATYPE *unitNodeData;
  Node<DATATYPE> *next;

  // CONSTRUCTOR:
  Node() {
    unitNodeData = nullptr;
    next = nullptr;
  }
  bool operator==(Node<DATATYPE> &) const;
};

template <typename DATATYPE>
bool Node<DATATYPE>::operator==(Node<DATATYPE> &right) const {
  if (*unitNodeData == right.*unitNodeData)
    return true;
  else
    return false;
}
//
// TEMPLATE FOR <List>:
// **************************************************************************************
template <typename NODETYPE>
class List {
 private:
  NODETYPE *head;
  int listSize;

 public:
  // CONSTRUCTOR:
  List() {
    head = nullptr;
    listSize = 0;
  }
  // DESTRUCTOR:
  ~List();

  // MEMBER FUNCTIONS:
  void appendNode(NODETYPE &);
  bool isNode(NODETYPE &);
  void deleteNode(NODETYPE &);
  NODETYPE *getListHead() const;
  int getListSize() const;
};
//
//
// **************************************************************************************
// TEMPLATE CLASS LIST'S MEMBER FUNCTIONS
// **************************************************************************************
//
// APPEND A NEW NODE AT THE END OF THE LIST:
// **************************************************************************************
template <typename NODETYPE>
void List<NODETYPE>::appendNode(NODETYPE &newData) {
  NODETYPE *newNode;
  NODETYPE *nodePtr;

  newNode = new NODETYPE;
  newNode = &newData;

  // if head is empty, replace head with newNode. Otherwise append to the end.
  if (!head)
    head = newNode;
  else {
    nodePtr = head;
    while (nodePtr->next) nodePtr = nodePtr->next;

    nodePtr->next = newNode;
  }
  listSize += 1;
}
//
// SEARCH THE LIST FOR A PARTICULAR NODE:
// **************************************************************************************
template <typename NODETYPE>
bool List<NODETYPE>::isNode(NODETYPE &searched) {
  NODETYPE *nodePtr;
  NODETYPE *tempNode;

  tempNode = new NODETYPE;
  tempNode = &searched;

  if (!head)
    return 0;

  else {
    nodePtr = head;
    while (nodePtr->next) {
      if (nodePtr->unitNodeData == searched.unitnodeData) return 1;
      nodePtr = nodePtr->next;
    }
    if (nodePtr->next == nullptr) return 0;
  }
}
//
// DELETE A PARTICULAR NODE WITH AT A PARTICULAR ORDER:
// **************************************************************************************
template <typename NODETYPE>
void List<NODETYPE>::deleteNode(NODETYPE &searchedCmd) {
  NODETYPE *nodePtr;
  NODETYPE *previousNode;

  // if head is empty, terminate algorithm.
  if (!head) return;

  // if searched value matches head, delete head.
  if (head->unitNodeData == searchedCmd.unitNodeData) {
    nodePtr = head->next;
    delete head;
    head = nodePtr;
  }
  // otherwise, keep searching until a match is found, then delete.
  else {
    nodePtr = head;

    while (nodePtr != nullptr &&
           nodePtr->unitNodeData != searchedCmd.unitNodeData) {
      previousNode = nodePtr;
      nodePtr = nodePtr->next;
    }
    if (nodePtr) {
      previousNode->next = nodePtr->next;
      delete nodePtr;
    }
  }
  listSize -= 1;
}
//
// GET THE HEAD OF THE LIST:
// **************************************************************************************
template <typename NODETYPE>
NODETYPE *List<NODETYPE>::getListHead() const {
  return head;
}
//
// GET THE SIZE OF THE LIST:
// **************************************************************************************
template <typename NODETYPE>
int List<NODETYPE>::getListSize() const {
  return listSize;
}
//
// DESTRUCT THE LIST FROM MEMORY, ALSO UPDATE COMMANDS.CSV WHILE AT IT.
// **************************************************************************************
template <typename NODETYPE>
List<NODETYPE>::~List() {
  NODETYPE *nodePtr;
  NODETYPE *nextNode;

  nodePtr = head;

  while (nodePtr != nullptr) {
    nextNode = nodePtr->next;
    delete nodePtr;
    nodePtr = nextNode;
  }
}
#endif
