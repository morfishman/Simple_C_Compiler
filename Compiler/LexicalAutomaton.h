//#pragma once
//#include "_TokenDefinitions.h"
//
//
//
//
//
//class LexicalAutomaton {
//private:
//    int currentState;
//    std::vector<std::vector<int>> transitionMatrix;
//    int maxTokenSize;
//    std::unordered_map<TokenType, std::vector<int>> tokenStateMap;
//
//public:
//    int getCurrentState() const {
//        return currentState;
//    }
//
//    void transition(char inputChar) {
//
//        currentState = transitionMatrix[currentState][inputChar];
//    }
//
//    void resetCurrentState() {
//        currentState = 0;
//    }
//
//    void setCurrentState(int state) {
//        currentState = state;
//    }
//
//    void generateTransitionMatrix() {
//        this->generateTokenStateMap();
//        int stateCounter = 1;
//        constexpr int numCols = 128;
//        std::vector<std::vector<int>> tempMat(stateCounter, std::vector<int>(numCols, 0));
//        for (size_t index = 0; index < maxTokenSize; index++) {
//            for (const auto& entry : tokenStringsMap) {
//                const std::string& tokenString = entry.second;
//                TokenType token = entry.first;
//                if (index == tokenString.size()) {
//                    tempMat[tokenStateMap[token][index - 1]][tokenString[index - 1]] = tokenStateMap[token][index];
//                }
//                else if (index < tokenString.size()) {
//                    if (tempMat[tokenStateMap[token][index]][tokenString[index]] > 0) {
//                        tokenStateMap[token][index + 1] = *((int*)(tempMat[tokenStateMap[token][index]][tokenString[index]]));
//                    }
//                    else {
//                        if (one_string.find(token) == one_string.end()) {
//                            tempMat.emplace_back(numCols, 0); // Add a new row to the matrix
//                        }
//                        else
//                        {
//                            tempMat.emplace_back(numCols, -1000);
//                        }
//                        tempMat[tokenStateMap[token][index]][tokenString[index]] = (int)(&(tokenStateMap[token][index + 1]));
//                        tokenStateMap[token][index + 1] = stateCounter++;
//                    }
//                    if (index != 0) {
//                        tempMat[tokenStateMap[token][index - 1]][tokenString[index - 1]] = tokenStateMap[token][index];
//                    }
//                }
//            }
//            int t = index;
//        }
//
//        //numbers
//        int index_of_last_element = tempMat.size();
//        tempMat.emplace_back(numCols, -(int)(TokenType::NUMERIC)); // Add a new row to the matrix for difinders....
//
//        for (const auto& entry : numericCharsMap) {
//            const char& NumberChar = entry.second;
//            TokenType token = entry.first;
//            tempMat[tempMat.size() - 1][NumberChar] = index_of_last_element; //back to start
//            tempMat[0][NumberChar] = index_of_last_element; //back to start
//        }
//
//
//        //literal
//        for (const auto& entry : literalDelimiters) {
//            index_of_last_element++;
//            tempMat.emplace_back(numCols, index_of_last_element); // Add a new row to the matrix for difinders....
//            const char& NumberChar = entry.second;
//            TokenType token = entry.first;
//            tempMat[tempMat.size() - 1][NumberChar] = -(int)(TokenType::LITTERAL); //back to start
//            tempMat[0][NumberChar] = index_of_last_element; //back to start
//        }
//
//
//        index_of_last_element = tempMat.size();
//        tempMat.emplace_back(numCols, index_of_last_element); // Add a new row to the matrix for difinders....
//        // fill the seperators
//        for (const auto& entry : delimiterCharsMap) {
//            const char& seperatorChar = entry.second;
//            TokenType token = entry.first;
//            for (size_t index = 0; index < stateCounter; index++)
//            {
//                if (tempMat[index][seperatorChar] == 0) {
//                    tempMat[index][seperatorChar] = -(int)token;
//                }
//            }
//            tempMat[tempMat.size() - 1][seperatorChar] = -(int)(TokenType::IDENTIFIER); //back to start
//
//        }
//
//        for (size_t i = 0; i < tempMat.size(); i++)
//        {
//            for (const auto& entry : unusedCharsMap)
//            {
//                const char& NumberChar = entry.second;
//                TokenType token = entry.first;
//                tempMat[i][NumberChar] = -(int)(token);
//            }
//
//        }
//
//        transitionMatrix = tempMat;
//    }
//
//
//    const std::vector<std::vector<int>>& getTransitionMatrix() const {
//        return transitionMatrix;
//    }
//
//private:
//
//    void generateTokenStateMap() {
//        size_t maxSize = 0;
//        for (const auto& entry : tokenStringsMap) {
//            TokenType token = entry.first;
//            const std::string& str = entry.second;
//            tokenStateMap[token] = std::vector<int>(str.size() + 1, 0);
//            maxSize = std::max(maxSize, str.size());
//        }
//        maxTokenSize = maxSize + 1;
//    }
//
//    
//};
//
//

#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Token.h"

class LexicalAutomaton {
private:
    int currentState;
    std::vector<std::vector<int>> transitionMatrix;
    int maxTokenSize;
    std::unordered_map<TokenType, std::vector<int>> tokenStateMap;

public:
    int getCurrentState() const;
    void transition(char inputChar);
    void resetCurrentState();
    void setCurrentState(int state);
    void generateTransitionMatrix();
    const std::vector<std::vector<int>>& getTransitionMatrix() const;

private:
    void generateTokenStateMap();
};

