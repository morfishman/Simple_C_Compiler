#include "ParserTable.h"
#include "Token.h"

ParseTreeNode::ParseTreeNode(ParseNodeData* nodeData, int stateNumber) : data(nodeData), stateNumber(stateNumber) {
    side = true;
    register_number = 0;
    type = nullptr;
    maxdepgh = -1;
    line_number = -1;
}

ParseTreeNode::~ParseTreeNode() {
    for (auto child : childrens) {
        delete child;
    }
    delete data;
}

int ParseTreeNode::get_line_number() {
    if (line_number != -1)return line_number;
    return get_line_number(this);
}
int ParseTreeNode::get_line_number(ParseTreeNode* p) {
    if (p->line_number != -1)return p->line_number;
    if (p->getChildrens().size() == 0) {
        p->line_number = dynamic_cast<Token*>(p->getData())->line_number;
        return p->line_number;
    }
    for (ParseTreeNode* ptn : p->getChildrens()) {
        int temp = get_line_number(ptn);
        if (temp == -1) {
            p->line_number = -1;
            return temp;
        }
        if (p->line_number == -1) {
            p->line_number = temp;
        }
        else {
            if (p->line_number != temp) {
                p->line_number = -1;
                return p->line_number;
            }
        }
    }
    return p->line_number;
}

TokenType* ParseTreeNode::getType() {
    return type;
}

void ParseTreeNode::setType(TokenType t) {
    type = new TokenType(t);
}

int ParseTreeNode::getMaxDepgh() {
    if (maxdepgh >= 0)return maxdepgh;
    int number = getMaxDepgh(this);
    maxdepgh = number;
    return number;
}

int ParseTreeNode::getMaxDepgh(ParseTreeNode* p) {
    if (maxdepgh >= 0)return maxdepgh;
    int returnal = 0;
    for (ParseTreeNode* ptn : p->getChildrens()) {
        int temp = getMaxDepgh(ptn);
        if (returnal < temp) {
            returnal = temp;
        }
    }
    p->maxdepgh = returnal;
    return returnal + 1;
}

std::vector<ParseTreeNode*> ParseTreeNode::getChildrens() {
    if (side) {
        std::reverse(childrens.begin(), childrens.end());
        side = false;
    }
    return childrens;
}

int ParseTreeNode::getStateNumber() const {
    return stateNumber;
}

void ParseTreeNode::setStateNumber(int newState) {
    this->stateNumber = newState;
}

ParseNodeData* ParseTreeNode::getData() const {
    return data;
}

void ParseTreeNode::addChild(ParseTreeNode* child) {
    childrens.push_back(child);
}

void ParseTreeNode::PrintNode(int indentation) const {
    // Print the indentation for the current depth
    for (int i = 0; i < indentation; ++i) {
        std::cout << "|   ";
    }

    // Print the branch symbol and the data
    std::cout << "|-- " + (type != nullptr ? " type: " + tokenStringsMap[*type] + ", " : "");
    data->print();
    std::cout << std::endl;
    // Recursively print the children nods in reverse order
    std::vector<ParseTreeNode*> it = childrens;
    for (int count = 0; count < it.size(); ++count) {
        it[count]->PrintNode(indentation + 1);
    }
}

void ParseTreeNode::print(int depth) const {
    PrintNode(depth);
}

ParseTree::ParseTree() : root(nullptr) {}

ParseTree::~ParseTree() {
    delete root;
}

void ParseTree::setRoot(ParseTreeNode* node) {
    root = node;
}

void ParseTree::print() const {
    if (root) {
        root->print();
    }
}
