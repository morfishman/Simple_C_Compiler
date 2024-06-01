#include "ParserTable.h"

ParserTable::ParserTable(const std::string& gotoTable__, const std::string& actionTable__) {
    initActionTable(actionTable__);
    initGotoTable(gotoTable__);
}

Action* ParserTable::actionTableCheck(int currentState, const TokenType* tokenFromInput) {
    auto actionIt = (this->actionTable[currentState]).find(*tokenFromInput);
    if (actionIt == this->actionTable[currentState].end()) {
        return nullptr;
    }
    Action currentAction = actionIt->second;

    if (currentAction.actionType == ActionType::ACTION_ERROR)
    {
        return nullptr;
    }
    return &currentAction;
}

int ParserTable::gotoTableCheck(int currentState, const NonTerminal* tokenFromStack) {
    auto gotoIt = (this->gotoTable[currentState]).find(*tokenFromStack);
    if (gotoIt == this->gotoTable[currentState].end()) {
        return -1;
    }
    return gotoIt->second;
}

void ParserTable::initActionTable(const std::string& fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }

    std::string line;
    int currentState = -1;

    while (std::getline(inputFile, line, '\r')) {
        currentState++;
        std::stringstream ss(line);

        for (int i = 0; i < NUM_OF_TERMINALS; i++) {
            std::string stateStr;
            std::getline(ss, stateStr, ',');
            Action newAction;

            if (stateStr == "acc") {
                newAction.actionType = ActionType::ACTION_ACCEPT;
                newAction.toState = 0;
                actionTable[currentState][static_cast<TokenType>(i)] = newAction;
            }
            else if (!stateStr.empty()) {
                char token = stateStr[0];
                int state = std::stoi(stateStr.substr(1));

                switch (token) {
                case 's':
                    newAction.actionType = ActionType::ACTION_SHIFT;
                    break;
                case 'r':
                    newAction.actionType = ActionType::ACTION_REDUCE;
                    break;
                default:
                    std::cerr << "Invalid action type." << std::endl;
                    continue;
                }

                newAction.toState = state;
                actionTable[currentState][static_cast<TokenType>(i)] = newAction;
            }
            else {
                Action newAction = { ActionType::ACTION_ERROR, -1 };
                actionTable[currentState][static_cast<TokenType>(i)] = newAction;
            }
        }
    }

    inputFile.close();
}

void ParserTable::initGotoTable(const std::string& fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }

    std::string line;
    int currentState = -1;

    while (std::getline(inputFile, line, '\r')) {
        currentState++;
        std::stringstream ss(line);

        for (int i = 0; i < NUM_OF_NON_TERMINALS; i++) {
            std::string stateStr;
            std::getline(ss, stateStr, ',');

            if (!stateStr.empty()) {
                int state = std::stoi(stateStr);
                gotoTable[currentState][static_cast<NonTerminal>(i)] = state;
            }
            else {
                gotoTable[currentState][static_cast<NonTerminal>(i)] = -1;
            }
        }
    }

    inputFile.close();
}
