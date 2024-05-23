#include "lexer.h"

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
            _tokens.push_back(Token { PLUS, "+", _position });
            break;
        case '-':
            _position++;
            _tokens.push_back(Token { MINUS, "-", _position });
            break;
        case '*':
            _position++;
            _tokens.push_back(Token { MULTIPLY, "*", _position });
            break;
        case '/':
            _position++;
            _tokens.push_back(Token { DIVIDE, "/", _position });
            break;
        case '(':
            _position++;
            _tokens.push_back(Token { LPAREN, "(", _position });
            break;
        case ')':
            _position++;
            _tokens.push_back(Token { RPAREN, ")", _position });
            break;
        case ';':
            _position++;
            _tokens.push_back(Token { SEMICOLON, ";", _position });
            break;
        case ',':
            _position++;
            _tokens.push_back(Token { COMMA, ",", _position });
            break;
        case '&':
            _position++;
            _tokens.push_back(Token { AND, "&", _position });
            break;
        case '|':
            _position++;
            _tokens.push_back(Token { OR, "|", _position });
            break;
        case '{':
            _position++;
            _tokens.push_back(Token { LBRACE, "{", _position });
            break;
        case '\n':
            _position++;
            _tokens.push_back(Token { EOL, "EOL", _position });
            break;
        case '}':
            _position++;
            _tokens.push_back(Token { RBRACE, "}", _position });
            break;
        case '[':
            _position++;
            _tokens.push_back(Token { LSQUARE, "[", _position });
            break;
        case ']':
            _position++;
            _tokens.push_back(Token { RSQUARE, "]", _position });
            break;
        case '!':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                _tokens.push_back(Token { NOT_EQUALS, "!=", _position });
                break;
            } else {
                _position++;
                _tokens.push_back(Token { NOT, "!", _position });
                break;
            }
        case '<':
        case '>':
        case '=':
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                if (currentChar == '<') {
                    _tokens.push_back(Token { LESS_OR_EQUALS, "<=", _position });
                    break;
                } else if (currentChar == '>') {
                    _tokens.push_back(Token { GREATER_OR_EQUALS, ">=", _position });
                    break;
                } else if (currentChar == '=') {
                    _tokens.push_back(Token { EQUALS, "==", _position });
                    break;
                }
            } else {
                _position++;
                if (currentChar == '<') {
                    _tokens.push_back(Token { LESS, "<", _position });
                    break;
                } else if (currentChar == '>') {
                    _tokens.push_back(Token { GREATER, ">", _position });
                    break;
                } else if (currentChar == '=') {
                    _tokens.push_back(Token { ASSIGN, "=", _position });
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
                    _tokens.push_back(Token { INT_DECLARE, "int", _position });
                    break;
                } else if (word == "float") {
                    _tokens.push_back(Token { FLOAT_DECLARE, "float", _position });
                    break;
                } else if (word == "array") {
                    _tokens.push_back(Token { ARRAY_DECLARE, "array", _position });
                    break;
                } else if (word == "print") {
                    _tokens.push_back(Token { PRINT, "print", _position });
                    break;
                } else if (word == "input") {
                    _tokens.push_back(Token { INPUT, "input", _position });
                    break;
                } else if (word == "if") {
                    _tokens.push_back(Token { IF, "if", _position });
                    break;
                } else if (word == "else") {
                    _tokens.push_back(Token { ELSE, "else", _position });
                    break;
                } else if (word == "while") {
                    _tokens.push_back(Token { WHILE, "while", _position });
                    break;
                } else if (word == "const") {
                    _tokens.push_back(Token { CONST_DECLARE, "const", _position });
                    break;
                } else {
                    _tokens.push_back(Token { NAME, word, _position });
                    break;
                }
            } else if (isspace(currentChar)) {
                skipWhitespace();
                continue;
            }
            break;
        }

        if (_tokens.back().type == ERROR) {
            std::cout << "Lexer panics!  " << _tokens.back();
            exit(1);
        }
    }

    _tokens.push_back(Token { END, "END", ++_position });
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
                return Token { ERROR, "ERROR", _position }; // 13. Символ в неположенном месте.
            }
            if (_position + 1 < _input.length() && isdigit(_input[_position + 1])
                && _position - 1 >= 0 && isdigit(_input[_position - 1])) {
                isFloat = true;
                x = static_cast<float>(n); // 10. Переход с целого числа на вещественное.
            } else { // Если точка не окружена цифрами.
                if (_input[_position + 1] == ';' || isspace(_input[_position + 1])) {
                    _position++;
                    return Token { ERROR, "ERROR", _position }; // 13. Символ в неположенном месте.
                } else {
                    _position++;
                    return Token { ERROR, "ERROR", _position }; // 13. Символ в неположенном месте.
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
        case '(':
        case ')':
        case '[':
        case ']':
            return isFloat ? Token { FLOAT, x, _position } : Token { INTEGER, n, _position };
            break;
        default:
            if (!isdigit(currentChar)) {
                _position++;
                return Token { ERROR, result, _position };
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
    return isFloat ? Token { FLOAT, x, _position } : Token { INTEGER, n, _position };
}

void Lexer::skipWhitespace()
{
    while (_position < _input.length() && isspace(_input[_position])) {
        _position++;
    }
}
