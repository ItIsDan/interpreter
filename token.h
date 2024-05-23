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
    LESS_OR_EQUALS,
    GREATER_OR_EQUALS,
    EQUALS,
    NOT_EQUALS,
    ASSIGN,
    INT_DECLARE,
    FLOAT_DECLARE,
    ARRAY_DECLARE,
    CONST_DECLARE,
    PRINT,
    INPUT,
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

enum RPSElementType
{
    RPS_STRING,
    RPS_INTEGER,
    RPS_FLOAT,
    RPS_OPERATOR,
    RPS_ARRAY_DECLARE,
    RPS_INDEX,
    RPS_PRINT,
    RPS_INPUT
};

struct RPSElement
{
    RPSElementType type;
    TokenType tokenType; // Как уточнение
    std::variant<std::string, int, float> value;

    friend std::ostream &operator<<(std::ostream &os, const RPSElement element);
};

#endif // TOKEN_H
