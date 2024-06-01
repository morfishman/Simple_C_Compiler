#include "LexicalAnalyzer.h"

// Assuming tokenLookupTable is defined somewhere in your project
extern std::unordered_map<std::string, TokenType> tokenLookupTable;

LexicalAnalyzer::LexicalAnalyzer(const std::string& input, const LexicalAutomaton& lexerAutomaton)
    : inputString(input), automaton(lexerAutomaton), inputIndex(0), recognizedTokens() {}

void LexicalAnalyzer::_BOOT_() {
    automaton.resetCurrentState();
    automaton.generateTransitionMatrix();
    inputIndex = 0;
    recognizedTokens.clear();
}

Token* LexicalAnalyzer::getNextToken() {
    bool tokenier = false;
    std::string currentToken = "";
    bool identifierFlag = false;
    bool done = false;
    int currentState = 0;
    while (!done && inputIndex < inputString.size()) {
        char ch = this->inputString[this->inputIndex];
        this->automaton.transition(ch);
        currentState = this->automaton.getCurrentState();
        // Handle transitions and build currentToken
        std::string _stringos_ = "" + ch;


        if (currentState > 0) {
            currentToken += ch;
        }
        else if (currentState == 0) {
            currentToken += ch;
            this->automaton.setCurrentState(this->automaton.getTransitionMatrix().size() - 1);
            identifierFlag = true;
        }
        else {
            if (currentToken.empty()) {
                currentToken += ch;
                TokenType temp = tokenLookupTable[currentToken];
                Token* tempToken = new Token(currentToken, temp, this->inputIndex);
                currentToken = "";
                currentState = 0;
                done = true;
                recognizedTokens.push_back(tempToken);
                tokenier = true;
            }
            else {
                auto it = tokenLookupTable.find(currentToken);
                if ((int)(TokenType::NUMERIC) == currentState * (-1)) {
                    it = tokenLookupTable.find("''number''");
                }
                else if ((int)(TokenType::LITTERAL) == currentState * (-1)) {
                    it = tokenLookupTable.find("''literal''");
                    if (currentToken[0] == '\'') {
                        currentToken.erase(0, 1);
                        if (currentToken.size() > 1 || currentToken.size() == 0) {
                            it = tokenLookupTable.find("''error''");
                        }
                        else {
                            it = tokenLookupTable.find("''chr_literal''");
                        }
                    }
                    else {
                        currentToken.erase(0, 1);
                        if (currentToken.size() == 1) {
                            it = tokenLookupTable.find("''chr_literal''");
                        }
                        else if (currentToken.size() == 0) {
                            it = tokenLookupTable.find("''error''");
                        }
                        else {
                            it = tokenLookupTable.find("''error''");
                        }
                    }
                    this->inputIndex++;
                }
                if (it == tokenLookupTable.end()) identifierFlag = true;
                if (identifierFlag) {
                    TokenType temp = TokenType::IDENTIFIER;
                    Token* tempToken = new Token(currentToken, temp, this->inputIndex);
                    done = true;
                    identifierFlag = false;
                    currentToken = "";
                    recognizedTokens.push_back(tempToken);
                    tokenier = true;
                }
                else {
                    TokenType temp = it->second;
                    Token* tempToken = new Token(currentToken, temp, this->inputIndex);
                    done = true;
                    recognizedTokens.push_back(tempToken);
                    tokenier = true;
                }
                currentToken = "";
                currentState = 0;
                inputIndex--;
            }

        }
        // Emit token when necessary
        inputIndex++;
    }
    if (!currentToken.empty()) {
        tokenier = true;
        if (currentToken[0] == '\'' || currentToken[0] == '\"') {
            TokenType temp = TokenType::ERROR;
            Token* tempToken = new Token(currentToken, temp, this->inputIndex);
            recognizedTokens.push_back(tempToken);
            tokenier = true;
        }
        else {
            auto it = tokenLookupTable.find(currentToken);
            if ((int)(TokenType::NUMERIC) == currentState * (-1)) {
                it = tokenLookupTable.find("''number''");
            }
            else if ((int)(TokenType::LITTERAL) == currentState * (-1)) {
                it = tokenLookupTable.find("''literal''");
                if (currentToken[0] == '\'') {
                    currentToken.erase(0, 1);
                    if (currentToken.size() > 1 || currentToken.size() == 0) {
                        it = tokenLookupTable.find("''error''");
                    }
                    else {
                        it = tokenLookupTable.find("''chr_literal''");
                    }
                }
                else {
                    currentToken.erase(0, 1);
                    if (currentToken.size() == 1) {
                        it = tokenLookupTable.find("''chr_literal''");
                    }
                    else if (currentToken.size() == 0) {
                        it = tokenLookupTable.find("''error''");
                    }
                    else {
                        it = tokenLookupTable.find("''error''");
                    }
                }
                this->inputIndex++;
            }
            if (it == tokenLookupTable.end()) identifierFlag = true;
            if (identifierFlag) {
                TokenType temp = TokenType::IDENTIFIER;
                Token* tempToken = new Token(currentToken, temp, this->inputIndex);
                done = true;
                identifierFlag = false;
                recognizedTokens.push_back(tempToken);
                tokenier = true;
            }
            else {
                TokenType temp = it->second;
                Token* tempToken = new Token(currentToken, temp, this->inputIndex);
                done = true;
                recognizedTokens.push_back(tempToken);
                tokenier = true;
            }
        }
    }
    automaton.resetCurrentState();

    if (inputIndex >= inputString.size() && tokenier == false) {
        return nullptr;
    }
    return recognizedTokens.back();
}

const std::vector<Token*>& LexicalAnalyzer::getRecognizedTokens() const {
    return recognizedTokens;
}
