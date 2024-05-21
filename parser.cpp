#include "parser.h"

Parser::Parser()
{}

void Parser::setTokens(const std::vector<Token> &tokens)
{
    _tokens = tokens;
}

bool Parser::isOperator(const TokenType type)
{
    return type == PLUS || type == MULTIPLY || type == DIVIDE || type == ASSIGN || type == EQUALS
           || type == NOT_EQUALS || type == LESS || type == GREATER || type == LESS_OR_EQUALS
           || type == GREATER_OR_EQUALS;
}

int Parser::precedence(const TokenType type)
{
    switch (type) {
    case MULTIPLY:
    case DIVIDE:
        return 3;
    case EQUALS:
    case NOT_EQUALS:
    case GREATER_OR_EQUALS:
    case LESS_OR_EQUALS:
    case LESS:
    case GREATER:
        return 2;
    case PLUS:
    case MINUS:
        return 1;
    case ASSIGN:
        return 0;
    default:
        return -1;
    }
}

std::string Parser::getStringFromVariant(const std::variant<std::string, int, float> &var)
{
    if (std::holds_alternative<std::string>(var)) {
        return std::get<std::string>(var);
    } else if (std::holds_alternative<int>(var)) {
        return std::to_string(std::get<int>(var));
    } else if (std::holds_alternative<float>(var)) {
        return std::to_string(std::get<float>(var));
    } else {
        throw std::runtime_error("Unsupported variant type");
    }
}

std::vector<std::string> Parser::parseToRPN()
{
    if (_tokens[0].type == END)
        return std::vector<std::string> { "Empty" };

    std::vector<std::string> output;
    std::stack<Token> operators;

    for (const auto &token : _tokens) {
        switch (token.type) {
        case NAME:
        case INTEGER:
            output.push_back(getStringFromVariant(token.value));
            break;
        case FLOAT:
            output.push_back(getStringFromVariant(token.value));
            break;
        case ASSIGN:
            operators.push(token);
            break;
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
            while (!operators.empty()
                   && precedence(operators.top().type) >= precedence(token.type)) {
                output.push_back(getStringFromVariant(operators.top().value));
                operators.pop();
            }
            operators.push(token);
            break;
        case LPAREN:
            operators.push(token);
            break;
        case RPAREN:
            while (!operators.empty() && operators.top().type != LPAREN) {
                output.push_back(getStringFromVariant(operators.top().value));
                operators.pop();
            }
            if (operators.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.pop(); // Удаляем левую скобку
            break;
        case SEMICOLON:
            while (!operators.empty()) {
                output.push_back(getStringFromVariant(operators.top().value));
                operators.pop();
            }
            break;
        default:
            break;
        }
    }

    while (!operators.empty()) {
        if (operators.top().type == LPAREN) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(getStringFromVariant(operators.top().value));
        operators.pop();
    }

    return output;
}
