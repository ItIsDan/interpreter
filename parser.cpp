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

std::vector<RPSElement> Parser::parseToRPN()
{
    if (_tokens[0].type == END) {
        std::cout << "Tokens were empty";
        exit(0);
    }
    // Empty lexer

    for (const auto &token : _tokens)
        if (token.type == ERROR) {
            std::cout << "Parser panics! " << token;
            exit(2);
        }
    // Error token found, somehow passed lexer

    std::vector<RPSElement> output;
    std::stack<RPSElement> operators;
    std::unordered_set<std::string> declaredVariables;

    for (size_t i = 0; i < _tokens.size(); ++i) {
        switch (_tokens[i].type) {
        case NAME:
            if ((i - 1 >= 0)
                && ((_tokens[i - 1].type == INT_DECLARE) || _tokens[i - 1].type == FLOAT_DECLARE)
                && (_tokens[i + 1].type != ASSIGN)) {
                break;
            }
            if (declaredVariables.find(getStringFromVariant(_tokens[i].value))
                == declaredVariables.end()) {
                throw std::runtime_error("Use of undeclared variable: "
                                         + getStringFromVariant(_tokens[i].value));
            }
            output.push_back({ RPS_STRING, _tokens[i].type, _tokens[i].value });
            break;
        case INTEGER:
            output.push_back({ RPS_INTEGER, _tokens[i].type, _tokens[i].value });
            break;
        case FLOAT:
            output.push_back({ RPS_FLOAT, _tokens[i].type, _tokens[i].value });
            break;
        case ASSIGN:
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
            while (!operators.empty()
                   && precedence(static_cast<TokenType>(operators.top().tokenType))
                       >= precedence(_tokens[i].type)) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push({ RPS_OPERATOR, _tokens[i].type, _tokens[i].value });
            break;
        case LPAREN:
        case LSQUARE:
            operators.push({ RPS_OPERATOR, _tokens[i].type, _tokens[i].value });
            break;
        case RPAREN:
            while (!operators.empty() && operators.top().type != LPAREN) {
                output.push_back(
                 { RPS_OPERATOR, operators.top().tokenType, operators.top().value });
                operators.pop();
            }
            if (operators.empty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.pop(); // Удаляем левую скобку
            break;
        case RSQUARE:
            while (!operators.empty() && operators.top().type != LSQUARE) {
                output.push_back(
                 { RPS_OPERATOR, operators.top().tokenType, operators.top().value });
                operators.pop();
            }
            if (operators.empty()) {
                throw std::runtime_error("Mismatched square brackets");
            }
            operators.pop(); // Удаляем левую квадратную скобку
            output.push_back(
             { RPS_INDEX, INTEGER, "INDEX" }); // Добавляем оператор индексации массива
            break;
        case SEMICOLON:
            while (!operators.empty()) {
                output.push_back(operators.top());
                operators.pop();
            }
            break;
        case ARRAY_DECLARE:
            if (i + 3 < _tokens.size() && _tokens[i + 1].type == NAME
                && _tokens[i + 2].type == LSQUARE && _tokens[i + 3].type == INTEGER
                && _tokens[i + 4].type == RSQUARE) {
                auto varName = getStringFromVariant(_tokens[i + 1].value);
                declaredVariables.insert(varName);

                output.push_back({ RPS_STRING, _tokens[i + 1].type, _tokens[i + 1].value });
                output.push_back({ RPS_INTEGER, _tokens[i + 3].type, _tokens[i + 3].value });
                output.push_back({ RPS_ARRAY_DECLARE, ARRAY_DECLARE, "ARRAY_DECLARE" });
                i += 4;
            } else if (_tokens[i + 3].type == NAME) {
                auto varName = getStringFromVariant(_tokens[i + 1].value);
                declaredVariables.insert(varName);

                output.push_back({ RPS_STRING, _tokens[i + 1].type, _tokens[i + 1].value });
                output.push_back({ RPS_STRING, _tokens[i + 3].type, _tokens[i + 3].value });
                output.push_back({ RPS_ARRAY_DECLARE, ARRAY_DECLARE, "ARRAY_DECLARE" });
                i += 4;
            } else {
                throw std::runtime_error("Invalid array declaration syntax");
            }
            break;
        case PRINT:
        case INPUT:
            if (i + 3 < _tokens.size() && _tokens[i + 1].type == LPAREN
                && _tokens[i + 2].type == NAME && _tokens[i + 3].type == RPAREN) {
                std::string varName = getStringFromVariant(_tokens[i + 2].value);
                if (declaredVariables.find(varName) == declaredVariables.end()) {
                    throw std::runtime_error("Use of undeclared variable: " + varName);
                }
                output.push_back({ RPS_STRING, _tokens[i + 2].type, _tokens[i + 2].value });

                RPSElement rpsElement;
                if (_tokens[i].type == PRINT)
                    rpsElement = RPSElement { RPS_PRINT, PRINT, "PRINT" };
                else
                    rpsElement = RPSElement { RPS_INPUT, INPUT, "INPUT" };

                output.push_back(rpsElement);
                i += 3; // Пропускаем следующие 3 токена
            } else {
                throw std::runtime_error("Invalid i/o syntax");
            }
            break;
        case FLOAT_DECLARE:
        case INT_DECLARE:
            if (i + 1 < _tokens.size() && _tokens[i + 1].type == NAME) {
                auto varName = getStringFromVariant(_tokens[i + 1].value);
                declaredVariables.insert(varName);
                //                i += 1; // Пропускаем токен имени
            } else {
                throw std::runtime_error("Invalid variable declaration syntax");
            }
            break;

        default:
            break;
        }
    }

    while (!operators.empty()) {
        if (operators.top().tokenType == LPAREN || operators.top().tokenType == LSQUARE) {
            throw std::runtime_error("Mismatched parentheses");
        }
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}
