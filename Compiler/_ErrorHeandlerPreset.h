#pragma once 
#include <iostream>
#include <fstream>
#include <string>
#define RESET           "\033[0m" 
#define BLACK           "\033[30m"              /* Black */ 
#define RED             "\033[31m"              /* Red */ 
#define GREEN           "\033[32m"              /* Green */ 
#define YELLOW          "\033[33m"              /* Yellow */ 
#define BLUE            "\033[34m"              /* Blue */ 
#define PURPLE          "\033[35m"              /* Purple */ 
#define CYAN            "\033[36m"              /* Cyan */ 
#define WHITE           "\033[37m"              /* White */ 
#define BOLD_BLACK      "\033[1m\033[30m"       /* Bold Black */ 
#define BOLD_RED        "\033[1m\033[31m"       /* Bold Red */ 
#define BOLD_GREEN      "\033[1m\033[32m"       /* Bold Green */ 
#define BOLD_YELLOW     "\033[1m\033[33m"       /* Bold Yellow */ 
#define BOLD_BLUE       "\033[1m\033[34m"       /* Bold Blue */ 
#define BOLD_MAGENTA    "\033[1m\033[35m"       /* Bold Magenta */ 
#define BOLD_CYAN       "\033[1m\033[36m"       /* Bold Cyan */ 
#define BOLD_WHITE      "\033[1m\033[37m"       /* Bold White */ 

enum class Error_Type
{
    Error_General,
    Error_Lexical,
    Error_Syntax,
    Error_Semantic,
};




class Error_heandler {
    Error_Type* type_erorr;
    std::string* file_name;
public:
    Error_heandler(std::string* file_name);
    void error_handler_report(int line, Error_Type error_type);
    const char* error_handler_error_to_str(Error_Type error_type);
    void custume_error_handler_report(int line, Error_Type error_type, const char* format);
private:
    std::string getLineFromFile(const std::string& filename, int lineNumber);
    void error_handler_report(int line, Error_Type error_type, const char* format, ...);

};


