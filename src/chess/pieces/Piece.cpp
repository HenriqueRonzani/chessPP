//
// Created by global on 20/01/2026.
//

#include "Piece.h"

#include <algorithm>

bool Piece::isEnemy(const Piece* piece) const {
    return piece->color != color;
}

bool Piece::isValidMove(const Position from, Position to, Board& board) {
    const std::vector<Position> validMoves = generateMoves(from, board);
    return std::ranges::any_of(validMoves, [&](const auto& move) {
        return move == to;
    });
}

std::vector<Position> Piece::generateMoves(Position pos, Board &board) {
    return {};
}
