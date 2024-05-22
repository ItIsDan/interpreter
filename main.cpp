#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lexer.h"
#include "parser.h"

int main()
{
    std::string input = "float a; a = 4.4;";
    Lexer lexer;
    lexer.setText(input);

    lexer.generateTokens();
    auto tokens = lexer.tokens();

    for (const Token &token : tokens) {
        //        std::cout << token;
    }

    Parser parser;
    parser.setTokens(tokens);

    auto RPN = parser.parseToRPN();
    //            std::cout << input << "\n";

    for (const auto &a : RPN) std::cout << a << " ";

    std::cout << "_|_" << std::endl;

    return 0;
}
