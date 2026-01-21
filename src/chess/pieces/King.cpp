//
// Created by ronzani on 1/18/26.
//

#include "King.h"

#include <algorithm>

std::vector<Position> King::generateMoves(Position pos, Board &board) {
    const std::vector<Position> diagonalDirections = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    const std::vector<Position> horizontalDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::vector<Position> moves = generateSlidingMoves(pos, board, horizontalDirections, 1);
    std::vector<Position> diagonalMoves = generateSlidingMoves(pos, board, diagonalDirections, 1);

    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
    return moves;
}
