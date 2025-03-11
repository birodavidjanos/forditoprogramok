#include <iostream>
#include <regex>
#include <string>
#include <vector>

// Token típusok
enum class TokenType {
    KONSTANS,
    AZONOSITO,
    OPERÁTOR,
    RELÁCIÓS_JEL,
    FAJL_VEGE
};

// Token struktúra
struct Token {
    TokenType type;
    std::string value;
};

// Tokenizáló függvény
std::vector<Token> lexikalalisElemzo(const std::string& bemenet) {
    std::vector<Token> tokenek;
    std::regex tokenRegEx(R"((\d+|[A-ZÁÉÍÓÖŐÚÜŰ]+|[=><!*{}()$]))"); // Regular expression a tokenekhez
    auto words_begin = std::sregex_iterator(bemenet.begin(), bemenet.end(), tokenRegEx);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        std::string token = it->str();

        // Azonosítók és konstansok kezelése
        if (std::isdigit(token[0])) {
            tokenek.push_back({TokenType::KONSTANS, token});
        } else if (token == "{" || token == "}" || token == "*" || token == "**" || token == "(" || token == ")" || token == "<>" || token == "$") {
            tokenek.push_back({TokenType::OPERÁTOR, token});
        } else {
            tokenek.push_back({TokenType::AZONOSITO, token});
        }
    }

    // EOF token hozzáadása
    tokenek.push_back({TokenType::FAJL_VEGE, "$"});

    return tokenek;
}

// Tokenek kiírása
void kiirTokenek(const std::vector<Token>& tokenek) {
    for (const auto& token : tokenek) {
        switch (token.type) {
            case TokenType::KONSTANS:
                std::cout << "konstans: " << token.value << std::endl;
                break;
            case TokenType::AZONOSITO:
                std::cout << "azonosito: " << token.value << std::endl;
                break;
            case TokenType::OPERÁTOR:
                std::cout << "operátor vagy relációsjel: " << token.value << std::endl;
                break;
            case TokenType::FAJL_VEGE:
                std::cout << "eof: " << token.value << std::endl;
                break;
        }
    }
}

int main() {
    std::string bemenet = "2003ISTRÁB2003>=ÁRVAI{*DÁVID**}<>(**CSABA*)128TAMÁS$";
    
    // Tokenizálás
    std::vector<Token> tokenek = lexikalalisElemzo(bemenet);

    // Tokenek kiírása
    kiirTokenek(tokenek);

    return 0;
}
