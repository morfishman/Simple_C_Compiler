#pragma once
#include "ParserTree.h"
#include <stack>

// Class to represent a Stack of Parse Tree Nodes
class ParseTreeNodeStack {
private:
    std::stack<ParseTreeNode*> nodeStack;

public:
    ~ParseTreeNodeStack();
    // Push a new node onto the stack
    void push(ParseTreeNode* node);

    // Pop a node from the stack
    ParseTreeNode* pop();

    // Get the top node from the stack without removing it
    ParseTreeNode* top();

    // Check if the stack is empty
    bool isEmpty() const;
};
