//#pragma once
//#include "ParserPreset.h"
//#include "_TokenDefinitions.h"
//#include <string>
//#include <iostream>
//#include <vector>
//
//// Base class for data associated with parse tree nodes
//class ParseNodeData {
//public:
//    // Virtual destructor to ensure proper cleanup
//    virtual ~ParseNodeData() {}
//    // Pure virtual function for printing node data
//    virtual void print() const = 0;
//};
//
//// Class to represent Non-Terminal Data
//class NonTerminalData : public ParseNodeData {
//public:
//    NonTerminal nonTerminalType;
//
//public:
//    NonTerminalData(NonTerminal type) : nonTerminalType(type) {}
//
//    NonTerminal getType() const {
//        return nonTerminalType;
//    }
//
//    void print() const override {
//        std::cout << "NonTerminal: " << nonTerminalNames[nonTerminalType] << std::endl;
//    }
//};
//
//// TreeNode class
//class TreeNode {
//public:
//    virtual void print(int depth) const = 0;
//    virtual ~TreeNode() {}
//};
//
//// Class to represent a Node in the Parse Tree
//class ParseTreeNode : public TreeNode {
//private:
//    ParseNodeData* data;
//    int stateNumber;
//    std::vector<ParseTreeNode*> childrens;
//    bool side;
//    TokenType* type;
//    int maxdepgh;
//
//public:
//    int register_number;
//    ParseTreeNode(ParseNodeData* nodeData, int stateNumber) : data(nodeData), stateNumber(stateNumber) {
//        side = true;
//        register_number = 0;
//        type = nullptr;
//        maxdepgh = -1;
//    }
//
//    TokenType* getType() {
//        return type;
//    }
//
//    void setType(TokenType t) {
//        type = new TokenType(t);
//    }
//
//    int getMaxDepgh() {
//        if (maxdepgh >= 0)return maxdepgh;
//        int number = getMaxDepgh(this);
//        maxdepgh = number;
//        return number;
//    }
//    int getMaxDepgh(ParseTreeNode* p) {
//        if (maxdepgh >= 0)return maxdepgh;
//        int returnal = 0;
//        for (ParseTreeNode* ptn : p->getChildrens()) {
//            int temp = getMaxDepgh(ptn);
//            if (returnal < temp) {
//                returnal = temp;
//            }
//        }
//        p->maxdepgh = returnal;
//        return returnal+1;
//
//    }
//
//    ~ParseTreeNode() {
//        for (auto child : childrens) {
//            delete child;
//        }
//        delete data;
//    }
//
//    std::vector<ParseTreeNode*> getChildrens() {
//        if (side) {
//            std::reverse(childrens.begin(), childrens.end());
//            side = false;
//        }
//        return childrens;
//    }
//
//    int getStateNumber() const {
//        return stateNumber;
//    }
//
//    void setStateNumber(int newState) {
//        this->stateNumber = newState;
//    }
//
//    ParseNodeData* getData() const {
//        return data;
//    }
//
//    void addChild(ParseTreeNode* child) {
//        childrens.push_back(child);
//    }
//
//    void PrintNode(int indentation = 0) const {
//        // Print the indentation for the current depth
//        for (int i = 0; i < indentation; ++i) {
//            std::cout << "|   ";
//        }
//
//        // Print the branch symbol and the data
//        std::cout << "|-- " + (type != nullptr ? " type: " + tokenStringsMap[*type]  + ", ": "");
//        data->print();
//        std::cout << std::endl;
//        // Recursively print the children nods in reverse order
//        std::vector<ParseTreeNode*> it = childrens;
//        for (int count = 0; count < it.size(); ++count) {
//            it[count]->PrintNode(indentation + 1);
//        }
//    }
//
//    void print(int depth = 0) const override {
//        PrintNode(depth);
//    }
//};
//
//// Class to represent the Parse Tree
//class ParseTree {
//private:
//    ParseTreeNode* root;
//
//public:
//    ParseTree() : root(nullptr) {}
//
//    ~ParseTree() {
//        delete root;
//    }
//
//    void setRoot(ParseTreeNode* node) {
//        root = node;
//    }
//
//    void print() const {
//        if (root) {
//            root->print();
//        }
//    }
//};
#pragma once
#include "ParserPreset.h"
#include "_TokenDefinitions.h"
#include <iostream>
#include <vector>

// Base class for data associated with parse tree nodes
class ParseNodeData {
public:
    // Virtual destructor to ensure proper cleanup
    virtual ~ParseNodeData() {}
    // Pure virtual function for printing node data
    virtual void print() const = 0;
};

// Class to represent Non-Terminal Data
class NonTerminalData : public ParseNodeData {
public:
    NonTerminal nonTerminalType;

public:
    NonTerminalData(NonTerminal type) : nonTerminalType(type) {}

    NonTerminal getType() const {
        return nonTerminalType;
    }

    void print() const override {
        std::cout << "NonTerminal: " << nonTerminalNames[nonTerminalType] << std::endl;
    }
};

// TreeNode class
class TreeNode {
public:
    virtual void print(int depth) const = 0;
    virtual ~TreeNode() {}
};

// Class to represent a Node in the Parse Tree
class ParseTreeNode : public TreeNode {
private:
    ParseNodeData* data;
    int stateNumber;
    std::vector<ParseTreeNode*> childrens;
    bool side;
    TokenType* type;
    int maxdepgh;
    int line_number;

public:
    int register_number;
    ParseTreeNode(ParseNodeData* nodeData, int stateNumber);
    TokenType* getType();
    void setType(TokenType t);
    int getMaxDepgh();
    int getMaxDepgh(ParseTreeNode* p);
    int get_line_number();
    int get_line_number(ParseTreeNode* p);
    ~ParseTreeNode();
    std::vector<ParseTreeNode*> getChildrens();
    int getStateNumber() const;
    void setStateNumber(int newState);
    ParseNodeData* getData() const;
    void addChild(ParseTreeNode* child);
    void PrintNode(int indentation = 0) const;
    void print(int depth = 0) const override;
};

// Class to represent the Parse Tree
class ParseTree {
private:
    ParseTreeNode* root;

public:
    ParseTree();
    ~ParseTree();
    void setRoot(ParseTreeNode* node);
    void print() const;
};
