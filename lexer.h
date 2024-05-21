#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <variant>
#include <vector>
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

    friend std::ostream &operator<<(std::ostream &os, const Token token);
};

class Lexer
{
public:
    explicit Lexer();

    void setText(const std::string &text);

    void generateTokens();

    static std::string tokenToString(Token token);

    std::vector<Token> tokens() const;

private:
    std::string _input;
    size_t _position;

    Token parseNumber();

    void skipWhitespace();

    std::vector<Token> _tokens;
};

#endif // LEXER_H
