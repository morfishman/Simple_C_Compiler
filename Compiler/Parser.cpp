#include "Parser.h"

Parser::Parser(const std::string& gotoTable__, const std::string& actionTable__, ParseTreeNodeStack* stack)
    : parserStack(stack) {
    initProductionRule();  // Initialize production rules

    // Allocate ParserTable dynamically
    this->parserTable = new ParserTable(gotoTable__, actionTable__);

    // Allocate firstTreeNode dynamically
    ParseTreeNode* firstTreeNode = new ParseTreeNode(nullptr, 0);
    parserStack->push(firstTreeNode);
}

int Parser::syntaxAnalays(Token* tokenToParse) {
    if (tokenToParse == nullptr) {
        return 0;
    }
    if (parserDelimiterCharsMap.find(tokenToParse->getType()) != parserDelimiterCharsMap.end()) {
        return 1;
    }
    ParseTreeNode* currentTopOfStack = parserStack->top();
    TokenType typeToken = tokenToParse->getType();
    int num = currentTopOfStack->getStateNumber();
    Action* action = parserTable->actionTableCheck(currentTopOfStack->getStateNumber(), &typeToken);
    if (action == nullptr) {
        return 0;
    }
    else {
        int toState = action->toState;
        if (action->actionType == ActionType::ACTION_SHIFT) {
            int number = action->toState;
            ParseTreeNode* tempTreeNode = new ParseTreeNode(tokenToParse, number);
            parserStack->push(tempTreeNode);
            return 1;
        }
        else if (action->actionType == ActionType::ACTION_REDUCE) {

            ProductionRule* productionRule = productionRules[toState];
            int toPop = productionRule->ruleLength;
            NonTerminal nonTerminal = productionRule->nonTerminalType;
            NonTerminalData* nonTerminalData = new NonTerminalData(nonTerminal);
            ParseTreeNode* reducedTree = new ParseTreeNode(nonTerminalData, 0);
            for (size_t i = 0; i < toPop; i++) {
                ParseTreeNode* tempNode = parserStack->pop();
                reducedTree->addChild(tempNode);
            }
            ParseTreeNode* topOfStack = parserStack->top();
            int nextState = parserTable->gotoTableCheck(topOfStack->getStateNumber(), &nonTerminal);
            reducedTree->setStateNumber(nextState);
            parserStack->push(reducedTree);
            return -1;
        }
        else {
            return 1;
        }
    }
}

