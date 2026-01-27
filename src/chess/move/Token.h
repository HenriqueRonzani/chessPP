//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_TOKEN_H
#define CCHESS_TOKEN_H
#include <string>

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

struct Token {
    TokenType type;
    char value;

    static TokenType getTokenType(char v);

    explicit Token(char v);
};


#endif //CCHESS_TOKEN_H