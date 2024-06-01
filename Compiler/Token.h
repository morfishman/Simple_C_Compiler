//#pragma once
//#include "_TokenDefinitions.h"
//#include "ParserTree.h"
//
//
//class Token : public ParseNodeData {
//public:
//    std::string tokenValue;
//    TokenType tokenType;
//    size_t serialNumber;
//
//public:
//    Token(const std::string& value, TokenType type, size_t serialNumber)
//        : tokenValue(value), tokenType(type), serialNumber(serialNumber) {}
//
//    const std::string& getValue() const {
//        return tokenValue;
//    }
//
//    TokenType getType() const {
//        return tokenType;
//    }
//
//    size_t getSerialNumber() const {
//        return serialNumber;
//    }
//
//    // Implementation of the print function from the base class
//    void print() const override {
//        std::cout << "Token Value: " << tokenValue
//            << ", Token Type: " << allTokenStringsMap[tokenType]
//            << ", Serial Number: " << serialNumber << std::endl;
//    }
//
//};


#pragma once

#include <iostream>
#include <string>
#include "_TokenDefinitions.h"
#include "ParserTree.h"

class Token : public ParseNodeData {
public:
    std::string tokenValue;
    TokenType tokenType;
    size_t serialNumber;
    size_t line_number;


public:
    Token(const std::string& value, TokenType type, size_t serialNumber);

    const std::string& getValue() const;
    TokenType getType() const;
    size_t getSerialNumber() const;

    // Implementation of the print function from the base class
    void print() const override;
};
