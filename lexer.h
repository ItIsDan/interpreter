#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <string>
#include <vector>

class Lexer
{
public:
    explicit Lexer();

    void setText(const std::string &text);

    void generateTokens();

    std::vector<Token> tokens() const;

private:
    std::string _input;
    size_t _position;

    Token parseNumber();

    void skipWhitespace();

    std::vector<Token> _tokens;
};

#endif // LEXER_H
