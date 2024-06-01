#include "SymbalTable.h"



GenericSymbal::GenericSymbal(std::string name, TokenType* type) : name(name), type(type), scope(nullptr), orderNumber(0) {}
    
Identifer::Identifer(std::string name, TokenType* type) : GenericSymbal(name, type) {}

Function::Function(std::string name, TokenType* returnType, std::vector<TokenType*>* passedTypes) : GenericSymbal(name, returnType), passedTypes(passedTypes) {}



int SymbalTable::getIdNum() {
    if (number_of_identifiers != -1) return number_of_identifiers;
    for (size_t i = 0; i < this->tokensInScope->size(); i++)
    {
        Identifer* Id = dynamic_cast<Identifer*>((*(this->tokensInScope))[i]);
        if (Id != nullptr)number_of_identifiers++;
    }
    return ++number_of_identifiers;
}

SymbalTable::SymbalTable() : number_of_identifiers(-1), param_known(0),scope_found(0), currentScope(0), used_space(0), found(0) {
        perent = nullptr;
        tokensInScope = new std::vector<GenericSymbal*>();
        lowerScops = new std::vector<SymbalTable*>();
    } // Constructor

int SymbalTable::calculateMatchAccuracy(Function* func, std::vector<TokenType*>* passed_params) {
        // Get the parameters of the function
        std::vector<TokenType*>* funcParams = func->passedTypes;
        if (funcParams->size() != passed_params->size())return -1;
        // Convert passed parameter types to a bit representation
        int passedParamBit = 0;
        for (size_t i = 0; i < passed_params->size(); ++i) {
            if (*((*passed_params)[i]) != *((*funcParams)[i])) {
                int temp = 1;
                temp <<= (passed_params->size() - i);
                passedParamBit |= temp;
            }
        }
        return passedParamBit; // Return the accuracy value
    }



    bool SymbalTable::IsNameTaken(Token* token) {
        // Variables to store the best match found so far
        std::string str = token->getValue();
        for (GenericSymbal* token : *tokensInScope) {
            Function* func = dynamic_cast<Function*>(token);
            if (token->name == str)
            {
                return true;
            }
        }
        return false;
    }

    bool SymbalTable::IsNameTakenInLowerScopes(Token* tokener, int scope_level) {
        if (scope_level <= currentScope) {
            return false;
        }
        std::string str = tokener->getValue();
        // First search in the current scope
        bool token = IsNameTaken(tokener);
        if (token) {
            return token;
        }


        for (SymbalTable* lowerScope : *lowerScops) {
            bool token2 = lowerScope->IsNameTakenInLowerScopes(tokener, scope_level);
            if (token2 == false)
                continue;
            return token2;
        }

        return false;
    }




    GenericSymbal* SymbalTable::searchFunction(Token* token, std::vector<TokenType*>* passed_params) {
        // Variables to store the best match found so far
        std::string str = token->getValue();
        for (GenericSymbal* token : *tokensInScope) {
            Function* func = dynamic_cast<Function*>(token);
            if (func != nullptr && token->name == str &&
                !((TokenType::VOID != *(token->type) && *(func->type) == TokenType::VOID) ||
                    (TokenType::VOID == *(token->type) && *(func->type) != TokenType::VOID)))
            {
                int accuracy = calculateMatchAccuracy(func, passed_params);
                if (accuracy < 0) return nullptr;
                if (accuracy >= 0) {
                    return func;
                }
            }
        }
        return nullptr;
    }


    GenericSymbal* SymbalTable::searchIdentifier(const std::string& str) {
        for (GenericSymbal* token : *tokensInScope) {
            if (dynamic_cast<Identifer*>(token) != nullptr) {
                if (token->name == str) {
                    return token;
                }
            }
        }
        return nullptr; // Not found
    }

    void SymbalTable::addToken(GenericSymbal* name) {
        tokensInScope->push_back(name);
        name->scope = this;
        name->orderNumber = tokensInScope->size() - 1;
    }

    SymbalTable* SymbalTable::newScope() {
        SymbalTable* s = new SymbalTable();
        s->currentScope = this->currentScope + 1;
        lowerScops->push_back(s);
        s->perent = this;
        if (s->currentScope == 1) {
            s->function_number = this->tokensInScope->size();
        }
        else {
            s->function_number = this->function_number;
        }
        return s;
    }

    GenericSymbal* SymbalTable::searchFunctionInLowerScopes(Token* tokener, int scope_level, std::vector<TokenType*>* passed_params) {
        if (scope_level <= currentScope) {
            return nullptr;
        }
        std::string str = tokener->getValue();
        // First search in the current scope
        GenericSymbal* token = searchFunction(tokener, passed_params);
        if (token != nullptr) {
            return token;
        }


        for (SymbalTable* lowerScope : *lowerScops) {
            GenericSymbal* token2 = lowerScope->searchFunctionInLowerScopes(tokener, scope_level, passed_params);
            if (token2 == nullptr)
                continue;
            return token2;
        }

        return nullptr;
    }

    GenericSymbal* SymbalTable::searchIdentifierInLowerScopes(const std::string& str, int scope_level,int fn) {
        if (currentScope == 0) {
            GenericSymbal* token;
            for (SymbalTable* lowerScope : *lowerScops) {
                token = lowerScope->searchIdentifierInLowerScopes(str, scope_level, fn);
                if (token != nullptr) {
                    return token;
                }
            }
            return nullptr; // Not found in any scope
        }
        if (scope_level <= currentScope || fn != function_number) {
            return nullptr;
        }
        // First search in the current scope
        GenericSymbal* token = searchIdentifier(str);
        if (token != nullptr) {
            return token;
        }
        // If not found, search in lower scopes recursively
        for (SymbalTable* lowerScope : *lowerScops) {
            token = lowerScope->searchIdentifierInLowerScopes(str, scope_level,fn);
            if (token != nullptr) {
                return token;
            }
        }
        return nullptr; // Not found in any scope
    }





