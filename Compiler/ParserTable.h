//#pragma once
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <string>
//#include <sstream>
//#include <algorithm>
//#include "ParserPreset.h"
//#include "_TokenDefinitions.h"
//#include "ParserTree.h"
//
//struct Action
//{
//    ActionType actionType;
//    int toState;
//    //sementic func
//    /*int (*semanticFunc)();*/
//
//};
//
//class ParserTable {
//private:
//    std::unordered_map<int, std::unordered_map<TokenType, Action >> actionTable;
//    std::unordered_map<int, std::unordered_map< NonTerminal, int >> gotoTable;
//
//public:
//    ParserTable(const std::string& gotoTable__, const std::string& actionTable__) {
//        initActionTable(actionTable__);
//        initGotoTable(gotoTable__);
//    }
//    
//    Action* actionTableCheck(int currentState, const TokenType* tokenFromInput) {
//        auto actionIt = (this->actionTable[currentState]).find(*tokenFromInput);
//        Action currentAction = actionIt->second;
//
//        if (currentAction.actionType == ActionType::ACTION_ERROR)
//        {
//            return nullptr;
//        }
//        return &currentAction;
//    }
//
//    int gotoTableCheck(int currentState, const NonTerminal* tokenFromStack) {
//        auto gotoIt = (this->gotoTable[currentState]).find(*tokenFromStack);
//        int gotoState = gotoIt->second;
//        return gotoState;
//    }
//
//
//    void initActionTable(const std::string& fileName) {
//        std::ifstream inputFile(fileName);
//
//        if (!inputFile.is_open()) {
//            std::cerr << "Failed to open the input file." << std::endl;
//            return;
//        }
//
//        std::string line;
//        int currentState = -1;
//
//        while (std::getline(inputFile, line, '\r')) {
//            currentState++;
//            std::stringstream ss(line);
//
//            for (int i = 0; i < NUM_OF_TERMINALS; i++) {
//                std::string stateStr;
//                std::getline(ss, stateStr, ',');
//                Action newAction;
//
//                if (stateStr == "acc") {
//                   newAction.actionType = ActionType::ACTION_ACCEPT;
//                   newAction.toState = 0;
//                   actionTable[currentState][static_cast<TokenType>(i)] = newAction;
//                }
//                else if (!stateStr.empty()) {
//                    char token = stateStr[0];
//                    int state = std::stoi(stateStr.substr(1));
//
//                    switch (token) {
//                    case 's':
//                        newAction.actionType = ActionType::ACTION_SHIFT;
//                        break;
//                    case 'r':
//                        newAction.actionType = ActionType::ACTION_REDUCE;
//                        break;
//                    default:
//                        std::cerr << "Invalid action type." << std::endl;
//                        continue;
//                    }
//
//                    newAction.toState = state;
//                    actionTable[currentState][static_cast<TokenType>(i)] = newAction;
//                }
//                else {
//                    Action newAction = { ActionType::ACTION_ERROR, -1 };
//                    actionTable[currentState][static_cast<TokenType>(i)] = newAction;
//                }
//            }
//        }
//
//        inputFile.close();
//    }
//    
//    void initGotoTable(const std::string& fileName) {
//        std::ifstream inputFile(fileName);
//
//        if (!inputFile.is_open()) {
//            std::cerr << "Failed to open the input file." << std::endl;
//            return;
//        }
//
//        std::string line;
//        int currentState = -1;
//
//        while (std::getline(inputFile, line,'\r')) {
//            currentState++;
//            std::stringstream ss(line);
//
//            for (int i = 0; i < NUM_OF_NON_TERMINALS; i++) {
//                std::string stateStr;
//                std::getline(ss, stateStr, ',');
//
//                if (!stateStr.empty()) {
//                    int state = std::stoi(stateStr);
//                    gotoTable[currentState][static_cast<NonTerminal>(i)] = state;
//                }
//                else {
//                    gotoTable[currentState][static_cast<NonTerminal>(i)] = -1;
//                }
//            }
//        }
//
//        inputFile.close();
//    }
//
//};
//
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include "ParserPreset.h"
#include "_TokenDefinitions.h"
#include "ParserTree.h"

struct Action
{
    ActionType actionType;
    int toState;
};

class ParserTable {
private:
    std::unordered_map<int, std::unordered_map<TokenType, Action >> actionTable;
    std::unordered_map<int, std::unordered_map< NonTerminal, int >> gotoTable;

public:
    ParserTable(const std::string& gotoTable__, const std::string& actionTable__);
    Action* actionTableCheck(int currentState, const TokenType* tokenFromInput);
    int gotoTableCheck(int currentState, const NonTerminal* tokenFromStack);

private:
    void initActionTable(const std::string& fileName);
    void initGotoTable(const std::string& fileName);
};
