#include <iostream>
#include <string>
#include <vector>
#include <map>

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
    string value {};
};

class Lexer
{
public:
    Lexer(const string &input) : input(input), position(0)
    {}

    // Lexical analysis
    Token getNextToken()
    {
        while (position < input.length()) {
            char currentChar = input[position];
            if (isdigit(currentChar) || currentChar == '.') {
                return parseNumber();
            } else if (currentChar == '+') {
                position++;
                return Token { PLUS, "+" };
            } else if (currentChar == '-') {
                position++;
                return Token { MINUS, "-" };
            } else if (currentChar == '*') {
                position++;
                return Token { MULTIPLY, "*" };
            } else if (currentChar == '/') {
                position++;
                return Token { DIVIDE, "/" };
            } else if (currentChar == '(') {
                position++;
                return Token { LPAREN, "(" };
            } else if (currentChar == ')') {
                position++;
                return Token { RPAREN, ")" };
            } else if (currentChar == ';') {
                position++;
                return Token { SEMICOLON, ";" };
            } else if (currentChar == ',') {
                position++;
                return Token { COMMA, "," };
            } else if (currentChar == '&') {
                position++;
                return Token { AND, "&" };
            } else if (currentChar == '|') {
                position++;
                return Token { OR, "|" };
            } else if (currentChar == '{') {
                position++;
                return Token { LBRACE, "{" };
            } else if (currentChar == '}') {
                position++;
                return Token { RBRACE, "}" };
            } else if (currentChar == '[') {
                position++;
                return Token { LSQUARE, "[" };
            } else if (currentChar == ']') {
                position++;
                return Token { RSQUARE, "]" };
            } else if (currentChar == '!') {
                if (position + 1 < input.length() && input[position + 1] == '=') {
                    position += 2;
                    return Token { NOT_EQUALS, "!=" };
                } else {
                    position++;
                    return Token { NOT, "!" };
                }
            } else if (currentChar == '<' || currentChar == '>' || currentChar == '=') {
                // Check for relational operators
                if (position + 1 < input.length() && input[position + 1] == '=') {
                    position += 2;
                    if (currentChar == '<') {
                        return Token { LESS_OR_EQUAL, "<=" };
                    } else if (currentChar == '>') {
                        return Token { GREATER_OR_EQUAL, ">=" };
                    } else if (currentChar == '=') {
                        return Token { EQUAL, "==" };
                    }
                } else {
                    position++;
                    if (currentChar == '<') {
                        return Token { LESS, "<" };
                    } else if (currentChar == '>') {
                        return Token { GREATER, ">" };
                    } else if (currentChar == '=') {
                        return Token { ASSIGN, "=" };
                    }
                }
            } else if (isalpha(currentChar)) {
                // Check for keywords
                string word;
                while (position < input.length() && isalnum(input[position])) {
                    word += input[position];
                    position++;
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
                    // Treat as identifier
                    return Token { NAME, word };
                }
            } else if (isspace(currentChar)) {
                skipWhitespace();
                continue;
            }
        }

        // End of input
        return Token { END, "\0" };
    }

    string tokenToString(TokenType token)
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
            return "ARR";
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

private:
    const string input;
    size_t position;

    Token parseNumber()
    {
        string result;
        bool isFloat = false;

        for (; position < input.length(); position++) {
            char currentChar = input[position];

            switch (currentChar) {
            case '.':
                if (isFloat) {
                    position++;
                    cout << result << "\n";
                    return Token { ERROR, result };
                }
                if (position + 1 < input.length() && isdigit(input[position + 1])) {
                    // Если следующий символ - цифра, число считается вещественным
                    isFloat = true;
                    result += currentChar;
                } else {
                    // Если точка не следует за цифрой или после неё нет цифры, это ошибка
                    if (input[position + 1] == ';' || isspace(input[position + 1])) {
                        position++;
                        return Token { ERROR, result };
                    } else {
                        position++;
                        return Token { ERROR, result };
                    }
                }
                break;
            case ';':
                // Если после числа идет точка с запятой, возвращаем INTEGER и SEMICOLON
                if (isFloat) {
                    return Token { FLOAT, result };
                } else {
                    return Token { INTEGER, result };
                }
                break;
            default:
                if (!isdigit(currentChar)) {
                    // Если текущий символ не является цифрой, точкой или точкой с запятой, это
                    // ошибка
                    if (isspace(currentChar)) {
                        break;
                    }
                    position++;
                    return Token { ERROR, result };
                }
                result += currentChar;
                break;
            }
        }

        // Если достигнут конец строки, возвращаем INTEGER
        if (isFloat) {
            return Token { FLOAT, result };
        } else {
            return Token { INTEGER, result };
        }
    }

    void skipWhitespace()
    {
        while (position < input.length() && isspace(input[position])) {
            position++;
        }
    }
};

int main()
{
    string input = "0.154436.";
    Lexer lexer(input);

    vector<Token> tokens;
    Token token = lexer.getNextToken();
    while (token.type != END) {
        tokens.push_back(token);
        token = lexer.getNextToken();
    }

    // Print tokens
    for (const Token &token : tokens) cout << lexer.tokenToString(token.type) << " ";
    cout << endl;

    return 0;
}
