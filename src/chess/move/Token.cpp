//
// Created by global on 23/01/2026.
//

#include "Token.h"

#include <stdexcept>

Token::Token(const char v) {
    value = v;
    type = getTokenType(v);
}

TokenType Token::getTokenType(const char v) {
    if (v == 'x') return TokenType::Action;
    if (PIECES.find(v) != std::string_view::npos) return TokenType::Piece;
    if (COLUMNS.find(v) != std::string_view::npos) return TokenType::Column;
    if (ROWS.find(v) != std::string_view::npos) return TokenType::Row;
    if (SPECIALS.find(v) != std::string_view::npos) return TokenType::Special;
    throw std::invalid_argument("Invalid character on move");
}
