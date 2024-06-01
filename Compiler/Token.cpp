#include "Token.h"


// Assuming allTokenStringsMap is defined somewhere in your project
extern std::unordered_map<TokenType, std::string> allTokenStringsMap;

Token::Token(const std::string& value, TokenType type, size_t serialNumber)
    : tokenValue(value), tokenType(type), serialNumber(serialNumber) {}

const std::string& Token::getValue() const {
    return tokenValue;
}

TokenType Token::getType() const {
    return tokenType;
}

size_t Token::getSerialNumber() const {
    return serialNumber;
}

void Token::print() const {
    std::cout << "Token Value: " << tokenValue
        << ", Token Type: " << allTokenStringsMap[tokenType]
        << ", Serial Number: " << serialNumber << std::endl;
}
