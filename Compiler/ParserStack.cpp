#include "ParserStack.h"

// Class to represent a Stack of Parse Tree Nodes

ParseTreeNodeStack::~ParseTreeNodeStack() {
    // Clean up all the nodes in the stack
    while (!nodeStack.empty()) {
        delete nodeStack.top();
        nodeStack.pop();
    }
}

// Push a new node onto the stack
void  ParseTreeNodeStack::push(ParseTreeNode* node) {
    nodeStack.push(node);
}

// Pop a node from the stack
ParseTreeNode* ParseTreeNodeStack::pop() {
    if (nodeStack.empty()) {
        return nullptr;
    }

    ParseTreeNode* topNode = nodeStack.top();
    nodeStack.pop();
    return topNode;
}

// Get the top node from the stack without removing it
ParseTreeNode* ParseTreeNodeStack::top() {
    if (nodeStack.empty()) {
        return nullptr;
    }

    return nodeStack.top();
}

// Check if the stack is empty
bool  ParseTreeNodeStack::isEmpty() const {
    return nodeStack.empty();
}

