#include "lexer.h"

Lexer::Lexer() : _position(0)
{}

void Lexer::setText(const string &text)
{
    if (_input == text)
        return;

    _input = text;
}

Token Lexer::getNextToken()
{
    while (_position < _input.length()) {
        char currentChar = _input[_position];
        if (isdigit(currentChar) || currentChar == '.') {
            return parseNumber();
        } else if (currentChar == '+') {
            _position++;
            return Token { PLUS, "+" };
        } else if (currentChar == '-') {
            _position++;
            return Token { MINUS, "-" };
        } else if (currentChar == '*') {
            _position++;
            return Token { MULTIPLY, "*" };
        } else if (currentChar == '/') {
            _position++;
            return Token { DIVIDE, "/" };
        } else if (currentChar == '(') {
            _position++;
            return Token { LPAREN, "(" };
        } else if (currentChar == ')') {
            _position++;
            return Token { RPAREN, ")" };
        } else if (currentChar == ';') {
            _position++;
            return Token { SEMICOLON, ";" };
        } else if (currentChar == ',') {
            _position++;
            return Token { COMMA, "," };
        } else if (currentChar == '&') {
            _position++;
            return Token { AND, "&" };
        } else if (currentChar == '|') {
            _position++;
            return Token { OR, "|" };
        } else if (currentChar == '{') {
            _position++;
            return Token { LBRACE, "{" };
        } else if (currentChar == '}') {
            _position++;
            return Token { RBRACE, "}" };
        } else if (currentChar == '[') {
            _position++;
            return Token { LSQUARE, "[" };
        } else if (currentChar == ']') {
            _position++;
            return Token { RSQUARE, "]" };
        } else if (currentChar == '!') {
            if (_position + 1 < _input.length() && _input[_position + 1] == '=') {
                _position += 2;
                return Token { NOT_EQUALS, "!=" };
            } else {
                _position++;
                return Token { NOT, "!" };
            }
        } else if (currentChar == '<' || currentChar == '>' || currentChar == '=') {
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
        } else if (isalpha(currentChar)) {
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
    }
    return Token { END, "\0" };
}

string Lexer::tokenToString(TokenType token)
{
    switch (token) {
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
    default:
        return "UNKNOWN";
    }
}

Token Lexer::parseNumber()
{
    string result;
    bool isFloat = false;

    for (; _position < _input.length(); _position++) {
        char currentChar = _input[_position];

        switch (currentChar) {
            case '.':
                if (isFloat) {
                    _position++;
                    return Token { ERROR, result };
                }
                if (_position + 1 < _input.length() && isdigit(_input[_position + 1])) {
                    isFloat = true;
                    result += currentChar;
                } else {
                    if (_input[_position + 1] == ';' || isspace(_input[_position + 1])) {
                        _position++;
                        return Token { ERROR, result };
                    } else {
                        _position++;
                        return Token { ERROR, result };
                    }
                }
                break;
            case ';':
                return isFloat ? Token { FLOAT, std::stod(result) } : Token { INTEGER, std::stoi(result) };
            default:
                if (!isdigit(currentChar)) {
                    if (isspace(currentChar))
                        break;

                    _position++;
                    return Token { ERROR, result };
                }
                result += currentChar;
                break;
        }
    }
    return isFloat ? Token { FLOAT, std::stod(result) } : Token { INTEGER, std::stoi(result) };
}

void Lexer::skipWhitespace()
{
    while (_position < _input.length() && isspace(_input[_position])) {
        _position++;
    }
}
