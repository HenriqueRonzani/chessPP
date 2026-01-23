//
// Created by global on 23/01/2026.
//

#ifndef CCHESS_TOKEN_H
#define CCHESS_TOKEN_H
#include <string>

constexpr std::string_view PIECES = "KQRBN";
constexpr std::string_view COLUMNS = "abcdefgh";
constexpr std::string_view ROWS = "12345678";
constexpr std::string_view SPECIALS = "+#=";

enum class TokenType {
    Piece,
    Column,
    Row,
    Action,
    Special,
};

struct MoveData {

};

class Token {
    TokenType type;
    char value;

    static TokenType getTokenType(const char v);

public:
    explicit Token(const char v);
};


#endif //CCHESS_TOKEN_H