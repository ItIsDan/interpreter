#include "lexer.h"
#include <iostream>

Lexer::Lexer() : _position(0)
{}

void Lexer::setText(const string &text)
{
    if (_input == text)
        return;

    _input = text;
    _position = 0;
}

Token Lexer::getNextToken()
{
    while (_position < _input.length()) {
        char currentChar = _input[_position];

        switch (currentChar) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            return parseNumber();
        case '+':
            _position++;
            return Token { PLUS, "+" };
        case '-':
            _position++;
            return Token { MINUS, "-" };
        case '*':
            _position++;
            return Token { MULTIPLY, "*" };
        case '/':
            _position++;
            return Token { DIVIDE, "/" };
        case '(':
            _position++;
            return Token { LPAREN, "(" };
        case ')':
            _position++;
            return Token { RPAREN, ")" };
        case ';':
            _position++;
            return Token { SEMICOLON, ";" };
        case ',':
            _position++;
            return Token { COMMA, "," };
        case '&':
            _position++;
            return Token { AND, "&" };
        case '|':
            _position++;
            return Token { OR, "|" };
        case '{':
            _position++;
            return Token { LBRACE, "{" };
        case '\n':
            _position++;
            return Token { EOL, "EOL" };
        case '}':
            _position++;
            return Token { RBRACE, "}" };
        case '[':
            _position++;
            return Token { LSQUARE, "[" };
        case ']':
            _position++;
            return Token { RSQUARE, "]" };
        case '!':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                return Token { NOT_EQUALS, "!=" };
            } else {
                _position++;
                return Token { NOT, "!" };
            }
        case '<':
        case '>':
        case '=':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                if (currentChar == '<') {
                    return Token { LESS_OR_EQUAL, "<=" };
                } else if (currentChar == '>') {
                    return Token { GREATER_OR_EQUAL, ">=" };
                } else if (currentChar == '=') {
                    return Token { EQUAL, "==" };
                }
            } else {
                _position++;
                if (currentChar == '<') {
                    return Token { LESS, "<" };
                } else if (currentChar == '>') {
                    return Token { GREATER, ">" };
                } else if (currentChar == '=') {
                    return Token { ASSIGN, "=" };
                }
            }
        default:
            if (isalpha(currentChar)) {
                string word;
                while (_position < _input.length() && isalnum(_input[_position])) {
                    word += _input[_position];
                    _position++;
                }

                if (word == "int") {
                    return Token { INT_DECLARE, "int" };
                } else if (word == "float") {
                    return Token { FLOAT_DECLARE, "float" };
                } else if (word == "arr") {
                    return Token { ARRAY_DECLARE, "arr" };
                } else if (word == "read") {
                    return Token { READ, "read" };
                } else if (word == "write") {
                    return Token { WRITE, "write" };
                } else if (word == "if") {
                    return Token { IF, "if" };
                } else if (word == "else") {
                    return Token { ELSE, "else" };
                } else if (word == "while") {
                    return Token { WHILE, "while" };
                } else {
                    return Token { NAME, word };
                }
            } else if (isspace(currentChar)) {
                skipWhitespace();
                continue;
            }
            break;
        }
    }

    return Token { END, "\0" };
}

string Lexer::tokenToString(Token token)
{
    switch (token.type) {
    case TokenType::DEFAULT:
        return "DEFAULT";
    case TokenType::EMPTY:
        return "EMPTY";
    case TokenType::ERROR:
        return "ERROR";
    case TokenType::INTEGER:
        return "INTEGER";
    case TokenType::FLOAT:
        return "FLOAT";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::MULTIPLY:
        return "MULTIPLY";
    case TokenType::DIVIDE:
        return "DIVIDE";
    case TokenType::LPAREN:
        return "LPAREN";
    case TokenType::RPAREN:
        return "RPAREN";
    case TokenType::SEMICOLON:
        return "SEMICOLON";
    case TokenType::COMMA:
        return "COMMA";
    case TokenType::LBRACE:
        return "LBRACE";
    case TokenType::RBRACE:
        return "RBRACE";
    case TokenType::LSQUARE:
        return "LSQUARE";
    case TokenType::RSQUARE:
        return "RSQUARE";
    case TokenType::NOT:
        return "NOT";
    case TokenType::LESS:
        return "LESS";
    case TokenType::GREATER:
        return "GREATER";
    case TokenType::LESS_OR_EQUAL:
        return "LESS_OR_EQUAL";
    case TokenType::GREATER_OR_EQUAL:
        return "GREATER_OR_EQUAL";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::NOT_EQUALS:
        return "NOT_EQUALS";
    case TokenType::ASSIGN:
        return "ASSIGN";
    case TokenType::INT_DECLARE:
        return "INT_DECLARE";
    case TokenType::FLOAT_DECLARE:
        return "FLOAT_DECLARE";
    case TokenType::ARRAY_DECLARE:
        return "ARRAY";
    case TokenType::READ:
        return "READ";
    case TokenType::WRITE:
        return "WRITE";
    case TokenType::IF:
        return "IF";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::NAME:
        return "NAME";
    case TokenType::AND:
        return "AND";
    case TokenType::OR:
        return "OR";
    case TokenType::END:
        return "END";
    case TokenType::EOL:
        return "EOL";
    default:
        return "UNKNOWN";
    }
}

Token Lexer::parseNumber()
{
    string result;
    int n { 0 };
    float x;
    float d { 1 };
    bool isFloat = false;

    for (; _position < _input.length(); _position++) {
        char currentChar = _input[_position];

        switch (currentChar) {
        case '.':
            if (isFloat) { // Если число уже вещественное.
                _position++;
                return Token { ERROR, "ERROR" }; // 13. Символ в неположенном месте.
            }
            if (_position + 1 < _input.length() && isdigit(_input[_position + 1])
                && _position - 1 >= 0 && isdigit(_input[_position - 1])) {
                isFloat = true;
                x = static_cast<float>(n); // 10. Переход с целого числа на вещественное.
            } else { // Если точка не окружена цифрами.
                if (_input[_position + 1] == ';' || isspace(_input[_position + 1])) {
                    _position++;
                    return Token { ERROR, "ERROR" }; // 13. Символ в неположенном месте.
                } else {
                    _position++;
                    return Token { ERROR, "ERROR" }; // 13. Символ в неположенном месте.
                }
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case ';':
        case '=':
        case ' ':
        case '{':
        case '}':
            return isFloat ? Token { FLOAT, x } : Token { INTEGER, n };
            break;
        default:
            if (!isdigit(currentChar)) {
                _position++;
                return Token { ERROR, result };
            }
            if (!isFloat) // 2. Продолжение лексемы числа
                n = n * 10 + (int)currentChar - (int)'0';
            else { // 11. Продолжение лексемы вещественного числа
                d *= 0.1f;
                x = x + ((int)currentChar - (int)'0') * d;
            }
            break;
        }
    }
    return isFloat ? Token { FLOAT, x } : Token { INTEGER, n };
}

void Lexer::skipWhitespace()
{
    while (_position < _input.length() && isspace(_input[_position])) {
        _position++;
    }
}
