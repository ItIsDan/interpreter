#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <variant>

using namespace std;

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
    END
};

struct Token
{
    TokenType type { EMPTY };
    std::variant<std::string, int, double> value;
};

class Lexer
{
public:
    explicit Lexer();

    void setText(const string &text);

    Token getNextToken();

    string tokenToString(TokenType token);

private:
    string _input;
    size_t _position;

    Token parseNumber();

    void skipWhitespace();
};

#endif // LEXER_H
