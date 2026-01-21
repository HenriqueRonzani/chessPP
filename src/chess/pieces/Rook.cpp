//
// Created by ronzani on 1/18/26.
//

#include "Rook.h"

#include <algorithm>

bool Rook::isValidMove(const Position from, Position to, Board& board) {
    const std::vector<Position> validMoves = generateMoves(from, board);
    return std::ranges::any_of(validMoves, [&](const auto& move) {
        return move == to;
    });
}

std::vector<Position> Rook::generateMoves(Position pos, Board &board) {
    std::vector<Position> possibleMoves;

    const std::vector<std::vector<int>> moveDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (const std::vector<int>& dir : moveDirections) {
        for (int i = 1; i < 8 - pos.x; i++) {
            const Position move = { pos.x + dir[0] * i, pos.y + dir[1] * i };
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
