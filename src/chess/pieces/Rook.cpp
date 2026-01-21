//
// Created by ronzani on 1/18/26.
//

#include "Rook.h"

std::vector<Position> Rook::generateMoves(const Position pos, Board &board) {
    const std::vector<Position> moveDirections = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    return generateSlidingMoves(pos, board, moveDirections);
}
