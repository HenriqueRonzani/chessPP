//
// Created by ronzani on 1/18/26.
//

#include "Queen.h"

std::vector<Position> Queen::generateMoves(Position pos, Board &board) {
    const std::vector<Position> diagonalDirections = {{1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    const std::vector<Position> horizontalDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::vector<Position> moves = generateSlidingMoves(pos, board, horizontalDirections);
    std::vector<Position> diagonalMoves = generateSlidingMoves(pos, board, diagonalDirections);

    moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
    return moves;
}
