//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_TOKEN_H
#define CCHESS_TOKEN_H
#include <string>
#include <vector>

constexpr std::string_view PIECES = "KQRBN";
constexpr std::string_view COLUMNS = "abcdefgh";
constexpr std::string_view ROWS = "12345678";
constexpr std::string_view SPECIALS = "+#";
constexpr std::string_view PROMOTION = "=";

enum class TokenType {
    Piece,
    Column,
    Row,
    Action,
    Promotion,
    Special,
};

class Token {
    static TokenType get_token_type(char v);

public:
    TokenType type;
    char value;
    static std::vector<Token> string_to_token (const std::string_view& s);

    explicit Token(char v);
};


#endif //CCHESS_TOKEN_H