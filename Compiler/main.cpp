#include "LexicalAutomaton.h" // Include the header file for LexicalAutomaton class
#include "LexicalAnalyzer.h"  // Include the header file for LexicalAnalyzer class
#include "Parser.h"
#include "SymanticAnalayser.h"
#include "CodeGenerator.h"
#include "_ErrorHeandlerPreset.h"
#include <thread> // for sleep_for function
#include <chrono> // for chrono literals



int main(int argc, char* argv[]) {
    
    if(argc!= 3){
        std::cerr << "for the compiler pass end-to-end files" << std::endl;
    }
    else {
        std::string* input_file_name = new std::string(argv[1]);
        Error_heandler* Er = new Error_heandler(input_file_name);
        std::ifstream inputFile(input_file_name->c_str()); // Assuming the input file is named "input.txt"
        // Check if the file is opened successfully
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the input file. "  << input_file_name->c_str()<< std::endl;
            return 1; // Return with an error status
        }

        // Read the content of the file into a string
        std::string input((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        // Close the input file
        inputFile.close();
        input += "\x03";

        // Create an instance of LexicalAutomaton
        LexicalAutomaton automaton;

        int line_number = 0;

        // Create an instance of LexicalAnalyzer
        LexicalAnalyzer lex(input, automaton);


        lex._BOOT_();


        ParseTreeNodeStack* parserStack = new ParseTreeNodeStack();
        Parser parser("C:\\Users\\User\\source\\repos\\Compiler\\Compiler\\goto_table.csv", "C:\\Users\\User\\source\\repos\\Compiler\\Compiler\\action_table.csv", parserStack);

        // Process tokens one by one
        Token* currentToken;
        while ((currentToken = lex.getNextToken()) != nullptr) {
            if (currentToken->getType() == TokenType::LINE_FEED)
            {
                line_number++;
            }
            if (currentToken->getType() == TokenType::ERROR) {
                Er->error_handler_report(line_number, Error_Type::Error_Lexical);
                return 0;
            }
            else {
                currentToken->line_number = line_number;
            }
            int stateOfParse;
            do
            {
                stateOfParse = parser.syntaxAnalays(currentToken);
            } while (stateOfParse < 0);
            if (stateOfParse == 0) {

                Er->error_handler_report(line_number, Error_Type::Error_Syntax);
                return 0;
            }
        }

        printf("\n[%s\t -> %s]\n",
            "Lexical Analysis", "succsed");
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 4 seconds
        printf("\n[%s\t -> %s]\n",
            "Syntax Analysis", "succsed");
        std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Sleep for 4 seconds
        SymanticAnalaser* sa = new SymanticAnalaser(parser.extractTree(), Er);
        sa->setFunctionMap();
        bool result = sa->Symantic_Aalisers();
        if (result) {
            printf("\n[%s\t -> %s]\n",
                "Symantic Analysis", "succsed");
            std::this_thread::sleep_for(std::chrono::milliseconds(1700)); // Sleep for 4 seconds
            Code_Generator* Cg = new Code_Generator(parser.extractTree(), sa->extract_symbalTable());
            bool t = Cg->init(new std::string(argv[2]));
            if (!t)return 1;
            Cg->generate();
            printf("\n[%s\t\t -> %s]\n",
                "Generating", "succsed");

        }
        printf("\n%s","Cleaning up memory");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf(".");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf(".");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        printf(".");
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        printf(".\n");
        // Clean up memory allocated for tokens
        const std::vector<Token*>& recognizedTokens = lex.getRecognizedTokens();
        for (Token* token : recognizedTokens) {
            delete token;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("->\t%s\n", "succsed");
        return 0;
    }
    return 1;
}
