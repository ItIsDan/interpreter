#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lexer.h"

int main()
{
    std::string input = "54.44 e";
    Lexer lexer;
    lexer.setText(input);

    lexer.generateTokens();

    for (const Token &token : lexer.tokens()) {
        std::cout << token;
    }

    std::cout << std::endl;

    return 0;
}
