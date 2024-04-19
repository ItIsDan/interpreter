#ifndef LEXER_H
#define LEXER_H

#include <string>
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
    std::string value {};
    int begin; // Начало лексемы
    int end; // конец лексемы
    //    int intresult;
    //    float fresult;
};

// Когда меняется позиция вводит две переменные , где номер в строке увеличивается, если \n то номер
// в строке обнуляем а номер строки увеличиваем.

class Lexer
{
public:
    explicit Lexer();

    void setText(const string &text);

    Token getNextToken();

    string tokenToString(Token token);

private:
    string _input;
    size_t _position;

    Token parseNumber();

    void skipWhitespace();
};

#endif // LEXER_H
