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

std::vector<Position> Piece::generateSlidingMoves(const Position pos, const Board &board, const std::vector<Position>& moveDirections) {
    std::vector<Position> possibleMoves;
    for (const Position& dir : moveDirections) {
        for (int i = 1; i < 8 - pos.x; i++) {
            const Position move = { pos.x + dir.x * i, pos.y + dir.y * i };
            if (!move.isValid()) break;

            const Piece* pieceAtPosition = board.atPosition(move);
            if (pieceAtPosition == nullptr) {
                possibleMoves.push_back(move);
            } else {
                if (pieceAtPosition->isEnemy(this)) {
                    possibleMoves.push_back(move);
                }
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<Position> Piece::generateMoves(Position pos, Board &board) {
    return {};
}
