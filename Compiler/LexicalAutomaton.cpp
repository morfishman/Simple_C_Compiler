#include "LexicalAutomaton.h"

int LexicalAutomaton::getCurrentState() const {
    return currentState;
}

void LexicalAutomaton::transition(char inputChar) {
    currentState = transitionMatrix[currentState][inputChar];
}

void LexicalAutomaton::resetCurrentState() {
    currentState = 0;
}

void LexicalAutomaton::setCurrentState(int state) {
    currentState = state;
}

void LexicalAutomaton::generateTransitionMatrix() {
    this->generateTokenStateMap();
    int stateCounter = 1;
    constexpr int numCols = 128;
    std::vector<std::vector<int>> tempMat(stateCounter, std::vector<int>(numCols, 0));

    for (size_t index = 0; index < maxTokenSize; index++) {
        for (const auto& entry : tokenStringsMap) {
            const std::string& tokenString = entry.second;
            TokenType token = entry.first;
            if (index == tokenString.size()) {
                tempMat[tokenStateMap[token][index - 1]][tokenString[index - 1]] = tokenStateMap[token][index];
            }
            else if (index < tokenString.size()) {
                if (tempMat[tokenStateMap[token][index]][tokenString[index]] > 0) {
                    tokenStateMap[token][index + 1] = *((int*)(tempMat[tokenStateMap[token][index]][tokenString[index]]));
                }
                else {
                    if (one_string.find(token) == one_string.end()) {
                        tempMat.emplace_back(numCols, 0);
                    }
                    else {
                        tempMat.emplace_back(numCols, -1000);
                    }
                    tempMat[tokenStateMap[token][index]][tokenString[index]] = (int)(&(tokenStateMap[token][index + 1]));
                    tokenStateMap[token][index + 1] = stateCounter++;
                }
                if (index != 0) {
                    tempMat[tokenStateMap[token][index - 1]][tokenString[index - 1]] = tokenStateMap[token][index];
                }
            }
        }
    }

    // Numbers
    int index_of_last_element = tempMat.size();
    tempMat.emplace_back(numCols, -(int)(TokenType::NUMERIC));

    for (const auto& entry : numericCharsMap) {
        const char& NumberChar = entry.second;
        TokenType token = entry.first;
        tempMat[tempMat.size() - 1][NumberChar] = index_of_last_element;
        tempMat[0][NumberChar] = index_of_last_element;
    }

    // Literal
    for (const auto& entry : literalDelimiters) {
        index_of_last_element++;
        tempMat.emplace_back(numCols, index_of_last_element);
        const char& NumberChar = entry.second;
        TokenType token = entry.first;
        tempMat[tempMat.size() - 1][NumberChar] = -(int)(TokenType::LITTERAL);
        tempMat[0][NumberChar] = index_of_last_element;
    }

    // Delimiters
    index_of_last_element = tempMat.size();
    tempMat.emplace_back(numCols, index_of_last_element);
    for (const auto& entry : delimiterCharsMap) {
        const char& separatorChar = entry.second;
        TokenType token = entry.first;
        for (size_t index = 0; index < stateCounter; index++) {
            if (tempMat[index][separatorChar] == 0) {
                tempMat[index][separatorChar] = -(int)token;
            }
        }
        tempMat[tempMat.size() - 1][separatorChar] = -(int)(TokenType::IDENTIFIER);
    }

    // Unused characters
    for (size_t i = 0; i < tempMat.size(); i++) {
        for (const auto& entry : unusedCharsMap) {
            const char& NumberChar = entry.second;
            TokenType token = entry.first;
            tempMat[i][NumberChar] = -(int)(token);
        }
    }

    transitionMatrix = tempMat;
}

const std::vector<std::vector<int>>& LexicalAutomaton::getTransitionMatrix() const {
    return transitionMatrix;
}

void LexicalAutomaton::generateTokenStateMap() {
    size_t maxSize = 0;
    for (const auto& entry : tokenStringsMap) {
        TokenType token = entry.first;
        const std::string& str = entry.second;
        tokenStateMap[token] = std::vector<int>(str.size() + 1, 0);
        maxSize = std::max(maxSize, str.size());
    }
    maxTokenSize = maxSize + 1;
}