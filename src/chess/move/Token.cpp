//
// Created by global on 23/01/2026.
//

#include "Token.h"

#include <stdexcept>

Token::Token(const char v) {
    value = v;
    type = get_token_type(v);
}

TokenType Token::get_token_type(const char v) {
    if (v == 'x') return TokenType::Action;
    if (PIECES.find(v) != std::string_view::npos) return TokenType::Piece;
    if (COLUMNS.find(v) != std::string_view::npos) return TokenType::Column;
    if (ROWS.find(v) != std::string_view::npos) return TokenType::Row;
    if (SPECIALS.find(v) != std::string_view::npos) return TokenType::Special;
    if (PROMOTION.find(v) != std::string_view::npos) return TokenType::Promotion;
    throw std::invalid_argument("Invalid character on move");
}

std::vector<Token> Token::string_to_token(const std::string_view& s) {
    std::vector<Token> tokens;
    for (const char character : s) tokens.emplace_back(character);
    return tokens;
}
