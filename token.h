#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>
#include <iostream>

enum TokenType : int
{
    DEFAULT = -3,
    EMPTY = -2,
    ERROR = -1,
    INTEGER,
    FLOAT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    SEMICOLON,
    COMMA,
    LBRACE,
    RBRACE,
    LSQUARE,
    RSQUARE,
    NOT,
    LESS,
    GREATER,
    LESS_OR_EQUAL,
    GREATER_OR_EQUAL,
    EQUAL,
    NOT_EQUALS,
    ASSIGN,
    INT_DECLARE,
    FLOAT_DECLARE,
    ARRAY_DECLARE,
    READ,
    WRITE,
    IF,
    ELSE,
    WHILE,
    AND,
    OR,
    NAME,
    EOL,
    END
};

// Текущие состояния, енам состояний
enum State
{

};

struct Token
{
    TokenType type { EMPTY };
    std::variant<std::string, int, float> value;
    size_t endPosition;

    friend std::ostream &operator<<(std::ostream &os, const Token token);
};

std::string tokenToString(TokenType type);

#endif // TOKEN_H
