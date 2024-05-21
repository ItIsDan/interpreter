#include "lexer.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Token token)
{
    os << "Token type: " << Lexer::tokenToString(token) << ", value: ";
    std::visit(
     [&os](auto &&arg) {
         os << arg;
     },
     token.value);
    return os << "\n";
}

Lexer::Lexer() : _position(0)
{}

void Lexer::setText(const std::string &text)
{
    if (_input == text)
        return;

    _input = text;

    _position = 0;
}

void Lexer::generateTokens()
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
            _tokens.push_back(parseNumber());
            break;
        case '+':
            _position++;
            _tokens.push_back(Token { PLUS, "+" });
            break;
        case '-':
            _position++;
            _tokens.push_back(Token { MINUS, "-" });
            break;
        case '*':
            _position++;
            _tokens.push_back(Token { MULTIPLY, "*" });
            break;
        case '/':
            _position++;
            _tokens.push_back(Token { DIVIDE, "/" });
            break;
        case '(':
            _position++;
            _tokens.push_back(Token { LPAREN, "(" });
            break;
        case ')':
            _position++;
            _tokens.push_back(Token { RPAREN, ")" });
            break;
        case ';':
            _position++;
            _tokens.push_back(Token { SEMICOLON, ";" });
            break;
        case ',':
            _position++;
            _tokens.push_back(Token { COMMA, "," });
            break;
        case '&':
            _position++;
            _tokens.push_back(Token { AND, "&" });
            break;
        case '|':
            _position++;
            _tokens.push_back(Token { OR, "|" });
            break;
        case '{':
            _position++;
            _tokens.push_back(Token { LBRACE, "{" });
            break;
        case '\n':
            _position++;
            _tokens.push_back(Token { EOL, "EOL" });
            break;
        case '}':
            _position++;
            _tokens.push_back(Token { RBRACE, "}" });
            break;
        case '[':
            _position++;
            _tokens.push_back(Token { LSQUARE, "[" });
            break;
        case ']':
            _position++;
            _tokens.push_back(Token { RSQUARE, "]" });
            break;
        case '!':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                _tokens.push_back(Token { NOT_EQUALS, "!=" });
                break;
            } else {
                _position++;
                _tokens.push_back(Token { NOT, "!" });
                break;
            }
        case '<':
        case '>':
        case '=':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                if (currentChar == '<') {
                    _tokens.push_back(Token { LESS_OR_EQUAL, "<=" });
                    break;
                } else if (currentChar == '>') {
                    _tokens.push_back(Token { GREATER_OR_EQUAL, ">=" });
                    break;
                } else if (currentChar == '=') {
                    _tokens.push_back(Token { EQUAL, "==" });
                    break;
                }
            } else {
                _position++;
                if (currentChar == '<') {
                    _tokens.push_back(Token { LESS, "<" });
                    break;
                } else if (currentChar == '>') {
                    _tokens.push_back(Token { GREATER, ">" });
                    break;
                } else if (currentChar == '=') {
                    _tokens.push_back(Token { ASSIGN, "=" });
                    break;
                }
            }
        default:
            if (isalpha(currentChar)) {
                std::string word;
                while (_position < _input.length() && isalnum(_input[_position])) {
                    word += _input[_position];
                    _position++;
                }

                if (word == "int") {
                    _tokens.push_back(Token { INT_DECLARE, "int" });
                    break;
                } else if (word == "float") {
                    _tokens.push_back(Token { FLOAT_DECLARE, "float" });
                    break;
                } else if (word == "arr") {
                    _tokens.push_back(Token { ARRAY_DECLARE, "arr" });
                    break;
                } else if (word == "read") {
                    _tokens.push_back(Token { READ, "read" });
                    break;
                } else if (word == "write") {
                    _tokens.push_back(Token { WRITE, "write" });
                    break;
                } else if (word == "if") {
                    _tokens.push_back(Token { IF, "if" });
                    break;
                } else if (word == "else") {
                    _tokens.push_back(Token { ELSE, "else" });
                    break;
                } else if (word == "while") {
                    _tokens.push_back(Token { WHILE, "while" });
                    break;
                } else {
                    _tokens.push_back(Token { NAME, word });
                    break;
                }
            } else if (isspace(currentChar)) {
                skipWhitespace();
                continue;
            }
            break;
        }
    }

    _tokens.push_back(Token { END, "\0" });
}

std::string Lexer::tokenToString(Token token)
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

std::vector<Token> Lexer::tokens() const
{
    return _tokens;
}

Token Lexer::parseNumber()
{
    std::string result;
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
