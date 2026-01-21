//
// Created by ronzani on 1/18/26.
//

#include "King.h"

#include <algorithm>

bool King::isValidMove(const Position from, Position to, Board& board) {
    const std::vector<Position> validMoves = generateMoves(from, board);
    return std::ranges::any_of(validMoves, [&](const auto& move) {
        return move == to;
    });
}

std::vector<Position> King::generateMoves(Position pos, Board &board) {
    std::vector<Position> possibleMoves;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            const Position movePosition = {pos.x + i, pos.y + j};

            if (movePosition.isValid()) {
                const Piece* pieceAtPosition = board.atPosition(movePosition);
                if (pieceAtPosition == nullptr || pieceAtPosition->isEnemy(this))
                   possibleMoves.push_back(movePosition);
            }
        }
    }

    return possibleMoves;
}
