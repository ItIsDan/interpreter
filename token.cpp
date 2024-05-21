#include "token.h"

std::ostream &operator<<(std::ostream &os, const Token token)
{
    os << "Token type: " << tokenToString(token.type) << "\t\tvalue: ";
    std::visit(
     [&os](auto &&arg) {
         os << arg;
     },
     token.value);
    return os << "\t\tEnd position: " << token.endPosition << "\n";
}

std::string tokenToString(TokenType type)
{
    switch (type) {
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
