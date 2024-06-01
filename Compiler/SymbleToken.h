#pragma once
#include "_TokenDefinitions.h"
#include "ParserTree.h"
#include <unordered_map>



class SymbleTokens : public ParseNodeData {
private:
    std::unordered_map<std::string,TokenType> SymbalMap;
public:
    SymbleTokens()
        : SymbalMap(NULL) {}

    TokenType getType(const std::string& identifierName) const {
        if (SymbalMap.find(identifierName) == SymbalMap.end()) {
            return TokenType::ERROR;
        }
        else {
            return SymbalMap.find(identifierName)->second;
        }
    }

    void print() const override {
        std::cout << "Symbol Tokens:" << std::endl;
        for (const auto& pair : SymbalMap) {
            std::cout << "Identifier: " << pair.first << ", TokenType: " << allTokenStringsMap[pair.second] << std::endl;
        }
    }

};
