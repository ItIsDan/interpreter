#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <iostream>
#include <stack>

class Parser
{
public:
    Parser();

    void setTokens(const std::vector<Token> &tokens);
    std::string getStringFromVariant(const std::variant<std::string, int, float> &var);
    std::vector<std::string> parseToRPN();

    bool isOperator(const TokenType type);

    int precedence(const TokenType type);

private:
    std::vector<Token> _tokens;
};

#endif // PARSER_H
