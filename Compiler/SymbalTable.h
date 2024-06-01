//#pragma once
//#include "ParserTree.h"
//#include "_TokenDefinitions.h"
//#include <string>
//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <algorithm>
//#include <functional>
//
//
//class SymbalTable;
//
//class GenericSymbal {
//public:
//    std::string name;
//    TokenType* type;
//    SymbalTable* scope;
//    int orderNumber;
//    std::string* address;
//
//
//    GenericSymbal(std::string name, TokenType* type) : name(name), type(type), scope(nullptr), orderNumber(0) {}
//    virtual ~GenericSymbal() {} // Make the base class polymorphic
//};
//
//
//// Derive Identifer from the common base class
//class Identifer : public GenericSymbal {
//public:
//    Identifer(std::string name, TokenType* type) : GenericSymbal(name, type) {}
//};
//
//// Derive Function from the common base class
//class Function : public GenericSymbal {
//public:
//    std::vector<TokenType*>* passedTypes;
//
//    Function(std::string name, TokenType* returnType, std::vector<TokenType*>* passedTypes) : GenericSymbal(name, returnType), passedTypes(passedTypes) {}
//};
//
//
//
//class SymbalTable {
//public:
//    std::vector<GenericSymbal*>* tokensInScope;
//    int currentScope;
//    std::vector<SymbalTable*>* lowerScops;
//    SymbalTable* perent;
//    int used_space;
//    int found;
//    int scope_found;
//
//    SymbalTable() : scope_found(0),currentScope(0), used_space(0), found(0){
//        perent = nullptr;
//        tokensInScope = new std::vector<GenericSymbal*>();
//        lowerScops = new std::vector<SymbalTable*>();
//    } // Constructor
//     
//    int calculateMatchAccuracy(Function* func, std::vector<TokenType*>* passed_params) {
//        // Get the parameters of the function
//        std::vector<TokenType*>* funcParams = func->passedTypes;
//        if (funcParams->size() != passed_params->size())return -1;
//        // Convert passed parameter types to a bit representation
//        int passedParamBit = 0;
//        for (size_t i = 0; i < passed_params->size(); ++i) {
//            if (*((*passed_params)[i]) != *((*funcParams)[i])) {
//                int temp = 1;
//                temp <<= (passed_params->size() - i);
//                passedParamBit |= temp;
//            }           
//        }
//        return passedParamBit; // Return the accuracy value
//    }
//
//  
//    
//    bool IsNameTaken(Token* token) {
//        // Variables to store the best match found so far
//        std::string str = token->getValue();
//        for (GenericSymbal* token : *tokensInScope) {
//            Function* func = dynamic_cast<Function*>(token);
//            if (token->name == str)
//            {
//                return true;
//            }
//        }
//        return false;
//    }
//
//    bool IsNameTakenInLowerScopes(Token* tokener, int scope_level) {
//        if (scope_level <= currentScope) {
//            return false;
//        }
//        std::string str = tokener->getValue();
//        // First search in the current scope
//        bool token = IsNameTaken(tokener);
//        if (token) {
//            return token;
//        }
//
//
//        for (SymbalTable* lowerScope : *lowerScops) {
//            bool token2 = lowerScope->IsNameTakenInLowerScopes(tokener, scope_level);
//            if (token2 == false)
//                continue;
//            return token2;
//        }
//
//        return false;
//    }
//
//
//
//
//    GenericSymbal* searchFunction(Token* token, std::vector<TokenType*>* passed_params) {
//        // Variables to store the best match found so far
//        std::string str = token->getValue();
//        for (GenericSymbal* token : *tokensInScope) {
//            Function* func = dynamic_cast<Function*>(token);
//            if (func != nullptr && token->name == str && 
//                !((TokenType::VOID != *(token->type) && *(func->type) == TokenType::VOID) ||
//                  (TokenType::VOID == *(token->type) && *(func->type) != TokenType::VOID)))
//            {
//                int accuracy = calculateMatchAccuracy(func, passed_params);
//                if (accuracy < 0) return nullptr;
//                if (accuracy >= 0) {
//                    return func;
//                }
//            }
//        }
//        return nullptr;
//    }
//
//
//    GenericSymbal* searchIdentifier(const std::string& str) {
//        for (GenericSymbal* token : *tokensInScope) {
//            if (dynamic_cast<Identifer*>(token) != nullptr) {
//                if (token->name == str) {
//                    return token;
//                }
//            }
//        }
//        return nullptr; // Not found
//    }
//
//    void addToken(GenericSymbal* name) {        
//        tokensInScope->push_back(name);
//        name->scope = this;
//        name->orderNumber = tokensInScope->size() - 1;
//    }
//
//    SymbalTable* newScope() {
//        SymbalTable* s = new SymbalTable();
//        s->currentScope = this->currentScope + 1;
//        lowerScops->push_back(s);
//        s->perent = this;
//        return s;
//    }
//
//    GenericSymbal* searchFunctionInLowerScopes(Token* tokener, int scope_level, std::vector<TokenType*>* passed_params){
//        if (scope_level <= currentScope) {
//            return nullptr;
//        }
//        std::string str = tokener->getValue();
//        // First search in the current scope
//        GenericSymbal* token = searchFunction(tokener, passed_params);
//        if (token != nullptr) {
//            return token;
//        }
//        
//
//        for (SymbalTable* lowerScope : *lowerScops) {
//            GenericSymbal* token2 = lowerScope->searchFunctionInLowerScopes(tokener, scope_level, passed_params);
//            if (token2 == nullptr)
//                continue;
//            return token2;
//        }
//        
//        return nullptr;
//    }
//
//    GenericSymbal* searchIdentifierInLowerScopes(const std::string& str, int scope_level) {
//        if (scope_level <= currentScope) {
//            return nullptr;
//        }
//        // First search in the current scope
//        GenericSymbal* token = searchIdentifier(str);
//        if (token != nullptr) {
//            return token;
//        }
//        // If not found, search in lower scopes recursively
//        for (SymbalTable* lowerScope : *lowerScops) {
//            token = lowerScope->searchIdentifierInLowerScopes(str, scope_level);
//            if (token != nullptr) {
//                return token;
//            }
//        }
//        return nullptr; // Not found in any scope
//    }
//
//    
//
//};
//
//


