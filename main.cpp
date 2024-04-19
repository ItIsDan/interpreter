#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "lexer.h"

int main()
{
    string input = "a.1";
    Lexer lexer;
    lexer.setText(input);

    vector<Token> tokens;
    Token token = lexer.getNextToken();
    while (token.type != END) {
        tokens.push_back(token);
        token = lexer.getNextToken();
    }

    for (const Token &token : tokens) std::cout << lexer.tokenToString(token) << " ";
    cout << endl;

    return 0;
}