void Parser::initProductionRule() {
    		// rule 1 => S -> PROGRAM
    		ProductionRule* productionRule1 = new ProductionRule{ NonTerminal::ACCEPT, 1 };
    		this->productionRules.push_back(productionRule1);
    
    
    		// rule 2 => PROGRAM -> PROGRAM FUNCTION
    		ProductionRule* productionRule2 = new ProductionRule{ NonTerminal::PROGRAM, 2 };
    		this->productionRules.push_back(productionRule2);
    
    		// rule 3 => PROGRAM -> FUNCTION
    		ProductionRule* productionRule3 = new ProductionRule{ NonTerminal::PROGRAM, 1 };
    		this->productionRules.push_back(productionRule3);
    
    		// rule 4 => FUNCTION -> RETURN_FUNC
    		ProductionRule* productionRule4 = new ProductionRule{ NonTerminal::FUNCTION, 1 };
    		this->productionRules.push_back(productionRule4);
    
    		// rule 5 => FUNCTION -> NONE_RETURN_FUNC
    		ProductionRule* productionRule5 = new ProductionRule{ NonTerminal::FUNCTION, 1 };
    		this->productionRules.push_back(productionRule5);
    
    		// rule 6 => RETURN_FUNC -> RETURN_FUNC_HEAD SCOPE
    		ProductionRule* productionRule6 = new ProductionRule{ NonTerminal::RETURN_FUNC, 2 };
    		this->productionRules.push_back(productionRule6);
    
    		// rule 7 => NONE_RETURN_FUNC -> NONE_RETURN_FUNC_HEAD SCOPE
    		ProductionRule* productionRule7 = new ProductionRule{ NonTerminal::NONE_RETURN_FUNC, 2 };
    		this->productionRules.push_back(productionRule7);
    
    		// rule 8 => RETURN_STMT -> return computing_expretion
    		ProductionRule* productionRule8 = new ProductionRule{ NonTerminal::RETURN_STMT, 2 };
    		this->productionRules.push_back(productionRule8);
    
    		// rule 9 => SCOPE -> new ProductionRule {BLOCK }
    		ProductionRule* productionRule9 = new ProductionRule{ NonTerminal::SCOPE, 3 };
    		this->productionRules.push_back(productionRule9);
    
    		// rule 10 => SCOPE -> new ProductionRule {}
    		ProductionRule* productionRule10 = new ProductionRule{ NonTerminal::SCOPE, 2 };
    		this->productionRules.push_back(productionRule10);
    
    		// rule 11 => BLOCK -> STMT BLOCK
    		ProductionRule* productionRule11 = new ProductionRule{ NonTerminal::BLOCK, 2 };
    		this->productionRules.push_back(productionRule11);
    
    		// rule 12 => BLOCK -> STMT 
    		ProductionRule* productionRule12 = new ProductionRule{ NonTerminal::BLOCK, 1 };
    		this->productionRules.push_back(productionRule12);
    
    		// rule 13 => STMT -> LINE_STMT ; 
    		ProductionRule* productionRule13 = new ProductionRule{ NonTerminal::STMT, 2 };
    		this->productionRules.push_back(productionRule13);
    
    		// rule 14 => STMT -> CONTROL_STATEMENT
    		ProductionRule* productionRule14 = new ProductionRule{ NonTerminal::STMT, 1 };
    		this->productionRules.push_back(productionRule14);
    
    		// rule 15 => STMT -> RETURN_STMT ;
    		ProductionRule* productionRule15 = new ProductionRule{ NonTerminal::STMT, 2 };
    		this->productionRules.push_back(productionRule15);
    
    		// rule 16 => STMT -> FUNC_CALL ;
    		ProductionRule* productionRule16 = new ProductionRule{ NonTerminal::STMT, 2 };
    		this->productionRules.push_back(productionRule16);
    
    		// rule 17 => LINE_STMT -> ASSIGN
    		ProductionRule* productionRule17 = new ProductionRule{ NonTerminal::LINE_STMT, 1 };
    		this->productionRules.push_back(productionRule17);
    
    		// rule 18 => LINE_STMT -> FUNC_CALL
    		ProductionRule* productionRule18 = new ProductionRule{ NonTerminal::LINE_STMT, 1 };
    		this->productionRules.push_back(productionRule18);
    
    		// rule 19 => LINE_STMT -> VAL_CHANGE_TYPE
    		ProductionRule* productionRule19 = new ProductionRule{ NonTerminal::LINE_STMT, 1 };
    		this->productionRules.push_back(productionRule19);
    
    		// rule 20 => LINE_STMT -> LINE_STMT , ASSIGN
    		ProductionRule* productionRule20 = new ProductionRule{ NonTerminal::LINE_STMT, 3 };
    		this->productionRules.push_back(productionRule20);
    
    		// rule 21 => LINE_STMT -> LINE_STMT , VAL_CHANGE_TYPE
    		ProductionRule* productionRule21 = new ProductionRule{ NonTerminal::LINE_STMT, 3 };
    		this->productionRules.push_back(productionRule21);
    
    		// rule 22 => LINE_STMT -> LINE_STMT , FUNC_CALL
    		ProductionRule* productionRule22 = new ProductionRule{ NonTerminal::LINE_STMT, 3 };
    		this->productionRules.push_back(productionRule22);
    
    		// rule 23 => CONTROL_STATEMENT -> IF_STATEMENT
    		ProductionRule* productionRule23 = new ProductionRule{ NonTerminal::CONTROL_STATEMENT, 1 };
    		this->productionRules.push_back(productionRule23);
    
    		// rule 24 => CONTROL_STATEMENT -> WHILE_STATEMENT
    		ProductionRule* productionRule24 = new ProductionRule{ NonTerminal::CONTROL_STATEMENT, 1 };
    		this->productionRules.push_back(productionRule24);
    
    		// rule 25 => CONTROL_STATEMENT -> FOR_STATEMENT
    		ProductionRule* productionRule25 = new ProductionRule{ NonTerminal::CONTROL_STATEMENT, 1 };
    		this->productionRules.push_back(productionRule25);
    
    		// rule 26 => CONTROL_STATEMENT -> IF_ELSE_STATEMENT
    		ProductionRule* productionRule26 = new ProductionRule{ NonTerminal::CONTROL_STATEMENT, 1 };
    		this->productionRules.push_back(productionRule26);
    
    		// rule 27 => IF_STATEMENT -> if ( CONTROL_EXP ) SCOPE
    		ProductionRule* productionRule27 = new ProductionRule{ NonTerminal::IF_STATEMENT, 5 };
    		this->productionRules.push_back(productionRule27);
    
    		// rule 28 => IF_ELSE_STATEMENT -> if ( CONTROL_EXP ) SCOPE else SCOPE
    		ProductionRule* productionRule28 = new ProductionRule{ NonTerminal::IF_ELSE_STATEMENT, 7 };
    		this->productionRules.push_back(productionRule28);
    
    		// rule 29 => WHILE_STATEMENT -> while ( CONTROL_EXP ) SCOPE 
    		ProductionRule* productionRule29 = new ProductionRule{ NonTerminal::WHILE_STATEMENT, 5 };
    		this->productionRules.push_back(productionRule29);
    
    		// rule 30 => FOR_STATEMENT -> for ( FOR_EXP FOR_EXP CONTROL_EXP ) SCOPE
    		ProductionRule* productionRule30 = new ProductionRule{ NonTerminal::FOR_STATEMENT, 7 };
    		this->productionRules.push_back(productionRule30);
    
    		// rule 31 => FOR_STATEMENT -> for ( FOR_EXP FOR_EXP ) SCOPE
    		ProductionRule* productionRule31 = new ProductionRule{ NonTerminal::FOR_STATEMENT, 6 };
    		this->productionRules.push_back(productionRule31);
    
    		// rule 32 => TYPE_CONTROL_EXP -> ASSIGN
    		ProductionRule* productionRule32 = new ProductionRule{ NonTerminal::TYPE_CONTROL_EXP, 1 };
    		this->productionRules.push_back(productionRule32);
    
    		// rule 33 => TYPE_CONTROL_EXP -> VAL_CHANGE_TYPE
    		ProductionRule* productionRule33 = new ProductionRule{ NonTerminal::TYPE_CONTROL_EXP, 1 };
    		this->productionRules.push_back(productionRule33);
    
    		// rule 34 => TYPE_CONTROL_EXP -> computing_expretion
    		ProductionRule* productionRule34 = new ProductionRule{ NonTerminal::TYPE_CONTROL_EXP, 1 };
    		this->productionRules.push_back(productionRule34);
    
    		// rule 35 => TYPE_CONTROL_EXP -> FUNC_CALL
    		ProductionRule* productionRule35 = new ProductionRule{ NonTerminal::TYPE_CONTROL_EXP, 1 };
    		this->productionRules.push_back(productionRule35);
    
    		// rule 36 => CONTROL_EXP -> TYPE_CONTROL_EXP
    		ProductionRule* productionRule36 = new ProductionRule{ NonTerminal::CONTROL_EXP, 1 };
    		this->productionRules.push_back(productionRule36);
    
    		// rule 37 => CONTROL_EXP -> TYPE_CONTROL_EXP , CONTROL_EXP
    		ProductionRule* productionRule37 = new ProductionRule{ NonTerminal::CONTROL_EXP, 3 };
    		this->productionRules.push_back(productionRule37);
    
    		// rule 38 => FOR_EXP -> CONTROL_EXP ;
    		ProductionRule* productionRule38 = new ProductionRule{ NonTerminal::FOR_EXP, 2 };
    		this->productionRules.push_back(productionRule38);
    
    		// rule 39 => FOR_EXP -> ;
    		ProductionRule* productionRule39 = new ProductionRule{ NonTerminal::FOR_EXP, 1 };
    		this->productionRules.push_back(productionRule39);
    
    		// rule 40 => VAL_CHANGE_TYPE -> id VAL_CHANGE_OP computing_expretion
    		ProductionRule* productionRule40 = new ProductionRule{ NonTerminal::VAL_CHANGE_TYPE, 3 };
    		this->productionRules.push_back(productionRule40);
    
    		// rule 41 => VAL_CHANGE_TYPE -> PRE_ONARY_ARITMATIC
    		ProductionRule* productionRule41 = new ProductionRule{ NonTerminal::VAL_CHANGE_TYPE, 1 };
    		this->productionRules.push_back(productionRule41);
    
    		// rule 42 => VAL_CHANGE_TYPE -> POST_ONARY_ARITMATIC
    		ProductionRule* productionRule42 = new ProductionRule{ NonTerminal::VAL_CHANGE_TYPE, 1 };
    		this->productionRules.push_back(productionRule42);
    
    		// rule 43 => VAL_CHANGE -> VAL_CHANGE_TYPE
    		ProductionRule* productionRule43 = new ProductionRule{ NonTerminal::VAL_CHANGE, 1 };
    		this->productionRules.push_back(productionRule43);
    
    		// rule 44 => VAL_CHANGE -> VAL_CHANGE_TYPE , VAL_CHANGE
    		ProductionRule* productionRule44 = new ProductionRule{ NonTerminal::VAL_CHANGE, 3 };
    		this->productionRules.push_back(productionRule44);
    
    		// rule 45 => VAL_CHANGE_OP -> +=
    		ProductionRule* productionRule45 = new ProductionRule{ NonTerminal::VAL_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule45);
    
    		// rule 46 => VAL_CHANGE_OP -> -=
    		ProductionRule* productionRule46 = new ProductionRule{ NonTerminal::VAL_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule46);
    
    		// rule 47 => VAL_CHANGE_OP -> *=
    		ProductionRule* productionRule47 = new ProductionRule{ NonTerminal::VAL_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule47);
    
    		// rule 48 => VAL_CHANGE_OP -> /=
    		ProductionRule* productionRule48 = new ProductionRule{ NonTerminal::VAL_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule48);
    
    		// rule 49 => VAL_CHANGE_OP -> %=
    		ProductionRule* productionRule49 = new ProductionRule{ NonTerminal::VAL_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule49);
    
    		// rule 50 => ONARY_CHANGE_OP -> --
    		ProductionRule* productionRule50 = new ProductionRule{ NonTerminal::ONARY_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule50);
    
    		// rule 51 => ONARY_CHANGE_OP -> ++
    		ProductionRule* productionRule51 = new ProductionRule{ NonTerminal::ONARY_CHANGE_OP, 1 };
    		this->productionRules.push_back(productionRule51);
    
    		// rule 52 => DECLERATION -> RETURN_TYPE id 
    		ProductionRule* productionRule52 = new ProductionRule{ NonTerminal::DECLERATION, 2 };
    		this->productionRules.push_back(productionRule52);
    
    		// rule 53 => DECLERATION -> NONE_RETURN_TYPE id 
    		ProductionRule* productionRule53 = new ProductionRule{ NonTerminal::DECLERATION, 2 };
    		this->productionRules.push_back(productionRule53);
    
    		// rule 54 => ASSIGN -> id = computing_expretion 
    		ProductionRule* productionRule54 = new ProductionRule{ NonTerminal::ASSIGN, 3 };
    		this->productionRules.push_back(productionRule54);
    
    		// rule 55 => ASSIGN -> DECLERATION = computing_expretion  
    		ProductionRule* productionRule55 = new ProductionRule{ NonTerminal::ASSIGN, 3 };
    		this->productionRules.push_back(productionRule55);
    
    		// rule 56 => ASSIGN_OR_DEC -> DECLERATION 
    		ProductionRule* productionRule56 = new ProductionRule{ NonTerminal::ASSIGN_OR_DEC, 1 };
    		this->productionRules.push_back(productionRule56);
    
    		// rule 57 => ASSIGN_OR_DEC -> ASSIGN 
    		ProductionRule* productionRule57 = new ProductionRule{ NonTerminal::ASSIGN_OR_DEC, 1 };
    		this->productionRules.push_back(productionRule57);
    
    		// rule 58 => ASSIGN_OR_DEC -> ASSIGN_OR_DEC , ASSIGN 
    		ProductionRule* productionRule58 = new ProductionRule{ NonTerminal::ASSIGN_OR_DEC, 3 };
    		this->productionRules.push_back(productionRule58);
    
    		// rule 59 => ASSIGN_OR_DEC -> ASSIGN_OR_DEC , DECLERATION 
    		ProductionRule* productionRule59 = new ProductionRule{ NonTerminal::ASSIGN_OR_DEC, 3 };
    		this->productionRules.push_back(productionRule59);
    
    		// rule 60 => computing_expretion -> bool_expretion  
    		ProductionRule* productionRule60 = new ProductionRule{ NonTerminal::COMPUTING_EXPRETION, 1 };
    		this->productionRules.push_back(productionRule60);
    
    		// rule 61 => computing_expretion -> aritmatic  
    		ProductionRule* productionRule61 = new ProductionRule{ NonTerminal::COMPUTING_EXPRETION, 1 };
    		this->productionRules.push_back(productionRule61);
    
    		// rule 62 => bool_expretion -> bool_cmp boolean_combo bool_cmp  
    		ProductionRule* productionRule62 = new ProductionRule{ NonTerminal::BOOL_EXPRETION, 3 };
    		this->productionRules.push_back(productionRule62);
    
    		// rule 63 => bool_expretion -> bool_expretion boolean_combo bool_cmp  
    		ProductionRule* productionRule63 = new ProductionRule{ NonTerminal::BOOL_EXPRETION, 3 };
    		this->productionRules.push_back(productionRule63);
    
    		// rule 64 => bool_expretion -> bool_cmp  
    		ProductionRule* productionRule64 = new ProductionRule{ NonTerminal::BOOL_EXPRETION, 1 };
    		this->productionRules.push_back(productionRule64);
    
    		// rule 65 => bool_cmp -> bool_cmp boolean_compersion expr  
    		ProductionRule* productionRule65 = new ProductionRule{ NonTerminal::BOOL_CMP, 3 };
    		this->productionRules.push_back(productionRule65);
    
    		// rule 66 => bool_cmp -> expr boolean_compersion expr  
    		ProductionRule* productionRule66 = new ProductionRule{ NonTerminal::BOOL_CMP, 3 };
    		this->productionRules.push_back(productionRule66);
    
    		// rule 67 => bool_cmp -> expr  
    		ProductionRule* productionRule67 = new ProductionRule{ NonTerminal::BOOL_CMP, 1 };
    		this->productionRules.push_back(productionRule67);
    
    		// rule 68 => expr -> bool_expr  
    		ProductionRule* productionRule68 = new ProductionRule{ NonTerminal::EXPR, 1 };
    		this->productionRules.push_back(productionRule68);
    
    		// rule 69 => expr -> aritmatic  
    		ProductionRule* productionRule69 = new ProductionRule{ NonTerminal::EXPR, 1 };
    		this->productionRules.push_back(productionRule69);
    
    		// rule 70 => bool_expr -> ! aritmatic  
    		ProductionRule* productionRule70 = new ProductionRule{ NonTerminal::BOOL_EXPR, 2 };
    		this->productionRules.push_back(productionRule70);
    
    		// rule 71 => aritmatic -> aritmatic + T  
    		ProductionRule* productionRule71 = new ProductionRule{ NonTerminal::ARITMATIC, 3 };
    		this->productionRules.push_back(productionRule71);
    
    		// rule 72 => aritmatic -> aritmatic - T  
    		ProductionRule* productionRule72 = new ProductionRule{ NonTerminal::ARITMATIC, 3 };
    		this->productionRules.push_back(productionRule72);
    
    		// rule 73 => aritmatic -> T  
    		ProductionRule* productionRule73 = new ProductionRule{ NonTerminal::ARITMATIC, 1 };
    		this->productionRules.push_back(productionRule73);
    
    		// rule 74 => T -> T * F  
    		ProductionRule* productionRule74 = new ProductionRule{ NonTerminal::T, 3 };
    		this->productionRules.push_back(productionRule74);
    
    		// rule 75 => T -> T / F  
    		ProductionRule* productionRule75 = new ProductionRule{ NonTerminal::T, 3 };
    		this->productionRules.push_back(productionRule75);
    
    		// rule 76 => T -> T % F  
    		ProductionRule* productionRule76 = new ProductionRule{ NonTerminal::T, 3 };
    		this->productionRules.push_back(productionRule76);
    
    		// rule 77 => T -> F  
    		ProductionRule* productionRule77 = new ProductionRule{ NonTerminal::T, 1 };
    		this->productionRules.push_back(productionRule77);
    
    		// rule 78 => F -> ( aritmatic )  
    		ProductionRule* productionRule78 = new ProductionRule{ NonTerminal::F, 3 };
    		this->productionRules.push_back(productionRule78);
    
    		// rule 79 => F -> PRE_ONARY_ARITMATIC  
    		ProductionRule* productionRule79 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule79);
    
    		// rule 80 => F -> POST_ONARY_ARITMATIC  
    		ProductionRule* productionRule80 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule80);
    
    		// rule 81 => F -> id  
    		ProductionRule* productionRule81 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule81);
    
    		// rule 82 => F -> numeric  
    		ProductionRule* productionRule82 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule82);
    
    		// rule 83 => F -> FUNC_CALL  
    		ProductionRule* productionRule83 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule83);
    
    		// rule 84 => F -> literal  
    		ProductionRule* productionRule84 = new ProductionRule{ NonTerminal::F, 1 };
    		this->productionRules.push_back(productionRule84);
    
    		// rule 85 => PRE_ONARY_ARITMATIC -> id ONARY_CHANGE_OP  
    		ProductionRule* productionRule85 = new ProductionRule{ NonTerminal::PRE_ONARY_ARITMATIC, 2 };
    		this->productionRules.push_back(productionRule85);
    
    		// rule 86 => POST_ONARY_ARITMATIC -> ONARY_CHANGE_OP id  
    		ProductionRule* productionRule86 = new ProductionRule{ NonTerminal::POST_ONARY_ARITMATIC, 2 };
    		this->productionRules.push_back(productionRule86);
    
    		// rule 87 => boolean_compersion -> !=  
    		ProductionRule* productionRule87 = new ProductionRule{ NonTerminal::BOOLEAN_COMPERSION, 1 };
    		this->productionRules.push_back(productionRule87);
    
    		// rule 88 => boolean_compersion -> ==  
    		ProductionRule* productionRule88 = new ProductionRule{ NonTerminal::BOOLEAN_COMPERSION, 1 };
    		this->productionRules.push_back(productionRule88);
    
    		// rule 89 => boolean_compersion -> >=  
    		ProductionRule* productionRule89 = new ProductionRule{ NonTerminal::BOOLEAN_COMPERSION, 1 };
    		this->productionRules.push_back(productionRule89);
    
    		// rule 90 => boolean_compersion -> <=  
    		ProductionRule* productionRule90 = new ProductionRule{ NonTerminal::BOOLEAN_COMPERSION, 1 };
    		this->productionRules.push_back(productionRule90);
    
    		// rule 91 => boolean_combo -> &&  
    		ProductionRule* productionRule91 = new ProductionRule{ NonTerminal::BOOLEAN_COMBO, 1 };
    		this->productionRules.push_back(productionRule91);
    
    		// rule 92 => boolean_combo -> ||  
    		ProductionRule* productionRule92 = new ProductionRule{ NonTerminal::BOOLEAN_COMBO, 1 };
    		this->productionRules.push_back(productionRule92);
    
    		// rule 93 => FUNC_CALL -> id ( )  
    		ProductionRule* productionRule93 = new ProductionRule{ NonTerminal::FUNC_CALL, 3 };
    		this->productionRules.push_back(productionRule93);
    
    		// rule 94 => FUNC_CALL -> id ( PASS_PARAM )  
    		ProductionRule* productionRule94 = new ProductionRule{ NonTerminal::FUNC_CALL, 4 };
    		this->productionRules.push_back(productionRule94);
    
    		// rule 95 => PASS_PARAM -> computing_expretion  
    		ProductionRule* productionRule95 = new ProductionRule{ NonTerminal::PASS_PARAM, 1 };
    		this->productionRules.push_back(productionRule95);
    
    		// rule 96 => PASS_PARAM -> computing_expretion , PASS_PARAM  
    		ProductionRule* productionRule96 = new ProductionRule{ NonTerminal::PASS_PARAM, 3 };
    		this->productionRules.push_back(productionRule96);
    
    		// rule 97 => RETURN_FUNC_HEAD -> RETURN_TYPE id ( PARAMS )  
    		ProductionRule* productionRule97 = new ProductionRule{ NonTerminal::RETURN_FUNC_HEAD, 5 };
    		this->productionRules.push_back(productionRule97);
    
    		// rule 98 => RETURN_FUNC_HEAD -> RETURN_TYPE id ( )  
    		ProductionRule* productionRule98 = new ProductionRule{ NonTerminal::RETURN_FUNC_HEAD, 4 };
    		this->productionRules.push_back(productionRule98);
    
    		// rule 99 => NONE_RETURN_FUNC_HEAD -> NONE_RETURN_TYPE id ( PARAMS )  
    		ProductionRule* productionRule99 = new ProductionRule{ NonTerminal::NONE_RETURN_FUNC_HEAD, 5 };
    		this->productionRules.push_back(productionRule99);
    
    		// rule 100 => NONE_RETURN_FUNC_HEAD -> NONE_RETURN_TYPE id ( )  
    		ProductionRule* productionRule100 = new ProductionRule{ NonTerminal::NONE_RETURN_FUNC_HEAD, 4 };
    		this->productionRules.push_back(productionRule100);
    
    		// rule 101 => PARAMS -> DECLERATION  
    		ProductionRule* productionRule101 = new ProductionRule{ NonTerminal::PARAMS, 1 };
    		this->productionRules.push_back(productionRule101);
    
    		// rule 102 => PARAMS -> PARAMS , DECLERATION  
    		ProductionRule* productionRule102 = new ProductionRule{ NonTerminal::PARAMS, 3 };
    		this->productionRules.push_back(productionRule102);
    
    		// rule 103 => RETURN_TYPE -> int  
    		ProductionRule* productionRule103 = new ProductionRule{ NonTerminal::RETURN_TYPE, 1 };
    		this->productionRules.push_back(productionRule103);
    
    		// rule 104 => RETURN_TYPE -> char  
    		ProductionRule* productionRule104 = new ProductionRule{ NonTerminal::RETURN_TYPE, 1 };
    		this->productionRules.push_back(productionRule104);
    
    		// rule 105 => RETURN_TYPE -> int [ ]  
    		ProductionRule* productionRule105 = new ProductionRule{ NonTerminal::RETURN_TYPE, 3 };
    		this->productionRules.push_back(productionRule105);
    
    		// rule 106 => RETURN_TYPE -> char [ ]  
    		ProductionRule* productionRule106 = new ProductionRule{ NonTerminal::RETURN_TYPE, 3 };
    		this->productionRules.push_back(productionRule106);
    
    		// rule 107 => NONE_RETURN_TYPE -> void [ ]  
    		ProductionRule* productionRule107 = new ProductionRule{ NonTerminal::NONE_RETURN_TYPE, 3 };
    		this->productionRules.push_back(productionRule107);
    
    		// rule 108 => NONE_RETURN_TYPE -> void  
    		ProductionRule* productionRule108 = new ProductionRule{ NonTerminal::NONE_RETURN_TYPE, 1 };
    		this->productionRules.push_back(productionRule108);
    	}

ParseTreeNode* Parser::extractTree() {
    return parserStack->top();
}

void Parser::printTree() {
    ParseTreeNode* t = parserStack->top();
    t->print(5);
}
