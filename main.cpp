#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lexer.h"

int main()
{
    string input = "1 == hello 13 31.23 .. 32";
    Lexer lexer;
    lexer.setText(input);

    vector<Token> tokens;
    Token token = lexer.getNextToken();
    while (token.type != END) {
        tokens.push_back(token);
        token = lexer.getNextToken();
    }

    for (const Token &token : tokens) {
        if (token.type != ERROR)
            std::cout << lexer.tokenToString(token) << " ";
        else {
            std::cout << lexer.tokenToString(token) << "\n";
            exit(-1);
        }
    }
    cout << endl;

    return 0;
}
