#include <stdlib.h> 
#include <stdio.h> 
#include <stdarg.h> 
#include <string> 
#include <iostream>
#include <fstream>


#include "_ErrorHeandlerPreset.h" 

Error_heandler::Error_heandler(std::string* file_name):file_name(file_name) {
    type_erorr = nullptr;
}

std::string Error_heandler::getLineFromFile(const std::string& filename, int lineNumber) {
    if (lineNumber == -1) {
        return "";
    }
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return "";
    }

    std::string line;
    int currentLine = 0;

    while (std::getline(file, line)) {
        if (currentLine == lineNumber) {
            return line;
        }
        currentLine++;
    }

    std::cerr << "Line number " << lineNumber << " does not exist in the file. \n" << std::endl;
    return "";
}


void Error_heandler::error_handler_report(int line, Error_Type error_type) {
    error_handler_report(line, error_type, getLineFromFile(file_name->c_str(), line).c_str());
}

void Error_heandler::error_handler_report(int line, Error_Type error_type, const char* format, ...)
{
    if (line == -1) {
        printf("\n[ %s ] \n",
            error_handler_error_to_str(error_type));
        return;
    }

    printf("\n[ %s on line %d ] \n",
        error_handler_error_to_str(error_type), line+1);

    va_list args;           // Declare a va_list type variable 
    va_start(args, format); // Initialize the va_list with the ... 
    vprintf(format, args);  // Forward ... to vprintf 
    va_end(args);           // Clean up the va_list 
    printf("\n");
}

void Error_heandler::custume_error_handler_report(int line, Error_Type error_type, const char* format)
{
    if (line == -1) {
        printf("\n[ %s -> %s] \n",
            error_handler_error_to_str(error_type), format);
        return;
    }

    printf("\n[ %s on line %d -> %s ] \n",
        error_handler_error_to_str(error_type), line + 1,format);
    printf("\n");

}

const char* Error_heandler::error_handler_error_to_str(Error_Type error_type) {
    switch (error_type)
    {
    case Error_Type::Error_Lexical: return "Lexical Error";
    case Error_Type::Error_Syntax: return "Syntax Error";
    case Error_Type::Error_Semantic: return "Semantic Error";
    default: return "Error";
    }
}
