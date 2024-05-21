#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lexer.h"

int main()
{
    std::string input = "int a = 4.2;";
    Lexer lexer;
    lexer.setText(input);

    lexer.generateTokens();

    for (const Token &token : lexer.tokens()) {
        if (token.type != ERROR)
            std::cout << token;
        else {
            std::cout << token;
            exit(-1);
        }
    }

    std::cout << std::endl;

    return 0;
}
