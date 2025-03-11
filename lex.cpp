#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Enum class to define the token types
enum class TokenType {
    KONSTANS,
    AZONOSITO,
    OPERATOR,
    EOF_SYMBOL,
    UNKNOWN
};

// Struct for tokens
struct Token {
    TokenType type;
    string value;

    Token(TokenType t, const string& v) : type(t), value(v) {}
};

// Function to determine if a character is an operator
bool isOperator(char c) {
    return c == '>' || c == '<' || c == '=' || c == '*' || c == '{' || c == '}' || c == '(' || c == ')' || c == '$';
}

// Function to tokenize the input string
vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) {
        char current = input[i];

        // Skip whitespace
        if (isspace(current)) {
            i++;
            continue;
        }

        // Recognize numbers (constants)
        if (isdigit(current)) {
            string num;
            while (i < input.size() && isdigit(input[i])) {
                num += input[i++];
            }
            tokens.emplace_back(TokenType::KONSTANS, num);
            continue;
        }

        // Recognize identifiers (alphanumeric sequences starting with a letter)
        if (isalpha(current)) {
            string id;
            while (i < input.size() && (isalnum(input[i]) || input[i] == '_')) {
                id += input[i++];
            }
            tokens.emplace_back(TokenType::AZONOSITO, id);
            continue;
        }

        // Recognize operators
        if (isOperator(current)) {
            string op(1, current);

            // Handle multi-character operators
            if (i + 1 < input.size() && isOperator(input[i + 1])) {
                op += input[++i];
            }
            tokens.emplace_back(TokenType::OPERATOR, op);
            i++;
            continue;
        }

        // Recognize EOF symbol
        if (current == '$') {
            tokens.emplace_back(TokenType::EOF_SYMBOL, "$");
            i++;
            continue;
        }

        // If none of the above, mark as unknown
        tokens.emplace_back(TokenType::UNKNOWN, string(1, current));
        i++;
    }

    return tokens;
}

// Function to get the token type as a string
string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::KONSTANS: return "konstans";
        case TokenType::AZONOSITO: return "azonosito";
        case TokenType::OPERATOR: return "operátor vagy relációsjel";
        case TokenType::EOF_SYMBOL: return "eof";
        default: return "ismeretlen";
    }
}

// Function to print the tokens
void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << getTokenTypeName(token.type) << ": " << token.value << endl;
    }
}

// Main function
int main() {
    string input = "2003ISTRÁB2003>=ÁRVAI{*DÁVID**}<>(**CSABA*)128TAMÁS$";

    cout << "Bemenet: " << input << endl << endl;

    vector<Token> tokens = tokenize(input);

    cout << "Tokenek:" << endl;
    printTokens(tokens);

    return 0
