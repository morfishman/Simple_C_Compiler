//#pragma once
//#include "ParserTree.h"
//#include "Token.h"
//#include "SymbalTable.h"
//#include <string>
//#include <iostream>
//#include <vector>
//#include <stack>
//#include <unordered_map>
//#include <functional>
//#include <algorithm> 
//using NonTerminalFunction = std::function<bool(ParseTreeNode&, SymbalTable&)>;
//
//class SymanticAnalaser {
//private:
//    // Functions for the Functions Map
//
//    GenericSymbal* IdentifierInSymbalTable(SymbalTable& sTable, Token* token) {
//        GenericSymbal* returnal = sTable.searchIdentifier(token->getValue());
//        returnal = returnal == nullptr ? symbalTable->searchIdentifierInLowerScopes(token->getValue(), sTable.currentScope):returnal;
//        return returnal;
//    }
//
//    GenericSymbal* FunctionInSymbalTable(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param,int state) {
//        GenericSymbal* returnal = sTable.searchFunction(token,passed_param);
//        returnal = returnal == nullptr ? symbalTable->searchFunctionInLowerScopes(token, sTable.currentScope, passed_param) : returnal;
//        return returnal;
//    }
//    bool FunctionName(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param, int state) {
//        bool returnal = sTable.IsNameTaken(token);
//        returnal = returnal == false ? symbalTable->IsNameTakenInLowerScopes(token, sTable.currentScope) : returnal;
//        return returnal;
//    }
//    
//    TokenType* RETURN_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (!childrens.empty()) {
//            if (Token* t = dynamic_cast<Token*>(childrens[0]->getData())) {
//                TokenType* typePtr = new TokenType(t->getType());
//                return typePtr;
//            }
//        }
//        return nullptr;
//    }
//
//    bool DECLERATION(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// 
//        ///     DECLERATION:
//        ///     /           \
//        /// Return_TYPE    identifer
//        /// </summary>
//
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (IdentifierInSymbalTable(sTable, dynamic_cast<Token*>(childrens[1]->getData())) != nullptr) {
//            return false;
//        }
//        TokenType* type = RETURN_TYPE(*childrens[0] , sTable);
//        Identifer* tempGenericSymbal = new Identifer(dynamic_cast<Token*>(childrens[1]->getData())->getValue(), type);
//        sTable.addToken(tempGenericSymbal);
//        return true;
//    }
//    
//    TokenType* F(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* emptyType) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            if (!childrens.empty()) {
//                if (Token* t = dynamic_cast<Token*>(ptn->getData())) {
//                    GenericSymbal* gos;
//                    switch (t->getType())
//                    {
//                    case TokenType::IDENTIFIER:
//                        gos = IdentifierInSymbalTable(sTable, t);
//                        if (gos != nullptr) {
//                            treeNode.setType(*(gos->type));
//                            return gos->type;
//                        }
//                        else {
//                            return nullptr;
//                        }
//                    case TokenType::NUMERIC:
//                        treeNode.setType(TokenType::INT);
//                        return new TokenType(TokenType::INT);
//                    case TokenType::CHAR_LITTERAL:
//                        treeNode.setType(TokenType::CHAR);
//                        return new TokenType(TokenType::CHAR);
//                    case TokenType::LEFT_BRACKET:
//                        break;
//                    default:
//                        return nullptr;
//                    }
//                }
//                else {
//                    ///need code
//                    NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//                    TokenType* gs;
//                    switch (ntd->getType())
//                    {
//                    case NonTerminal::FUNC_CALL:
//                        gs = FUNC_CALL_CHECK(*ptn, sTable);
//                        if (gs != nullptr) {
//                            treeNode.setType(*gs);
//                            return gs;
//                        }
//                        else {
//                            return nullptr;
//                        }
//                    case NonTerminal::POST_ONARY_ARITMATIC:
//                        gs = POST_ONARY_ARITMATIC(*ptn, sTable);
//                        if (gs != nullptr) {
//                            treeNode.setType(*gs);
//                            return gs;
//                        }
//                        else {
//                            return nullptr;
//                        }
//
//                    case NonTerminal::PRE_ONARY_ARITMATIC:
//                        gs = PRE_ONARY_ARITMATIC(*ptn, sTable);
//                        if (gs != nullptr) {
//                            treeNode.setType(*gs);
//                            return gs;
//                        }
//                        else {
//                            return nullptr;
//                        }
//                    case NonTerminal::ARITMATIC:                            
//                        gs = COMPUTING_EXPRETION(*ptn, sTable, emptyType);
//                        treeNode.setType(*gs);
//                        return gs;
//
//                    default:
//                        break;
//                    }
//
//                }
//            }
//        }
//        return nullptr;
//    }
//
//    TokenType* POST_ONARY_ARITMATIC(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (!childrens.empty()) {
//            if (Token* t = dynamic_cast<Token*>(childrens[1]->getData())) {
//                GenericSymbal* gs;
//                switch (t->getType())
//                {
//                case TokenType::IDENTIFIER:
//                    gs = IdentifierInSymbalTable(sTable, t);
//                    if (gs != nullptr) {
//                        if (*(gs->type) != TokenType::INT) {
//                            return nullptr;
//                        }
//                        else {
//                            return gs->type;
//                        }
//
//                    }
//                    else {
//                        return nullptr;
//                    }
//                default:
//                    return nullptr;
//                }
//            }
//            else {
//                return nullptr;
//            }
//        }
//        return nullptr;
//    }
//    TokenType* PRE_ONARY_ARITMATIC(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (!childrens.empty()) {
//            if (Token* t = dynamic_cast<Token*>(childrens[0]->getData())) {
//                GenericSymbal* gs;
//                switch (t->getType())
//                {
//                case TokenType::IDENTIFIER:
//                    gs = IdentifierInSymbalTable(sTable, t);
//                    if (gs != nullptr) {
//                        if (*(gs->type) != TokenType::INT) {
//                            return nullptr;
//                        }
//                        else {
//                            return gs->type;
//                        }
//
//                    }
//                    else {
//                        return nullptr;
//                    }
//                default:
//                    return nullptr;
//                }
//            }
//            else {
//                return nullptr;
//            }
//        }
//        return nullptr;
//    }
//
//    bool POST_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (!childrens.empty()) {
//            if (Token* t = dynamic_cast<Token*>(childrens[1]->getData())) {
//                GenericSymbal* gs;
//                switch (t->getType())
//                {
//                case TokenType::IDENTIFIER:
//                    gs = IdentifierInSymbalTable(sTable, t);
//                    if (gs != nullptr) {
//                        if (*(gs->type) != TokenType::INT) {
//                            return false;
//                        }
//                        else {
//                            return gs->type;
//                        }
//
//                    }
//                    else {
//                        return false;
//                    }
//                default:
//                    return false;
//                }
//            }
//            else {
//                return false;
//            }
//        }
//        return false;
//    }
//    bool PRE_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (!childrens.empty()) {
//            if (Token* t = dynamic_cast<Token*>(childrens[0]->getData())) {
//                GenericSymbal* gs;
//                switch (t->getType())
//                {
//                case TokenType::IDENTIFIER:
//                    gs = IdentifierInSymbalTable(sTable, t);
//                    if (gs != nullptr) {
//                        if (*(gs->type) != TokenType::INT) {
//                            return false;
//                        }
//                        else {
//                            return gs->type;
//                        }
//
//                    }
//                    else {
//                        return false;
//                    }
//                default:
//                    return false;
//                }
//            }
//            else {
//                return false;
//            }
//        }
//        return false;
//    }
//
//
//
//    bool VAL_CHANGE_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (childrens.size() == 1) {
//            if (NonTerminalData* nonterminal = dynamic_cast<NonTerminalData*>(childrens[0]->getData())) {
//                NonTerminalFunction func = (*functionMap)[nonterminal->getType()];
//                bool result = func(*childrens[0], sTable);
//                if (!result) {
//                    //rais the right heandle for declaration error;
//                    return false;
//                }
//                else {
//                    return true;
//                }
//            }
//            else {
//                return false;
//            }
//        }
//        else {
//            TokenType* leftType = nullptr;
//            TokenType* rightType = nullptr;
//            Token* identifiertoken = dynamic_cast<Token*>(childrens[0]->getData());
//            GenericSymbal* result = IdentifierInSymbalTable(sTable, identifiertoken);
//            if (result == nullptr) {
//                //the identifer not exists
//                return false;
//            }
//            else {
//                leftType = result->type;
//            }
//            //computing expretion
//            NonTerminalData* rightNonterminal = dynamic_cast<NonTerminalData*>(childrens[2]->getData());
//            if (rightNonterminal == nullptr) {
//                return false;
//            }
//            rightType = COMPUTING_EXPRETION(*childrens[2], sTable, leftType);
//
//            if (rightType == nullptr)return false;
//
//            return true;
//        }
//        
//    }
//
//
//
//    //with return type for the expretion calc....
//    TokenType* FUNC_CALL_CHECK(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        //param vector
//        std::vector<TokenType*>* returnal = new std::vector<TokenType*>();
//        if (childrens.size() > 3) {
//            PASSED_PARAMS(*childrens[2], sTable, returnal);
//            if (returnal == nullptr) {
//                return nullptr;
//            }
//        }
//        //
//        GenericSymbal* func = FunctionInSymbalTable(sTable, dynamic_cast<Token*>(childrens[0]->getData()), returnal,1);
//        if (func == nullptr) {
//            return nullptr;
//        }
//        return dynamic_cast<Function*>(func)->type;
//    }
//    //not with return type for the line stmt...
//    bool FUNC_CALL(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        //param vector
//        std::vector<TokenType*>* returnal = new std::vector<TokenType*>();
//        if (childrens.size() > 3) {
//            PASSED_PARAMS(*childrens[2], sTable, returnal);
//            if (returnal == nullptr) {
//                return false;
//            }
//        }
//        //
//        GenericSymbal* func = FunctionInSymbalTable(sTable, dynamic_cast<Token*>(childrens[0]->getData()), returnal,1);
//        if (func == nullptr) {
//            return false;
//        }
//        return true;
//    }
//
//
//
//    void PASSED_PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                TokenType* toAdd = nullptr;
//                switch (ntd->getType())
//                {
//
//                case NonTerminal::COMPUTING_EXPRETION:
//                    toAdd = COMPUTING_EXPRETION(*ptn, sTable, new TokenType(TokenType::INT));
//                    if (toAdd == nullptr) {
//                        returnal = nullptr;
//                        return;
//                    }
//                    returnal->push_back(toAdd);
//                    break;
//                case NonTerminal::PASS_PARAM:
//                    PASSED_PARAMS(*ptn, sTable, returnal);
//                    return;
//
//                default:
//                    returnal = nullptr;
//                    return;
//
//                }
//            }
//        }
//
//    }
//
//    // ����� �� �� ���� ����
//    // ������� ���� ����� ��� �� ��� ��� �� �� ���� ����� ��� �������� ������� ����� ������
//    // ����� ���� ���� ������ �� ���� �� ��� �����
//    TokenType* COMPUTING_EXPRETION(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* emptyType) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        TokenType* currentType = emptyType;
//        TokenType* temp;
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::F:
//                    temp = F(*ptn, sTable,emptyType);
//                    if (temp == nullptr)return nullptr;
//                    if (*currentType == TokenType::VOID) {
//                        if (*temp != *currentType) {
//                            return nullptr;
//                        }
//                    }
//                    else {
//                        if (*temp == TokenType::VOID) {
//                            return nullptr;
//                        }
//                    }
//                    break;
//                default:
//                    temp = COMPUTING_EXPRETION(*ptn, sTable, currentType);
//                    if (temp == nullptr)return nullptr;
//                    if (*currentType == TokenType::VOID) {
//                        if (*temp != *currentType) {
//                            return nullptr;
//                        }
//                    }
//                    else {
//                        if (*temp == TokenType::VOID) {
//                            return nullptr;
//                        }
//                    }
//                }
//               
//            }
//        }
//        treeNode.setType(*currentType);
//        return new TokenType(*currentType);
//    }
//
//    bool ASSIGN(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        ///          ASSIGN
//        ///         /      \
//        /// DECLERATION  COMPUTING_EXPRETION
//        /// --------------------------------
//        ///          ASSIGN
//        ///         /      \
//        /// IDENTIFER  COMPUTING_EXPRETION
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        TokenType* leftType = nullptr;
//        TokenType* rightType = nullptr;
//        if (NonTerminalData* nonterminal = dynamic_cast<NonTerminalData*>(childrens[0]->getData())) {
//            NonTerminalFunction func = (*functionMap)[nonterminal->getType()];
//            bool result = func(*childrens[0], sTable);
//            if (!result) {
//                //rais the right heandle for declaration error;
//                return false;
//            }
//            else {
//                leftType = sTable.tokensInScope->back()->type;
//            }
//        }
//        else
//        {
//            Token* identifiertoken = dynamic_cast<Token*>(childrens[0]->getData());
//            GenericSymbal* result = IdentifierInSymbalTable(sTable, identifiertoken);
//            if (result==nullptr) {
//                //the identifer not exists
//                return false;
//            }
//            else {
//                leftType = result->type;
//            }
//
//        }
//        
//        //computing expretion
//        NonTerminalData* rightNonterminal = dynamic_cast<NonTerminalData*>(childrens[2]->getData());
//        if (rightNonterminal == nullptr) {
//            return false;
//        }
//        rightType = COMPUTING_EXPRETION(*childrens[2], sTable, leftType);
//
//        if (rightType == nullptr)return false;
//        
//        return true;
//    }
//
//
//
//
//    //return type;
//    bool RETURN_FUNC(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        SymbalTable* new_scope = RETURN_FUNC_HEAD(*childrens[0], sTable);
//        if (new_scope == nullptr)return false;
//        TokenType* save_type = sTable.tokensInScope->back()->type;
//        if (!SCOPE(*childrens[1], *new_scope, save_type))return false;
//        return true;
//        
//
//
//    }
//
//
//    bool NONE_RETURN_FUNC(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        SymbalTable* new_scope = NONE_RETURN_FUNC_HEAD(*childrens[0], sTable);
//        if (new_scope == nullptr)return false;
//        TokenType* save_type = sTable.tokensInScope->back()->type;
//        if (!SCOPE(*childrens[1], *new_scope, save_type))return false;
//        return true;
//
//
//
//    }
//
//    SymbalTable* NONE_RETURN_FUNC_HEAD(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        TokenType* returnType = new TokenType(TokenType::VOID);
//        Token* identifer = dynamic_cast<Token*>(childrens[1]->getData());
//        std::vector<TokenType*>* returnal = new std::vector<TokenType*>();
//        SymbalTable* temp = sTable.newScope();
//        if (childrens.size() > 4) {
//            SymbalTable& new_stabel = *temp;
//            PARAMS(*childrens[3], new_stabel, returnal);
//            if (returnal->empty()) {
//                return nullptr;
//            }
//
//        }
//        GenericSymbal* func = FunctionInSymbalTable(sTable, identifer, returnal,0);
//        bool taken = FunctionName(sTable, identifer, returnal, 0);
//        if (func != nullptr || taken) {
//            return nullptr;
//        }
//        sTable.addToken(new Function(identifer->tokenValue, returnType, returnal));
//        return temp;
//    }
//
//
//
//
//
//    //return type;
//    bool SCOPE(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* save_type) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (*save_type != TokenType::VOID) {
//            save_type = new TokenType(*save_type);
//            return_type->push(save_type);
//            if (childrens.size() <= 2)return false;
//            if (!BLOCK(*childrens[1], sTable))return false;
//            if (!return_type->empty() && return_type->top() == save_type) {
//                return false;
//            }
//            return true;
//        }
//        else {
//            if (!BLOCK(*childrens[1], sTable))return false;
//            return true;
//        }
//
//    }
//
//
//    //return type;
//    int CONCIDERING_SCOPE(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* save_type) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (*save_type != TokenType::VOID) {
//            save_type = new TokenType(*save_type);
//            return_type->push(save_type);
//            if (childrens.size() <= 2) {
//                return_type->pop();
//                return 2;
//            }
//            if (!BLOCK(*childrens[1], sTable))return 0;
//            if (!return_type->empty() && return_type->top() == save_type) {
//                return_type->pop();
//                return 2;
//            }
//            return 1;
//        }
//        else {
//            if (!BLOCK(*childrens[1], sTable))return false;
//            return true;
//        }
//
//    }
//
//
//    /// <summary>
//    /// 
//    /// </summary>
//    bool BLOCK(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::STMT:
//                    if (!STMT(*ptn, sTable)) {
//                        return false;
//                    }
//                    break;
//                default:
//                    return BLOCK(*ptn, sTable);
//                }
//            }
//            else {
//                return false;
//            }
//        }
//        return true;
//    }
//
//    /// <summary>
//    /// 
//    /// </summary>
//    /// <param name="treeNode"></param>
//    /// <param name="sTable"></param>
//    /// <returns></returns>
//    bool STMT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::LINE_STMT:
//                    if (!LINE_STMT(*ptn, sTable))return false;
//                    break;
//                case NonTerminal::CONTROL_STATEMENT:
//                    if (!CONTROL_STATEMENT(*ptn, sTable))return false;
//                    break;
//                case NonTerminal::FUNC_CALL:
//                    //here
//                    if (!FUNC_CALL(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::RETURN_STMT:
//                    if (!RETURN_STMT(*ptn, sTable))return false;
//                    break;
//                        
//                default:
//                    return false;
//                }
//            }
//        }
//        return true;
//    }
//
//
//
//    //NEED FIX
//    bool CONTROL_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::IF_STATEMENT:
//                    if(!WHILE_STATEMENT(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::WHILE_STATEMENT:
//                    if(!WHILE_STATEMENT(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::FOR_STATEMENT://kmokmolmklm
//                    if (!FOR_STATEMENT(*ptn,sTable))return false;
//                    break;
//
//                case NonTerminal::IF_ELSE_STATEMENT:
//                    if (!IF_ELSE_STATEMENT(*ptn, sTable))return false;
//                    break;
//                default:
//                    return false;
//                }
//            }
//        }
//        return true;
//    }
//
//    bool IF_ELSE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        SymbalTable* new_scope_ = sTable.newScope();
//        SymbalTable* newer_scope_ = sTable.newScope();
//        bool else_scope = false;
//        bool time_else_scope = false;
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//                    if (!CONTROL_EXP(*ptn, *new_scope_))return false;
//                }
//                else if (ntd->getType() == NonTerminal::SCOPE)
//                {
//                    if (!else_scope) {
//
//                        TokenType* temp = new TokenType(TokenType::VOID);
//                        if (!return_type->empty()) {
//                            temp = return_type->top();
//                        }
//                        int res;
//                        if (!time_else_scope) {
//                            res = CONCIDERING_SCOPE(*ptn, *new_scope_, temp);
//                            time_else_scope = true;
//                        }
//                        else {
//                            res = CONCIDERING_SCOPE(*ptn, *newer_scope_, temp);
//                        }
//                        if (0 == res)return false;
//                        else if (1 == res) {
//                            else_scope = true;
//                        }
//                    }
//                    else {
//                        TokenType* temp = new TokenType(TokenType::VOID);
//                        if (!return_type->empty()) {
//                            temp = return_type->top();
//                        }
//                        int res;
//                        if (!time_else_scope) {
//                            res = CONCIDERING_SCOPE(*ptn, *new_scope_, temp);
//                            time_else_scope = true;
//                        }
//                        else {
//                            res = CONCIDERING_SCOPE(*ptn, *newer_scope_, temp);
//                        }                        
//                        if (0 == res)return false;
//                        else if (1 == res) {
//                            return_type->pop();
//                        }
//                    }
//                }
//            }
//        }
//        return true;
//    }
//
//
//
//
//    bool WHILE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        SymbalTable* new_scope_ = sTable.newScope();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//                    if (!CONTROL_EXP(*ptn, *new_scope_))return false;
//                }
//                else if(ntd->getType() == NonTerminal::SCOPE)
//                {
//                    TokenType* temp = new TokenType(TokenType::VOID);
//                    if (!return_type->empty()) {
//                        temp = return_type->top();
//                    }
//                    int res = CONCIDERING_SCOPE(*ptn, *new_scope_, temp);
//                    if (0 == res)return false;
//                    
//                }
//            }
//        }
//        return true;
//    }
//
//
//    bool FOR_STATEMENT (ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        SymbalTable* new_scope_ = sTable.newScope();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//                    if (!CONTROL_EXP(*ptn, *new_scope_))return false;
//                }
//                else if(ntd->getType() == NonTerminal::FOR_EXP) {
//                    if (!FOR_EXP(*ptn, *new_scope_))return false;
//                }
//                else
//                {
//                    TokenType* temp = new TokenType(TokenType::VOID);
//                    if (!return_type->empty()) {
//                        temp = return_type->top();
//                    }
//                    int res = CONCIDERING_SCOPE(*ptn, *new_scope_, temp);
//                    if (0 == res)return false;
//                }
//            }
//        }
//        return true;
//    }
//
//    bool FOR_EXP(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        if (childrens.size() == 1) {
//            return true;
//        }
//        if (!CONTROL_EXP(*childrens[0], sTable))return false;
//        return true;
//    }
//
//    //NEED FIX
//    bool CONTROL_EXP(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::ASSIGN:
//                    if (!ASSIGN(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::FUNC_CALL:
//                    if (!FUNC_CALL(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::VAL_CHANGE_TYPE:
//                    if (!VAL_CHANGE_TYPE(*ptn, sTable))return false;
//                    break;
//                case NonTerminal::COMPUTING_EXPRETION:
//                    if (COMPUTING_EXPRETION(*ptn, sTable,new TokenType(TokenType::INT)) == nullptr)return false;
//                    break;
//
//                case NonTerminal::TYPE_CONTROL_EXP:
//                    if (!CONTROL_EXP(*ptn, sTable))return false;
//                    break;
//                case NonTerminal::CONTROL_EXP:
//                    if (!CONTROL_EXP(*ptn, sTable))return false;
//                    break;
//                default:
//                    return false;
//                }
//            }
//        }
//        return true;
//    }
//
//    //NEED FIX
//    bool LINE_STMT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                switch (ntd->getType())
//                {
//                case NonTerminal::ASSIGN:
//                    if(!ASSIGN(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::FUNC_CALL:
//                    if (!FUNC_CALL(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::VAL_CHANGE_TYPE://kmokmolmklm
//                    if (!VAL_CHANGE_TYPE(*ptn, sTable))return false;
//                    break;
//
//                case NonTerminal::LINE_STMT:
//                    if(!LINE_STMT(*ptn, sTable))return false;
//                    break;
//                default:
//                    return false;
//                }
//            }
//        }
//        return true;
//    }
//
//    //it is not the best and not bad
//    bool RETURN_STMT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        /// <summary>
//        /// check if its is exists in the symbal table
//        /// </summary>
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        TokenType* returnal = COMPUTING_EXPRETION(*childrens[1], sTable, new TokenType(TokenType::INT));
//        if (return_type->empty()) {
//            return false;
//        }
//        TokenType* expected_returnal = return_type->top();
//        return_type->pop();
//        if (returnal != nullptr) {
//            return true;
//        }
//        else {
//            return false;
//        }
//    }
//
//    SymbalTable* RETURN_FUNC_HEAD(ParseTreeNode& treeNode, SymbalTable& sTable) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        TokenType* returnType = RETURN_TYPE(*childrens[0], sTable);
//        Token* identifer = dynamic_cast<Token*>(childrens[1]->getData());
//        std::vector<TokenType*>* returnal = new std::vector<TokenType*>();
//        SymbalTable* temp = sTable.newScope();
//        if (childrens.size() > 4) {
//             SymbalTable& new_stabel = *temp;
//             PARAMS(*childrens[3], new_stabel, returnal);
//             if (returnal->empty()) {
//                 return nullptr;
//             }
//
//        }
//        GenericSymbal* func = FunctionInSymbalTable(sTable, identifer, returnal,0);
//        bool taken = FunctionName(sTable, identifer, returnal, 0);
//        if (func != nullptr||taken) {
//            return nullptr;
//        }
//        sTable.addToken(new Function(identifer->tokenValue, returnType, returnal));
//        return temp;
//    }
//
//
//    void PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal) {
//        std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (ntd != nullptr) {
//                bool toAdd = false;
//                switch (ntd->getType())
//                {
//
//                case NonTerminal::DECLERATION:
//                    toAdd = DECLERATION(*ptn, sTable);
//                    if (toAdd == false) {
//                        returnal->clear();
//                        return;
//                    }
//                    returnal->push_back(sTable.tokensInScope->back()->type);
//                    break;
//
//                case NonTerminal::PARAMS:
//                    PARAMS(*ptn, sTable, returnal);
//                    if (returnal->empty())return;
//                    break;
//
//                default:
//                    returnal->clear();
//                    return;
//
//                }
//            }
//        }
//
//    }
//
//private:
//    ParseTreeNode* treeNodeToScan;
//    SymbalTable* symbalTable;
//    std::unordered_map<NonTerminal, NonTerminalFunction>* functionMap;
//    //when entering to calcution_expretion 
//    std::stack<TokenType*>* return_type;
//
//public:
//    SymanticAnalaser(ParseTreeNode* treeNodeToScan)
//        : treeNodeToScan(treeNodeToScan),
//        functionMap(new std::unordered_map<NonTerminal, NonTerminalFunction>()),
//        symbalTable(new SymbalTable()),
//        return_type(new std::stack<TokenType*>()){
//        setFunctionMap(); // Initialize the function map
//        Function* get_c = new Function("get_c", new TokenType(TokenType::CHAR), new std::vector<TokenType*>());
//        std::vector<TokenType*>* temp = new std::vector<TokenType*>();
//        temp->push_back(new TokenType(TokenType::CHAR));
//        Function* print_c = new Function("print_c", new TokenType(TokenType::VOID),temp);
//        symbalTable->addToken(print_c);
//        symbalTable->addToken(get_c);
//    }
//
//
//    ~SymanticAnalaser() {
//        delete functionMap; // Deallocate memory for functionMap
//        delete treeNodeToScan;
//    }
//
//
//    void setFunctionMap() {
//        // Add functions to the function map
//        addFunctionToMap(NonTerminal::DECLERATION, &SymanticAnalaser::DECLERATION);
//        addFunctionToMap(NonTerminal::ASSIGN, &SymanticAnalaser::ASSIGN);
//
//
//        addFunctionToMap(NonTerminal::RETURN_FUNC, &SymanticAnalaser::RETURN_FUNC);
//        addFunctionToMap(NonTerminal::BLOCK, &SymanticAnalaser::BLOCK);
//        addFunctionToMap(NonTerminal::FUNC_CALL, &SymanticAnalaser::FUNC_CALL);
//        addFunctionToMap(NonTerminal::STMT, &SymanticAnalaser::STMT);
//        addFunctionToMap(NonTerminal::LINE_STMT, &SymanticAnalaser::LINE_STMT);
//        addFunctionToMap(NonTerminal::RETURN_STMT, &SymanticAnalaser::RETURN_STMT);
//        addFunctionToMap(NonTerminal::NONE_RETURN_FUNC, &SymanticAnalaser::NONE_RETURN_FUNC);
//        addFunctionToMap(NonTerminal::POST_ONARY_ARITMATIC, &SymanticAnalaser::POST_ONARY_ARITMATICA);
//        addFunctionToMap(NonTerminal::PRE_ONARY_ARITMATIC, &SymanticAnalaser::PRE_ONARY_ARITMATICA);
//        addFunctionToMap(NonTerminal::VAL_CHANGE_TYPE, &SymanticAnalaser::VAL_CHANGE_TYPE);
//
//    }
//
//    void addFunctionToMap(NonTerminal nonTerminal, bool (SymanticAnalaser::* function)(ParseTreeNode&, SymbalTable&)) {
//        (*functionMap)[nonTerminal] = std::bind(function, this, std::placeholders::_1, std::placeholders::_2);
//    }
//    
//    bool Symantic_Aalisers() {
//        return Symantic_Aalisis(treeNodeToScan);
//    }
//    SymbalTable* extract_symbalTable() {
//        return symbalTable;
//    }
//
//
//private:
//    bool Symantic_Aalisis(ParseTreeNode* ptner) {
//        std::vector<ParseTreeNode*> childrens = ptner->getChildrens();
//        for (ParseTreeNode* ptn : childrens) {
//            NonTerminalData* nonterminal = dynamic_cast<NonTerminalData*>(ptn->getData());
//            if (nonterminal) {
//                // Search for the key in the function map
//                auto it = functionMap->find(nonterminal->getType());
//                if (it != functionMap->end()) {
//                    // Key found, execute the corresponding function
//                    NonTerminalFunction func = it->second;
//                    bool result = func(*ptn, *symbalTable);
//                    // Handle the result if needed
//                    if (result == false)return false;
//                }
//                else {
//                    bool result = Symantic_Aalisis(ptn);
//                    if (result == false) return false;
//                    // Key not found, go deeper into the tree
//                    // You might need to call another function recursively here
//                }
//            }
//        }
//        return true;
//    }
//
//};
#pragma once
#include "ParserTree.h"
#include "Token.h"
#include "SymbalTable.h"
#include "_ErrorHeandlerPreset.h"
#include <stack>



using NonTerminalFunction = std::function<bool(ParseTreeNode&, SymbalTable&)>;

class SymanticAnalaser {
private:
    // Functions for the Functions Map
    GenericSymbal* IdentifierInSymbalTable(SymbalTable& sTable, Token* token);
    GenericSymbal* FunctionInSymbalTable(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param, int state);
    bool FunctionName(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param, int state);
    TokenType* RETURN_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool DECLERATION(ParseTreeNode& treeNode, SymbalTable& sTable);
    TokenType* F(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* emptyType);
    TokenType* POST_ONARY_ARITMATIC(ParseTreeNode& treeNode, SymbalTable& sTable);
    TokenType* PRE_ONARY_ARITMATIC(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool POST_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool PRE_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool VAL_CHANGE_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable);
    //with return type for the expretion calc....
    TokenType* FUNC_CALL_CHECK(ParseTreeNode& treeNode, SymbalTable& sTable);
    //not with return type for the line stmt...
    bool FUNC_CALL(ParseTreeNode& treeNode, SymbalTable& sTable);
    void PASSED_PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal);
    // ����� �� �� ���� ����
    // ������� ���� ����� ��� �� ��� ��� �� �� ���� ����� ��� �������� ������� ����� ������
    // ����� ���� ���� ������ �� ���� �� ��� �����
    TokenType* COMPUTING_EXPRETION(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* emptyType);
    bool ASSIGN(ParseTreeNode& treeNode, SymbalTable& sTable);
    //return type;
    bool RETURN_FUNC(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool NONE_RETURN_FUNC(ParseTreeNode& treeNode, SymbalTable& sTable);
    SymbalTable* NONE_RETURN_FUNC_HEAD(ParseTreeNode& treeNode, SymbalTable& sTable);
    //return type;
    bool SCOPE(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* save_type);
    //return type;
    int CONCIDERING_SCOPE(ParseTreeNode& treeNode, SymbalTable& sTable, TokenType* save_type);
    bool BLOCK(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool STMT(ParseTreeNode& treeNode, SymbalTable& sTable);
    //NEED FIX
    bool CONTROL_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool IF_ELSE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool WHILE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool FOR_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
    bool FOR_EXP(ParseTreeNode& treeNode, SymbalTable& sTable);
    //NEED FIX
    bool CONTROL_EXP(ParseTreeNode& treeNode, SymbalTable& sTable);
    //NEED FIX
    bool LINE_STMT(ParseTreeNode& treeNode, SymbalTable& sTable);
    //it isnot the best and not bad
    bool RETURN_STMT(ParseTreeNode& treeNode, SymbalTable& sTable);
    SymbalTable* RETURN_FUNC_HEAD(ParseTreeNode& treeNode, SymbalTable& sTable);
    void PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal);
private:
    ParseTreeNode* treeNodeToScan;
    SymbalTable* symbalTable;
    std::unordered_map<NonTerminal, NonTerminalFunction>* functionMap;
    //when entering to calcution_expretion 
    std::stack<TokenType*>* return_type;
    Error_heandler* err;
public:
    SymanticAnalaser(ParseTreeNode* treeNodeToScan,Error_heandler* err);
    ~SymanticAnalaser();
    void setFunctionMap();
    void addFunctionToMap(NonTerminal nonTerminal, bool (SymanticAnalaser::* function)(ParseTreeNode&, SymbalTable&));
    bool Symantic_Aalisers();
    SymbalTable* extract_symbalTable();
private:
    bool Symantic_Aalisis(ParseTreeNode* ptner);
};