#pragma once
#include "ParserTree.h"
#include "Token.h"
#include "_TokenDefinitions.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>


class SymbalTable;

class GenericSymbal {
public:
    std::string name;
    TokenType* type;
    SymbalTable* scope;
    int orderNumber;
    std::string* address;


    GenericSymbal(std::string name, TokenType* type);
    virtual ~GenericSymbal() {} // Make the base class polymorphic
};


// Derive Identifer from the common base class
class Identifer : public GenericSymbal {
public:
    Identifer(std::string name, TokenType* type);
};

// Derive Function from the common base class
class Function : public GenericSymbal {
public:
    std::vector<TokenType*>* passedTypes;

    Function(std::string name, TokenType* returnType, std::vector<TokenType*>* passedTypes);
};



class SymbalTable {
public:
    std::vector<GenericSymbal*>* tokensInScope;
    int currentScope;
    std::vector<SymbalTable*>* lowerScops;
    SymbalTable* perent;
    int used_space;
    int param_known;
    int found;
    int scope_found;
    int number_of_identifiers;
    int function_number;
    SymbalTable();
    int calculateMatchAccuracy(Function* func, std::vector<TokenType*>* passed_params);
    int getIdNum();
    bool IsNameTaken(Token* token);
    bool IsNameTakenInLowerScopes(Token* tokener, int scope_level);
    GenericSymbal* searchFunction(Token* token, std::vector<TokenType*>* passed_params);
    GenericSymbal* searchIdentifier(const std::string& str);
    void addToken(GenericSymbal* name);
    SymbalTable* newScope();
    GenericSymbal* searchFunctionInLowerScopes(Token* tokener, int scope_level, std::vector<TokenType*>* passed_params);
    GenericSymbal* searchIdentifierInLowerScopes(const std::string& str, int scope_level, int fn);
};


